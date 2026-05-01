.PHONY: all test clean

all: writer

test: writer
	./finder-test.sh

writer: writer.c
	$(CROSS_COMPILE)gcc -Wall -Wextra -pedantic -O3 "$@".c -o "$@"

clean:
	rm -f writer
