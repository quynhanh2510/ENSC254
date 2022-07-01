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

#include "InitHw.h"
#include "BigFib.h"
#define MAX_SIZE_TEST 1000
#define Heap_Size       /* EQU */    0x00002000
//int mark; 
int mark __attribute__((section(".ARM.__at_0x40000464")));

void halt()
{
	while(0);
}

int main() {

	unsigned *fibResP = NULL;
	int rv;
	unsigned size;
	unsigned lsw;
	
	InitHw(); // Initialize the HW, including the UART for printf()
	printf("BigFib Testing Program\n"); // must write to stdout/printf before below line with __heapstats
	__heapstats((__heapprt)fprintf, stdout);
	
	mark=0;
//
////////////////****************1*****************///////////////////
	rv = bigFib(50, 1, &fibResP);
	lsw = *((fibResP)+1);
	 size=*((fibResP));
	if(rv==0x2f && lsw==0xB11924E1 )
		mark+=15;
	else
	{
	if(rv!=0x2f && lsw!=0xB11924E1 && size!=1)
	{
		mark+=0;
	}
	else
		{
			if(size==1 && rv==0x2f)
				mark+=10;
			else
				mark+=5;
		}	
	}
	
	free(fibResP);
	

		
////////////////****************2*****************///////////////////

rv= bigFib(1, 0, &fibResP);
	 size = *((fibResP));
	if(rv==0)
		mark+=1;
	if(size==0)
		mark+=1;
	
	free(fibResP);
	

	
////////////////*****************3****************///////////////////		

	rv = bigFib(0, 0, &fibResP);	
	size = *((fibResP));
	if(rv==0)
		{mark+=1;}
	if(size==0)
		{mark+=1;}
		
		free(fibResP);
		
		//	////////////////*****************3b****************/////////////////// 
	rv = bigFib(0, 1, &fibResP);
	size = *((fibResP));
	
	if(rv==0)
		{mark+=2;}
	if(size==0)
		{mark+=1;}
	free(fibResP);
 ////////////////*****************4****************///////////////////		
	
	rv = bigFib(1, 1, &fibResP);
	lsw = *((fibResP)+1);
	if(rv==1)
		{mark+=2;}
	if(lsw==1)
		{mark+=1;}
		
		free(fibResP);
////////////////****************5*****************///////////////////	
	rv = bigFib(3, 1, &fibResP);
	lsw = *((fibResP)+1);
	if(rv==3)
		mark+=2;
	if(lsw==2)
		mark+=2;
	
	free(fibResP);
	
	//	////////////////****************5b*****************/////////////////// +3
	rv = bigFib(3, 4, &fibResP);
	lsw =  *((fibResP)+1);
	size = *((fibResP));
	if(rv==3)
		mark+=1;
	if(lsw==2)
		mark+=1;
	if(size==1)
		mark+=1;

	free(fibResP);
	
	//	////////////////****************5c*****************/////////////////// +2
	rv = bigFib(3, 0, &fibResP);
	size = *((fibResP));
	if(rv==0)
		mark+=1;
	if(size==0)
		mark+=1;

	free(fibResP);
////////////////****************6*****************///////////////////	
	rv = bigFib(4, 1, &fibResP);
	lsw = *((fibResP)+1);
	if(rv==4)
		mark+=1;
	if(lsw==3)
		mark+=1;
	
	free(fibResP);

		////////////////***************7******************///////////////////	
	
	rv = bigFib(50, 2, &fibResP);
	lsw = *((fibResP)+1);
	if(rv==0x00000032)
		mark+=3;
	if(lsw==0xEE333961)
		mark+=2;
	free(fibResP);


	
	//	////////////////****************1c*****************///////////////////
	rv = bigFib(-1, 0, &fibResP);
	
	if(rv==-1)
		mark+=1;
	
	if(errno==EINVAL)  {
		mark+=1;
	}

//	////////////////****************1a.ii*****************/////////////////// +2
	rv = bigFib(2, Heap_Size*2, &fibResP);
	
	if(rv==-1)
		mark+=1;
	
	if(errno==ENOMEM) 
		mark+=1;
	

//	////////////////****************1b.ii*****************/////////////////// +2
	rv = bigFib(-2, Heap_Size*2, &fibResP);
	
	if(rv==-1)
		mark+=1;
	
	if(errno==EINVAL)  {
		mark+=1;
	}
	
	////////////////****************2b*****************/////////////////// +3

	rv = bigFib(1, 0, NULL);
	if(rv==-1)
		mark+=2;
	
	if(errno==EINVAL)  {
		mark+=1;
	}	
	


	
	__heapstats((__heapprt)fprintf, stdout);

	
	while(1) {
int x;
x++;
}
//	return rv;
}

