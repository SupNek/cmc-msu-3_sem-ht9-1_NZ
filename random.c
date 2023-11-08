#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "random_source.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

enum
{
    WR_SEED = 1,
    WR_MEM_ALLOC = 2,
    WR_FILE = 3,
    WR_READ = 10,
    SIZE_TO_READ = 64 / 8,
};

double
next_ran(RandomSource *src)
{
    unsigned long long num = 0;
    if (read(src->fd, &num, SIZE_TO_READ) != SIZE_TO_READ) {
        fprintf(stderr, "In random.c: Error, while reading\n");
        exit(WR_READ);
    }
    return ((double) num) / ULLONG_MAX;
}

RandomSource *
destroy_ran(RandomSource *src)
{
    free(src->opt);
    free(src);
    return NULL;
}

RandomSource *
random_random_factory(const char *params)
{
    RandomSource *new = calloc(1, sizeof(*new));
    RandomSourceOperations *op = calloc(1, sizeof(*op));
    if (!new || !op) {
        fprintf(stderr, "In random.c: Error wrong memory allocation\n");
        exit(WR_MEM_ALLOC);
    }
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "In random.c: Error with opening /dev/urandom!\n");
        exit(WR_FILE);
    }
    new->opt = op;
    new->fd = fd;
    new->opt->next = next_ran;
    new->opt->destroy = destroy_ran;
    return new;
}
