#ifndef STRUCT_STACK_H
#define STRUCT_STACK_H

struct object;

struct stack {

	size_t top;
	size_t size;

	struct object *o;
};

struct object {

	uint8_t type;

	union { // not used

		uint8_t u8; // used
		int8_t i8;
		uint32_t u32;
		int32_t i32;

		void *ptr;
	};
};

#endif // STRUCT_STACK_H
