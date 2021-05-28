#pragma once
#include "stdafx.h"
#include "registers.h"
#include <unordered_map>

#define MAX_SYSCALLS 0xFF
#define RAM 0xFFFF
#define STACK 0xFFFF
#define DEBUG

class virtual_machine;

class core_machine {
public:
	virtual_machine* create_vm(uint32_t* thread_id = nullptr);
	void add_syscall(void(*function)(virtual_machine*), int id);

	uint8_t* get_ram() { return ram; }
	void* get_syscall(int index) { return syscall_table[index]; }
	registers* get_context(uint32_t thread_id) { return &context[thread_id]; }
protected:
	std::unordered_map<uint32_t, registers> context;
	uint8_t ram[RAM];
	void* syscall_table[MAX_SYSCALLS];
	uint32_t thread_id_count;
};

core_machine* get_core();

class virtual_machine {
public:
	void execute(uint8_t* payload, void* argument = nullptr);
	void print_registers();

	registers* get_current_context() { return get_core()->get_context(thread_id); }
	uint32_t get_thread_id() { return thread_id; }
	uint8_t* get_stack() { return stack; }
	uint8_t* get_payload() { return payload; }
	void* get_argument() { return argument; }

	void set_thread_id(uint32_t id) { thread_id = id; }
	void set_payload(uint8_t* p) { payload = p; }
	void set_argument(void* p) { argument = p; }
private:
	void* argument;
	uint8_t* payload;
	uint32_t thread_id;
	uint8_t stack[STACK];
};