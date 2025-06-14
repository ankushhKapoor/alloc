/* alloc.c */
#include "alloc.h"

extern heap *memspace;

void *mkalloc(word words, header *hdr) {
	void *ret;
	// void *bytesin;
	word wordsin;

	wordsin = ((word *)hdr - (word *)memspace) + 1;

	// Invalid pointer arithemetic (Done for GCC but not actually recommended) -by Jonas Birch
	// void has byte granularity in GCC
	// bytesin = ($v (($v hdr) - memspace));
	// wordsin = (((word)bytesin)/4)+1;

	if (words > (Maxwords-wordsin)) {
		reterr(ErrNoMem);
	}

	hdr->w = words;
	hdr->alloced = true;
	ret = (void *)((char *)hdr + 4); 
	
	return ret;
	// ret = ($v hdr)+4;

}

void *alloc(int32 bytes) {
	word words;
	header *hdr;
	void *mem;

	words = (!(bytes % 4)) ?
		bytes/4 :
		(bytes/4) + 1;

	mem = $v memspace;	
	hdr = $h mem;

	if (!(hdr->w)) {
		if (words > Maxwords) {
			reterr(ErrNoMem);
		}

		//If hdr ka w is empty i.e. pehle se koi initialised memmory nahi hai to call mkalloc
		mem = mkalloc(words, hdr);
		if(!mem	)
			return $v 0;

		return mem;

	} else {
		(void)0;
	}

	return $v 0;
}

int main(int argc, char *argv[]) {
	int8 *p;

	p = alloc(7);
	printf("0x%x\n", $i p);

	return 0;
}
