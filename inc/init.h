// #ifndef
// #define

/* ---------------------------------------------------------------------------------------------------- */

#include "stack.struct.h"

/* ---------------------------------------------------------------------------------------------------- */

void init_stack(struct stack *s, size_t size);
void free_stack(struct stack *s);
void set_ops(uint8_t *(**ops)(uint8_t *, struct stack *),
			 unsigned int ops_count,
			 uint8_t *(*op)(uint8_t *, struct stack *));
void init_ops(uint8_t *(**ops)(uint8_t *, struct stack *));

/* ---------------------------------------------------------------------------------------------------- */

// #endif //
