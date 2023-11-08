all: printrandom

printrandom: printrandom.c random.c linear.c random_source.h
	    $(CC) $(CFLAGS) -g -rdynamic -o $@ $^ -ldl

clean:
	    rm -rf *.o
