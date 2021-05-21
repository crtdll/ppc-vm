#pragma once
#include "stdafx.h"

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
		uint32_t : 1;
		uint32_t _ : 10;
		uint32_t rb : 5;
		uint32_t ra : 5;
		uint32_t l : 1;
		uint32_t : 1;
		uint32_t crfd : 3;
		uint32_t opcode : 6;
	} bits;

};
union cmpi {
	uint32_t value;

	struct {
		uint32_t ds : 16;
		uint32_t ra : 5;
		uint32_t l : 1;
		uint32_t : 1;
		uint32_t crfd : 3;
		uint32_t opcode : 6;
	} bits;

};
union cmpl {
	uint32_t value;

	struct {
		uint32_t : 1;
		uint32_t _ : 10;
		uint32_t rb : 5;
		uint32_t ra : 5;
		uint32_t l : 1;
		uint32_t : 1;
		uint32_t crfd : 3;
		uint32_t opcode : 6;
	} bits;

};
union cmpli {
	uint32_t value;

	struct {
		uint32_t ds : 16;
		uint32_t ra : 5;
		uint32_t l : 1;
		uint32_t : 1;
		uint32_t crfd : 3;
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
	op_cmpli = 10,
	op_cmpi = 11,
	op_li = 14, // same as addi?
	op_lis = 15,
	op_sc = 17,
	op_b = 18,
	op_bc = 16,
	op_bundle_19 = 19, // branches
	op_bundle_31 = 31,
	op_lwz = 32,
	op_stw = 36,
	op_stwu = 37,
	op_stb = 38
};

enum extended_opcode {
	eop_none = -1,
	eop_cmp = 0,
	eop_cmpl = 32,
	eop_add = 266,
	eop_or = 444,
	eop_bclr = 16,
	eop_mtspr = 467,
	eop_mfspr = 339,
};

enum iteration_reason {
	it_ok,
	it_continue,
	it_return
};