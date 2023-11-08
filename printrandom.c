#include <stdio.h>
#include <errno.h>
#include "random_source.h"
#include <dlfcn.h>

enum
{
    WR_SEED = 1,
    WR_MEM_ALLOC = 2,
    WR_FILE = 3,
    WR_ARGC = 4,
    WR_NUMC = 5,
    RADIX = 10,
    MAX_COUNT = 100000,
};


int
main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "In printrandom.c: wrong args number\n");
        return WR_ARGC;
    }
    char *eptr = NULL;
    errno = 0;
    void *buf = NULL;
    RandomSource *num_gen = NULL;
    long lval = strtol(argv[2], &eptr, RADIX);
    if (errno || *eptr || eptr == argv[2] || (int) lval != lval || lval > MAX_COUNT || lval < 0) {
        fprintf(stderr, "In printrandom.c: Wrong numbers number!\n");
        return WR_NUMC;
    }
    void *handle = dlopen(NULL, RTLD_LAZY); //
    if (!strncmp(argv[1], "linear.c", sizeof("linear.c"))) {
        buf = dlsym(handle, "random_linear_factory");
        if (!buf) {
            fprintf(stderr, "In printrandom.c: Wrong number generator!\n");
            return WR_NUMGEN;
        }
    } else if (!strncmp(argv[1], "random.c", sizeof("random.c"))) {
        buf = dlsym(handle, "random_random_factory");
        if (!buf) {
            fprintf(stderr, "In printrandom.c: Wrong number generator!\n");
            return WR_NUMGEN;
        }
    }
    num_gen = ((RandomSource * (*)(const char *)) buf(argv[3]);
    for (int i = 0; i < lval; ++i) {
        printf("%.10g\n", num_gen->opt->next(num_gen));
    }
    num_gen->opt->destroy(num_gen);
    return 0;
}