#include "struct_stack.h"

void stack_init(struct stack *s, size_t size);
void stack_free(struct stack *s);
void instruction_set_init(uint8_t *(*ops[256])(uint8_t *, struct stack *));
