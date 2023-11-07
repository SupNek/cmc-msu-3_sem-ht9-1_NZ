typedef struct RandomSourceOperations {
    RandomSource * (*destroy)(RandomSource *src);
    double (*next)(RandomSource *src); //double при int?
} RandomSourceOperations;

typedef struct RandomSource {
    RandomSourceOperations *opt;
    double base;
} RandomSource;