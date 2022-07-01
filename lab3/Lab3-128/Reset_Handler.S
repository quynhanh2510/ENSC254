;@============================================================================
;@ Name         Reset_Handler.s
;@ Description  128-bit Fibonacci calculation
;@ Copyright (C) 2021 Craig Scratchley    wcs (at) sfu (dot) ca  
;@============================================================================

;@ Highly recommended in Edit > Configuration 
;@ Tabs set for 8 characters for ASM files
		
	AREA	||.aRESET||, CODE, READONLY, Align=3
	EXPORT  overfl
	EXPORT  done

	;@ Pointers to the variables
	ldr r0, =prev		;@ prev is 128-bit
	ldr r1, =curr		;@ curr is 128-bit
	
	;@ Load a 128-bit 0 into variable prev and 1 into curr
	mov r2, #0		;@ Constant used for initializing the variables
	str r2, [r0, #0]	;@ Set the value of prev
	str r2, [r0, #4]
	str r2, [r0, #8]
	str r2, [r0, #12]

	str r2, [r1, #0]	;@ Set the value of curr
	str r2, [r1, #4]
	str r2, [r1, #8]
	mov r2, #1		;@ Constant used for initializing LSW of curr
	str r2, [r1, #12]

	;@ What Fibonacci subscript is variable curr holding?
	mov r5, #1

loop	cmp	r5, #185

	beq	done

	bl 	add128		;@ Perform a 128-bit add
		
			;@ *** If our variable curr did not overflow… ***
	addvc 	r5, r5, #1	;@ *** Increment the subscript (in r5), and ***
	bvc	loop	 	;@ ***     branch back to "loop" ***
				
overfl	b 	overfl		;@ Oops, the add overflowed!  Fib number in prev.

done	b 	done		;@ Program done! Loop forever. Fib number in curr.
	
;@ Subroutine to add 128-bit unsigned variables and move one of them. 
;@	curr at r1 moved to prev at r0 and sum put in curr.   
;@ 	Carry flag set if unsigned overflow did occur.
;@	Does not modify r0 or r1.
add128	nop			;@ Do nothing (NO OPeration)
	mov 	r10, lr		;@ *** May need to do something here to help to return ***

;@ We clear the carry flag to begin with.
;@ Start with the least significant word (word 0 at offset 12).
;@ We add all words using a carry.
;@ We set the status flags for subsequent operations.
	
	adds 	r0, r0, #0	;@ Clear the carry flag

	mov 	r2, #12
	bl 	doPart
	
	mov 	r2, #8
	bl 	doPart

	mov 	r2, #4
	bl 	doPart

	mov 	r2, #0
	bl 	doPart
	
;@ *** Complete the 128-bit addition algorithm ***

;@ *** What issue do/might we have returning from subroutine? How can we fix it? 
	mov 	pc, r10		;@ *** Return from subroutine ***
	
;@ Subroutine to load parts of operands, do a 32-bit add, 
;@ 	move curr part into prev part and store
;@ 	the result of the add in place of curr part.
;@	r0 points to the beginning of prev
;@	r1 points to the beginning of curr
;@	<??> is <what ???>
;@ 	Does not modify r0 or r1.

;@ *** Update this subroutine to take another argument so it can
;@     be reused for processing all four words ***
doPart	ldr 	r3,  [r0, r2]	;@ Load a value from prev
	ldr 	r12, [r1, r2]	;@ Load a value from curr	
	str	r12, [r0, r2]	;@    ... move into prev
	;@ 32-bit add
	adcs 	r3,  r3, r12	;@ Add words at r3 with carry, set status flags
	str 	r3,  [r1, r2]	;@ Store the result into curr
	mov	pc,  lr		;@ Return from subroutine

;@ *******************
	AREA myData, DATA, READWRITE, Align=2
;@ variables start at address 0x4000 0000

prev	space 16		;@ Previous Fibonacci value (128-bit) ***
curr	space 16		;@ Current Fibonacci value (128-bit) ***	
	
	END			;@ End of assembly in program file	