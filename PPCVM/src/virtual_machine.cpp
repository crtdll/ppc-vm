#include "virtual_machine.h"
#include "instructions.h"
#include <unordered_map>
#include <functional>

core_machine* get_core() {
	static core_machine instance;
	return &instance;
}

namespace handlers {
	void breakpoint(instruction in, virtual_machine* vm, iteration_reason* out_reason) {
		printf("breaking\n");
		__debugbreak();
	}

	void cmpi(instruction in, virtual_machine* vm, iteration_reason* out_reason) {
		registers* context = vm->get_current_context();
		::cmpi val = { in.value };

		context->cr[val.bits.crfd].reset();
		if (val.bits.l) {
			int64_t ra = (int64_t)context->gpr[val.bits.ra];
			int64_t ds = (int64_t)val.bits.ds;

			context->cr[val.bits.crfd].set(registers::cr_bit::eq, ra == ds);
			context->cr[val.bits.crfd].set(registers::cr_bit::lt, ra < ds);
			context->cr[val.bits.crfd].set(registers::cr_bit::gt, ra > ds);
		} else {
			int32_t ra = (int32_t)context->gpr[val.bits.ra];
			int32_t ds = (int32_t)val.bits.ds;

			context->cr[val.bits.crfd].set(registers::cr_bit::eq, ra == ds);
			context->cr[val.bits.crfd].set(registers::cr_bit::lt, ra < ds);
			context->cr[val.bits.crfd].set(registers::cr_bit::gt, ra > ds);
		}

		context->cr[val.bits.crfd].set(registers::cr_bit::so, context->xer.bits.so);

#ifdef DEBUG
		if (val.bits.l) {
			// cmpdi
			printf("cmpdi cr%i, r%i, 0x%x\n", val.bits.crfd, val.bits.ra, val.bits.ds);
		} else {
			// cmpwi
			printf("cmpwi cr%i, r%d, 0x%x\n", val.bits.crfd, val.bits.ra, val.bits.ds);
		}
#endif
	}

	void li(instruction in, virtual_machine* vm, iteration_reason* out_reason) {
		registers* context = vm->get_current_context();
		::li val = { in.value };

		context->gpr[val.bits.rt] = val.bits.ra == 0 ? val.bits.si : context->gpr[val.bits.ra | 0] + val.bits.si;

#ifdef DEBUG
		if (val.bits.ra == 0) {
			printf("li r%i, 0x%x\n", val.bits.rt, val.bits.si);
		} else {
			printf("addi r%i, r%i, 0x%x\n", val.bits.rt, val.bits.ra | 0, val.bits.si);
		}
#endif
	}

	void lis(instruction in, virtual_machine* vm, iteration_reason* out_reason) {
		registers* context = vm->get_current_context();
		::li val = { in.value };

		context->gpr[val.bits.rt] = val.bits.ra == 0 ? (val.bits.si || 0) : (val.bits.ra | 0) + (val.bits.si || 0);

#ifdef DEBUG
		if (val.bits.ra == 0) {
			printf("lis r%i, 0x%x\n", val.bits.rt, (val.bits.si || 0));
		} else {
			printf("addic r%i, r%i, 0x%x\n", val.bits.rt, val.bits.ra | 0, (val.bits.si || 0));
		}
#endif
	}

	void sc(instruction in, virtual_machine* vm, iteration_reason* out_reason) {
		registers* context = vm->get_current_context();
		::sc val = { in.value };

#ifdef DEBUG
		printf("sc\n");

#endif
		if (val.bits.lev == 2) {
			// the syscall should handle setting return registers
			((void(*)(virtual_machine*))get_core()->get_syscall((int)context->gpr[0]))(vm);
		}
	}

	void lwz(instruction in, virtual_machine* vm, iteration_reason* out_reason) {
		registers* context = vm->get_current_context();
		::lwz val = { in.value };

		context->gpr[val.bits.rt] = _byteswap_ulong(*(uint32_t*)(context->gpr[val.bits.ra] + (short)val.bits.ds));

#ifdef DEBUG
		printf("lwz r%i, %s0x%X(r%i)\n", val.bits.rt, (short)val.bits.ds > 0 ? "" : "-", (short)val.bits.ds > 0 ? (short)val.bits.ds : abs((short)val.bits.ds), val.bits.ra);
#endif
	}

	void stwu(instruction in, virtual_machine* vm, iteration_reason* out_reason) {
		registers* context = vm->get_current_context();
		::stwu val = { in.value };

		if (val.bits.ra == 1) {
			// if it's a stack allocation
			uint64_t current_stack = context->gpr[1];
			context->gpr[1] += (short)val.bits.ds;
			*(uint64_t*)(context->gpr[1]) = current_stack; // back chain
		} else {
			*(uint32_t*)(context->gpr[val.bits.ra] + (short)val.bits.ds) = _byteswap_ulong((uint32_t)context->gpr[val.bits.rt]);
		}

#ifdef DEBUG
		printf("stwu r%i, %s0x%X(r%i)\n", val.bits.rt, (short)val.bits.ds > 0 ? "" : "-", (short)val.bits.ds > 0 ? (short)val.bits.ds : abs((short)val.bits.ds), val.bits.ra);
#endif
	}

	void stw(instruction in, virtual_machine* vm, iteration_reason* out_reason) {
		registers* context = vm->get_current_context();
		::stw val = { in.value };

		*(uint32_t*)(context->gpr[val.bits.ra] + (short)val.bits.ds) = _byteswap_ulong((uint32_t)context->gpr[val.bits.rt]);
#ifdef DEBUG
		printf("stw r%i, %s0x%X(r%i)\n", val.bits.rt, (short)val.bits.ds > 0 ? "" : "-", (short)val.bits.ds > 0 ? (short)val.bits.ds : abs((short)val.bits.ds), val.bits.ra);
#endif
	}

	void stb(instruction in, virtual_machine* vm, iteration_reason* out_reason) {
		registers* context = vm->get_current_context();
		::stb val = { in.value };

		*(uint8_t*)(context->gpr[val.bits.ra] + (short)val.bits.ds) = (uint8_t)context->gpr[val.bits.rt];
#ifdef DEBUG
		printf("stb r%i, %s0x%X(r%i)\n", val.bits.rt, (short)val.bits.ds > 0 ? "" : "-", (short)val.bits.ds > 0 ? (short)val.bits.ds : abs((short)val.bits.ds), val.bits.ra);
#endif
	}

	void b(instruction in, virtual_machine* vm, iteration_reason* out_reason) {
		registers* context = vm->get_current_context();
		bx val = { in.value };

		if (val.bits.lk) {
			context->lr = context->iar + 1;
		}

		uint32_t offset = val.bits.li - 1;
		if (val.bits.aa == 0) {
			context->iar += offset;
		} else {
			context->iar = offset;
		}

#ifdef DEBUG
		if (val.bits.aa == 0 && val.bits.lk == 0) {
			// b
			printf("b 0x%X\n", val.bits.li * 4);
		} else if (val.bits.aa == 1 && val.bits.lk == 0) {
			// ba
			printf("ba 0x%X\n", val.bits.li * 4);
		} else if (val.bits.aa == 0 && val.bits.lk == 1) {
			// bl
			printf("bl 0x%X\n", val.bits.li * 4);
		} else if (val.bits.aa == 1 && val.bits.lk == 1) {
			// bla
			printf("bla 0x%X\n", val.bits.li * 4);
		}
#endif
	}

	void bc(instruction in, virtual_machine* vm, iteration_reason* out_reason) {
		registers* context = vm->get_current_context();
		bcx val = { in.value };

		uint32_t cr_field = val.bits.bi >> 2;
		uint32_t cr_field_bit = val.bits.bi & 3;
		uint32_t branch_offset = val.bits.bd << 2;

		bool decrement_ctr = false;
		if (!(val.bits.bo & 0b00100)) {
			context->ctr = context->ctr - 1;
			decrement_ctr = true;
		}

		bool should_branch = false;
		if (val.bits.bo & 0b10000) {
			if (decrement_ctr) {
				should_branch = true;
			} else if (val.bits.bo & 0b00010) {
				should_branch = context->ctr == 0;
#ifdef DEBUG
				printf("bdz cr%d, %s0x%x\n", cr_field, (int16_t)branch_offset > 0 ? "" : "-", (int16_t)branch_offset > 0 ? (int16_t)branch_offset : abs((int16_t)branch_offset));
#endif
			} else {
				should_branch = context->ctr != 0;
#ifdef DEBUG
				printf("bdnz cr%d, %s0x%x\n", cr_field, (int16_t)branch_offset > 0 ? "" : "-", (int16_t)branch_offset > 0 ? (int16_t)branch_offset : abs((int16_t)branch_offset));
#endif
			}
		} else {
			if (val.bits.bo & 0b01000) {
				should_branch = context->cr[cr_field].test(cr_field_bit);
#ifdef DEBUG
				switch (cr_field_bit) {
					case registers::cr_bit::lt: {
						printf("blt cr%d, %s0x%x\n", cr_field, (int16_t)branch_offset > 0 ? "" : "-", (int16_t)branch_offset > 0 ? (int16_t)branch_offset : abs((int16_t)branch_offset));
						break;
					}

					case registers::cr_bit::gt: {
						printf("bgt cr%d, %s0x%x\n", cr_field, (int16_t)branch_offset > 0 ? "" : "-", (int16_t)branch_offset > 0 ? (int16_t)branch_offset : abs((int16_t)branch_offset));
						break;
					}

					case registers::cr_bit::eq: {
						printf("beq cr%d, %s0x%x\n", cr_field, (int16_t)branch_offset > 0 ? "" : "-", (int16_t)branch_offset > 0 ? (int16_t)branch_offset : abs((int16_t)branch_offset));
						break;
					}
				}
#endif
			} else {
				should_branch = !context->cr[cr_field].test(cr_field_bit);
#ifdef DEBUG
				switch (cr_field_bit) {
					case registers::cr_bit::lt: {
						printf("bge cr%d, %s0x%x\n", cr_field, (int16_t)branch_offset > 0 ? "" : "-", (int16_t)branch_offset > 0 ? (int16_t)branch_offset : abs((int16_t)branch_offset));
						break;
					}

					case registers::cr_bit::gt: {
						printf("ble cr%d, %s0x%x\n", cr_field, (int16_t)branch_offset > 0 ? "" : "-", (int16_t)branch_offset > 0 ? (int16_t)branch_offset : abs((int16_t)branch_offset));
						break;
					}

					case registers::cr_bit::eq: {
						printf("bne cr%d, %s0x%x\n", cr_field, (int16_t)branch_offset > 0 ? "" : "-", (int16_t)branch_offset > 0 ? (int16_t)branch_offset : abs((int16_t)branch_offset));
						break;
					}
				}
#endif
			}
		}

		if (should_branch) {
			if (val.bits.lk) {
				context->lr = context->iar + 1;
			}

			int32_t offset = (int32_t)((int16_t)(branch_offset) / sizeof(int32_t));
			context->iar = val.bits.aa ? (uint32_t)(offset) : (uint32_t)(context->iar + offset);
		}
	}

	void cmpli(instruction in, virtual_machine* vm, iteration_reason* out_reason) {
		registers* context = vm->get_current_context();
		::cmpli val = { in.value };

		context->cr[val.bits.crfd].reset();
		if (val.bits.l) {
			uint64_t ra = (uint64_t)context->gpr[val.bits.ra];
			uint64_t ds = (uint64_t)val.bits.ds;

			context->cr[val.bits.crfd].set(registers::cr_bit::eq, ra == ds);
			context->cr[val.bits.crfd].set(registers::cr_bit::lt, ra < ds);
			context->cr[val.bits.crfd].set(registers::cr_bit::gt, ra > ds);
		} else {
			uint32_t ra = (uint32_t)context->gpr[val.bits.ra];
			uint32_t ds = (uint32_t)val.bits.ds;

			context->cr[val.bits.crfd].set(registers::cr_bit::eq, ra == ds);
			context->cr[val.bits.crfd].set(registers::cr_bit::lt, ra < ds);
			context->cr[val.bits.crfd].set(registers::cr_bit::gt, ra > ds);
		}

		context->cr[val.bits.crfd].set(registers::cr_bit::so, context->xer.bits.so);

#ifdef DEBUG
		if (val.bits.l) {
			// cmpldi
			printf("cmpldi cr%i, r%i, 0x%x\n", val.bits.crfd, val.bits.ra, val.bits.ds);
		} else {
			// cmplwi
			printf("cmplwi cr%i, r%i, 0x%x\n", val.bits.crfd, val.bits.ra, val.bits.ds);
		}
#endif
	}

	void cmp(instruction in, virtual_machine* vm, iteration_reason* out_reason) {
		registers* context = vm->get_current_context();
		::cmp val = { in.value };

		context->cr[val.bits.crfd].reset();
		if (val.bits.l) {
			int64_t ra = (int64_t)context->gpr[val.bits.ra];
			int64_t rb = (int64_t)context->gpr[val.bits.rb];

			context->cr[val.bits.crfd].set(registers::cr_bit::eq, ra == rb);
			context->cr[val.bits.crfd].set(registers::cr_bit::lt, ra < rb);
			context->cr[val.bits.crfd].set(registers::cr_bit::gt, ra > rb);
		} else {
			int32_t ra = (int32_t)context->gpr[val.bits.ra];
			int32_t rb = (int32_t)context->gpr[val.bits.rb];

			context->cr[val.bits.crfd].set(registers::cr_bit::eq, ra == rb);
			context->cr[val.bits.crfd].set(registers::cr_bit::lt, ra < rb);
			context->cr[val.bits.crfd].set(registers::cr_bit::gt, ra > rb);
		}

		context->cr[val.bits.crfd].set(registers::cr_bit::so, context->xer.bits.so);

#ifdef DEBUG
		if (val.bits.l) {
			// cmpd
			printf("cmpd cr%i, r%i, r%i\n", val.bits.crfd, val.bits.ra, val.bits.rb);
		} else {
			// cmpw
			printf("cmpw cr%i, r%i, r%i\n", val.bits.crfd, val.bits.ra, val.bits.rb);
		}
#endif
	}

	void cmpl(instruction in, virtual_machine* vm, iteration_reason* out_reason) {
		registers* context = vm->get_current_context();
		::cmpl val = { in.value };

		context->cr[val.bits.crfd].reset();

		if (val.bits.l) {
			uint64_t ra = (uint64_t)context->gpr[val.bits.ra];
			uint64_t rb = (uint64_t)context->gpr[val.bits.rb];

			context->cr[val.bits.crfd].set(registers::cr_bit::eq, ra == rb);
			context->cr[val.bits.crfd].set(registers::cr_bit::lt, ra < rb);
			context->cr[val.bits.crfd].set(registers::cr_bit::gt, ra > rb);
		} else {
			uint32_t ra = (uint32_t)context->gpr[val.bits.ra];
			uint32_t rb = (uint32_t)context->gpr[val.bits.rb];

			context->cr[val.bits.crfd].set(registers::cr_bit::eq, ra == rb);
			context->cr[val.bits.crfd].set(registers::cr_bit::lt, ra < rb);
			context->cr[val.bits.crfd].set(registers::cr_bit::gt, ra > rb);
		}

		context->cr[val.bits.crfd].set(registers::cr_bit::so, context->xer.bits.so);

#ifdef DEBUG
		if (val.bits.l) {
			// cmpld
			printf("cmpld cr%i, r%i, r%i\n", val.bits.crfd, val.bits.ra, val.bits.rb);
		} else {
			// cmplw
			printf("cmplw cr%i, r%i, r%i\n", val.bits.crfd, val.bits.ra, val.bits.rb);
		}
#endif
	}

	void _or(instruction in, virtual_machine* vm, iteration_reason* out_reason) {
		registers* context = vm->get_current_context();
		::_or val = { in.value };

		context->gpr[val.bits.ra] = (0 || val.bits.ui) == 1 ? context->gpr[val.bits.rs] : context->gpr[val.bits.rs] | (0 || val.bits.ui);

#ifdef DEBUG
		if ((0 || val.bits.ui) == 1) {
			printf("mr r%i, r%i\n", val.bits.ra, val.bits.rs);
		}
#endif
	}

	void add(instruction in, virtual_machine* vm, iteration_reason* out_reason) {
		registers* context = vm->get_current_context();
		addx val = { in.value };

		uint64_t ra = (uint64_t)context->gpr[val.bits.ra];
		uint64_t rb = (uint64_t)context->gpr[val.bits.rb];

		context->gpr[val.bits.rt] = ra + rb;

		uint64_t rt = context->gpr[val.bits.rt];

		if (val.bits.oe) {
			if ((ra ^ ~rb) & (ra ^ rt) & 0x80000000) {
				context->xer.bits.so = 1;
				context->xer.bits.ov = 1;
			} else {
				context->xer.bits.ov = 0;
			}
		}

		if (val.bits.rc) {
			context->cr[0].reset();
			if (context->gpr[val.bits.rt] == 0) {
				context->cr[0].set(registers::cr_bit::eq, true);
			} else if (context->gpr[val.bits.rt] & 0x80000000) {
				context->cr[0].set(registers::cr_bit::lt, true);
			} else {
				context->cr[0].set(registers::cr_bit::gt, true);
			}

			context->cr[0].set(registers::cr_bit::so, context->xer.bits.so);
		}

#ifdef DEBUG
		if (val.bits.oe == 0 && val.bits.rc == 0) {
			// add
			printf("add r%i, r%i, r%i\n", val.bits.rt, val.bits.ra, val.bits.rb);
		} else if (val.bits.oe == 0 && val.bits.rc == 1) {
			// add.
			printf("add. r%i, r%i, r%i\n", val.bits.rt, val.bits.ra, val.bits.rb);
		} else if (val.bits.oe == 1 && val.bits.rc == 0) {
			// addo
			printf("addo r%i, r%i, r%i\n", val.bits.rt, val.bits.ra, val.bits.rb);
		} else if (val.bits.oe == 1 && val.bits.rc == 1) {
			// addo.
			printf("addo. r%i, r%i, r%i\n", val.bits.rt, val.bits.ra, val.bits.rb);
		}
#endif
	}

	void mfspr(instruction in, virtual_machine* vm, iteration_reason* out_reason) {
		registers* context = vm->get_current_context();
		::mfspr val = { in.value };

		switch (((val.bits.spr >> 5) & 0x1F) | (val.bits.spr & 0x1F)) {
			case 1: { // xer
				context->gpr[val.bits.rt] = (uint64_t)context->xer.value;

#ifdef DEBUG
				printf("mfxer r%i\n", val.bits.rt);
#endif
				break;
			}

			case 8: { // lr
				context->gpr[val.bits.rt] = context->lr;

#ifdef DEBUG
				printf("mflr r%i\n", val.bits.rt);
#endif
				break;
			}

			case 9: { // ctr
				context->gpr[val.bits.rt] = context->ctr;

#ifdef DEBUG
				printf("mfctr r%i\n", val.bits.rt);
#endif
				break;
			}
		}
	}

	void mtspr(instruction in, virtual_machine* vm, iteration_reason* out_reason) {
		registers* context = vm->get_current_context();
		::mtspr val = { in.value };

		switch (((val.bits.spr >> 5) & 0x1F) | (val.bits.spr & 0x1F)) {
			case 1: { // xer
				context->xer.value = (uint32_t)context->gpr[val.bits.rt];

#ifdef DEBUG
				printf("mtxer r%i\n", val.bits.rt);
#endif
				break;
			}

			case 8: { // lr
				context->lr = context->gpr[val.bits.rt];
#ifdef DEBUG
				printf("mtlr r%i\n", val.bits.rt);
#endif
				break;
			}

			case 9: { // ctr
				context->ctr = context->gpr[val.bits.rt];
#ifdef DEBUG
				printf("mtctr r%i\n", val.bits.rt);
#endif
				break;
			}
		}
	}

	void bundle_31(instruction in, virtual_machine* vm, iteration_reason* out_reason) {
		::bundle_31 val = { in.value };

		switch (val.bits._) {
			case eop_cmp: return cmp(in, vm, out_reason);
			case eop_cmpl: return cmpl(in, vm, out_reason);
			case eop_or: return _or(in, vm, out_reason);
			case eop_add: return add(in, vm, out_reason);
			case eop_mfspr: return mfspr(in, vm, out_reason);
			case eop_mtspr: return mtspr(in, vm, out_reason);
		}
	}

	void bclr(instruction in, virtual_machine* vm, iteration_reason* out_reason) {
		registers* context = vm->get_current_context();
		::bundle_19 val = { in.value };

		if (val.bits.bo & 0b10100) {
#ifdef DEBUG
			printf("blr\n");
#endif

			if (context->lr == 0) {
				*out_reason = it_return;
				return;
			}

			context->iar = context->lr;
			*out_reason = it_continue;
			return;
		}
	}

	void bundle_19(instruction in, virtual_machine* vm, iteration_reason* out_reason) {
		::bundle_19 val = { in.value };
		switch (val.bits._) {
			case eop_bclr: return bclr(in, vm, out_reason);
		}
	}
}

std::unordered_map<uint32_t, std::function<void(instruction, virtual_machine*, iteration_reason*)>> table = {
	{ 63, handlers::breakpoint },
	{ op_cmpi, handlers::cmpi },
	{ op_li, handlers::li },
	{ op_lis, handlers::lis },
	{ op_sc, handlers::sc },
	{ op_lwz, handlers::lwz },
	{ op_stwu, handlers::stwu },
	{ op_stw, handlers::stw },
	{ op_stb, handlers::stb },
	{ op_b, handlers::b },
	{ op_bc, handlers::bc },
	{ op_cmpli, handlers::cmpli },
	{ op_bundle_31, handlers::bundle_31 },
	{ op_bundle_19, handlers::bundle_19 },
};

void virtual_machine::execute(uint8_t* payload) {
	printf("\n======== EXECUTING PAYLOAD 0x%p ========\n", payload);

	set_payload(payload);
	memset(get_stack(), 0, STACK);

	get_current_context()->gpr[1] = (uint64_t)&get_stack()[STACK];

	CreateThread(0, 0, [](LPVOID param) -> DWORD {
		virtual_machine* _this = (virtual_machine*)param;

		while (true) {
			uint8_t* payload = _this->get_payload();
			instruction in = { _byteswap_ulong(*(uint32_t*)(&payload[_this->get_current_context()->iar * sizeof(uint32_t)])) };
			if (table[in.bits.opcode]) {
				iteration_reason reason = it_ok;
				table[in.bits.opcode](in, _this, &reason);

				if (reason == it_continue) continue;
				if (reason == it_return) return 0;
			} else return 0;

			_this->get_current_context()->iar++;
		};

		delete _this;
		return 0;
	}, this, 0, 0);
}

void core_machine::add_syscall(void(*function)(virtual_machine*), int id) {
	if (id < MAX_SYSCALLS) {
		syscall_table[id] = function;
	}
}

void virtual_machine::print_registers() {
	for (int i = 0; i < 32; i++) {
		printf("r%i=0x%016I64X ", i, get_current_context()->gpr[i]);

		if ((i + 1) % 4 == 0) {
			printf("\n");
		}
	}

	printf("msr=0x%016I64X iar=0x%016I64X lr=0x%016I64X ctr=0x%016I64X\n", get_current_context()->msr, get_current_context()->iar, get_current_context()->lr, get_current_context()->ctr);
	printf("cr0=0x%X cr1=0x%X cr2=0x%X cr3=0x%X\n", get_current_context()->cr[0].to_ulong(), get_current_context()->cr[1].to_ulong(), get_current_context()->cr[2].to_ulong(), get_current_context()->cr[3].to_ulong());
	printf("cr4=0x%X cr5=0x%X cr6=0x%X cr7=0x%X\n", get_current_context()->cr[4].to_ulong(), get_current_context()->cr[5].to_ulong(), get_current_context()->cr[6].to_ulong(), get_current_context()->cr[7].to_ulong());
}

virtual_machine* core_machine::create_vm(uint32_t thread_id) {
	if (context.find(thread_id) == end(context)) {
		virtual_machine* vm = new virtual_machine();
		if (vm) {
			context[thread_id] = registers();
			vm->set_thread_id(thread_id);
		}

		return vm;
	}

	return nullptr;
}