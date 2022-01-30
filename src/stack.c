#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
// #include <assert.h>

#include "stack.h"

/* ---------------------------------------------------------------------------------------------------- */

static void check_stack_overflow(struct stack *s);
static void check_stack_underflow(struct stack *s);

static void error_stack(const char *err_msg);

/* ---------------------------------------------------------------------------------------------------- */

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

/* ---------------------------------------------------------------------------------------------------- */

static void check_stack_overflow(struct stack *s) {

	if (s->top == s->size) { // (!(s->top < s->size))

		error_stack("stack overflow");
	}
}

static void check_stack_underflow(struct stack *s) {

	if (s->top == 0) { // (!(s->top > 0))

		error_stack("stack underflow");
	}
}

/* ---------------------------------------------------------------------------------------------------- */

static void error_stack(const char *err_msg) {

	fflush(stdout);
	fprintf(stderr, "\nError: %s\n", err_msg);

	exit(1);
}
