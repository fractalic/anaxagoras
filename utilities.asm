;--------------------------------------------------------
; File Created by C51
; Version 1.0.0 #1034 (Dec 12 2012) (MSVC)
; This file was generated Mon Mar 10 20:21:08 2014
;--------------------------------------------------------
$name utilities
$optc51 --model-small
	R_DSEG    segment data
	R_CSEG    segment code
	R_BSEG    segment bit
	R_XSEG    segment xdata
	R_PSEG    segment xdata
	R_ISEG    segment idata
	R_OSEG    segment data overlay
	BIT_BANK  segment data overlay
	R_HOME    segment code
	R_GSINIT  segment code
	R_IXSEG   segment xdata
	R_CONST   segment code
	R_XINIT   segment code
	R_DINIT   segment code

;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	public _delay
	public _num2char
;--------------------------------------------------------
; Special Function Registers
;--------------------------------------------------------
;--------------------------------------------------------
; special function bits
;--------------------------------------------------------
;--------------------------------------------------------
; overlayable register banks
;--------------------------------------------------------
	rbank0 segment data overlay
;--------------------------------------------------------
; internal ram data
;--------------------------------------------------------
	rseg R_DSEG
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
	rseg	R_OSEG
;--------------------------------------------------------
; indirectly addressable internal ram data
;--------------------------------------------------------
	rseg R_ISEG
;--------------------------------------------------------
; absolute internal ram data
;--------------------------------------------------------
	DSEG
;--------------------------------------------------------
; bit data
;--------------------------------------------------------
	rseg R_BSEG
;--------------------------------------------------------
; paged external ram data
;--------------------------------------------------------
	rseg R_PSEG
;--------------------------------------------------------
; external ram data
;--------------------------------------------------------
	rseg R_XSEG
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	XSEG
;--------------------------------------------------------
; external initialized ram data
;--------------------------------------------------------
	rseg R_IXSEG
	rseg R_HOME
	rseg R_GSINIT
	rseg R_CSEG
;--------------------------------------------------------
; Interrupt vectors
;--------------------------------------------------------
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	rseg R_HOME
	rseg R_GSINIT
	rseg R_GSINIT
;--------------------------------------------------------
; data variables initialization
;--------------------------------------------------------
	rseg R_DINIT
	; The linker places a 'ret' at the end of segment R_DINIT.
;--------------------------------------------------------
; code
;--------------------------------------------------------
	rseg R_CSEG
;------------------------------------------------------------
;Allocation info for local variables in function 'delay'
;------------------------------------------------------------
;j                         Allocated to registers r2 r3 
;k                         Allocated to registers r4 r5 
;------------------------------------------------------------
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\utilities.c:17: void delay(void)
;	-----------------------------------------
;	 function delay
;	-----------------------------------------
_delay:
	using	0
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\utilities.c:20: for(j=0; j<100; j++)
	mov	r2,#0x00
	mov	r3,#0x00
L002004?:
	clr	c
	mov	a,r2
	subb	a,#0x64
	mov	a,r3
	xrl	a,#0x80
	subb	a,#0x80
	jnc	L002008?
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\utilities.c:22: for(k=0; k<100; k++);
	mov	r4,#0x64
	mov	r5,#0x00
L002003?:
	dec	r4
	cjne	r4,#0xff,L002017?
	dec	r5
L002017?:
	mov	a,r4
	orl	a,r5
	jnz	L002003?
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\utilities.c:20: for(j=0; j<100; j++)
	inc	r2
	cjne	r2,#0x00,L002004?
	inc	r3
	sjmp	L002004?
L002008?:
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'num2char'
;------------------------------------------------------------
;number                    Allocated to registers 
;------------------------------------------------------------
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\utilities.c:29: char num2char(unsigned short number)
;	-----------------------------------------
;	 function num2char
;	-----------------------------------------
_num2char:
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\utilities.c:31: return (char)((number % 10) + 48);
	mov	__moduint_PARM_2,#0x0A
	clr	a
	mov	(__moduint_PARM_2 + 1),a
	lcall	__moduint
	mov	r2,dpl
	mov	a,#0x30
	add	a,r2
	mov	dpl,a
	ret
	rseg R_CSEG

	rseg R_XINIT

	rseg R_CONST

	CSEG

end
