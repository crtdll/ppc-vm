#pragma once
#include "stdafx.h"

struct registers {
	uint64_t msr; // machine status register
	uint64_t iar; // instruction address register
	uint64_t lr;  // link register
	uint64_t ctr; // count register

	uint64_t gpr[32]; // general registers 0 to 31

	// xer register
	union {
		uint32_t value;
		struct {
			uint32_t so : 1;
			uint32_t ov : 1;
			uint32_t ca : 1;
		} bits;
	} xer;

	// condition register - not using bits, bitset is nicer to work with
	enum cr_bit { lt, gt, eq, so };
	std::array<std::bitset<4>, 8> cr; // bools instead of bits

	double fpscr;	// floating point status/control register
	double fpr[32]; // floating point registers 0 to 31

	registers() {
		msr = 0; iar = 0; lr = 0; ctr = 0;
		memset(gpr, 0, sizeof(gpr));
	}
};