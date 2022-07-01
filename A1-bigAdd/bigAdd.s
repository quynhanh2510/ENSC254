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
;@ Helpers: NONE
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
;@ Name        : bigAdd.s
;@ Description : bigAdd subroutine for Assignment.
;@ 2021   
;@============================================================================

;@ Tabs set for 8 characters in Edit > Configuration

		GLOBAL	bigAdd
		AREA	||.text||, CODE, READONLY
		
bigAdd	

	
	push	{r3-r10, lr}	;@ push registers into stack

	ldr 	r3, [r0, #0]	;@ sizeBigN0P
	ldr 	r4, [r1, #0] 	;@ sizeBigN1P
	
	mov		r5, #1		;@ index = 1;

	;@ max or min(sizeBigN0P, sizeBigN1P)
	;@ r6 holds max value
	;@ r7 holds min value
	cmp		r3, r4		
	;@sizeBigN0P >= sizeBigN1P
	movhs 	r6, r3		;@sizeBigN0P = max
 	movhs	r7, r4		;@sizeBigN1P = min
	;@sizeBigN0P < sizeBigN1P
	movlo 	r7, r3		;@sizeBigN0P = min
	movlo	r6, r4		;@sizeBigN1P = max

	cmp 	r6, r2		
	bhi		error_condition

	bl		add_upTo_minValue
	mrs		r10, CPSR	
	cmp		r3, r4
	
	beq		CheckIf_SizeBigN0P_equal_maxN0Size
	bllo 	sizeBigN0P_lessT_sizeBigN1P
	blhi	sizeBigN0P_greater_sizeBigN1P
	

CheckIf_SizeBigN0P_equal_maxN0Size
	teq		r3, r2

	bne		sizeBigN0P_notEqual_maxN0Size
	beq		done

add_upTo_minValue
;@ calculate the LSB of the result
	adds 	r0, r0, #0	;@clear carry flag
	;mrs		r10, CPSR	
loop

	;msr		CPSR, r10
	
	ldr 	r8, [r0, r5, lsl#2]	;@ bigN0[index]
	ldr 	r9, [r1, r5, lsl#2]	;@ bigN1[index]
	adcs	r8, r8, r9		;@ bigN0[index] + bigN1[index]

	str 	r8, [r0, r5, lsl#2]	
	add 	r5, r5, #1
	
	;mrs		r10, CPSR		;@ Saves CPSR to r10 so it would not be overwritten by CMP instruction below
	teq		r5, r7			;@ index <= min value 
	bne		loop
	beq		r5_Equal_r7
r5_Equal_r7
	ldr 	r8, [r0, r5, lsl#2]	;@ bigN0[index]
	ldr 	r9, [r1, r5, lsl#2]	;@ bigN1[index]
	adcs	r8, r8, r9		;@ bigN0[index] + bigN1[index]

	str 	r8, [r0, r5, lsl#2]	
	add 	r5, r5, #1
	teq		r5, r7	
	
	movne	pc, lr			

sizeBigN0P_lessT_sizeBigN1P
;@ sizeBigN0P < sizeBigN1P
;@ calculate the MSB of the result

	msr		CPSR, r10		;@ Restore the previous value of CPSR from r10
loop2
	ldr 	r9, [r1, r5, lsl#2]	;@ the MSB of bigN1[index]
	adcs 	r8, r9, #0		;@ bigN0P[index] = bigN1P[index] + carry;

	str 	r8, [r0, r5, lsl#2]	
	add 	r5, r5, #1
	
	;mrs		r10, CPSR		;@ Saves CPSR to r10 so it would not be overwritten by CMP instruction below
	teq		r5, r4			
	bne		loop2	;@index <= sizeBigN1P 
	
;	beq		r5_Equal_r4
;r5_Equal_r4
	
	ldreq 	r9, [r1, r5, lsl#2]	;@ the MSB of bigN1[index]
	adcseq 	r8, r9, #0		;@ bigN0P[index] = bigN1P[index] + carry;

	streq 	r8, [r0, r5, lsl#2]	
	addeq 	r5, r5, #1
	
	teq		r5, r4	
	strne	r4, [r0, #0]	;@ sizeBigN0 = sizeBigN1
	movne 	r3, r4			;@ Updates sizeBigN0 in r3, which would then be used later in other parts of program
	movne	pc, lr	

sizeBigN0P_greater_sizeBigN1P
;@ sizeBigN0P >= sizeBigN1P
;@ calculate the MSB of the result

	msr		CPSR, r10		;@ Restore the previous value of CPSR from r10
loop3
	bcc		done			;@If no carry, program ends, return 0 in r0

	ldr 	r8, [r0, r5, lsl#2]	;@ the MSB of bigN0[index]
	adcs 	r8, r8, #0		;@ bigN0P[index] += carry;
	str 	r8, [r0, r5, lsl#2]
	add 	r5, r5, #1
	
	;mrs		r10, CPSR		;@ Saves CPSR to r10 so it would not be overwritten by CMP instruction below
	teq		r5, r3			;
	
	bne		loop3	;@index <= sizeBigN0P
	
	bcc		done			;@If no carry, program ends, return 0 in r0
	ldreq 	r8, [r0, r5, lsl#2]	;@ the MSB of bigN0[index]
	adcseq 	r8, r8, #0		;@ bigN0P[index] += carry;
	streq 	r8, [r0, r5, lsl#2]
	addeq 	r5, r5, #1
	
	;mrs		r10, CPSR		;@ Saves CPSR to r10 so it would not be overwritten by CMP instruction below
	teq		r5, r3			;		
	
	movne	pc, lr	

sizeBigN0P_notEqual_maxN0Size
;@sizeBigN0P != maxN0Size

	;msr		CPSR, r10		;@ Restore the previous value of CPSR from r10

	mov		r8, #0
	adc 	r8, r8, #0		;@ Set BigN0[index] = carry

	str		r8, [r0, r5, lsl#2]
	adcs	r3, r3, #0		;@ sizeBigN0P = sizeBigN0P + carry and carry flag will be cleared after this one
	;mrs		r10, CPSR		;@ Saves CPSR to r10 
	str 	r3, [r0, #0]

	b 		done

error_condition
;@ max(sizeBigN0P, sizeBigN1P) > maxN0Size
	mov		r0, #-1			;@return -1	
	pop		{r3-r10, lr}	;@ pop registers out of stack
	mov		pc, lr
 
done	
	;msr		CPSR, r10		;@ Restore the previous value of CPSR from r10
 
	pop		{r3-r10, lr}	;@ pop registers out of stack

;@ Link back to main routine	
	mov 	r0, #0			;@Return carry
	adcs 	r0, r0, #0
 	mov		pc, lr

		end 

