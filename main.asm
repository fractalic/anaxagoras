;--------------------------------------------------------
; File Created by C51
; Version 1.0.0 #1034 (Dec 12 2012) (MSVC)
; This file was generated Mon Mar 10 18:50:16 2014
;--------------------------------------------------------
$name main
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
	public _main
	public _timer0_event
	public _time_string
	public _drive_left
	public _drive_right
	public _hundredths
	public _hundredths_count
	public _tenths
	public _tenths_count
	public _right_wheel_pwm
	public _left_wheel_pwm
	public _pwmcount
	public _LCD_setCursor_PARM_2
	public _delay
	public _LCD_write
	public _LCD_writeString
	public _LCD_setCursor
	public _LCD_cmd
	public _LCD_init
	public _LCD_apply
	public _LCD_clock
	public _timer0_init
	public _timer0_restart
	public _reset_time
	public _init_ports
	public _lights
	public _display_time
;--------------------------------------------------------
; Special Function Registers
;--------------------------------------------------------
_ACC            DATA 0xe0
_ADCON0         DATA 0x8e
_ADCON1         DATA 0x97
_ADINS          DATA 0xa3
_ADMODA         DATA 0xc0
_ADMODB         DATA 0xa1
_AD0BH          DATA 0xbb
_AD0BL          DATA 0xa6
_AD0DAT0        DATA 0xc5
_AD0DAT1        DATA 0xc6
_AD0DAT2        DATA 0xc7
_AD0DAT3        DATA 0xf4
_AD1BH          DATA 0xc4
_AD1BL          DATA 0xbc
_AD1DAT0        DATA 0xd5
_AD1DAT1        DATA 0xd6
_AD1DAT2        DATA 0xd7
_AD1DAT3        DATA 0xf5
_AUXR1          DATA 0xa2
_B              DATA 0xf0
_BRGR0          DATA 0xbe
_BRGR1          DATA 0xbf
_BRGCON         DATA 0xbd
_CCCRA          DATA 0xea
_CCCRB          DATA 0xeb
_CCCRC          DATA 0xec
_CCCRD          DATA 0xed
_CMP1           DATA 0xac
_CMP2           DATA 0xad
_DEECON         DATA 0xf1
_DEEDAT         DATA 0xf2
_DEEADR         DATA 0xf3
_DIVM           DATA 0x95
_DPH            DATA 0x83
_DPL            DATA 0x82
_FMADRH         DATA 0xe7
_FMADRL         DATA 0xe6
_FMCON          DATA 0xe4
_FMDATA         DATA 0xe5
_I2ADR          DATA 0xdb
_I2CON          DATA 0xd8
_I2DAT          DATA 0xda
_I2SCLH         DATA 0xdd
_I2SCLL         DATA 0xdc
_I2STAT         DATA 0xd9
_ICRAH          DATA 0xab
_ICRAL          DATA 0xaa
_ICRBH          DATA 0xaf
_ICRBL          DATA 0xae
_IEN0           DATA 0xa8
_IEN1           DATA 0xe8
_IP0            DATA 0xb8
_IP0H           DATA 0xb7
_IP1            DATA 0xf8
_IP1H           DATA 0xf7
_KBCON          DATA 0x94
_KBMASK         DATA 0x86
_KBPATN         DATA 0x93
_OCRAH          DATA 0xef
_OCRAL          DATA 0xee
_OCRBH          DATA 0xfb
_OCRBL          DATA 0xfa
_OCRCH          DATA 0xfd
_OCRCL          DATA 0xfc
_OCRDH          DATA 0xff
_OCRDL          DATA 0xfe
_P0             DATA 0x80
_P1             DATA 0x90
_P2             DATA 0xa0
_P3             DATA 0xb0
_P0M1           DATA 0x84
_P0M2           DATA 0x85
_P1M1           DATA 0x91
_P1M2           DATA 0x92
_P2M1           DATA 0xa4
_P2M2           DATA 0xa5
_P3M1           DATA 0xb1
_P3M2           DATA 0xb2
_PCON           DATA 0x87
_PCONA          DATA 0xb5
_PSW            DATA 0xd0
_PT0AD          DATA 0xf6
_RSTSRC         DATA 0xdf
_RTCCON         DATA 0xd1
_RTCH           DATA 0xd2
_RTCL           DATA 0xd3
_SADDR          DATA 0xa9
_SADEN          DATA 0xb9
_SBUF           DATA 0x99
_SCON           DATA 0x98
_SSTAT          DATA 0xba
_SP             DATA 0x81
_SPCTL          DATA 0xe2
_SPSTAT         DATA 0xe1
_SPDAT          DATA 0xe3
_TAMOD          DATA 0x8f
_TCON           DATA 0x88
_TCR20          DATA 0xc8
_TCR21          DATA 0xf9
_TH0            DATA 0x8c
_TH1            DATA 0x8d
_TH2            DATA 0xcd
_TICR2          DATA 0xc9
_TIFR2          DATA 0xe9
_TISE2          DATA 0xde
_TL0            DATA 0x8a
_TL1            DATA 0x8b
_TL2            DATA 0xcc
_TMOD           DATA 0x89
_TOR2H          DATA 0xcf
_TOR2L          DATA 0xce
_TPCR2H         DATA 0xcb
_TPCR2L         DATA 0xca
_TRIM           DATA 0x96
_WDCON          DATA 0xa7
_WDL            DATA 0xc1
_WFEED1         DATA 0xc2
_WFEED2         DATA 0xc3
;--------------------------------------------------------
; special function bits
;--------------------------------------------------------
_ACC_7          BIT 0xe7
_ACC_6          BIT 0xe6
_ACC_5          BIT 0xe5
_ACC_4          BIT 0xe4
_ACC_3          BIT 0xe3
_ACC_2          BIT 0xe2
_ACC_1          BIT 0xe1
_ACC_0          BIT 0xe0
_ADMODA_7       BIT 0xc7
_ADMODA_6       BIT 0xc6
_ADMODA_5       BIT 0xc5
_ADMODA_4       BIT 0xc4
_ADMODA_3       BIT 0xc3
_ADMODA_2       BIT 0xc2
_ADMODA_1       BIT 0xc1
_ADMODA_0       BIT 0xc0
_BNDI1          BIT 0xc7
_BURST1         BIT 0xc6
_SCC1           BIT 0xc5
_SCAN1          BIT 0xc4
_BNDI0          BIT 0xc3
_BURST0         BIT 0xc2
_SCC0           BIT 0xc1
_SCAN0          BIT 0xc0
_B_7            BIT 0xf7
_B_6            BIT 0xf6
_B_5            BIT 0xf5
_B_4            BIT 0xf4
_B_3            BIT 0xf3
_B_2            BIT 0xf2
_B_1            BIT 0xf1
_B_0            BIT 0xf0
_I2CON_7        BIT 0xdf
_I2CON_6        BIT 0xde
_I2CON_5        BIT 0xdd
_I2CON_4        BIT 0xdc
_I2CON_3        BIT 0xdb
_I2CON_2        BIT 0xda
_I2CON_1        BIT 0xd9
_I2CON_0        BIT 0xd8
_I2EN           BIT 0xde
_STA            BIT 0xdd
_STO            BIT 0xdc
_SI             BIT 0xdb
_AA             BIT 0xda
_CRSEL          BIT 0xd8
_IEN0_7         BIT 0xaf
_IEN0_6         BIT 0xae
_IEN0_5         BIT 0xad
_IEN0_4         BIT 0xac
_IEN0_3         BIT 0xab
_IEN0_2         BIT 0xaa
_IEN0_1         BIT 0xa9
_IEN0_0         BIT 0xa8
_EA             BIT 0xaf
_EWDRT          BIT 0xae
_EBO            BIT 0xad
_ES             BIT 0xac
_ESR            BIT 0xac
_ET1            BIT 0xab
_EX1            BIT 0xaa
_ET0            BIT 0xa9
_EX0            BIT 0xa8
_IEN1_7         BIT 0xef
_IEN1_6         BIT 0xee
_IEN1_5         BIT 0xed
_IEN1_4         BIT 0xec
_IEN1_3         BIT 0xeb
_IEN1_2         BIT 0xea
_IEN1_1         BIT 0xe9
_IEN1_0         BIT 0xe8
_EADEE          BIT 0xef
_EST            BIT 0xee
_ECCU           BIT 0xec
_ESPI           BIT 0xeb
_EC             BIT 0xea
_EKBI           BIT 0xe9
_EI2C           BIT 0xe8
_IP0_7          BIT 0xbf
_IP0_6          BIT 0xbe
_IP0_5          BIT 0xbd
_IP0_4          BIT 0xbc
_IP0_3          BIT 0xbb
_IP0_2          BIT 0xba
_IP0_1          BIT 0xb9
_IP0_0          BIT 0xb8
_PWDRT          BIT 0xbe
_PBO            BIT 0xbd
_PS             BIT 0xbc
_PSR            BIT 0xbc
_PT1            BIT 0xbb
_PX1            BIT 0xba
_PT0            BIT 0xb9
_PX0            BIT 0xb8
_IP1_7          BIT 0xff
_IP1_6          BIT 0xfe
_IP1_5          BIT 0xfd
_IP1_4          BIT 0xfc
_IP1_3          BIT 0xfb
_IP1_2          BIT 0xfa
_IP1_1          BIT 0xf9
_IP1_0          BIT 0xf8
_PADEE          BIT 0xff
_PST            BIT 0xfe
_PCCU           BIT 0xfc
_PSPI           BIT 0xfb
_PC             BIT 0xfa
_PKBI           BIT 0xf9
_PI2C           BIT 0xf8
_P0_7           BIT 0x87
_P0_6           BIT 0x86
_P0_5           BIT 0x85
_P0_4           BIT 0x84
_P0_3           BIT 0x83
_P0_2           BIT 0x82
_P0_1           BIT 0x81
_P0_0           BIT 0x80
_T1             BIT 0x87
_KB7            BIT 0x87
_CMP_1          BIT 0x86
_KB6            BIT 0x86
_CMPREF         BIT 0x85
_KB5            BIT 0x85
_CIN1A          BIT 0x84
_KB4            BIT 0x84
_CIN1B          BIT 0x83
_KB3            BIT 0x83
_CIN2A          BIT 0x82
_KB2            BIT 0x82
_CIN2B          BIT 0x81
_KB1            BIT 0x81
_CMP_2          BIT 0x80
_KB0            BIT 0x80
_P1_7           BIT 0x97
_P1_6           BIT 0x96
_P1_5           BIT 0x95
_P1_4           BIT 0x94
_P1_3           BIT 0x93
_P1_2           BIT 0x92
_P1_1           BIT 0x91
_P1_0           BIT 0x90
_OCC            BIT 0x97
_OCB            BIT 0x96
_RST            BIT 0x95
_INT1           BIT 0x94
_INT0           BIT 0x93
_SDA            BIT 0x93
_T0             BIT 0x92
_SCL            BIT 0x92
_RXD            BIT 0x91
_TXD            BIT 0x90
_P2_7           BIT 0xa7
_P2_6           BIT 0xa6
_P2_5           BIT 0xa5
_P2_4           BIT 0xa4
_P2_3           BIT 0xa3
_P2_2           BIT 0xa2
_P2_1           BIT 0xa1
_P2_0           BIT 0xa0
_ICA            BIT 0xa7
_OCA            BIT 0xa6
_SPICLK         BIT 0xa5
_SS             BIT 0xa4
_MISO           BIT 0xa3
_MOSI           BIT 0xa2
_OCD            BIT 0xa1
_ICB            BIT 0xa0
_P3_7           BIT 0xb7
_P3_6           BIT 0xb6
_P3_5           BIT 0xb5
_P3_4           BIT 0xb4
_P3_3           BIT 0xb3
_P3_2           BIT 0xb2
_P3_1           BIT 0xb1
_P3_0           BIT 0xb0
_XTAL1          BIT 0xb1
_XTAL2          BIT 0xb0
_PSW_7          BIT 0xd7
_PSW_6          BIT 0xd6
_PSW_5          BIT 0xd5
_PSW_4          BIT 0xd4
_PSW_3          BIT 0xd3
_PSW_2          BIT 0xd2
_PSW_1          BIT 0xd1
_PSW_0          BIT 0xd0
_CY             BIT 0xd7
_AC             BIT 0xd6
_F0             BIT 0xd5
_RS1            BIT 0xd4
_RS0            BIT 0xd3
_OV             BIT 0xd2
_F1             BIT 0xd1
_P              BIT 0xd0
_SCON_7         BIT 0x9f
_SCON_6         BIT 0x9e
_SCON_5         BIT 0x9d
_SCON_4         BIT 0x9c
_SCON_3         BIT 0x9b
_SCON_2         BIT 0x9a
_SCON_1         BIT 0x99
_SCON_0         BIT 0x98
_SM0            BIT 0x9f
_FE             BIT 0x9f
_SM1            BIT 0x9e
_SM2            BIT 0x9d
_REN            BIT 0x9c
_TB8            BIT 0x9b
_RB8            BIT 0x9a
_TI             BIT 0x99
_RI             BIT 0x98
_TCON_7         BIT 0x8f
_TCON_6         BIT 0x8e
_TCON_5         BIT 0x8d
_TCON_4         BIT 0x8c
_TCON_3         BIT 0x8b
_TCON_2         BIT 0x8a
_TCON_1         BIT 0x89
_TCON_0         BIT 0x88
_TF1            BIT 0x8f
_TR1            BIT 0x8e
_TF0            BIT 0x8d
_TR0            BIT 0x8c
_IE1            BIT 0x8b
_IT1            BIT 0x8a
_IE0            BIT 0x89
_IT0            BIT 0x88
_TCR20_7        BIT 0xcf
_TCR20_6        BIT 0xce
_TCR20_5        BIT 0xcd
_TCR20_4        BIT 0xcc
_TCR20_3        BIT 0xcb
_TCR20_2        BIT 0xca
_TCR20_1        BIT 0xc9
_TCR20_0        BIT 0xc8
_PLEEN          BIT 0xcf
_HLTRN          BIT 0xce
_HLTEN          BIT 0xcd
_ALTCD          BIT 0xcc
_ALTAB          BIT 0xcb
_TDIR2          BIT 0xca
_TMOD21         BIT 0xc9
_TMOD20         BIT 0xc8
;--------------------------------------------------------
; overlayable register banks
;--------------------------------------------------------
	rbank0 segment data overlay
	rbank1 segment data overlay
;--------------------------------------------------------
; overlayable bit register bank
;--------------------------------------------------------
	rseg BIT_BANK
bits:
	ds 1
	b0 equ  bits.0 
	b1 equ  bits.1 
	b2 equ  bits.2 
	b3 equ  bits.3 
	b4 equ  bits.4 
	b5 equ  bits.5 
	b6 equ  bits.6 
	b7 equ  bits.7 
;--------------------------------------------------------
; internal ram data
;--------------------------------------------------------
	rseg R_DSEG
_LCD_setCursor_PARM_2:
	ds 2
_pwmcount:
	ds 1
_left_wheel_pwm:
	ds 1
_right_wheel_pwm:
	ds 1
_tenths_count:
	ds 4
_tenths:
	ds 4
_hundredths_count:
	ds 4
_hundredths:
	ds 4
_drive_right:
	ds 2
_drive_left:
	ds 2
_time_string:
	ds 8
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
	rseg	R_OSEG
	rseg	R_OSEG
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
	XSEG at 0xffc8
_BODCFG: ds 1
	public _BODCFG
	rseg R_XSEG
	XSEG at 0xffde
_CLKCON: ds 1
	public _CLKCON
	rseg R_XSEG
	XSEG at 0xffe1
_PGACON1: ds 1
	public _PGACON1
	rseg R_XSEG
	XSEG at 0xffe4
_PGACON1B: ds 1
	public _PGACON1B
	rseg R_XSEG
	XSEG at 0xffe3
_PGA1TRIM8X16X: ds 1
	public _PGA1TRIM8X16X
	rseg R_XSEG
	XSEG at 0xffe2
_PGA1TRIM2X4X: ds 1
	public _PGA1TRIM2X4X
	rseg R_XSEG
	XSEG at 0xffca
_PGACON0: ds 1
	public _PGACON0
	rseg R_XSEG
	XSEG at 0xffce
_PGACON0B: ds 1
	public _PGACON0B
	rseg R_XSEG
	XSEG at 0xffcd
_PGA0TRIM8X16X: ds 1
	public _PGA0TRIM8X16X
	rseg R_XSEG
	XSEG at 0xffcc
_PGA0TRIM2X4X: ds 1
	public _PGA0TRIM2X4X
	rseg R_XSEG
	XSEG at 0xffbf
_RTCDATH: ds 1
	public _RTCDATH
	rseg R_XSEG
	XSEG at 0xffbe
_RTCDATL: ds 1
	public _RTCDATL
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
; Reset entry point and interrupt vectors
;--------------------------------------------------------
	CSEG at 0x0000
	ljmp	_crt0
	CSEG at 0x000b
	ljmp	_timer0_event
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
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/pwm.c:30: int drive_right = 0;
	clr	a
	mov	_drive_right,a
	mov	(_drive_right + 1),a
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/pwm.c:31: int drive_left = 0;
	clr	a
	mov	_drive_left,a
	mov	(_drive_left + 1),a
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
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/utilities.c:12: void delay(void)
;	-----------------------------------------
;	 function delay
;	-----------------------------------------
_delay:
	using	0
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/utilities.c:15: for(j=0; j<100; j++)
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
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/utilities.c:17: for(k=0; k<1000; k++);
	mov	r4,#0xE8
	mov	r5,#0x03
L002003?:
	dec	r4
	cjne	r4,#0xff,L002017?
	dec	r5
L002017?:
	mov	a,r4
	orl	a,r5
	jnz	L002003?
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/utilities.c:15: for(j=0; j<100; j++)
	inc	r2
	cjne	r2,#0x00,L002004?
	inc	r3
	sjmp	L002004?
L002008?:
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'LCD_write'
;------------------------------------------------------------
;i                         Allocated to registers 
;------------------------------------------------------------
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:51: void LCD_write(char i) {
;	-----------------------------------------
;	 function LCD_write
;	-----------------------------------------
_LCD_write:
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:52: lcd_dc = 1; // set RS for data
	setb	_P2_7
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:53: lcd_rw = 0; // set RW for write
	clr	_P2_6
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:55: LCD_apply(i);
	lcall	_LCD_apply
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:57: LCD_clock();
	ljmp	_LCD_clock
;------------------------------------------------------------
;Allocation info for local variables in function 'LCD_writeString'
;------------------------------------------------------------
;string                    Allocated to registers r2 r3 r4 
;i                         Allocated to registers r5 r6 
;------------------------------------------------------------
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:62: void LCD_writeString(char *string)
;	-----------------------------------------
;	 function LCD_writeString
;	-----------------------------------------
_LCD_writeString:
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:65: while (string[i] != 0)
	mov	r5,#0x00
	mov	r6,#0x00
L004001?:
	mov	a,r5
	add	a,r2
	mov	r7,a
	mov	a,r6
	addc	a,r3
	mov	r0,a
	mov	ar1,r4
	mov	dpl,r7
	mov	dph,r0
	mov	b,r1
	lcall	__gptrget
	mov	r7,a
	jz	L004004?
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:67: LCD_write(string[i]);
	mov	dpl,r7
	push	ar2
	push	ar3
	push	ar4
	push	ar5
	push	ar6
	lcall	_LCD_write
	pop	ar6
	pop	ar5
	pop	ar4
	pop	ar3
	pop	ar2
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:68: i++;
	inc	r5
	cjne	r5,#0x00,L004001?
	inc	r6
	sjmp	L004001?
L004004?:
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'LCD_setCursor'
;------------------------------------------------------------
;row                       Allocated with name '_LCD_setCursor_PARM_2'
;col                       Allocated to registers r2 r3 
;where                     Allocated to registers r4 r5 
;------------------------------------------------------------
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:74: void LCD_setCursor(int col, int row) // col is column [0,15], row is [0,1]
;	-----------------------------------------
;	 function LCD_setCursor
;	-----------------------------------------
_LCD_setCursor:
	mov	r2,dpl
	mov	r3,dph
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:77: LCD_cmd(0x10); // set cursor home
	mov	dpl,#0x10
	push	ar2
	push	ar3
	lcall	_LCD_cmd
	pop	ar3
	pop	ar2
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:78: for(where = 0; where < (col+row*16); where++)
	mov	r4,_LCD_setCursor_PARM_2
	mov	a,(_LCD_setCursor_PARM_2 + 1)
	swap	a
	anl	a,#0xf0
	xch	a,r4
	swap	a
	xch	a,r4
	xrl	a,r4
	xch	a,r4
	anl	a,#0xf0
	xch	a,r4
	xrl	a,r4
	mov	r5,a
	mov	a,r4
	add	a,r2
	mov	r2,a
	mov	a,r5
	addc	a,r3
	mov	r3,a
	mov	r4,#0x00
	mov	r5,#0x00
L005001?:
	clr	c
	mov	a,r4
	subb	a,r2
	mov	a,r5
	xrl	a,#0x80
	mov	b,r3
	xrl	b,#0x80
	subb	a,b
	jnc	L005005?
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:80: LCD_cmd(0x14);
	mov	dpl,#0x14
	push	ar2
	push	ar3
	push	ar4
	push	ar5
	lcall	_LCD_cmd
	pop	ar5
	pop	ar4
	pop	ar3
	pop	ar2
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:78: for(where = 0; where < (col+row*16); where++)
	inc	r4
	cjne	r4,#0x00,L005001?
	inc	r5
	sjmp	L005001?
L005005?:
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'LCD_cmd'
;------------------------------------------------------------
;i                         Allocated to registers 
;------------------------------------------------------------
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:87: void LCD_cmd(char i) {
;	-----------------------------------------
;	 function LCD_cmd
;	-----------------------------------------
_LCD_cmd:
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:88: lcd_dc = 0; // set RS for command
	clr	_P2_7
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:89: lcd_rw = 0; // set RW for write
	clr	_P2_6
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:92: LCD_apply(i);
	lcall	_LCD_apply
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:93: LCD_clock();
	ljmp	_LCD_clock
;------------------------------------------------------------
;Allocation info for local variables in function 'LCD_init'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:98: void LCD_init() {
;	-----------------------------------------
;	 function LCD_init
;	-----------------------------------------
_LCD_init:
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:99: lcd_enable = 0;
	clr	_P2_5
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:100: delay();
	lcall	_delay
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:101: LCD_cmd(0x30); // wake up
	mov	dpl,#0x30
	lcall	_LCD_cmd
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:102: delay();
	lcall	_delay
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:103: LCD_cmd(0x30); // wake up 2
	mov	dpl,#0x30
	lcall	_LCD_cmd
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:104: delay();
	lcall	_delay
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:105: LCD_cmd(0x30); // wake up 3
	mov	dpl,#0x30
	lcall	_LCD_cmd
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:106: delay();
	lcall	_delay
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:108: LCD_cmd(0x38); // 8bit/2line
	mov	dpl,#0x38
	lcall	_LCD_cmd
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:110: LCD_cmd(0x10); // function set
	mov	dpl,#0x10
	lcall	_LCD_cmd
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:111: LCD_cmd(0x0c); // display on cursor on
	mov	dpl,#0x0C
	lcall	_LCD_cmd
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:112: LCD_cmd(0x06); // set display mode
	mov	dpl,#0x06
	lcall	_LCD_cmd
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:113: delay();
	lcall	_delay
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:114: LCD_cmd(0x01); // clear screen
	mov	dpl,#0x01
	ljmp	_LCD_cmd
;------------------------------------------------------------
;Allocation info for local variables in function 'LCD_apply'
;------------------------------------------------------------
;i                         Allocated to registers r2 
;------------------------------------------------------------
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:120: void LCD_apply(char i) {
;	-----------------------------------------
;	 function LCD_apply
;	-----------------------------------------
_LCD_apply:
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:121: lcd_data_7 = i & 1;
	mov	a,dpl
	mov	r2,a
	rrc	a
	mov	_P2_4,c
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:122: lcd_data_6 = (i >> 1) & 1;
	mov	a,r2
	mov	c,acc.1
	mov	_P2_3,c
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:123: lcd_data_5 = (i >> 2) & 1;
	mov	a,r2
	mov	c,acc.2
	mov	_P2_2,c
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:124: lcd_data_4 = (i >> 3) & 1;
	mov	a,r2
	mov	c,acc.3
	mov	_P2_1,c
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:126: lcd_data_3 = (i >> 4) & 1;
	mov	a,r2
	mov	c,acc.4
	mov	_P2_0,c
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:127: lcd_data_2 = (i >> 5) & 1;
	mov	a,r2
	mov	c,acc.5
	mov	_P1_7,c
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:128: lcd_data_1 = (i >> 6) & 1;
	mov	a,r2
	mov	c,acc.6
	mov	_P1_6,c
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:129: lcd_data_0 = (i >> 7) & 1;
	mov	a,r2
	rlc	a
	mov	_P1_4,c
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'LCD_clock'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:136: void LCD_clock()
;	-----------------------------------------
;	 function LCD_clock
;	-----------------------------------------
_LCD_clock:
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:139: lcd_enable = 1;
	setb	_P2_5
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:140: delay();
	lcall	_delay
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/lcd.c:141: lcd_enable = 0;
	clr	_P2_5
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'timer0_event'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/pwm.c:49: void timer0_event (void) interrupt 1 using 1
;	-----------------------------------------
;	 function timer0_event
;	-----------------------------------------
_timer0_event:
	using	1
	push	bits
	push	acc
	push	b
	push	dpl
	push	dph
	push	(0+2)
	push	(0+3)
	push	(0+4)
	push	(0+5)
	push	(0+6)
	push	(0+7)
	push	(0+0)
	push	(0+1)
	push	psw
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/pwm.c:52: timer0_restart();
	mov	psw,#0x00
	lcall	_timer0_restart
	mov	psw,#0x08
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/pwm.c:55: if(++pwmcount>99) pwmcount=0;
	inc	_pwmcount
	mov	a,_pwmcount
	add	a,#0xff - 0x63
	jnc	L010002?
	mov	_pwmcount,#0x00
L010002?:
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/pwm.c:57: if (drive_left) {
	mov	a,_drive_left
	orl	a,(_drive_left + 1)
	jz	L010004?
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/pwm.c:58: left_wheel=(left_wheel_pwm>pwmcount)?1:0;
	clr	c
	mov	a,_pwmcount
	subb	a,_left_wheel_pwm
	mov	_P3_0,c
L010004?:
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/pwm.c:60: if (drive_right) {
	mov	a,_drive_right
	orl	a,(_drive_right + 1)
	jz	L010006?
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/pwm.c:61: right_wheel = (right_wheel_pwm>pwmcount)?1:0;
	clr	c
	mov	a,_pwmcount
	subb	a,_right_wheel_pwm
	mov	_P3_1,c
L010006?:
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/pwm.c:66: if(++tenths_count>1000){
	mov	a,#0x01
	add	a,_tenths_count
	mov	_tenths_count,a
	clr	a
	addc	a,(_tenths_count + 1)
	mov	(_tenths_count + 1),a
	clr	a
	addc	a,(_tenths_count + 2)
	mov	(_tenths_count + 2),a
	clr	a
	addc	a,(_tenths_count + 3)
	mov	(_tenths_count + 3),a
	clr	c
	mov	a,#0xE8
	subb	a,_tenths_count
	mov	a,#0x03
	subb	a,(_tenths_count + 1)
	clr	a
	subb	a,(_tenths_count + 2)
	clr	a
	xrl	a,#0x80
	mov	b,(_tenths_count + 3)
	xrl	b,#0x80
	subb	a,b
	jnc	L010008?
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/pwm.c:67: tenths_count = 0;
	clr	a
	mov	_tenths_count,a
	mov	(_tenths_count + 1),a
	mov	(_tenths_count + 2),a
	mov	(_tenths_count + 3),a
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/pwm.c:68: tenths++;
	mov	a,#0x01
	add	a,_tenths
	mov	_tenths,a
	clr	a
	addc	a,(_tenths + 1)
	mov	(_tenths + 1),a
	clr	a
	addc	a,(_tenths + 2)
	mov	(_tenths + 2),a
	clr	a
	addc	a,(_tenths + 3)
	mov	(_tenths + 3),a
L010008?:
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/pwm.c:71: if(++hundredths_count>100){
	mov	a,#0x01
	add	a,_hundredths_count
	mov	_hundredths_count,a
	clr	a
	addc	a,(_hundredths_count + 1)
	mov	(_hundredths_count + 1),a
	clr	a
	addc	a,(_hundredths_count + 2)
	mov	(_hundredths_count + 2),a
	clr	a
	addc	a,(_hundredths_count + 3)
	mov	(_hundredths_count + 3),a
	clr	c
	mov	a,#0x64
	subb	a,_hundredths_count
	clr	a
	subb	a,(_hundredths_count + 1)
	clr	a
	subb	a,(_hundredths_count + 2)
	clr	a
	xrl	a,#0x80
	mov	b,(_hundredths_count + 3)
	xrl	b,#0x80
	subb	a,b
	jnc	L010011?
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/pwm.c:72: hundredths_count = 0;
	clr	a
	mov	_hundredths_count,a
	mov	(_hundredths_count + 1),a
	mov	(_hundredths_count + 2),a
	mov	(_hundredths_count + 3),a
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/pwm.c:73: hundredths++;
	mov	a,#0x01
	add	a,_hundredths
	mov	_hundredths,a
	clr	a
	addc	a,(_hundredths + 1)
	mov	(_hundredths + 1),a
	clr	a
	addc	a,(_hundredths + 2)
	mov	(_hundredths + 2),a
	clr	a
	addc	a,(_hundredths + 3)
	mov	(_hundredths + 3),a
L010011?:
	pop	psw
	pop	(0+1)
	pop	(0+0)
	pop	(0+7)
	pop	(0+6)
	pop	(0+5)
	pop	(0+4)
	pop	(0+3)
	pop	(0+2)
	pop	dph
	pop	dpl
	pop	b
	pop	acc
	pop	bits
	reti
;------------------------------------------------------------
;Allocation info for local variables in function 'timer0_init'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/pwm.c:79: void timer0_init (void)
;	-----------------------------------------
;	 function timer0_init
;	-----------------------------------------
_timer0_init:
	using	0
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/pwm.c:82: TR0=0; // Stop timer 0
	clr	_TR0
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/pwm.c:83: TF0=0; // Clear the overflow flag
	clr	_TF0
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/pwm.c:85: TMOD=(TMOD&0xf0)|0x01; // 16-bit timer
	mov	a,#0xF0
	anl	a,_TMOD
	orl	a,#0x01
	mov	_TMOD,a
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/pwm.c:88: timer0_restart();
	lcall	_timer0_restart
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/pwm.c:90: ET0=1; // Enable timer 0 interrupt
	setb	_ET0
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/pwm.c:91: EA=1;  // Enable global interrupts
	setb	_EA
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'timer0_restart'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/pwm.c:96: void timer0_restart()
;	-----------------------------------------
;	 function timer0_restart
;	-----------------------------------------
_timer0_restart:
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/pwm.c:98: TF0=0; // Clear the overflow flag
	clr	_TF0
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/pwm.c:100: TR0=0; // Stop timer 0
	clr	_TR0
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/pwm.c:103: TH0=TIMER0_RELOAD_VALUE/0x100; // upper8 bits
	mov	_TH0,#0xFE
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/pwm.c:104: TL0=TIMER0_RELOAD_VALUE%0x100;
	mov	_TL0,#0x90
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/pwm.c:106: TR0=1; // Start timer 0
	setb	_TR0
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'reset_time'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/pwm.c:111: void reset_time()
;	-----------------------------------------
;	 function reset_time
;	-----------------------------------------
_reset_time:
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/pwm.c:113: tenths = 0;
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\/pwm.c:114: hundredths = 0;
	clr	a
	mov	_tenths,a
	mov	(_tenths + 1),a
	mov	(_tenths + 2),a
	mov	(_tenths + 3),a
	mov	_hundredths,a
	mov	(_hundredths + 1),a
	mov	(_hundredths + 2),a
	mov	(_hundredths + 3),a
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'main'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\main.c:23: void main(void)
;	-----------------------------------------
;	 function main
;	-----------------------------------------
_main:
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\main.c:26: init_ports();
	lcall	_init_ports
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\main.c:29: LCD_init();
	lcall	_LCD_init
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\main.c:31: while(1)
L014002?:
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\main.c:33: lights(0x02);
	mov	dpl,#0x02
	lcall	_lights
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\main.c:35: delay();
	lcall	_delay
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\main.c:37: LCD_writeString("HI");
	mov	dptr,#__str_0
	mov	b,#0x80
	lcall	_LCD_writeString
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\main.c:38: LCD_setCursor(0,1);
	mov	_LCD_setCursor_PARM_2,#0x01
	clr	a
	mov	(_LCD_setCursor_PARM_2 + 1),a
	mov	dptr,#0x0000
	lcall	_LCD_setCursor
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\main.c:39: LCD_writeString("Hello");
	mov	dptr,#__str_1
	mov	b,#0x80
	lcall	_LCD_writeString
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\main.c:41: lights(0x01);
	mov	dpl,#0x01
	lcall	_lights
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\main.c:42: delay();
	lcall	_delay
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\main.c:44: display_time();
	lcall	_display_time
	sjmp	L014002?
;------------------------------------------------------------
;Allocation info for local variables in function 'init_ports'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\main.c:48: void init_ports() {
;	-----------------------------------------
;	 function init_ports
;	-----------------------------------------
_init_ports:
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\main.c:50: P1M1 = 0;
	mov	_P1M1,#0x00
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\main.c:51: P1M2 = 0;
	mov	_P1M2,#0x00
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\main.c:53: P2M1 = 0;
	mov	_P2M1,#0x00
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\main.c:54: P2M2 = 0;
	mov	_P2M2,#0x00
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'lights'
;------------------------------------------------------------
;i                         Allocated to registers r2 
;------------------------------------------------------------
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\main.c:57: void lights(char i) {
;	-----------------------------------------
;	 function lights
;	-----------------------------------------
_lights:
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\main.c:59: light_0 = (i) & 0x01;
	mov	a,dpl
	mov	r2,a
	rrc	a
	mov	_P1_2,c
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\main.c:60: light_1 = (i>>1) & 0x01;
	mov	a,r2
	mov	c,acc.1
	mov	_P1_3,c
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'display_time'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\main.c:64: void display_time()
;	-----------------------------------------
;	 function display_time
;	-----------------------------------------
_display_time:
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\main.c:66: time_string[0] = (char)(tenths%10);
	mov	__modslong_PARM_2,#0x0A
	clr	a
	mov	(__modslong_PARM_2 + 1),a
	mov	(__modslong_PARM_2 + 2),a
	mov	(__modslong_PARM_2 + 3),a
	mov	dpl,_tenths
	mov	dph,(_tenths + 1)
	mov	b,(_tenths + 2)
	mov	a,(_tenths + 3)
	lcall	__modslong
	mov	r2,dpl
	mov	_time_string,r2
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\main.c:67: time_string[1] = (char)(tenths%100);
	mov	__modslong_PARM_2,#0x64
	clr	a
	mov	(__modslong_PARM_2 + 1),a
	mov	(__modslong_PARM_2 + 2),a
	mov	(__modslong_PARM_2 + 3),a
	mov	dpl,_tenths
	mov	dph,(_tenths + 1)
	mov	b,(_tenths + 2)
	mov	a,(_tenths + 3)
	lcall	__modslong
	mov	r2,dpl
	mov	(_time_string + 0x0001),r2
;	C:\Users\Ben\Documents\unison\UBC\EECE284-rover\code\anaxagoras\main.c:68: LCD_writeString(time_string);
	mov	dptr,#_time_string
	mov	b,#0x40
	ljmp	_LCD_writeString
	rseg R_CSEG

	rseg R_XINIT

	rseg R_CONST
__str_0:
	db 'HI'
	db 0x00
__str_1:
	db 'Hello'
	db 0x00

	CSEG

end
