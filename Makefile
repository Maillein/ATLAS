CFLAGS = -std=c11 -g -static

ATLAS: ATLAS.c

# コマンド
.PHONY: all test clean
.DEFAULT_GOAL := all
all:
	docker run --rm -v $(CURDIR):/ATLAS -w /ATLAS compilerbook make test

test: ATLAS
	./test.sh

clean:
	rm -f ATLAS *.o *~ tmp*
