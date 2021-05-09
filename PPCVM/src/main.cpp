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

union addcx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 9;
        uint32_t oe : 1;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union addex {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 9;
        uint32_t oe : 1;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union addi {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union addic {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union addicx {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union addis {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union addmex {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 9;
        uint32_t oe : 1;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union addx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 9;
        uint32_t oe : 1;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union addzex {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 9;
        uint32_t oe : 1;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union andcx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union andisx {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union andix {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union andx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union bcctrx {
    uint32_t value;

    struct {
        uint32_t lk : 1;
        uint32_t _ : 10;
        uint32_t bb : 5;
        uint32_t bi : 5;
        uint32_t bo : 5;
        uint32_t opcode : 5;
    } bits;

};
union bclrx {
    uint32_t value;

    struct {
        uint32_t lk : 1;
        uint32_t _ : 10;
        uint32_t bb : 5;
        uint32_t bi : 5;
        uint32_t bo : 5;
        uint32_t opcode : 5;
    } bits;

};
union bcx {
    uint32_t value;

    struct {
        uint32_t lk : 1;
        uint32_t aa : 1;
        uint32_t bd : 14;
        uint32_t bi : 5;
        uint32_t bo : 5;
        uint32_t opcode : 6;
    } bits;

};
union bx {
    uint32_t value;

    struct {
        uint32_t lk : 1;
        uint32_t aa : 1;
        uint32_t li : 24;
        uint32_t opcode : 6;
    } bits;

};
union cmp {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union cmpi {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union cmpl {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union cmpli {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union cntlzdx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union cntlzwx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union crand {
    uint32_t value;

    struct {
        uint32_t lk : 1;
        uint32_t _ : 10;
        uint32_t bb : 5;
        uint32_t bi : 5;
        uint32_t bo : 5;
        uint32_t opcode : 5;
    } bits;

};
union crandc {
    uint32_t value;

    struct {
        uint32_t lk : 1;
        uint32_t _ : 10;
        uint32_t bb : 5;
        uint32_t bi : 5;
        uint32_t bo : 5;
        uint32_t opcode : 5;
    } bits;

};
union creqv {
    uint32_t value;

    struct {
        uint32_t lk : 1;
        uint32_t _ : 10;
        uint32_t bb : 5;
        uint32_t bi : 5;
        uint32_t bo : 5;
        uint32_t opcode : 5;
    } bits;

};
union crnand {
    uint32_t value;

    struct {
        uint32_t lk : 1;
        uint32_t _ : 10;
        uint32_t bb : 5;
        uint32_t bi : 5;
        uint32_t bo : 5;
        uint32_t opcode : 5;
    } bits;

};
union crnor {
    uint32_t value;

    struct {
        uint32_t lk : 1;
        uint32_t _ : 10;
        uint32_t bb : 5;
        uint32_t bi : 5;
        uint32_t bo : 5;
        uint32_t opcode : 5;
    } bits;

};
union cror {
    uint32_t value;

    struct {
        uint32_t lk : 1;
        uint32_t _ : 10;
        uint32_t bb : 5;
        uint32_t bi : 5;
        uint32_t bo : 5;
        uint32_t opcode : 5;
    } bits;

};
union crorc {
    uint32_t value;

    struct {
        uint32_t lk : 1;
        uint32_t _ : 10;
        uint32_t bb : 5;
        uint32_t bi : 5;
        uint32_t bo : 5;
        uint32_t opcode : 5;
    } bits;

};
union crxor {
    uint32_t value;

    struct {
        uint32_t lk : 1;
        uint32_t _ : 10;
        uint32_t bb : 5;
        uint32_t bi : 5;
        uint32_t bo : 5;
        uint32_t opcode : 5;
    } bits;

};
union dcbf {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union dcbi {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union dcbst {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union dcbt {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union dcbtst {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union divdux {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 9;
        uint32_t oe : 1;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union divdx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 9;
        uint32_t oe : 1;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union divwux {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 9;
        uint32_t oe : 1;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union divwx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 9;
        uint32_t oe : 1;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union eieio {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union eqvx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union extsbx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union extshx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union extswx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union fabsx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union fcfidx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union fcmpo {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union fcmpu {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union fctidx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union fctidzx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union fctiwx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union fctiwzx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union fmrx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union fnabsx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union fnegx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union frspx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union icbi {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union isync {
    uint32_t value;

    struct {
        uint32_t lk : 1;
        uint32_t _ : 10;
        uint32_t bb : 5;
        uint32_t bi : 5;
        uint32_t bo : 5;
        uint32_t opcode : 5;
    } bits;

};
union lbz {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union lbzu {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union lbzux {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union lbzx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union ldarx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union ldbrx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union ldux {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union ldx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union lfd {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union lfdu {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union lfdux {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union lfdx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union lfs {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union lfsu {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union lfsux {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union lfsx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union lha {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union lhau {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union lhaux {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union lhax {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union lhbrx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union lhz {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union lhzu {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union lhzux {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union lhzx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union lmw {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union lswi {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union lswx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union lwarx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union lwaux {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union lwax {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union lwbrx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union lwz {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union lwzu {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union lwzux {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union lwzx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union mcrf {
    uint32_t value;

    struct {
        uint32_t lk : 1;
        uint32_t _ : 10;
        uint32_t bb : 5;
        uint32_t bi : 5;
        uint32_t bo : 5;
        uint32_t opcode : 5;
    } bits;

};
union mcrfs {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union mcrxr {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union mfcr {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union mffsx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union mfmsr {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union mfspr {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t spr : 10;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union mftb {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t spr : 10;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union mtcrf {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t spr : 10;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union mtfsb0x {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union mtfsb1x {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union mtfsfix {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union mtfsfx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t w : 1;
        uint32_t fm : 8;
        uint32_t l : 1;
        uint32_t opcode : 5;
    } bits;

};
union mtmsr {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union mtmsrd {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union mtspr {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t spr : 10;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union mulhdux {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 9;
        uint32_t oe : 1;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union mulhdx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 9;
        uint32_t oe : 1;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union mulhwux {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 9;
        uint32_t oe : 1;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union mulhwx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 9;
        uint32_t oe : 1;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union mulldx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 9;
        uint32_t oe : 1;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union mulli {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union mullwx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 9;
        uint32_t oe : 1;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union nandx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union negx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 9;
        uint32_t oe : 1;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union norx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union orcx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union ori {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union oris {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union orx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union rldclx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t idx : 4;
        uint32_t mb5 : 1;
        uint32_t mb : 5;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union rldcrx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t idx : 4;
        uint32_t mb5 : 1;
        uint32_t mb : 5;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union rldiclx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t sh5 : 1;
        uint32_t idx : 3;
        uint32_t mb5 : 1;
        uint32_t mb : 5;
        uint32_t sh : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union rldicrx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t sh5 : 1;
        uint32_t idx : 3;
        uint32_t mb5 : 1;
        uint32_t mb : 5;
        uint32_t sh : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union rldicx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t sh5 : 1;
        uint32_t idx : 3;
        uint32_t mb5 : 1;
        uint32_t mb : 5;
        uint32_t sh : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union rldimix {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t sh5 : 1;
        uint32_t idx : 3;
        uint32_t mb5 : 1;
        uint32_t mb : 5;
        uint32_t sh : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union rlwimix {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t me : 5;
        uint32_t mb : 5;
        uint32_t sh : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union rlwinmx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t me : 5;
        uint32_t mb : 5;
        uint32_t sh : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union rlwnmx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t me : 5;
        uint32_t mb : 5;
        uint32_t sh : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union sc {
    uint32_t value;

    struct {
        uint32_t lev : 26;
        uint32_t opcode : 5;
    } bits;

};
union sldx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union slwx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union sradix {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t sh5 : 1;
        uint32_t _ : 9;
        uint32_t sh : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union sradx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union srawix {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union srawx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union srdx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union srwx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union stb {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union stbu {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union stbux {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union stbx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union stdbrx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union stdcx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union stdux {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union stdx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union stfd {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union stfdu {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union stfdux {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union stfdx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union stfiwx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union stfs {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union stfsu {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union stfsux {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union stfsx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union sth {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union sthbrx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union sthu {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union sthux {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union sthx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union stmw {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union stswi {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union stswx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union stw {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union stwbrx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union stwcx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union stwu {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union stwux {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union stwx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union subfcx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 9;
        uint32_t oe : 1;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union subfex {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 9;
        uint32_t oe : 1;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union subficx {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union subfmex {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 9;
        uint32_t oe : 1;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union subfx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 9;
        uint32_t oe : 1;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union subfzex {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 9;
        uint32_t oe : 1;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union sync {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union td {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union tdi {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union tw {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union twi {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union xori {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union xoris {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
    } bits;

};
union xorx {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 5;
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