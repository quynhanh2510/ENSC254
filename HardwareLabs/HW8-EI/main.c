/******************************************************************************/
/* main.C:                                                     */
/* Copyright (C) 2021 Craig Scratchley    wcs (at) sfu (dot) ca  */
/******************************************************************************/

/******************************************************************************/

#include <stdio.h>                      /* Standard input/output functions    */
#include <stdlib.h>

#include "InitHw.h"
#include "BigFib.h"
#define MAX_SIZE_TEST 1000

void InitHwAssembly(void);
void LoopFnc(void);

void halt()
{
	while(1); // make sure there is a breakpoint on this line
}

void FibCalc() {
	unsigned *fibResP = NULL;
	int rv;
	unsigned size;
	unsigned lsw;
	__heapstats((__heapprt)fprintf, stdout);

	rv = bigFib(1000000, MAX_SIZE_TEST, &fibResP);
	lsw =  *((fibResP)+1);
	size = *((fibResP));
	printf("F1000000 requested. F%d was calculated with size %u.\n", rv, size); 
	if(!(rv==0xB40F && lsw==0x05E66262)) //0xB40F  is 46095; F46095=0x...05E66262
			halt();
	
	__heapstats((__heapprt)fprintf, stdout);
	free(fibResP);
	__heapstats((__heapprt)fprintf, stdout);
	
}






int main() {	

	InitHwC(); 				// Start initializing the UART for printf()
	
	// allow the below line to be compiled and run for printf to work properly
	InitHwAssembly();	// Initialize some GPIO blocks, including for UART TX

  printf ("By Your Command\n");

	FibCalc();
	LoopFnc();
}
