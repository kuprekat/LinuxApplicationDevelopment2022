#include <stdio.h>
#include <errno.h>

#define ARGS_ERR 1
#define OPEN_ERR 2
#define READ_ERR 3
#define WRITE_ERR 4
#define CLOSE_ERR 5
#define REMOVE_ERR 6


int main(int argc, char** argv) {
    if (argc > 3) {
        printf("Too many arguments (usage: ./move infile outfile)\n");
        return ARGS_ERR;
    }
    if (argc < 3) {
        printf("Not enough arguments (usage: ./move infile outfile)\n");
        return ARGS_ERR;
    }

    FILE* infile = fopen(argv[1], "r");
    if (!infile) {
        perror("Can't open input file: ");
        return OPEN_ERR;
    }
    

    FILE* outfile = fopen(argv[2], "w");
    if (!outfile) {
        perror("Can't open output file: ");
        if (fclose(infile)) {
            perror("Input file closed with error: ");
        }
        return OPEN_ERR;
    }

    char c;
    int err_code = 0;
    while((c = fgetc(infile)) != EOF) {
    	if (ferror(infile)) {
    	    err_code = READ_ERR;
    	    break;
    	}    
        fputc(c, outfile);
        if (ferror(outfile)) {
    	    err_code = WRITE_ERR;
    	    break;
    	}
    }
    if (errno && err_code != WRITE_ERR) {
        err_code = READ_ERR;
    }
    if (err_code) {
        perror("Error while moving file: ");
    	if (fclose(infile))
            perror("Input file closed with error: ");
        if (fclose(outfile))
            perror("Output file closed with error: ");
        if(remove(argv[2])) {
            perror("Error while removing output file: ");
        }
        return err_code;
    }
    
    if (fclose(infile)) {
        perror("Input file closed with error: ");
        if(remove(argv[2])) {
            perror("Error while removing output file: ");
        }
        return CLOSE_ERR;
    }
    
    if (fclose(outfile)) {
        perror("Output file closed with error: ");
        remove(argv[2]);
        return CLOSE_ERR;
    }
    if(remove(argv[1])) {
        perror("Error while removing input file: ");
        return REMOVE_ERR;
    }


    return 0;
}
