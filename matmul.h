#ifndef MATMUL_H_
#define MATMUL_H_


#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>


#define MAX_FILE_PATH 255


typedef enum {
	PARALLEL_MATMUL_1,
	PARALLEL_MATMUL_2,
	SEQUNETIAL_MATMUL
} matmul_mode;

typedef struct matrix_t {
	char path[MAX_FILE_PATH];
	long long **values;
	int rows_num;
	int cols_num;
} matrix_t;


#include "parallel_matmul_method_1.h"
#include "parallel_matmul_method_2.h"

/**
 * @brief load a matrix from a file
 * @details load a matrix from a file into matrix_t.
 * 
 * @param path the path to the file
 * @return the pointer to the created matrix_t struct.
 */
matrix_t* load_matrix(char *path);

/**
 * @brief save a matrix to file.
 * @details write the given matrix_t to the output file path associated with it.
 * 
 * @param mat matrix to save
 * @return 0 indicating success error otherwise
 */
int save_matrix(matrix_t *mat);

/**
 * @brief multiply two matrices.
 * @details [long description]
 * 
 * @param a_path [description]
 * @param b_path [description]
 * @param out_path [description]
 * @param mode [description]
 * @return [description]
 */
int matmul(char *a_path, char *b_path, char *out_path, matmul_mode mode, int print_to_stdout);

/**
 * @brief print the matrix values to the stdout
 * @details print the matrix values to the stdout
 * 
 * @param mat matrix_t
 */
void print_matrix(matrix_t *mat);

/**
 * @brief free all memory allocated for the matrix.
 * @details free all memory allocated for the matrix
 * 
 * @param mat matrix_t
 */
void free_matrix(matrix_t *mat);

/**
 * @brief genertate random matrix.
 * @details genertate random matrix of size rows_num * cols_num, values range [min , max].
 * 
 * @param path the output file path.
 * @param rows_num number of rows in the generated matrix
 * @param cols_num number of cols in the generated matrix
 * @param min the minimum value in the generated matrix
 * @param max the maximum value in the generated matrix
 */
void generate_matrix(char *path, int rows_num, int cols_num, int min, int max);

/**
* @brief print the execution time of matmul to stdout.
 * @details print the execution time of matmul to stdout.
 * 
 * @param a fist matrix input file path
 * @param b second matrix input file path
 * @param c output matrix file path.
 * @param mode running mode:
 * 				0: PARALLEL METHOD 1
 * 				1: PARALLEL METHOD 2
 * 				2: SEQUENTIAL
 */
int matmul_with_benchmark(char* a, char*b, char* c, matmul_mode mode, int print_to_stdout);


#endif // MATMUL_H_