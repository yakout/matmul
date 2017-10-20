#include "parallel_matmul_method_2.h"

void* method_2_thread_runner(void *method_2_data_void) {
	method_2_data *data = (method_2_data*) method_2_data_void;
	int i = data->row;
	int j = data->col;
	
	for (int k = 0; k < data->mat_a->cols_num; ++k) {
		data->mat_c->values[i][j] += data->mat_a->values[i][k] * data->mat_b->values[k][j];
	}
	free(data);
	return NULL;
}


void parallel_matmmul_method_2(matrix_t *mat_a, matrix_t *mat_b, matrix_t *mat_c) {
	pthread_t **threads = malloc(sizeof(pthread_t*) * mat_a->rows_num * mat_b->cols_num);
	int thread_count = 0;

	for (int i = 0; i < mat_a->rows_num; ++i) {
		for (int j = 0; j < mat_b->cols_num; ++j) {
			method_2_data* data = malloc(sizeof(method_2_data));
			data->mat_a = mat_a;
			data->mat_b = mat_b;
			data->mat_c = mat_c;
			data->row = i;
			data->col = j;

			pthread_t *cell_thread = malloc(sizeof(pthread_t));
			threads[thread_count++] = cell_thread;

			if(pthread_create(cell_thread, NULL, method_2_thread_runner, data)) {
				fprintf(stderr, "Error creating thread\n");
				return;
			}
		}
	}

	for (int i = 0; i < thread_count; ++i) {
		pthread_join(*threads[i], NULL);
		free(threads[i]);
	}

	printf("* NUMBER OF THREADS: %d\n", thread_count);
	printf("****************************************\n");
}