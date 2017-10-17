#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

#include "matmul.h"


int main(int argc, char **argv) {
	struct timeval stop, start;
	// gettimeofday(&start, NULL); //start checking time
	
	generate_matrix("a.txt", 200, 100);
	generate_matrix("b.txt", 100, 300);

	// CODE
	if (argc == 1) {
		// use defaults
		// gettimeofday(&start, NULL); //start checking time
		// matmul("a.txt", "b.txt", "c.txt", PARALLEL_MATMUL_1);
		// gettimeofday(&stop, NULL); //end checking time
		// printf("Seconds taken %lu\n", stop.tv_sec - start.tv_sec);
		// printf("PARALLEL_MATMUL_1 MODE: Microseconds taken: %lu\n", stop.tv_usec - start.tv_usec);

		// gettimeofday(&start, NULL); //start checking time
		// matmul("a.txt", "b.txt", "c.txt", PARALLEL_MATMUL_2);
		// gettimeofday(&stop, NULL); //end checking time
		// printf("Seconds taken %lu\n", stop.tv_sec - start.tv_sec);
		// printf("PARALLEL_MATMUL_2 MODE: Microseconds taken: %lu\n", stop.tv_usec - start.tv_usec);

		// gettimeofday(&start, NULL); //start checking time
		// matmul("a.txt", "b.txt", "c.txt", SEQUNETIAL_MATMUL);
		// gettimeofday(&stop, NULL); //end checking time
		// printf("Seconds taken %lu\n", stop.tv_sec - start.tv_sec);
		// printf("SEQUNETIAL_MATMUL MODE: Microseconds taken: %lu\n", stop.tv_usec - start.tv_usec);
	} else if (argc != 4) {
		printf("%s\n", "usage: matmul MatA MatB OutMAt");
		return 1;
	} else {
		matmul(argv[1], argv[2], argv[3], PARALLEL_MATMUL_1);
	}
	//

	// gettimeofday(&stop, NULL); //end checking time
	// printf("Seconds taken %lu\n", stop.tv_sec - start.tv_sec);
	// printf("Microseconds taken: %lu\n", stop.tv_usec - start.tv_usec);
}