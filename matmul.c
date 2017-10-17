#include "matmul.h"


void* method_1_thread_runner(void *method_1_data_void) {
	method_1_data *data = (method_1_data*) method_1_data_void;
	int i = data->row;
	for (int j = 0; j < data->mat_b->cols_num; ++j) {
		for (int k = 0; k < data->mat_a->cols_num; ++k) {
			data->mat_c->values[i][j] += data->mat_a->values[i][k] * data->mat_b->values[k][j];
		}
	}
	return NULL;
}


void parallel_matmmul_method_1(matrix_t *mat_a, matrix_t *mat_b, matrix_t *mat_c) {
	pthread_t **threads = malloc(sizeof(pthread_t *) * mat_a->rows_num);

	for (int i = 0; i < mat_a->rows_num; ++i) {
		method_1_data* data = malloc(sizeof(method_1_data));
		data->mat_a = mat_a;
		data->mat_b = mat_b;
		data->mat_c = mat_c;
		data->row = i;

		pthread_t *row_thread = malloc(sizeof(pthread_t));
		threads[i] = row_thread;

		if(pthread_create(row_thread, NULL, method_1_thread_runner, data)) {
			fprintf(stderr, "Error creating thread\n");
			return;
		}
	}

	for (int i = 0; i < mat_a->rows_num; ++i) {
		pthread_join(threads[i], NULL);
	}

}

void* method_2_thread_runner(void *method_2_data_void) {
	method_2_data *data = (method_2_data*) method_2_data_void;
	int i = data->row;
	int j = data->col;
	
	for (int k = 0; k < data->mat_a->cols_num; ++k) {
		data->mat_c->values[i][j] += data->mat_a->values[i][k] * data->mat_b->values[k][j];
	}
	return NULL;
}


void parallel_matmmul_method_2(matrix_t *mat_a, matrix_t *mat_b, matrix_t *mat_c) {
	pthread_t **threads = malloc(sizeof(pthread_t *) * mat_a->rows_num * mat_b->cols_num);
	int count = 0;

	for (int i = 0; i < mat_a->rows_num; ++i) {
		for (int j = 0; j < mat_b->cols_num; ++j) {
			method_2_data* data = malloc(sizeof(method_2_data));
			data->mat_a = mat_a;
			data->mat_b = mat_b;
			data->mat_c = mat_c;
			data->row = i;
			data->col = j;

			pthread_t *cell_thread = malloc(sizeof(pthread_t));
			threads[count++] = cell_thread;

			if(pthread_create(cell_thread, NULL, method_2_thread_runner, data)) {
				fprintf(stderr, "Error creating thread\n");
				return;
			}
		}
	}

	for (int i = 0; i < count; ++i) {
		pthread_join(threads[i], NULL);
	}
}


void squential_matmul(matrix_t *mat_a, matrix_t *mat_b, matrix_t *mat_c) {
	for (int i = 0; i < mat_a->rows_num; ++i) {
		for (int j = 0; j < mat_b->cols_num; ++j) {
			for (int k = 0; k < mat_a->cols_num; ++k) {
				mat_c->values[i][j] += mat_a->values[i][k] * mat_b->values[k][j];
			}
		}
	}
}


int matmul(char *a_path, char *b_path, char *c_path, matmul_mode mode) {
	matrix_t* mat_a = load_matrix(a_path);
	matrix_t* mat_b = load_matrix(b_path);

	assert(mat_a->cols_num == mat_b->rows_num);

	float **c_values = malloc(sizeof(float*) * mat_a->rows_num);
	for (int i = 0; i < mat_a->rows_num; ++i) {
		c_values[i] = malloc(sizeof(float) * mat_b->cols_num);
		// make sure values are initialized with zero.
		for (int j = 0; j < mat_b->cols_num; ++j) {
			c_values[i][j] = 0;
		}
	}

	matrix_t *mat_c = malloc(sizeof(matrix_t));
	strcpy(mat_c->path, c_path);
	mat_c->values = c_values;
	mat_c->rows_num = mat_a->rows_num;
	mat_c->cols_num = mat_b->cols_num;


	switch(mode) {
		case PARALLEL_MATMUL_1:
			parallel_matmmul_method_1(mat_a, mat_b, mat_c);
			break;
		case PARALLEL_MATMUL_2:
			parallel_matmmul_method_2(mat_a, mat_b, mat_c);
			break;
		case SEQUNETIAL_MATMUL:
			squential_matmul(mat_a, mat_b, mat_c);
			break;
	}

	save_matrix(mat_c);

	free_matrix(mat_a);
	free_matrix(mat_b);
	free_matrix(mat_c);
	return 0;
}




matrix_t* load_matrix(char *path) {
	FILE* file = fopen(path, "r");
	if (errno != 0) {
		perror("matrix loading error: ");
		exit(EXIT_FAILURE);
	}

	int rows_num, cols_num;
	char *error_msg = "matrix loading error: invalid format";
	
	if(fscanf(file, "%d", &rows_num) < 1) {
		fprintf(stderr, "%s\n", error_msg);
		exit(EXIT_FAILURE);
	}

	if(fscanf(file, "%d", &cols_num) < 1) {
		fprintf(stderr, "%s\n", error_msg);
		exit(EXIT_FAILURE);
	}


	float **values = malloc(sizeof(float*) * rows_num);
	// NOTE: this will not allocate a contiguous region of memory.
	for (int i = 0; i < rows_num; ++i) {
		values[i] = malloc(sizeof(float) * cols_num);
	}

	// fill the array
	for (int i = 0; i < rows_num; ++i) {
		for (int j = 0; j < cols_num; ++j) {
			float val;
			if(fscanf(file, "%f", &val) < 1) {
				fprintf(stderr, "%s or dimentions\n", error_msg);
				exit(EXIT_FAILURE);	
			}
			values[i][j] = val;
		}
	}

	float dummy;
	if(fscanf(file, "%f", &dummy) > 0) {
		fprintf(stderr, "%s\n", "matrix loading error: invalid format or dimentions");
		exit(EXIT_FAILURE);	
	}


	matrix_t *mat = malloc(sizeof(matrix_t));
	strcpy(mat->path, path);
	// mat->name = "";  // TODO
	mat->rows_num = rows_num;
	mat->cols_num = cols_num;
	mat->values = values;

	fclose(file);
	return mat;
}


int save_matrix(matrix_t *mat) {
	FILE *file = fopen(mat->path, "w");

	for (int i = 0; i < mat->rows_num; ++i) {
		for (int j = 0; j < mat->cols_num; ++j) {
			fprintf(file, "%f\t\t", mat->values[i][j]);
		}
		fprintf(file, "\n");
	}

	// print_matrix(mat);
	fclose(file);
	return 0;
}


void print_matrix(matrix_t *mat) {
	if (mat == NULL) return;
	for (int i = 0; i < mat->rows_num; ++i) {
		for (int j = 0; j < mat->cols_num; ++j) {
			printf("%f\t\t", mat->values[i][j]);
		}
		printf("\n");
	}
}


void free_matrix(matrix_t *mat) {
	if (mat == NULL) return;

	for (int i = 0; i < mat->rows_num; ++i) {
		free(mat->values[i]);
	}
	free(mat->values);
}


int generate_number(int lowerLimit, int upperLimit) {
    int r =  lowerLimit + rand() % (upperLimit - lowerLimit);
    return r;
}

void generate_matrix(char *path, int rows_num, int cols_num) {
	FILE *file = fopen(path, "w");
	fprintf(file, "%d %d\n", rows_num, cols_num);
		
	for (int i = 0; i < rows_num; ++i) {
		for (int j = 0; j < cols_num; ++j) {
			fprintf(file, "%d\t", generate_number(0, 100));
		}
		fprintf(file, "\n");
	}

	fclose(file);
}

