;@============================================================================
;@
;@ Name        : bigAdd.s
;@ Description : bigAdd subroutine 
;@ Copyright (C) 2021 Craig Scratchley    wcs (at) sfu (dot) ca  
;@============================================================================

;@ Tabs set for 8 characters in Edit > Configuration

		GLOBAL	bigAdd
		AREA	||.text||, CODE, READONLY
		
bigAdd		ldr	r12, [r1]		;@ r12 now holds const arg size
		ldr	r3, [r0]		;@ r3 now holds non-const arg size
		cmp	r3, r12
		bhs	HS			;@ unsigned higher or same.  
	
		;@ r0 points to smaller size (r3) than r1 points to (r12)
		cmp 	r12, r2			;@ was r2 too small?
		movhi	r0, #-1			;@ perhaps we should have 'bls cont' here
		movhi	pc, lr

		push	{r4-r7}
		;@ move max size (max of r3, r12) +1 to r5
		add 	r5, r12, #1
		;@ move min size (min of r3, r12) +1 to r4 and clear carry flag
		adds	r4, r3, #1
		mov	r7, #1			;@ r7 holds index register		
		teq	r7, r4			
		beq	ExitL1			;@ branch if index equal to min + 1

L1		ldr	r6, [r0, r7, lsl #2]
		ldr	r3, [r1, r7, lsl #2]
		adcs	r6, r6, r3
		str	r6, [r0, r7, lsl #2]
		add	r7, r7, #1
		teq	r7, r4
		bne	L1

ExitL1		teq	r7, r5			;@ branch if index equal to max + 1
		beq	ExitL2

L2		ldr	r6, [r1, r7, lsl #2]
		adcs	r6, r6, #0
		str	r6, [r0, r7, lsl #2]
		add	r7, r7, #1
		teq	r7, r5
		bne	L2

ExitL2		bcc	leave

		;@ put final carry flag in r6
		mov	r6, #1
		teq	r2, r12			;@ equal (eq) if at the max size
		strne	r6, [r0, r7, lsl #2] 
		addne	r12, r12, r6 		;@ possible expand output size
		str	r12, [r0]
		
		;@ overflow return value
		movne	r0, #0			;@ 0 if not maxSize
		moveq	r0, r6			;@ if maxSize: r6 (holding carry value)
		pop	{r4-r7}
		mov	pc, lr

leave		str	r12, [r0]
		mov	r0, #0
		pop	{r4-r7}
		mov	pc, lr

		;@ r0 points to size higher than or same as what r1 points to
HS		cmp 	r3, r2			;@ was r2 too small?
		movhi	r0, #-1
		movhi	pc, lr

		push	{r4-r7}
		;@ move max size (max of r3, r12) +1 to r5
		add	r5, r3, #1
		;@ move min size (min of r3, r12) +1 to r4 and clear carry flag
		adds	r4, r12, #1		;@ also clear carry flag
		mov	r7, #1			;@ r7 holds index register
		teq	r7, r4			
		beq	ExitL1b			;@ branch if index equal to min + 1

L1b		ldr	r6, [r0, r7, lsl #2]
		ldr	r12, [r1, r7, lsl #2]
		adcs	r6, r6, r12
		str	r6, [r0, r7, lsl #2]
		add	r7, r7, #1
		teq	r7, r4
		bne	L1b

ExitL1b		bcc	leaveb

L3		teq	r7, r5			;@ carry is set
		beq	ExitL3

		ldr	r6, [r0, r7, lsl #2]
		adcs	r6, r6, #0
		str	r6, [r0, r7, lsl #2]
		add	r7, r7, #1
		bcs	L3 			;@ dont need to continue if there is no carry.

leaveb		mov	r0, #0;
		pop	{r4-r7}
		mov	pc, lr

ExitL3		;@ put final carry flag in r6
		mov	r6, #1			;@ carry is set
		teq	r2, r3			;@ equal (eq) if at the max size
		strne	r6, [r0, r7, lsl #2] 
		addne	r3, r3, r6 		;@ possible expand output size
		strne	r3, [r0]
		
		;@ overflow return value
		movne	r0, #0			;@ 0 if not maxSize
		moveq	r0, r6			;@ if maxSize: r6 (holding carry value)
		pop	{r4-r7}
		mov	pc, lr

		end
