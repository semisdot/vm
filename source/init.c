#include <stdlib.h>
#include <stdint.h>

#include "op.h"

void ops_fill(uint8_t *(*ops[256])(uint8_t *, struct stack *));
void ops_init(uint8_t *(*ops[256])(uint8_t *, struct stack *));

void stack_init(struct stack *s, size_t size) {

	s->top = 0;
	s->size = size;

	s->o = malloc(sizeof(*s->o) * size);
}

void stack_free(struct stack *s) {

	s->size = 0;

	free(s->o);
}

void instruction_set_init(uint8_t *(*ops[256])(uint8_t *, struct stack *)) {

	ops_fill(ops);
	ops_init(ops);
}

void ops_fill(uint8_t *(*ops[256])(uint8_t *, struct stack *)) {

	int i;

	for (i = 0; i < 256; ++i) {

		// no operation
		ops[i] = op_nop;
	}
}

void ops_init(uint8_t *(*ops[256])(uint8_t *, struct stack *)) {

	ops['c'] = op_push_char;
	ops['e'] = op_emit;
	ops['h'] = op_halt;
	ops['.'] = op_emit_ASCII_code;
	ops['+'] = op_sum_top;
	ops['x'] = op_switch_top;
}
