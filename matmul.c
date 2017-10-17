#include "matmul.h"



int matmul(char *a_path, char *b_path, char *c_path) {	
	matrix_t* mat_a = load_matrix(a_path);
	matrix_t* mat_b = load_matrix(b_path);

	assert(mat_a->cols_num == mat_b->rows_num);

	float **c_values = malloc(sizeof(float*) * mat_a->rows_num);
	for (int i = 0; i < mat_a->rows_num; ++i) {
		c_values[i] = malloc(sizeof(float) * mat_b->cols_num);
		for (int j = 0; j < mat_b->cols_num; ++j) {
			c_values[i][j] = 0;
		}
	}

	matrix_t *mat_c = malloc(sizeof(matrix_t));
	strcpy(mat_c->path, c_path);
	mat_c->values = c_values;
	mat_c->rows_num = mat_a->rows_num;
	mat_c->cols_num = mat_b->cols_num;


	for (int i = 0; i < mat_a->rows_num; ++i) {
		for (int j = 0; j < mat_b->cols_num; ++j) {
			for (int k = 0; k < mat_a->cols_num; ++k) {
				mat_c->values[i][j] += mat_a->values[i][k] * mat_b->values[k][j];
			}
		}
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

	// print_matrix(mat);

	return mat;
}


int save_matrix(matrix_t *mat) {
	print_matrix(mat);
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


