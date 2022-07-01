
; System Configuration registers (CFG) definitions
CFG_BASE        EQU     0x40000000      ; Configuration Registers  Base Address
CFG_R0_OFS      EQU     0x00            ; Configuration Register 0       Offset
CFG_PCGR0_OFS   EQU     0x08            ; Periph Clock Gating Register 0 Offset
CFG_PCGR1_OFS   EQU     0x0C            ; Periph Clock Gating Register 1 Offset
CFG_PCGR0_Rst   EQU     0x00000001      ; PCGR0 Peripherals Mask
CFG_PCGR1_Rst   EQU     0x00000000      ; PCGR1 Peripherals Mask

;// <e> Reset all Device Peripherals (except RAM)
PERIPH_RESET    EQU     0
;// </e>


; Enhanced Interrupt Controller (EIC) definitions
EIC_BASE        EQU     0xFFFFFC00      ; EIC Base Address
ICR_OFS         EQU     0x00            ; Interrupt Control Reg. Offset
CIPR_OFS        EQU     0x08            ; Curr. Int. Priority R. Offset
IVR_OFS         EQU     0x18            ; Interrupt Vector Reg. Offset
FIR_OFS         EQU     0x1C            ; Fast Interrupt Reg. Offset
IER0_OFS        EQU     0x20            ; Interrupt Enable Reg. 0 Offset
IER1_OFS        EQU     0x24            ; Interrupt Enable Reg. 1 Offset
IPR0_OFS        EQU     0x40            ; Interrupt Pending Reg. 0 Offset
IPR1_OFS        EQU     0x44            ; Interrupt Pending Reg. 1 Offset
SIR0_OFS        EQU     0x60            ; Source Interrupt Reg. 0 Offset
	
		END