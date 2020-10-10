#include <stdio.h>
#include <stdint.h>

#include "op.h"

#include "op_stack.h"

void put_ASCII_code(uint8_t u8);

uint8_t *op_nop(uint8_t *ip, struct stack *s) {

	return ip + 1;
}

uint8_t *op_push_char(uint8_t *ip, struct stack *s) {

	struct object o;

	o.type = 'c';
	o.u8 = *(ip + 1);

	stack_push(s, o);

	return ip + 2;
}

uint8_t *op_emit(uint8_t *ip, struct stack *s) {

	struct object o;

	o = stack_pop(s);

	putchar(o.u8);

	return ip + 1;
}

uint8_t *op_halt(uint8_t *ip, struct stack *s) {

	return NULL;
}

uint8_t *op_emit_ASCII_code(uint8_t *ip, struct stack *s) {

	struct object o;

	o = stack_pop(s);

	put_ASCII_code(o.u8);

	return ip + 1;
}

void put_ASCII_code(uint8_t u8) {

	if (u8 > 9) {

		put_ASCII_code(u8 / 10);

		u8 = u8 - (u8 / 10) * 10; // == last digit
	}

	putchar(u8 + '0');
}

uint8_t *op_sum_top(uint8_t *ip, struct stack *s) {

	struct object o;
	struct object top1, top2;

	top1 = stack_pop(s);
	top2 = stack_pop(s);

	o.type = 'c';
	o.u8 = top1.u8 + top2.u8;

	stack_push(s, o);

	return ip + 1;
}

uint8_t *op_switch_top(uint8_t *ip, struct stack *s) {

	struct object top1, top2;

	top1 = stack_pop(s);
	top2 = stack_pop(s);

	stack_push(s, top1);
	stack_push(s, top2);

	return ip + 1;
}
