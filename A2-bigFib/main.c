/******************************************************************************/
/* BigFib.C:                                                     */
/* Copyright (C) 2020 Craig Scratchley    wcs (at) sfu (dot) ca  */
/******************************************************************************/

/******************************************************************************/

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define Heap_Size       /* EQU */    0x00002000
//#include "asm_include.h"
#include "InitHw.h"
#include "BigFib.h"
#define MAX_SIZE_TEST 1000

void halt()
{
	while(1);
}

int main() {

	unsigned *fibResP = NULL;
	int rv;
	unsigned size;
	unsigned lsw;
	
	InitHw(); // Initialize the HW, including the UART for printf()
	printf("BigFib Testing Program\n"); // must write to stdout/printf before below line with __heapstats
	__heapstats((__heapprt)fprintf, stdout);

	////////////////****************1a.i*****************///////////////////
	rv = bigFib(2, Heap_Size/6, &fibResP);
	if(!(rv==-1 && errno==ENOMEM) ) {
		halt();
	}	
	else
		printf("Test 1a.i: %s\n", strerror(errno));
	
	////////////////****************1a.ii*****************///////////////////
	rv = bigFib(2, Heap_Size*2, &fibResP);
	if(!(rv==-1 && errno==ENOMEM) ) {
		halt();
	}	
	else
		printf("Test 1a.ii: %s\n", strerror(errno));

	////////////////****************1b.i*****************///////////////////
	rv = bigFib(-2, Heap_Size/6, &fibResP);
	if(!(rv==-1 && errno==EINVAL) ) {
		halt();
	}	
	else
		printf("Test 1b.i: %s\n", strerror(errno));

	////////////////****************1b.ii*****************///////////////////
	rv = bigFib(-2, Heap_Size*2, &fibResP);
	if(!(rv==-1 && errno==EINVAL) ) {
		halt();
	}	
	else
		printf("Test 1b.ii: %s\n", strerror(errno));

	////////////////****************1c*****************///////////////////
	rv = bigFib(-1, 0, &fibResP);
	if(!(rv==-1 && errno==EINVAL) ) {
		halt();
	}	
	else
		printf("Test 1c: %s\n", strerror(errno));

	////////////////****************1d*****************///////////////////
	rv = bigFib(1, 0, NULL);
	if(!(rv==-1 && errno==EINVAL) ) {
		halt();
	}	
	else
		printf("Test 1d: %s\n", strerror(errno));
	
	////////////////***************1e******************///////////////////

	rv = bigFib(-2, 1, &fibResP);
	printf("F-2 requested. \n"); 
	if(!(rv==-1 && errno==EINVAL) )  
		halt();
	
	////////////////***************1f******************///////////////////

	rv = bigFib(1, 100000000, &fibResP);
	printf("Maxsize 100000000 requested. \n"); 
	if(!(rv==-1 && errno==ENOMEM) )  
		halt();
	
  ////////////////****************2*****************///////////////////
	rv = bigFib(1, 0, &fibResP);
	size = *((fibResP));
	printf("F1 requested. F%d was calculated with size %u.\n", rv, size); 
	if(!(rv==0x0 && size==0) )
			halt();
	free(fibResP);

	////////////////*****************3****************///////////////////
	rv = bigFib(0, 0, &fibResP);
	size = *((fibResP));
	printf("F0 requested. F%d was calculated with size %u.\n", rv, size); 
	if(!(rv==0x0 && size==0) )
		halt();
	free(fibResP);

	 ////////////////*****************4****************///////////////////
	rv = bigFib(1, 1, &fibResP);
	lsw =  *((fibResP)+1);
	size = *((fibResP));
	printf("F1 requested. F%d was calculated as %u with size %u.\n", rv, lsw, size); 
	if(!(rv==0x1 && lsw==1 && size==1) )
		halt();
	free(fibResP);

	////////////////****************5*****************///////////////////
	rv = bigFib(3, 1, &fibResP);
	lsw =  *((fibResP)+1);
	size = *((fibResP));
	printf("F3 requested. F%d was calculated as %u with size %u.\n", rv, lsw, size); 
	if(!(rv==0x3 && lsw==2 && size==1) )
		halt();
	free(fibResP);

	////////////////****************5b*****************///////////////////
	rv = bigFib(3, 4, &fibResP);
	lsw =  *((fibResP)+1);
	size = *((fibResP));
	printf("F3 requested. F%d was calculated as %u with size %u.\n", rv, lsw, size); 
	if(!(rv==0x3 && lsw==2 && size==1) )
		halt();
	free(fibResP);

	////////////////****************5c*****************///////////////////
	rv = bigFib(3, 0, &fibResP);
	size = *((fibResP));
	if(!(rv==0x0 && size==0) )
		halt();
	free(fibResP);

  ////////////////***************6******************///////////////////

	rv = bigFib(50, 1, &fibResP);
	lsw =  *((fibResP)+1);
	size = *((fibResP));
	printf("F50 requested. F%d was calculated with lsw %u and with size %u.\n", rv, lsw, size); 
	if(!(rv==0x2f && lsw==0xB11924E1 && size==1) ) // 0x2f = 47
		halt();
	free(fibResP);

	////////////////***************7******************///////////////////

	rv = bigFib(1000000, MAX_SIZE_TEST/2, &fibResP);
	lsw =  *((fibResP)+1);
	size = *((fibResP));
	printf("F1000000 requested. F%d was calculated with lsw %u and with size %u.\n", rv, lsw, size); 
	if(!(rv > 0x2f && size==MAX_SIZE_TEST/2) ) // feel free to check other details.
		halt();
	free(fibResP);
	
									//MY TEST CASE//
		
	////////////////****************8*****************///////////////////
	rv = bigFib(1, -1, &fibResP);	//EINVAL case for maxSize <= -1
	size = *((fibResP));
	printf("F1 requested. F%d was calculated with size %u.\n", rv, size); 
	if(!(rv==-1 && errno==EINVAL))
			halt();
	
	////////////////***************9******************///////////////////

	rv = bigFib(100, 2, &fibResP);
	lsw =  *((fibResP)+1);
	size = *((fibResP));
	printf("F100 requested. F%d was calculated with size %u.\n", rv, size);
	if(!(rv==0x5D && lsw==0x221F2702)) // 0x5d is 93 ; F93=12200160415121876738=0xA94FAD42221F2702
		halt();
	free(fibResP);

	////////////////***************10******************///////////////////

	rv = bigFib(150, 3, &fibResP);
	lsw =  *((fibResP)+1);
	size = *((fibResP));
	printf("F150 requested. F%d was calculated with size %u.\n", rv, size);
	if(!(rv==0x8B && lsw==0x87ABB8E5)) // 0x8b is 139 ; F139=50095301248058391139327916261=0xA1DDDCAA3918DA3387ABB8E5
		halt();
	free(fibResP);
	
	////////////////***************11******************///////////////////
	rv = bigFib(300, 5, &fibResP);
	lsw =  *((fibResP)+1);
	size = *((fibResP));
	printf("F300 requested. F%d was calculated with size %u.\n", rv, size);
	if(!(rv==0xE8 && lsw==0xEC7A924B)) // 0xe8 is 232 ; F232=1366619256256991435939546543402365995473880912459=0xEF6153AEA33B505DE49AB936205382BAEC7A924B
		halt();
	free(fibResP);
	
	////////////////***************12******************///////////////////
	rv = bigFib(200, 5, &fibResP);
	lsw =  *((fibResP)+1);
	size = *((fibResP));
	printf("F200 requested. F%d was calculated with size %u.\n", rv, size);
	if(!(rv==0xC8 && lsw==0xDF17E395)) // 0xc8 is 200 ; F200=280571172992510140037611932413038677189525=0x338864A5C1CAEB07D0EF067CB83DF17E395
		halt();
	free(fibResP);
	
	////////////////***************13******************///////////////////
	rv = bigFib(250, 5, &fibResP);
	lsw =  *((fibResP)+1);
	size = *((fibResP));
	printf("250 requested. F%d was calculated with size %u.\n", rv, size);
	if(!(rv==0xE8 && lsw==0xEC7A924B)) // 0xe8 is 232 ; F232=1366619256256991435939546543402365995473880912459=0xEF6153AEA33B505DE49AB936205382BAEC7A924B
		halt();
	free(fibResP);
	
	//	 ////////////////*****************14****************///////////////////
	rv = bigFib(0, 1, &fibResP);
	lsw =  *((fibResP)+1);
	size = *((fibResP));
	printf("F0 requested. F%d was calculated with size %u.\n", rv, size); 
	if(!(rv==0x0 && lsw==0) )
		halt();
	free(fibResP);
	
	////////////////***************15******************///////////////////
	rv = bigFib(300, 6, &fibResP);
	lsw =  *((fibResP)+1);
	size = *((fibResP));
	printf("F300 requested. F%d was calculated with size %u.\n", rv, size);
	if(!(rv==0x116 && lsw==0x31036E09)) // 0x278 is 116 ; F278=5611500259351924431073312796924978741056961814867751431689=0xE4DACBDD268542EA74841C1EEB08F09486D5C7D631036E09
		halt();
	free(fibResP);
	
	//and now ...	
	rv = bigFib(1000000, MAX_SIZE_TEST, &fibResP);
	lsw =  *((fibResP)+1);
	size = *((fibResP));
	printf("F1000000 requested. F%d was calculated with size %u.\n", rv, size); 
	if(!(rv==0xB40F && lsw==0x05E66262)) //0xB40F  is 46095; F46095=0x...05E66262
			halt();
	
	__heapstats((__heapprt)fprintf, stdout);
	free(fibResP);
	__heapstats((__heapprt)fprintf, stdout);
	
	
	while(1);
//	return i;
}


