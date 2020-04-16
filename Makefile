CFLAGS=-std=c11 -g -static

ATLAS: main.c

test: ATLAS
	./test.sh

clean:
	rm -f ATLAS *.o *~ tmp*

.PHONY: test clean
