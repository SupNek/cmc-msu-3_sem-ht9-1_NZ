random.o:
	$(CC) -c random.c

linear.o:
	$(CC) -c linear.c

printrandom.o:
	$(CC) -c printrandom.c

all: printrandom
	$(CC) $(CFLAGS) -rdynamic printrandom.o random.o linear.o random_source.h -o ^@ $(LDFLAGS) $(LD)
