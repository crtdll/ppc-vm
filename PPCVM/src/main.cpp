#include "stdafx.h"
#include <cassert>

#define MAX_SYSCALLS 0xFF
#define RAM 0xFFFF
#define STACK 0xFFFF
#define DEBUG

struct registers {
	uint32_t xer; // xer register
	uint64_t msr; // machine status register
	uint64_t iar; // instruction address register
	uint64_t lr;  // link register
	uint64_t ctr; // count register

	uint64_t gpr[32]; // general registers 0 to 31
	
	// condition register
	union {
		uint32_t value;

		struct {
			uint32_t cr0 : 4;
			uint32_t cr1 : 4;
			uint32_t cr2 : 4;
			uint32_t cr3 : 4;
			uint32_t cr4 : 4;
			uint32_t cr5 : 4;
			uint32_t cr6 : 4;
			uint32_t cr7 : 4;
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
	uint32_t value;

	struct {
        uint32_t data : 26;
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
    } bits;

};
union addi {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
    } bits;

};
union addic {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
    } bits;

};
union addicx {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
    } bits;

};
union addis {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
    } bits;

};
union andisx {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
    } bits;

};
union andix {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
    } bits;

};
union cmpi {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
    } bits;

};
union cmpli {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
    } bits;

};
union lbz {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
    } bits;

};
union lbzu {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
    } bits;

};
union lfd {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
    } bits;

};
union lfdu {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
    } bits;

};
union lfs {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
    } bits;

};
union lfsu {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
    } bits;

};
union lha {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
    } bits;

};
union lhau {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
    } bits;

};
union lhz {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
    } bits;

};
union lhzu {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
    } bits;

};
union lmw {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
    } bits;

};
union lwz {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
    } bits;

};
union lwzu {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
    } bits;

};
union mfspr {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t spr : 10;
        uint32_t rt : 5;
        uint32_t opcode : 6;
    } bits;

};
union mftb {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t spr : 10;
        uint32_t rt : 5;
        uint32_t opcode : 6;
    } bits;

};
union mtcrf {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t spr : 10;
        uint32_t rt : 5;
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
    } bits;

};
union mtspr {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 10;
        uint32_t spr : 10;
        uint32_t rt : 5;
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
    } bits;

};
union mulli {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
    } bits;

};
union ori {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
    } bits;

};
union oris {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
    } bits;

};
union sc {
    uint32_t value;

    struct {
        uint32_t lev : 26;
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
    } bits;

};
union stb {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
    } bits;

};
union stbu {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
    } bits;

};
union stfd {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
    } bits;

};
union stfdu {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
    } bits;

};
union stfs {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
    } bits;

};
union stfsu {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
    } bits;

};
union sth {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
    } bits;

};
union sthu {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
    } bits;

};
union stmw {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
    } bits;

};
union stw {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
    } bits;

};
union stwu {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
    } bits;

};
union subficx {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
    } bits;

};
union tdi {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
    } bits;

};
union twi {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
    } bits;

};
union xori {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
    } bits;

};
union xoris {
    uint32_t value;

    struct {
        uint32_t ds : 16;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
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
        uint32_t opcode : 6;
    } bits;

};

union li {
	uint32_t value;

	struct {
		uint32_t si : 16;
		uint32_t ra : 5;
		uint32_t rt : 5;
		uint32_t opcode : 6;
	} bits;
};

union _or {
	uint32_t value;

	struct {
		uint32_t ui : 16;
		uint32_t ra : 5;
		uint32_t rs : 5;
		uint32_t opcode : 6;
	} bits;
};

union bundle_31 {
    uint32_t value;

    struct {
        uint32_t rc : 1;
        uint32_t _ : 9;
        uint32_t oe : 1;
        uint32_t rb : 5;
        uint32_t ra : 5;
        uint32_t rt : 5;
        uint32_t opcode : 6;
    } bits;
};

union bundle_19 {
    uint32_t value;

    struct {
        uint32_t lk : 1;
        uint32_t _ : 10;
        uint32_t bh : 2;
        uint32_t reserved : 3;
        uint32_t bl : 5;
        uint32_t bo : 5;
        uint32_t opcode : 6;
    } bits;
};

enum opcode {
	op_li = 14, // same as addi?
	op_lis = 15,
	op_sc = 17,
    op_b = 18,
    op_bundle_19 = 19, // branches
	op_bundle_31 = 31,
    op_lwz = 32,
    op_stw = 36,
    op_stwu = 37,
};

enum extended_opcode {
	eop_or = 444,
    eop_bclr = 16,
    eop_mtspr = 467,
    eop_mfspr = 339,
};

#pragma endregion

class virtual_machine {
public:
    virtual_machine() {
        memset(stack, 0, STACK);
        memset(ram, 0, RAM);
    }

	void execute(uint8_t* payload, uint32_t size) {
		execution = payload;
        context.gpr[1] = (uint64_t)&stack[STACK];

        do {
            instruction in = { _byteswap_ulong(*(uint32_t*)(&payload[context.iar * sizeof(uint32_t)])) };
            switch (in.bits.opcode) {
                case op_li: { // addi
                    li val = { in.value };
                    context.gpr[val.bits.rt] = val.bits.ra == 0 ? val.bits.si : context.gpr[val.bits.ra | 0] + val.bits.si;

#ifdef DEBUG
                    if (val.bits.ra == 0) {
                        printf("li r%i, 0x%x\n", val.bits.rt, val.bits.si);
                    } else {
                        printf("addi r%i, r%i, 0x%x\n", val.bits.rt, val.bits.ra | 0, val.bits.si);
                    }
#endif
                    break;
                }

                case op_lis: { // addic
                    li val = { in.value };
                    context.gpr[val.bits.rt] = val.bits.ra == 0 ? (val.bits.si || 0) : (val.bits.ra | 0) + (val.bits.si || 0);

#ifdef DEBUG
                    if (val.bits.ra == 0) {
                        printf("lis r%i, 0x%x\n", val.bits.rt, (val.bits.si || 0));
                    } else {
                        printf("addic r%i, r%i, 0x%x\n", val.bits.rt, val.bits.ra | 0, (val.bits.si || 0));
                    }
#endif
                    break;
                }

                case op_sc: {
#ifdef DEBUG
                    printf("sc\n");

#endif

                    sc val = { in.value };
                    if (val.bits.lev == 2) {
                        // the syscall should handle setting return registers
                        ((void(*)(virtual_machine*))syscall_table[(int)context.gpr[0]])(this);
                    }
                    break;
                }

                case op_lwz: {
                    lwz val = { in.value };
                    context.gpr[val.bits.rt] = _byteswap_ulong(*(uint32_t*)(context.gpr[val.bits.ra] + val.bits.ds));

#ifdef DEBUG
                    printf("lwz r%i, 0x%X(r%i)\n", val.bits.rt, val.bits.ds, val.bits.ra);
#endif
                    break;
                }

                case op_stwu: {
                    stwu val = { in.value };
                    if (val.bits.ra == 1) {
                        // if it's a stack allocation
                        uint64_t current_stack = context.gpr[1];
                        context.gpr[1] += (short)val.bits.ds;
                        *(uint64_t*)(context.gpr[1]) = current_stack; // backchain
                    } else {
                        *(uint32_t*)(context.gpr[val.bits.ra] + (short)val.bits.ds) = _byteswap_ulong(context.gpr[val.bits.rt]);
                    }

#ifdef DEBUG
                    printf("stwu r%i, %s0x%X(r%i)\n", val.bits.rt, (short)val.bits.ds > 0 ? "" : "-", (short)val.bits.ds > 0 ? (short)val.bits.ds : abs((short)val.bits.ds), val.bits.ra);
#endif

                    break;
                }

                case op_stw: {
                    stw val = { in.value };
                    *(uint32_t*)(context.gpr[val.bits.ra] + (short)val.bits.ds) = _byteswap_ulong(context.gpr[val.bits.rt]);
#ifdef DEBUG
                    printf("stw r%i, %s0x%X(r%i)\n", val.bits.rt, (short)val.bits.ds > 0 ? "" : "-", (short)val.bits.ds > 0 ? (short)val.bits.ds : abs((short)val.bits.ds), val.bits.ra);
#endif

                    break;
                }

                case op_b: {
                    bx val = { in.value };
                    if (val.bits.lk) {
                        context.lr = context.iar + 1;
                    }
                    
                    uint32_t offset = val.bits.li - 1;
                    if (val.bits.aa == 0) {
                        context.iar += offset;
                    } else {
                        context.iar = offset;
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


                        case eop_mfspr: { // mfspr
                            mfspr val_2 = { in.value };
                            switch (((val_2.bits.spr >> 5) & 0x1F) | (val_2.bits.spr & 0x1F)) {

                                case 1: { // xer
                                    context.gpr[val_2.bits.rt] = context.xer;
                                    break;
                                }
                                case 8: { // lr
                                    context.gpr[val_2.bits.rt] = context.lr;
                                    break;
                                }
                                case 9: { // ctr
                                    context.gpr[val_2.bits.rt] = context.ctr;
                                    break;
                                }
                            }
                            break;
                        }


                        case eop_mtspr: { // mtspr
                            mtspr val_2 = { in.value };
                            switch (((val_2.bits.spr >> 5) & 0x1F) | (val_2.bits.spr & 0x1F)) {

                                case 1: { // xer
                                    context.xer = context.gpr[val_2.bits.rt];
                                    break;
                                }
                                case 8: { // lr
                                    context.lr = context.gpr[val_2.bits.rt];
                                    break;
                                }
                                case 9: { // ctr
                                    context.ctr = context.gpr[val_2.bits.rt];
                                    break;
                                }
                            }
                            break;
                        }
                    }

                    break;
                }

                case op_bundle_19: {
                    bundle_19 val = { in.value };
                    switch (val.bits._) {
                       case eop_bclr: { // blr, bclrl
                           if (val.bits.bo & 0b10100) {
                               // blr

#ifdef DEBUG
                               printf("blr\n");
#endif
                               if (context.lr == 0) return; // end of program
                               context.iar = context.lr;
                               continue;
                           }

                           break;
                       }
                    }

                    break;
                }

                // TEMP FOR DEBUGGING
                case 63: {
                    printf("breaking\n");
                    DebugBreak();
                    break;
                }
            }

            context.iar++;
        } while (context.iar < size);
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
    uint8_t* get_stack() { return stack; }
private:
	// registers for the thread
	registers context;

	// syscall table
	void* syscall_table[MAX_SYSCALLS];

	// ram
	uint8_t ram[RAM];

	// stack
	uint8_t stack[STACK];

	// currently executing payload
	uint8_t* execution;
};

void setup_syscalls(virtual_machine* vm) {
	vm->add_syscall([](virtual_machine* vm) {
		// for now, only supports formatters
		printf("[PRINTF] %s", (const char*)(vm->get_context()->gpr[3]));
	}, 0); 

    vm->add_syscall([](virtual_machine* vm) {
        // set r3 to the address of the execution
        vm->get_context()->gpr[3] = (uint64_t)vm->get_execution();
    }, 1);

    vm->add_syscall([](virtual_machine* vm) {
        // print stack
        printf("current stack allocated: 0x%X\n", (uint64_t)&vm->get_stack()[STACK] - vm->get_context()->gpr[1]);
        printf("last stack frame: 0x%llx\n", *(uint64_t*)vm->get_context()->gpr[1]);
    }, 2);

    vm->add_syscall([](virtual_machine* vm) {
        // print registers
        vm->print_registers();
        printf("\n");
    }, 3);
}

int main() {
	/*uint8_t payload[] = {
		0x38, 0x80, 0x00, 0x59,		// li %r4, 0x59
		0x38, 0x84, 0x00, 0x10,		// addi %r4, %r4, 0x10
		0x38, 0x60, 0x00, 0x3C,		// li %r3, 0x3C					->>> offset from payload base to string
		0x38, 0x00, 0x00, 0x00,		// li %r0, 0					->>> "printf" syscall
		0x44, 0x00, 0x00, 0x02,		// sc
        0x38, 0x00, 0x00, 0x01,		// li %r0, 1					->>> "set r3 to execution" syscall
        0x44, 0x00, 0x00, 0x02,		// sc
        0x81, 0x63, 0x00, 0x24,     // lwz %r11, 0x24(%r3)
        0x94, 0x21, 0xFF, 0x90,     // stwu %r1, -0x70(%r1)
        0x90, 0x61, 0x00, 0x10,     // stw %r3, 0x10(%r1)
        0x38, 0x00, 0x00, 0x02,		// li %r0, 2					->>> "print stack" syscall
        0x44, 0x00, 0x00, 0x02,		// sc
        0x38, 0x21, 0x00, 0x70,     // addi %r1, %r1, 0x70
		0x4E, 0x80, 0x00, 0x20,		// blr
        0xFF, 0xFF, 0xFF, 0xFF,     // DEBUG BREAKPOINT
		
		0x68, 0x65, 0x79, 0x20,		// "hey "
		0x66, 0x72, 0x6F, 0x6D,		// "from"
		0x20, 0x50, 0x50, 0x43,		// " PPC"
		0x0A, 0x00, 0x00, 0x00		// "\n" + null terminator
	};*/

    uint8_t payload[] = {

        // testing mf/mt spr
        0x38, 0x60, 0x00, 0x69,
        0x7C, 0x68, 0x03, 0xA6,
        0xFF, 0xFF, 0xFF, 0xFF,     // DEBUG BREAKPOINT
        0x7D, 0x88, 0x02, 0xA6,
        0xFF, 0xFF, 0xFF, 0xFF,     // DEBUG BREAKPOINT
        // testing mf/mt spr

        0x94, 0x21, 0xFF, 0x00,
        0x48, 0x00, 0x00, 0x21, 
        0x38, 0x63, 0x00, 0x30,
        0x48, 0x00, 0x00, 0x0D, 
        0x38, 0x21, 0x01, 0x00, 
        0x4E, 0x80, 0x00, 0x20,
        0x38, 0x00, 0x00, 0x00, 
        0x44, 0x00, 0x00, 0x02, 
        0x4E, 0x80, 0x00, 0x20,
        0x38, 0x00, 0x00, 0x01, 
        0x44, 0x00, 0x00, 0x02, 
        0x4E, 0x80, 0x00, 0x20,
        0x6E, 0x69, 0x67, 0x67, 
        0x65, 0x72, 0x0A, 0x00
    };

	virtual_machine vm;
	setup_syscalls(&vm);

	vm.execute(payload, sizeof(payload) / sizeof(uint32_t));

	system("pause");
	return 0;
}