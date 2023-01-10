#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>

typedef int (*rmv_t)(const char* infile);

int remove(const char* infile) {
    rmv_t rmv; 
    if (strstr(infile, "PROTECT"))
        return 0;
    rmv = (rmv_t)dlsym(RTLD_NEXT,"remove");
    return rmv(infile);
 }
