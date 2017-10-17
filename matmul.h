#ifndef MATMUL_H_
#define MATMUL_H_


#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>


#define MAX_FILE_PATH 255
#define MAX_FILE_NAME 20

typedef struct matrix_t {
	char name[MAX_FILE_NAME];
	char path[MAX_FILE_PATH];
	float **values;
	int rows_num;
	int cols_num;
} matrix_t;


matrix_t* load_matrix(char *path);

int save_matrix(matrix_t *mat);

int matmul(char *a_path, char *b_path, char *out_path);

void print_matrix(matrix_t *mat);

void free_matrix(matrix_t *mat);


#endif // MATMUL_H_