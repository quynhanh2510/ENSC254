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
;@ Name        : bigAdd.s
;@ Description : bigAdd subroutine for Assignment.
;@ 2021   
;@============================================================================

;@ Tabs set for 8 characters in Edit > Configuration

		GLOBAL	bigAdd
		AREA	||.text||, CODE, READONLY
		
bigAdd	
	push	{r3-r9, lr}	;@ push registers into stack

	ldr 	r3, [r0, #0]	;@ sizeBigN0P
	ldr 	r4, [r1, #0] 	;@ sizeBigN1P
	
	mov	r5, #1		;@ index = 1;

	;@ max or min(sizeBigN0P, sizeBigN1P)
	;@ r6 holds max value
	;@ r7 holds min value
	cmp	r3, r4		
	;@sizeBigN0P >= sizeBigN1P
	movhs 	r6, r3		;@sizeBigN0P = max
 	movhs	r7, r4		;@sizeBigN1P = min
	;@sizeBigN0P < sizeBigN1P
	movlo 	r7, r3		;@sizeBigN0P = min
	movlo	r6, r4		;@sizeBigN1P = max

	cmp 	r6, r2		
	bhi	error_condition

	bl	add_upTo_minValue
		
	cmp	r3, r4
	
	beq	CheckIf_SizeBigN0P_equal_maxN0Size
	blhi	sizeBigN0P_greater_sizeBigN1P
	bllo 	sizeBigN0P_lessT_sizeBigN1P

CheckIf_SizeBigN0P_equal_maxN0Size
	cmp	r3, r2

	bne	sizeBigN0P_notEqual_maxN0Size
	beq	done

add_upTo_minValue
;@ calculate the LSB of the result
	adds 	r0, r0, #0	;@clear carry flag
	mrs	r12, CPSR	
loop

	msr	CPSR, r12
	ldr 	r8, [r0, r5, lsl#2]	;@ bigN0[index]
	ldr 	r9, [r1, r5, lsl#2]	;@ bigN1[index]
	adcs	r8, r8, r9		;@ bigN0[index] + bigN1[index]

	str 	r8, [r0, r5, lsl#2]	
	add 	r5, r5, #1
	
	mrs	r12, CPSR		;@ Saves CPSR to r12 so it would not be overwritten by CMP instruction below
	cmp	r5, r7			;@ index <= min value 
	bls	loop
	mov	pc, lr			

sizeBigN0P_lessT_sizeBigN1P
;@ sizeBigN0P < sizeBigN1P
;@ calculate the MSB of the result

	msr	CPSR, r12		;@ Restore the previous value of CPSR from r12

	ldr 	r9, [r1, r5, lsl#2]	;@ the MSB of bigN1[index]
	adcs 	r8, r9, #0		;@ bigN0P[index] = bigN1P[index] + carry;

	str 	r8, [r0, r5, lsl#2]	
	add 	r5, r5, #1
	
	mrs	r12, CPSR		;@ Saves CPSR to r12 so it would not be overwritten by CMP instruction below
	cmp	r5, r4			;@ for loop
	bls	sizeBigN0P_lessT_sizeBigN1P	;@index <= sizeBigN1P 
	
	str	r4, [r0, #0]	;@ sizeBigN0 = sizeBigN1
	mov 	r3, r4			;@ Updates sizeBigN0 in r3, which would then be used later in other parts of program
	mov	pc, lr	

sizeBigN0P_greater_sizeBigN1P
;@ sizeBigN0P >= sizeBigN1P
;@ calculate the MSB of the result

	msr	CPSR, r12		;@ Restore the previous value of CPSR from r12

	bcc	done			;@If no carry, program ends, return 0 in r0

	ldr 	r8, [r0, r5, lsl#2]	;@ the MSB of bigN0[index]
	adcs 	r8, r8, #0		;@ bigN0P[index] += carry;
	str 	r8, [r0, r5, lsl#2]
	add 	r5, r5, #1
	
	mrs	r12, CPSR		;@ Saves CPSR to r12 so it would not be overwritten by CMP instruction below
	cmp	r5, r3			;@ for loop
	bls	sizeBigN0P_greater_sizeBigN1P	;@index <= sizeBigN0P
	mov	pc, lr	

sizeBigN0P_notEqual_maxN0Size
;@sizeBigN0P != maxN0Size

	msr	CPSR, r12		;@ Restore the previous value of CPSR from r12

	mov	r8, #0
	adc 	r8, r8, #0		;@ Set BigN0[index] = carry

	str	r8, [r0, r5, lsl#2]
	adcs	r3, r3, #0		;@ sizeBigN0P = sizeBigN0P + carry and carry flag will be cleared after this one
	mrs	r12, CPSR		;@ Saves CPSR to r12 
	str 	r3, [r0, #0]

	b 	done

error_condition
;@ max(sizeBigN0P, sizeBigN1P) > maxN0Size
	mov	r0, #-1			;@return -1	
	pop	{r3-r9, lr}	;@ pop registers out of stack
	mov	pc, lr
 
done	
	msr	CPSR, r12		;@ Restore the previous value of CPSR from r12
 
	pop	{r3-r9, lr}	;@ pop registers out of stack

;@ Link back to main routine	
	mov 	r0, #0			;@Return carry
	adcs 	r0, r0, #0
 	mov	pc, lr

		end 

