#include "struct_stack.h"

size_t stack_push(struct stack *s, struct object o);
struct object stack_pop(struct stack *s);
struct object stack_peek(struct stack *s);
