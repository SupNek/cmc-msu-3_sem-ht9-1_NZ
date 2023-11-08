typedef struct RandomSource RandomSource;

typedef struct RandomSourceOperations {
    RandomSource * (*destroy)(RandomSource *src);
    double (*next)(RandomSource *src);
} RandomSourceOperations;

typedef struct RandomSource {
    RandomSourceOperations *opt;
    unsigned long long base;
    int fd;
} RandomSource;
