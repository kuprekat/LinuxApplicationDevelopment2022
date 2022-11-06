#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int start, end, step;
	step = 1;
	start = 0;
	switch(argc) {
		case 2:
			end = atoi(argv[1]);
			break;	
		case 3:
			start = atoi(argv[1]);
			end = atoi(argv[2]);
			break;
		case 4:
			start = atoi(argv[1]);
			end = atoi(argv[2]);
			step = atoi(argv[3]);
			break;
		default:
			printf("Use 1-3 parameters:\n");
			printf("./range N for [0, 1, ..., N-1]\n");
			printf("./range M, N for [M-1, ..., N-1]\n");
			printf("./range M, N, S for [M, M+S, M+2S,...,N-1]\n");
	}
	if (argc != 1)
		for(int i = start; i < end; i+=step)
			printf("%d\n", i);
	return 0;
}
