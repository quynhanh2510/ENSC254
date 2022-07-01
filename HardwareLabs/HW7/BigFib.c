/******************************************************************************
;@ Name        : BigFib.c
;@ Description : bigFib function for HW5.
;@ Copyright (C) 2021 Craig Scratchley    wcs (at) sfu (dot) ca  
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

typedef unsigned int bigNumN[];

int bigAdd(bigNumN bigN0P, const bigNumN bigN1P, unsigned int maxN0Size);

int bigFib(int n, int maxSize, unsigned **bNP) {

	unsigned* bNb;
	
	if (n < 0 || maxSize < 0 || !bNP) {
			errno = EINVAL;
			return -1;
	}
	bNb = malloc(4*(1 + maxSize));
	if (!bNb) {
		errno = ENOMEM;
		return -1;
	}
	if (n == 0 || maxSize == 0)
	{
		*bNb = 0;
		*bNP = bNb;
		return 0;
	}

	*bNb = 1;
 	*(bNb + 1) = 1;
	if (n == 1) {
		*bNP = bNb;
		return 1;
	}
	{
		int overflow = 0;
		int i = 2;
		unsigned* bNa;
		bNa = malloc(4*(1 + maxSize));
		if (!bNa) {
			free(bNb);
			errno = ENOMEM;
			return -1;
		}
		*bNa = 0;
		__heapstats((__heapprt)fprintf, stdout);

		while(1)
		{
			// a = a + b;
			overflow = bigAdd(bNa, bNb, maxSize);
			if (overflow) {
				*bNP = bNb;
				free(bNa);
				return --i;
			}
			if (i == n) {
				*bNP = bNa;
				free(bNb);
				return i;
			}
			//b = b + a;
			overflow = bigAdd(bNb, bNa, maxSize);
			if (overflow) {
				*bNP = bNa;
				free(bNb);
				return i;
			}
			i += 2;
			if (i > n) {
				*bNP = bNb;
				free(bNa);
				return n;
			}
		}
	}
}

