CC ?= clang 
CFLAGS ?= -Wall -Werror -pedantic -std=c99

.PHONY: clean
all: calc

calc: out/calc.o out/frac.o out/real.o out/stack.o
	$(CC) -o $@ $^ -lm

out/%.o: src/%.c out/primes.h out
	$(CC) $(CFLAGS) -c -I out -o $@ $<

out/primes.h: out/primes out
	$< > $@

out/primes: src/primegenerator.c out
	$(CC) $(CFLAGS) -o $@ $<

out:
	mkdir -p out

clean:
	rm -rf out
	rm calc
