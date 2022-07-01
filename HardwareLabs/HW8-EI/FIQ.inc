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
;@============================================================================
;		IMPORT FIQ_Handler
;		B      FIQ_Handler

#include "asm_include.h" 
#include "73x_tim_l.h" 
#include "73x_eic_l.h"

#define moveLEDleft     	0x0
#define moveLEDright    	0x1

#define INT0Interrupt		0x1
#define	TIM0Interrupt		0x2	
#define	TIM0andINT0Interrupt	0x3

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
	// r8 is stored half-word, so CC won't overflow
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

		LDR     PC, FIQ_Addr

FIQ_Addr        DCD     FIQHandler		