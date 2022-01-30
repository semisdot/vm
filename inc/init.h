// #ifndef
// #define

/* ---------------------------------------------------------------------------------------------------- */

#include "stack.struct.h"

/* ---------------------------------------------------------------------------------------------------- */

void init_stack(struct stack *s, size_t size);
void set_ops(uint8_t *(**ops)(uint8_t *, struct stack *), int ops_count, uint8_t *(*op)(uint8_t *, struct stack *));
void init_ops(uint8_t *(**ops)(uint8_t *, struct stack *));

/* ---------------------------------------------------------------------------------------------------- */

// #endif //
