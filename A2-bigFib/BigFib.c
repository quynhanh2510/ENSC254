/******************************************************************************
;@
;@ Student Name 1: Thanh Huy  Ho
;@ Student 1 #: 301385295
;@ Student 1 userid (email): thh1 (thh1@sfu.ca)
;@
;@ Student Name 2: Ngoc Quynh Anh  Vo
;@ Student 2 #: 301391358
;@ Student 2 userid (email): vongocv (vongocv@sfu.ca)
;@
;@ Below, edit to list any people who helped you with the code in this file,
;@      or put ‘none’ if nobody helped (the two of) you.
;@
;@ Helpers: None
;@
;@ Also, reference resources beyond the course textbooks and the course pages on Canvas
;@ that you used in making your submission.
;@
;@ Resources: https://stackoverflow.com/questions/5248219/about-number-of-bits-required-for-fibonacci-number/12440021?fbclid=IwAR3jIeIhE6veb-3D5SOwHks2ZuRcKiX6g1TxorMJuVLjiHrtHmJDYHW-yhA
;@
;@% Instructions:
;@ * Put your name(s), student number(s), userid(s) in the above section.
;@ * Edit the "Helpers" line and "Resources" line.
;@ * Your group name should be "<userid1>_<userid2>" (eg. stu1_stu2)
;@ * Form groups as described at:  https://courses.cs.sfu.ca/docs/students
;@ * Submit your file to courses.cs.sfu.ca
;@
;@ Name        : BigFib.c
;@ Description : bigFib subroutine for HW5.
******************************************************************************/

#include <stdlib.h>
#include <errno.h>

typedef unsigned int bigNumN[];

int bigAdd(bigNumN bigN0P, const bigNumN bigN1P, unsigned int maxN0Size);

int bigFib(int n, int maxSize, unsigned**bNP) {
	if (maxSize <= -1 || n < 0 || bNP == NULL){	//invalid arguments
		errno = EINVAL;
		return -1;
	}
	
	unsigned* bNa = malloc(4*(1 + maxSize)); // allocate memory for bNa

	if (maxSize == 0){	
		*bNa = 0;
		*bNP = bNa;
		return 0;
	}	
	
	if (bNa) { //if allocate memory successful for bNa
		//Initialize bNa=F0
		*bNa = 1;	
		*(bNa+1) = 0;
	
		//Initialize bNb=F1
		unsigned* bNb = malloc(4*(1 + maxSize)); //allocate memory for bNb
		if(bNb == NULL){ // check for null pointer being returned.	
			errno = ENOMEM;
			free(bNa);
			return -1;
		}
		//if allocate memory successful for bNb
		*bNb = 1;
		*(bNb+1) = 1;			

		
		if(n<2){
			if(n==0){
				*bNP = bNa;	//return F0
				free(bNb);
			}
			if(n==1){
				*bNP = bNb;	//return F1
				free(bNa);
			}			
			return n;
		}		
	
		int overflow;
		for(int i=2; i<=n; ++i){
			overflow = bigAdd(bNa, bNb, maxSize); //bigAdd(Fn, Fn+1, maxSize)
			if (!overflow){ 
				*bNP = bNa;	//swap bNa and bNb 
				bNa = bNb;
				bNb = *bNP;
				continue; //do the next iteration
			}
			else {
				free(bNa);
				return i-1;	// largest Fn accurately calculated before overflow occurs
			}
		}
 	}
	
	else {	// check for null pointer being returned.	
		errno = ENOMEM;
		return -1;
	}
	free(bNa);
	return n;
}
