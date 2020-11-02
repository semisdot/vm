#include <stdlib.h>
#include <stdint.h>

#include "op.h"

void instruction_set_fill(uint8_t *(**ops)(uint8_t *, struct stack *)) ;

void stack_init(struct stack *s, size_t size) {

	s->top = 0;
	s->size = size;

	s->o = malloc(sizeof(*s->o) * size);
}

void stack_free(struct stack *s) {

	s->size = 0;

	free(s->o);
}

void instruction_set_init(uint8_t *(**ops)(uint8_t *, struct stack *)) {

	instruction_set_fill(ops);

	ops['c'] = op_push_char;
	ops['e'] = op_emit;
	ops['h'] = op_halt;
	ops['.'] = op_emit_ASCII_code;
	ops['+'] = op_sum_top;
	ops['x'] = op_switch_top;
}

void instruction_set_fill(uint8_t *(**ops)(uint8_t *, struct stack *)) {

	int i;

	for (i = 0; i < 256; ++i) {

		ops[i] = op_nop; // no operation
	}
}
