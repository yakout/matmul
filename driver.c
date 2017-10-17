#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

#include "matmul.h"


int main(int argc, char **argv) {
	// generate_matrix("a.txt", 100, 100);
	// generate_matrix("b.txt", 100, 100);

	// generate_matrix("a100.txt", 100, 100);
	// generate_matrix("b100.txt", 100, 100);
	
	// CODE
	if (argc == 1) {
		// use defaults
		printf("RUNNING MODE 0\n");
		matmul("a.txt", "b.txt", "c.txt", PARALLEL_MATMUL_1);
	} else if (argc == 5) {
		int mode = atoi(argv[4]);
		switch(mode) {
			case 0:
				printf("RUNNING MODE 0\n");
				matmul_with_benchmark(argv[1], argv[2], argv[3], PARALLEL_MATMUL_1);
				break;
			case 1:
				printf("RUNNING MODE 1\n");
				matmul_with_benchmark(argv[1], argv[2], argv[3], PARALLEL_MATMUL_2);
				break;
			case 2:
				printf("RUNNING MODE 2\n");
				matmul_with_benchmark(argv[1], argv[2], argv[3], SEQUNETIAL_MATMUL);
				break;
			default:
				printf("INVALID MODE NUMBER %s\n", argv[4]);
				printf("usage: matmul [MatA] [MatB] [OutMAt] [MODE] \nMODES: \n");
				printf("0: PARALLEL METHOD 1 \n1: PARALLEL METHOD 2 \n2: SEQUENTIAL\n");
			}
	} else if (argc == 4) {
		matmul_with_benchmark(argv[1], argv[2], argv[3], PARALLEL_MATMUL_1);
	} else if (argc == 2) {
		int mode = atoi(argv[1]);
		switch(mode) {
			case 0:
				printf("RUNNING MODE 0\n");
				matmul_with_benchmark("a.txt", "b.txt", "c.txt", PARALLEL_MATMUL_1);
				break;
			case 1:
				printf("RUNNING MODE 1\n");
				matmul_with_benchmark("a.txt", "b.txt", "c.txt", PARALLEL_MATMUL_2);
				break;
			case 2:
				printf("RUNNING MODE 2\n");
				matmul_with_benchmark("a.txt", "b.txt", "c.txt", SEQUNETIAL_MATMUL);
				break;
			default:
				printf("INVALID MODE NUMBER %s\n", argv[1]);
				printf("usage: matmul [MatA] [MatB] [OutMAt] [MODE] \nMODES: \n");
				printf("0: PARALLEL METHOD 1 \n1: PARALLEL METHOD 2 \n2: SEQUENTIAL\n");
			}
	} else {
		printf("usage: matmul [MatA] [MatB] [OutMAt] [MODE] \nMODES: \n");
		printf("0: PARALLEL METHOD 1 \n1: PARALLEL METHOD 2 \n2: SEQUENTIAL\n");
	}
}