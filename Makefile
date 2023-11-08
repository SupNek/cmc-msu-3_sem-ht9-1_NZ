all: printrandom

printrandom: main.c random.o linear.o random_source.h
	$(CC) $(CFLAGS) -g -rdynamic -o $@ $^ -ldl $(LDFLAGS)

clean:
	rm -rf *.o