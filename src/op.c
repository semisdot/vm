#include <stdio.h>
#include <stdint.h>

#include "op.h"

#include "stack.h"

/* ---------------------------------------------------------------------------------------------------- */

static void put_ASCII_code(uint8_t u8);
static uint8_t _op_sum_top(struct stack *s);

/* ---------------------------------------------------------------------------------------------------- */

uint8_t *op_nop(uint8_t *ip, struct stack *s) {

	return ip + 1;
}

uint8_t *op_push_char(uint8_t *ip, struct stack *s) {

	{
		struct object o;

		o.type = 'c';
		o.u8 = *(ip + 1);

		stack_push(s, o);
	}

	return ip + 2;
}

uint8_t *op_emit(uint8_t *ip, struct stack *s) {

	{
		struct object o;

		o = stack_pop(s);

		putchar(o.u8);
	}

	return ip + 1;
}

uint8_t *op_halt(uint8_t *ip, struct stack *s) {

	return NULL;
}

uint8_t *op_emit_ASCII_code(uint8_t *ip, struct stack *s) {

	{
		struct object o;

		o = stack_pop(s);

		put_ASCII_code(o.u8);
	}

	return ip + 1;
}

uint8_t *op_sum_top(uint8_t *ip, struct stack *s) {

	{
		struct object o;

		o.type = 'c';
		o.u8 = _op_sum_top(s);

		stack_push(s, o);
	}

	return ip + 1;
}

uint8_t *op_switch_top(uint8_t *ip, struct stack *s) {

	{
		struct object top1, top2; // o1, o2

		top1 = stack_pop(s);
		top2 = stack_pop(s);

		stack_push(s, top1);
		stack_push(s, top2);
	}

	return ip + 1;
}

/* ---------------------------------------------------------------------------------------------------- */

static uint8_t _op_sum_top(struct stack *s) { // sum_top() ?!

	uint8_t u8;

	{
		struct object top1, top2; // o1, o2

		top1 = stack_pop(s);
		top2 = stack_pop(s);

		u8 = top1.u8 + top2.u8;
	}

	return u8;
}

static void put_ASCII_code(uint8_t u8) { // _op_emit_ASCII_code() ?!

	if (u8 > 9) { // (!(u8 < 10))

		put_ASCII_code(u8 / 10);

		u8 = u8 % 10; // == last digit // u8 = u8 - (u8 / 10) * 10
	}

	putchar(u8 + 48/*offset*/); // (u8 + '0')
}
