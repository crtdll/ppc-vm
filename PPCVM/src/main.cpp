#include "stdafx.h"
#include <cassert>

#define MAX_SYSCALLS 0xFF
#define RAM 0xFFFF
#define STACK 0xFFFF

struct registers {
	uint64_t msr; // machine status register
	uint64_t iar; // instruction address register
	uint64_t lr;  // link register
	uint64_t ctr; // count register

	uint64_t gpr[32]; // general registers 0 to 31
	
	// condition register
	union {
		uint32_t value;

		struct {
			unsigned int cr0 : 4;
			unsigned int cr1 : 4;
			unsigned int cr2 : 4;
			unsigned int cr3 : 4;
			unsigned int cr4 : 4;
			unsigned int cr5 : 4;
			unsigned int cr6 : 4;
			unsigned int cr7 : 4;
		};
	} cr;

	double fpscr;	// floating point status/control register
	double fpr[32]; // floating point registers 0 to 31

	registers() {
		memset(this, 0, sizeof(registers));
	}
};

#pragma region instructions
union instruction {
	int value;

	struct {
		unsigned int data : 26;
		unsigned int opcode : 5;
	} bits;
};

union li {
	int value;

	struct {
		unsigned int si : 16;
		unsigned int ra : 5;
		unsigned int rt : 5;
		unsigned int opcode : 5;
	} bits;
};

union sc {
	int value;

	struct {
		unsigned int lev : 26;
		unsigned int opcode : 5;
	} bits;
};

union bundle_31 {
	int value;

	struct {
		unsigned int rc : 1;
		unsigned int _ : 9;
		unsigned int oe : 1;
		unsigned int rb : 5;
		unsigned int ra : 5;
		unsigned int rt : 5;
		unsigned int opcode : 5;
	} bits;
};

union _or {
	int value;

	struct {
		unsigned int ui : 16;
		unsigned int ra : 5;
		unsigned int rs : 5;
		unsigned int opcode : 5;
	} bits;
};

enum opcode {
	op_li = 14, // same as addi?
	op_lis = 15,
	op_sc = 17,
	op_bundle_31 = 31
};

enum extended_opcode {
	eop_or = 444,
};

#pragma endregion

class virtual_machine {
public:
	void execute(uint8_t* payload, uint32_t size) {
		execution = payload;

		for (uint32_t i = 0; i < size; i++) {
			context.iar = (uint64_t)&payload[(i * sizeof(uint32_t))];

			instruction in = { _byteswap_ulong(*(uint32_t*)(context.iar)) };
			switch (in.bits.opcode) {
				case op_li: { // addi
					li val = { in.value };
					context.gpr[val.bits.rt] = val.bits.ra == 0 ? val.bits.si : context.gpr[val.bits.ra | 0] + val.bits.si;
					break;
				}

				case op_lis: { // addic
					li val = { in.value };
					context.gpr[val.bits.rt] = val.bits.ra == 0 ? (val.bits.si || 0) : (val.bits.ra | 0) + (val.bits.si || 0);
					break;
				}

				case op_sc: {
					sc val = { in.value };
					if (val.bits.lev == 2) {
						// the syscall should handle setting return registers
						((void(*)(virtual_machine*))syscall_table[(int)context.gpr[0]])(this);
					}

					break;
				}

				case op_bundle_31: {
					bundle_31 val = { in.value };
					switch (val.bits._) {
						case eop_or: { // mr
							_or val_2 = { in.value };
							context.gpr[val_2.bits.ra] = context.gpr[val_2.bits.rs] | (0 || val_2.bits.ui);
							break;
						}
					}

					break;
				}
			}
		}
	}

	void add_syscall(void(*function)(virtual_machine*), int id) {
		if (id < MAX_SYSCALLS) {
			syscall_table[id] = function;
		}
	}

	void print_registers() {
		for (int i = 0; i < 32; i++) {
			printf("r%i=0x%016I64X ", i, context.gpr[i]);

			if ((i + 1) % 4 == 0) {
				printf("\n");
			}
		}

		printf("msr=0x%016I64X iar=0x%016I64X lr=0x%016I64X ctr=0x%016I64X\n", context.msr, context.iar, context.lr, context.ctr);
		printf("cr0=0x%X cr1=0x%X cr2=0x%X cr3=0x%X\n", context.cr.cr0, context.cr.cr1, context.cr.cr2, context.cr.cr3);
		printf("cr4=0x%X cr5=0x%X cr6=0x%X cr7=0x%X\n", context.cr.cr4, context.cr.cr5, context.cr.cr6, context.cr.cr7);
	}

	uint8_t* get_ram() { return ram; }
	uint8_t* get_execution() { return execution; }
	registers* get_context() { return &context; }
private:
	// registers for the thread
	registers context;

	// syscall table
	void* syscall_table[MAX_SYSCALLS];

	// ram
	uint8_t ram[RAM];

	// stack
	uint8_t stack[STACK];
	int stack_offset = 0;

	// currently executing payload
	uint8_t* execution;
};

void setup_syscalls(virtual_machine* vm) {
	vm->add_syscall([](virtual_machine* vm) {
		// for now, only supports formatters
		printf((const char*)(vm->get_execution() + vm->get_context()->gpr[3]));
		vm->get_context()->gpr[3] = 0x1234;
	}, 0); 
}

int main() {
	uint8_t payload[] = {
		0x38, 0x80, 0x00, 0x59,		// li %r4, 0x59
		0x38, 0x84, 0x00, 0x10,		// addi %r4, %r4, 0x10
		0x38, 0x60, 0x00, 0x18,		// li %r3, 0x18					->>> offset from payload base to string
		0x38, 0x00, 0x00, 0x00,		// li %r0, 0					->>> "printf" syscall
		0x44, 0x00, 0x00, 0x02,		// sc
		0x4E, 0x80, 0x00, 0x20,		// blr
		
		// data has to be in little endian
		0x68, 0x65, 0x79, 0x20,		// "hey "
		0x66, 0x72, 0x6F, 0x6D,		// "from"
		0x20, 0x50, 0x50, 0x43,		// " PPC"
		0x0A, 0x00, 0x00, 0x00		// "\n" + null terminator
	};

	virtual_machine vm;
	setup_syscalls(&vm);

	vm.execute(payload, sizeof(payload) / sizeof(uint32_t));
	vm.print_registers();

	system("pause");
	return 0;
}