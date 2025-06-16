/* alloc.h */
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>
#include <birchutils.h>

#define packed __attribute__((__packed__))
#define unused __attribute__((__unused__))
#define Maxwords ((1024*1024*1024/4)-1)

#define ErrNoMem	1
#define ErrUnknown	2

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;
typedef unsigned long long int int64;
// typedef unsigned _BitInt(128) int128; 
typedef void heap;
typedef int32 word;

struct packed s_header {
	word w:30;
	bool alloced:1;
	bool unused reserved:1;
};
typedef struct packed s_header header;

#define $1 (int8 *)
#define $2 (int16)
#define $4 (int32)
#define $8 (int64)
#define $16 (int128)
#define $c (char *)
#define $i (int)
#define $v (void *)
#define $h (header *)

/*
Use do-while loop so we can use reterr in a fn without {} (loop is considered as a single statement)
and did while(false) so the loop runs only one time
*/ 
#define reterr(x) do { \
	errno = (x); \
	return $v 0; \
} while(false)
#define findblock(x) findblock_((header *)memspace,(x),0)
#define show() show_($h memspace)

void show_(header *);
header *findblock_(header*,word,word);
void *mkalloc(word, header*);
void *alloc(int32);
int main(int,char**);
