;@============================================================================
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
;@ Resources:  ___________
;@
;@% Instructions:
;@ * Put your name(s), student number(s), userid(s) in the above section.
;@ * Edit the "Helpers" line and "Resources" line.
;@ * Your group name should be "<userid1>_<userid2>" (eg. stu1_stu2)
;@ * Form groups as described at:  https://courses.cs.sfu.ca/docs/students
;@ * Submit your file to courses.cs.sfu.ca
;@
;@ Name        : assembly.s
;@ Description : bigAdd subroutine for Assignment.
;@ Copyright (C) 2021 Craig Scratchley    wcs (at) sfu (dot) ca  
;@============================================================================

;@ Tabs set for 8 characters in Edit > Configuration

#include "asm_include.h"
#include "73x_tim_l.h"
#include "73x_eic_l.h"

	IMPORT	printf
		
	PRESERVE8

	GLOBAL	FIQ_Init
	GLOBAL	FIQ_Handler
	GLOBAL	InitHwAssembly
	GLOBAL	LoopFnc
	AREA	||.text||, CODE, READONLY


	;@ *** modify the below lines for this assignment  ***
	;@ *** make pins of I/O port 0 strobe back and forth between
	;@     all the Bits in the range Bit 0 to Bit 15 ***
	;@  Turn on GPIO0 pin 0     
LoopFnc	LDR 	R12, =GPIO0_BASE 	

	;@propogating from pin#0 to pin#15
	push	{r3}
	ldr	r3, =GPIO_PIN_0
loopPinIncreasing
	LDRH	R1, [R12, #GPIO_PD_OFS]	//ON
	ORR 	R1, R1, r3
	STRH 	R1, [R12, #GPIO_PD_OFS]
	bl	delay
		
	LDRH	R1, [R12, #GPIO_PD_OFS]	//OFF
	BIC	r1, r1, r3
	STRH 	R1, [R12, #GPIO_PD_OFS]

	mov 	r3, r3, lsl#1
	cmp 	r3, #GPIO_PIN_15
	bls 	loopPinIncreasing
	
	
	;@propogating from pin#14 to pin#0
	ldr	r3, =GPIO_PIN_14
loopPinDecreasing
	LDRH	R1, [R12, #GPIO_PD_OFS]	//ON
	ORR 	R1, R1, r3
	STRH 	R1, [R12, #GPIO_PD_OFS]
	bl	delay
		
	LDRH	R1, [R12, #GPIO_PD_OFS]	//OFF
	BIC	r1, r1, r3
	STRH 	R1, [R12, #GPIO_PD_OFS]

	mov 	r3, r3, lsr#1
	cmp 	r3, #GPIO_PIN_1
	bhs	loopPinDecreasing
	
	B 	LoopFnc
	
	pop	{r3}
	;@ MOV 	PC, LR

InitHwAssembly
	;@  Setup GPIO6 - UART0 Tx pin setup (P6.9)     
	LDR 	R12, =GPIO6_BASE
	;@ GPIO_Mode_AF_PP
	LDRH	R1, [R12, #GPIO_PC0_OFS]
	ORR 	R1, R1, #GPIO_PIN_9
	STRH 	R1, [R12, #GPIO_PC0_OFS]
	
	LDRH 	R1, [R12, #GPIO_PC1_OFS]
	ORR 	R1, R1, #GPIO_PIN_9
	STRH 	R1, [R12, #GPIO_PC1_OFS]
	
	LDRH 	R1, [R12, #GPIO_PC2_OFS]
	ORR 	R1, R1, #GPIO_PIN_9
	STRH 	R1, [R12, #GPIO_PC2_OFS]

	
	;@  Setup GPIO0 - pin#0-15
	LDR 	R12, =GPIO0_BASE
	;@ GPIO_Mode_OUT_PP
	
	push	{r3}
	ldr	r3, =GPIO_PIN_0
LoopInit
	LDRH	R1, [R12, #GPIO_PC0_OFS]
	ORR 	R1, R1, r3
	STRH 	R1, [R12, #GPIO_PC0_OFS]
	
	LDRH 	R1, [R12, #GPIO_PC1_OFS]
	BIC	r1, r1, r3			;@ fill in an instruction to clear bit 0
	STRH 	R1, [R12, #GPIO_PC1_OFS]
	
	LDRH 	R1, [R12, #GPIO_PC2_OFS]
	ORR 	R1, R1, r3
	STRH 	R1, [R12, #GPIO_PC2_OFS]
	
	mov 	r3, r3, lsl#1
	cmp 	r3, #GPIO_PIN_15
	bls 	LoopInit
	
	pop	{r3}
	MOV	PC, LR

	
	// Below needed for HW7 and HW8
	// void* FIQ_Init (void* IRQ_Top);
	// make sure that FIQ_Init returns IRQ_Top in R0
	// FIQ_Init() will initialize R8 through R12 as desired,
	//     so is a non-conforming subroutine in this regard.
FIQ_Init
	// You can put your FIQ_Init here.
	MOV	PC, LR
	
FIQ_Handler
	// You can put your FIQ_Handler here.
	// At that point, you can remove some code from LoopFnc above at top.
	MOV	PC, LR

		
C_str   DCB  "C_string\n",0
	ALIGN	4

delay
	push	{r5}	
	
	mov	R5, #8000
loop1	nop
	sub	r5, r5, #1
	cmp	r5, #1
	bhi 	loop1


	mov	R5, #8000
loop2	nop
	sub	r5, r5, #1
	cmp	r5, #1
	bhi 	loop2
	
	
	mov	R5, #8000
loop3	nop
	sub	r5, r5, #1
	cmp	r5, #1
	bhi 	loop3
	
	mov	R5, #8000
loop4	nop
	sub	r5, r5, #1
	cmp	r5, #1
	bhi 	loop4
	
	mov	R5, #8000
loop5	nop
	sub	r5, r5, #1
	cmp	r5, #1
	bhi 	loop5

	mov	R5, #8000
loop6	nop
	sub	r5, r5, #1
	cmp	r5, #1
	bhi 	loop6
	
	
	pop	{r5}
	mov 	pc, lr		
	
	END
