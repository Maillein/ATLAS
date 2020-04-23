CFLAGS	= -std=c11 -g -static -Wall -Wextra
SRCS	= $(wildcard *.c)
OBJS	= $(SRCS:.c=.o)

ATLAS: $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

$(OBJS): ATLAS.h

# コマンド
.PHONY: all test clean
.DEFAULT_GOAL := all
all:
	docker run --rm -v $(CURDIR):/ATLAS -w /ATLAS compilerbook make test

test: ATLAS
	./test.sh

clean:
	rm -f ATLAS *.o *~ tmp*
