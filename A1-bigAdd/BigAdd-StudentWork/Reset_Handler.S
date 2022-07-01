;@============================================================================
;@ Name         Reset_Handler.s
;@ Description  Branches to Start subroutine and align ReadOnly Data
;@ Copyright (C) 2021 Craig Scratchley    wcs (at) sfu (dot) ca  
;@============================================================================

;@ Highly recommended in Edit > Configuration 
;@ Set "Auto Indent" to "None"
;@ Tabs set for 8 characters for ASM files
		
	extern Start
	preserve8
	
	;@ Make the alighment relatively large for ReadOnly Data.
	AREA	||.bRODATA||, DATA, READONLY, ALIGN=12
topROD	space	0
;@ *******************
	AREA	||.aRESET||, CODE, READONLY, Align=3
	ENTRY
	GLOBAL	Reset_Handler

Reset_Handler
;	ldr sp, =Stack_Top	;@ Initialize SP just past the end of RAM

;@ ******* The debugger will not highlight lines in this file ******
	b	Start

	LDR	SP, =topROD	;@ this is garbage
	END			;@ End of assembly in program file		