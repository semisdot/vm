#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "vm.h"
#include "load.h"
#include "init.h"
#include "op.h"

/* ---------------------------------------------------------------------------------------------------- */

#define STACK_SIZE	1024
#define MAX_OPS		256

/* ---------------------------------------------------------------------------------------------------- */

static void error_usage(const char *err_msg);

/* ---------------------------------------------------------------------------------------------------- */

int main(int argc, char **argv)
{
	uint8_t *code;

	{ // handle command line
		if (argc == 1) {

			code = load_stdin();

		} else if (argc == 2) {

			code = load_file(argv[1]);

		} else {

			error_usage("vm usage");
		}
	}

	{
		struct stack s;
		uint8_t *(*ops[MAX_OPS])(uint8_t *, struct stack *); // array of function pointers

		init_stack(&s, STACK_SIZE);

		set_ops(ops, MAX_OPS, op_nop);
		init_ops(ops);

		vm_run(code, &s, ops);

		// free_stack(&s);
	}

	/*
	free(code);
	code = NULL;
	*/

	return 0;
}

/* ---------------------------------------------------------------------------------------------------- */

static void error_usage(const char *err_msg)
{
	fprintf(stderr, "Error: %s\n", err_msg);

	exit(1);
}
