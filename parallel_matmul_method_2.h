#ifndef PARALLEL_MATMUL_METHOD_2_H_
#define PARALLEL_MATMUL_METHOD_2_H_

#include <pthread.h>

#include "matmul.h"


typedef struct method_2_data {
	matrix_t *mat_a;
	matrix_t *mat_b;
	matrix_t *mat_c;
	int row;
	int col;
} method_2_data;


void* method_2_thread_runner(void *method_2_data_void);
void parallel_matmmul_method_2(matrix_t *mat_a, matrix_t *mat_b, matrix_t *mat_c);



#endif // PARALLEL_MATMUL_METHOD_2_H_