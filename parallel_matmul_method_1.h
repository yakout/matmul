#ifndef PARALLEL_MATMUL_METHOD_1_H_
#define PARALLEL_MATMUL_METHOD_1_H_

#include <pthread.h>

#include "matmul.h"

typedef struct method_1_data {
	int row;
	matrix_t *mat_a;
	matrix_t *mat_b;
	matrix_t *mat_c;
} method_1_data;


void* method_1_thread_runner(void *method_1_data_void);
void parallel_matmmul_method_1(matrix_t *mat_a, matrix_t *mat_b, matrix_t *mat_c);


#endif // PARALLEL_MATMUL_METHOD_1_H_