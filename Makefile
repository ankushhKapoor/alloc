flags=-m32 -O2 -Wall -std=c2x
ldflags=-L$(HOME)/tools/birchutils -l:birchutils32.so

.PHONY: clean

all: clean alloc

alloc: alloc.o heap.o
	cc $(flags) $^ -o $@ $(ldflags)

alloc.o: alloc.c alloc.h
	cc $(flags) -c $<

heap.o: heap.asm
	nasm -f elf32 $^

clean:
	rm -f *.o alloc
