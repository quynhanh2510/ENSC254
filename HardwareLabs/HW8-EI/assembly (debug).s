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
	
	
#define moveLEDleft     	0x0
#define moveLEDright    	0x1
#define TIM_clearFLAG_OCB	0xF700

#define INT0Interrupt		0x1
#define	TIM0Interrupt		0x2	
#define	TIM0andINT0Interrupt	0x3

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

LoopFnc	

	MOV 	PC, LR

InitHwAssembly

	;@  Setup GPIO1 - pushbutton switch  (P1.8)     
	LDR 	R12, =GPIO1_BASE
	;@ GPIO_Mode_AF_PP
	LDRH	R1, [R12, #GPIO_PC0_OFS]	//PC0=1
	ORR 	R1, R1, #GPIO_PIN_8
	STRH 	R1, [R12, #GPIO_PC0_OFS]
	
	LDRH 	R1, [R12, #GPIO_PC1_OFS]	//PC1=0
	BIC	r1, r1, #GPIO_PIN_8		
	STRH 	R1, [R12, #GPIO_PC1_OFS]
	
	LDRH 	R1, [R12, #GPIO_PC2_OFS]	//PC2=0
	BIC	R1, R1, #GPIO_PIN_8
	STRH 	R1, [R12, #GPIO_PC2_OFS]


	;@  Setup INT0: INT0 external interrupt to be triggered with a rising edge
	LDR 	R12, =CFG_BASE
	;@ GPIO_Mode_AF_PP
	LDRH	R1, [R12, #CFG_EITE2]		//EITE2=1
	ORR 	R1, R1, #EXTERNAL_IT0
	STRH 	R1, [R12, #CFG_EITE2]
	
	LDRH 	R1, [R12, #CFG_EITE1]		//EITE1=0
	BIC 	R1, R1, #EXTERNAL_IT0		//clear bit0
	STRH 	R1, [R12, #CFG_EITE1]
	
	LDRH 	R1, [R12, #CFG_EITE0]		//EITE0=1
	ORR 	R1, R1, #EXTERNAL_IT0
	STRH 	R1, [R12, #CFG_EITE0]


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
	
	push	{r3}				//index R3 = GPIO_PIN_0 -> GPIO_PIN_15
	ldr	r3, =GPIO_PIN_0
LoopInit
;@ Using loop to initialize GPIO_PC0, GPIO_PC1, GPIO_PC2 of 16 pins (pin0-15)
	LDRH	R1, [R12, #GPIO_PC0_OFS]	//PC0=1	
	ORR 	R1, R1, r3
	STRH 	R1, [R12, #GPIO_PC0_OFS]
	
	LDRH 	R1, [R12, #GPIO_PC1_OFS]	//PC1=0
	BIC	r1, r1, r3			;@ fill in an instruction to clear bit 0
	STRH 	R1, [R12, #GPIO_PC1_OFS]
	
	LDRH 	R1, [R12, #GPIO_PC2_OFS]	//PC2=1
	ORR 	R1, R1, r3
	STRH 	R1, [R12, #GPIO_PC2_OFS]
	
	mov 	r3, r3, lsl#1
	cmp 	r3, #GPIO_PIN_15
	bls 	LoopInit
	
	pop	{r3}
	
	//Reset ECKEN to 0
	//Might want to adjust precscaler division factor (CC7-CC0) = 0x40. If computer is slow, increase this prescaler factor
	//By default, OCAR=OCBR=0x8000 -> square waveform
	//Initialize TIM0
	//Turn on PWM mode:
	//.Set OLVA=1; OLVB=0; OLVA -> OCMPA when Counter = OCAR and OLVB -> OCMPA OCMPA when Counter = OCBR
	//.Set OCAE=1
	//.Set PWM=1;
	//. Select prescaler CC7-CC0, try CC7-CC0=0x40
	
;@Timer 0 (TIM0)
	push	{r8}

	LDR 	R12, =TIM0_BASE 	
	
	
	LDRH	R8, [R12, #TIMn_CR1]		//Reset ECKEN to 0 (not using an external clock)  
	BIC	R8, R8, #TIM_ECK_ENABLE_Mask	
	STRH	R8, [R12, #TIMn_CR1]


	LDRH	R8, [R12, #TIMn_CR2]		//Adjust CC for changing interrupt frequency
	ORR 	R8, R8, #0x0A
	STRH	R8, [R12, #TIMn_CR2]
	
	
	LDRH	R8, [R12, #TIMn_CR1]		//Set PWM in CR1
	ORR 	R8, R8, #TIM_PWM_Mask
	STRH	R8, [R12, #TIMn_CR1]
	
	
	LDRH	R8, [R12, #TIMn_CR1]		//Enable counter (EN in CR1)
	ORR 	R8, R8, #TIM_ENABLE_Mask
	STRH	R8, [R12, #TIMn_CR1]
	
	
	LDRH	R8, [R12, #TIMn_CR2]		//Set OCBIE in CR2
	ORR 	R8, R8, #TIM_IT_OCB
	STRH	R8, [R12, #TIMn_CR2]
	
	
	;@ OCMPA=OLVLA when counter=OCAR
	;@ OCMPA=OLVLB, interrupt occurs
	;@ generating squarewave for PWM
	LDRH	R8, [R12, #TIMn_CR1]		//Set OLVLA=1 or OLVLB=0 in CR1
	ORR 	R8, R8, #TIM_OLVLA_Set_Mask
	STRH	R8, [R12, #TIMn_CR1]
	
	LDRH	R8, [R12, #TIMn_CR1]		//Set OLVLB=0 in CR1
	BIC 	R8, R8, #TIM_OLVLB_Set_Mask
	STRH	R8, [R12, #TIMn_CR1]				
					

	LDRH	R8, [R12, #TIMn_CR1]		//Set OCAE=1 (enable for OCMPA)in CR1
	ORR 	R8, R8, #TIM_OCA_ENABLE_Mask	
	STRH	R8, [R12, #TIMn_CR1]


;@Enhanced Interrupt Controller (EIC)
	LDR 	R12, =EIC_BASE
	
	LDRH	R8, [R12, #EIC_FIER]		    //Set EIC_FIER in EIC
	ORR 	R8, R8, #TIM0andINT0Interrupt	//enable both interrupt channels
	STRH	R8, [R12, #EIC_FIER]
	
	
	LDRH	R8, [R12, #EIC_ICR]		//Set FIQ_EN (global enable bit)
	ORR 	R8, R8, #EIC_FIQEnable_Mask
	STRH	R8, [R12, #EIC_ICR]

	pop	{r8}	
	
	MOV	PC, LR


	// Below needed for HW7 and HW8
	// void* FIQ_Init (void* IRQ_Top);
	// make sure that FIQ_Init returns IRQ_Top in R0
	// FIQ_Init() will initialize R8 through R12 as desired,
	//     so is a non-conforming subroutine in this regard.
FIQ_Init
;@ r0-r7,r15,cpsr are shared with user-mode
	// You can put your FIQ_Init here.
	;@initialize R8 through R12	
	MOV	R9, #0				//R9 is the direction bit: 0 means move LED to the left; 1 means move LED to the right
	MOV	r11, #GPIO_PIN_0 		//index R11 = GPIO_PIN_0 -> GPIO_PIN_15	
	
	MOV	PC, LR
	
FIQ_Handler
	// You can put your FIQ_Handler here.
	// At that point, you can remove some code from LoopFnc above at top.

	push	{r7}				//R7 saves current interrupt type
	LDR 	R12, =EIC_BASE

	LDRH	R8, [R12, #EIC_FIPR]		//Determine if FIQ is from the Timer0 or INT0 or both
	
	CMP	R8, #TIM0Interrupt			//Case1: From Timer0
	LDREQ	R7, =TIM0Interrupt
	BEQ	FIQ_Timer0	
	
	CMP	R8, #INT0Interrupt			//Case2: From INT0
	LDREQ	R7, =INT0Interrupt
	BEQ	FIQ_INT0
	
	CMP	R8, #TIM0andINT0Interrupt		//Case3: From both Timer0 and INT0
	LDREQ	R7, =TIM0andINT0Interrupt
	BEQ	FIQ_INT0
	
	B	ClearInterrupt

FIQ_INT0
	LDR 	R12, =TIM0_BASE 	
	
	LDRH	R8, [R12, #TIMn_CR2]		//Adjust CC for changing interrupt frequency
	ADD	R8, R8, #0x10 			//Add 0x10 to CC to slow down the strobing
	// r8 is stored half-word, so CC wont overflow
	STRH	R8, [R12, #TIMn_CR2]
	CMP	R7, #INT0Interrupt	
	BEQ	ClearInterrupt
	

FIQ_Timer0	
	LDR 	R12, =GPIO0_BASE 

	LDRH	R10, [R12, #GPIO_PD_OFS]	//OFF: clear GPIO_PD
	BIC	R10, R10, R11			//Clear bit
	STRH 	R10, [R12, #GPIO_PD_OFS]	
	
	;@ LED_direction
	cmp 	r11, #GPIO_PIN_0		//Check if changing direction needed (RIGHT->LEFT)
	LDREQ	r9, =moveLEDleft

	cmp 	r11, #GPIO_PIN_15		//Check if changing direction needed (LEFT->Right)
	LDREQ	r9, =moveLEDright
	
	cmp	r9, #moveLEDleft		//Move to left
	moveq	R11, R11, lsl#1	
	
	cmp	r9, #moveLEDright		//Move to right
	moveq	R11, R11, lsr#1			
	
	
	LDRH	R10, [R12, #GPIO_PD_OFS]	//ON: set GPIO_PD
	ORR 	R10, R10, R11
	STRH 	R10, [R12, #GPIO_PD_OFS]
	
ClearInterrupt	
	;@ clear EIC_FIER and EIC_FIPR and OCFB to clear interrupt after 1 cycle
	LDR 	R12, =EIC_BASE
	
	LDRH	R8, [R12, #EIC_FIER]		//Clear EIC_FIER in EIC
	BIC 	R8, R8, #TIM0andINT0Interrupt
	STRH	R8, [R12, #EIC_FIER]
	
	;@ the value read in from EIC_FIPR can just be written back to the register to clear all sources read in
	LDRH	R8, [R12, #EIC_FIPR]		//Clear EIC_FIPR in EIC
	
	CMP	R7, #TIM0Interrupt		//Case1: From Timer0
	LDREQ 	R8, =TIM0Interrupt
	
	CMP	R7, #INT0Interrupt		//Case2: From INT0
	LDREQ 	R8, =INT0Interrupt
	
	CMP	R7, #TIM0andINT0Interrupt	//Case3: From both Timer0 and INT0
	LDREQ 	R8, =TIM0andINT0Interrupt
	
	STRH	R8, [R12, #EIC_FIPR]
	
	pop	{r7}
	
	
	LDR 	R12, =TIM0_BASE 

	LDRH	R8, [R12, #TIMn_SR]		//Clear OCFB in SR
	BIC 	R8, R8, #TIM_FLAG_OCB
	STRH	R8, [R12, #TIMn_SR]
	

	LDR 	R12, =EIC_BASE
	
	LDRH	R8, [R12, #EIC_FIER]		//Set EIC_FIER in EIC:	re-enable to allow the pending bit (EIC_FIPR) to come through in the next cycle
	ORR 	R8, R8, #TIM0andINT0Interrupt
	STRH	R8, [R12, #EIC_FIER]
	
	MOV	PC, LR

C_str   DCB  "C_string\n",0
	ALIGN	4


	
	END
