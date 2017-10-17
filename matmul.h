#ifndef MATMUL_H_
#define MATMUL_H_


#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>


#define MAX_FILE_PATH 255
#define MAX_FILE_NAME 20


typedef enum {
	PARALLEL_MATMUL_1,
	PARALLEL_MATMUL_2,
	SEQUNETIAL_MATMUL
} matmul_mode;

typedef struct matrix_t {
	char name[MAX_FILE_NAME];
	char path[MAX_FILE_PATH];
	float **values;
	int rows_num;
	int cols_num;
} matrix_t;


typedef struct method_1_data {
	int row;
	matrix_t *mat_a;
	matrix_t *mat_b;
	matrix_t *mat_c;
} method_1_data;

typedef struct method_2_data {
	matrix_t *mat_a;
	matrix_t *mat_b;
	matrix_t *mat_c;
	int row;
	int col;
} method_2_data;


matrix_t* load_matrix(char *path);

int save_matrix(matrix_t *mat);

int matmul(char *a_path, char *b_path, char *out_path, matmul_mode mode);

void print_matrix(matrix_t *mat);

void free_matrix(matrix_t *mat);


#endif // MATMUL_H_