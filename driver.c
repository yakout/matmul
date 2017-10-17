#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

#include "matmul.h"


int main(int argc, char **argv) {
	struct timeval stop, start;
	gettimeofday(&start, NULL); //start checking time
	

	// CODE
	if (argc != 4) {
		printf("%s\n", "usage: matmul MatA MatB OutMAt");
		return 1;
	} 
	
	matmul(argv[1], argv[2], argv[3]);
	//

	gettimeofday(&stop, NULL); //end checking time
	printf("Seconds taken %lu\n", stop.tv_sec - start.tv_sec);
	printf("Microseconds taken: %lu\n", stop.tv_usec - start.tv_usec);
}