#pragma once
#include "stdafx.h"
#include "registers.h"

#define MAX_SYSCALLS 0xFF
#define RAM 0xFFFF
#define STACK 0xFFFF
#define DEBUG

class virtual_machine {
public:
	void execute(uint8_t* payload, uint32_t size);
	void add_syscall(void(*function)(virtual_machine*), int id);
	void print_registers();

	uint8_t* get_ram() { return ram; }
	uint8_t* get_stack() { return stack; }
	registers* get_context() { return &context; }
private:
	registers context;
	uint8_t ram[RAM];
	uint8_t stack[STACK];
	void* syscall_table[MAX_SYSCALLS];
};