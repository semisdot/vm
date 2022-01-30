#include <stdlib.h>
#include <stdint.h>

#include "init.h"

#include "op.h"

/* ---------------------------------------------------------------------------------------------------- */

void init_stack(struct stack *s, size_t size) {

	s->top = 0;
	s->size = size;

	s->o = malloc(sizeof(*s->o) * size);
}

void set_ops(uint8_t *(**ops)(uint8_t *, struct stack *), int ops_count, uint8_t *(*op)(uint8_t *, struct stack *)) {

	int i;

	for (i = 0; i < ops_count; ++i) {

		ops[i] = op;
	}
}

void init_ops(uint8_t *(**ops)(uint8_t *, struct stack *)) {

	ops['c'] = op_push_char;
	ops['e'] = op_emit;
	ops['h'] = op_halt;
	ops['.'] = op_emit_ASCII_code;
	ops['+'] = op_sum_top;
	ops['x'] = op_switch_top;
}
