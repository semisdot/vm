#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "load.h"
#include "init.h"

#define STACK_SIZE 1024

void vm_error(char *err_msg);

int main(int argc, char **argv) {

	uint8_t *ip; // instruction pointer
	uint8_t *code;
	struct stack s;
	uint8_t *(*ops[256])(uint8_t *, struct stack *); // instruction set // array of function pointers

	if (argc == 1) {

		code = load_stdin();

	} else if (argc == 2) {

		code = load_file(argv[1]);

	} else {

		vm_error("vm usage");
	}

	stack_init(&s, STACK_SIZE);
	instruction_set_init(ops);

	ip = code;

	while (ip) {

		ip = ops[*ip](ip, &s);
	}

	free(code);
	stack_free(&s);

	return 0;
}

void vm_error(char *err_msg) {

	fprintf(stderr, "ERROR: %s\n", err_msg);

	exit(1);
}
