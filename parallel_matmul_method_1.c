#include "parallel_matmul_method_1.h"

void* method_1_thread_runner(void *method_1_data_void) {
	method_1_data *data = (method_1_data*) method_1_data_void;
	int i = data->row;
	for (int j = 0; j < data->mat_b->cols_num; ++j) {
		for (int k = 0; k < data->mat_a->cols_num; ++k) {
			data->mat_c->values[i][j] += data->mat_a->values[i][k] * data->mat_b->values[k][j];
		}
	}
	free(data);
	return NULL;
}


void parallel_matmmul_method_1(matrix_t *mat_a, matrix_t *mat_b, matrix_t *mat_c) {
	pthread_t **threads = malloc(sizeof(pthread_t*) * mat_a->rows_num);
	int thread_count = 0;

	for (int i = 0; i < mat_a->rows_num; ++i) {
		method_1_data* data = malloc(sizeof(method_1_data));
		data->mat_a = mat_a;
		data->mat_b = mat_b;
		data->mat_c = mat_c;
		data->row = i;

		pthread_t *row_thread = malloc(sizeof(pthread_t));
		threads[thread_count++] =  row_thread;

		if(pthread_create(row_thread, NULL, method_1_thread_runner, data)) {
			fprintf(stderr, "Error creating thread\n");
			return;
		}
	}

	for (int i = 0; i < thread_count; ++i) {
		pthread_join(*threads[i], NULL);
		free(threads[i]);
	}

	printf("* NUMBER OF THREADS: %d\n", thread_count);
	printf("****************************************\n");

}