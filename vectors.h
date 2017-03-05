#ifndef VECTORS_H__
#define VECTORS_H__

#include <stdint.h>

typedef void (*isrfunc_t)(void);
typedef isrfunc_t vector_table_t[255];
typedef struct {
	uint32_t *stack_ptr;
	vector_table_t vectors;
} vt_with_sp_t;

#endif
