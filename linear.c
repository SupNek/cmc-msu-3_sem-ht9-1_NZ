#include "random_source.h" //

enum
{
    WR_SEED = 1,
    RADIX = 10,
    A = 1103515245,
    C = 12345,
    M = 1 << 31,
};

double base = 0;

double
next(RandomSource *src)
{
    src->base = (src->base*A + C) % M; //double?
    return base;
}

RandomSource *
destroy(RandomSource *src)
{
    free(src->op);
    free(src);
    return NULL;
}

RandomSource *
random_linear_factory(char *seed) {
    char *eptr = NULL;
    errno = 0;
    long long lval = strtoll(str, &eptr, RADIX);
    if (errno || *eptr || eptr == str) {
        fprintf(stderr, "In linear.c: Wrong seed!\n");
        return WR_SEED;
    }
    RandomSource *new = calloc(sizeof(*new), 1);
    RandomSourceOperations *op = calloc(sizeof(*op), 1);
    new->base = lval % M;
    new->opt = op;
    new->opt->next = next;
    new->opt->destroy = destroy;
    return new;
}