#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "random_source.h"

enum
{
    WR_SEED = 1,
    WR_MEM_ALLOC = 2,
    RADIX = 10,
    A = 1103515245,
    C = 12345,
    M = 1U << 31,
};

double
next_lin(RandomSource *src)
{
    src->base = (src->base * A + C) % M;
    return ((double) src->base) / (1ULL << 31);
}

RandomSource *
destroy_lin(RandomSource *src)
{
    free(src->opt);
    free(src);
    return NULL;
}

RandomSource *
random_linear_factory(const char *params)
{
    char *eptr = NULL;
    errno = 0;
    long long lval = strtoll(params, &eptr, RADIX);
    if (errno || *eptr || eptr == params) {
        fprintf(stderr, "In linear.c: Wrong seed!\n");
        exit(WR_SEED);
    }
    RandomSource *new = calloc(sizeof(*new), 1);
    RandomSourceOperations *op = calloc(sizeof(*op), 1);
    if (!new || !op) {
        fprintf(stderr, "In linear.c: error with memory allocation\n");
        exit(WR_MEM_ALLOC);
    }
    new->base = lval % M;
    new->opt = op;
    new->opt->next = next_lin;
    new->opt->destroy = destroy_lin;
    return new;
}
