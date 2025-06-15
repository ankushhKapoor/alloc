/* alloc.c */
#include "alloc.h"

extern heap *memspace;

header *findblock_(header *hdr, word allocation, word n) {
	bool ok;
	void *mem;
	header *hdr_;
	word n_;

	if ((n+allocation) > (Maxwords-2))
		reterr(ErrNoMem);

	ok = (!(hdr->w)) ? true :
		(!(hdr->alloced) && (hdr->w >= allocation)) ? true :
		false;

	if (ok)
		return hdr;
	else {
		mem = $v hdr + (hdr->w*4) + 4;
		hdr_ = $h mem;
		n_ = n + hdr->w;

		return findblock_(hdr_, allocation, n_);
	}

	reterr(ErrUnknown);
}

void *mkalloc(word words, header *hdr) {
	void *ret;
	// void *bytesin;
	word wordsin;

	wordsin = ((word *)hdr - (word *)memspace) + 1;

	// Invalid pointer arithemetic (Done for GCC but not actually recommended) -by Jonas Birch
	// void has byte granularity in GCC
	// bytesin = ($v (($v hdr) - memspace));
	// wordsin = (((word)bytesin)/4)+1;

	if (words > (Maxwords-wordsin))
		reterr(ErrNoMem);

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
		if (words > Maxwords)
			reterr(ErrNoMem);

		mem = mkalloc(words, hdr);
		if(!mem	)
			return $v 0;

		return mem;

	} else
		(void)0;

	return $v 0;
}

int main(int argc, char *argv[]) {
	header *hdr;
	int8 *p;

	p = alloc(7);
	printf("Allocated 0x%x\n", $i p);

	hdr = findblock(500);
	if(!hdr) {
		printf("Error %d \n", errno);

		return -1;
		
	}
	printf("Memspace = 0x%x\n", $i memspace);
	printf("Block = 0x%x\n", $i hdr);
	
	return 0;
}