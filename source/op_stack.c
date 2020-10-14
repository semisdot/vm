#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "op_stack.h"

void check_stack_overflow(struct stack *s);
void check_stack_underflow(struct stack *s);

size_t stack_push(struct stack *s, struct object o) {

	check_stack_overflow(s);

	s->o[s->top++] = o;

	return s->top; // not used
}

struct object stack_pop(struct stack *s) {

	check_stack_underflow(s);

	return s->o[--s->top];
}

struct object stack_peek(struct stack *s) { // not used

	check_stack_underflow(s);

	return s->o[s->top - 1];
}

void check_stack_overflow(struct stack *s) {

	if (!(s->top < s->size)) { // (s->top == s->size)

		fflush(stdout);
		fprintf(stderr, "\nERROR: stack overflow\n");

		exit(1);
	}
}

void check_stack_underflow(struct stack *s) {

	if (!s->top) {

		fflush(stdout);
		fprintf(stderr, "\nERROR: stack underflow\n");

		exit(1);
	}
}
