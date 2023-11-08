all: printrandom

printrandom: main.c random.c linear.c random_source.h
	$(CC) $(CFLAGS) -g -rdynamic -o $@ $^ -ldl $(LDFLAGS)

clean:
	rm -rf *.o