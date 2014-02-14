;--------------------------------------------------------
; File Created by C51
; Version 1.0.0 #1034 (Dec 12 2012) (MSVC)
; This file was generated Thu Feb 13 23:36:50 2014
;--------------------------------------------------------
$name pid
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
	public _run_rep
	public _time_step
	public _time
	public _error_step
	public _error_last
	public _s_error
	public _d_error
	public _error
	public _analogs
	public _kd
	public _ki
	public _kp
	public _tape_right
	public _tape_left
	public _sensor_right
	public _sensor_left
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
_sensor_left:
	ds 2
_sensor_right:
	ds 2
_tape_left:
	ds 4
_tape_right:
	ds 4
_kp:
	ds 4
_ki:
	ds 4
_kd:
	ds 4
_analogs:
	ds 4
_error:
	ds 4
_d_error:
	ds 4
_s_error:
	ds 4
_error_last:
	ds 2
_error_step:
	ds 2
_time:
	ds 2
_time_step:
	ds 2
_run_rep_sloc0_1_0:
	ds 4
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
	rseg R_OSEG
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
;	C:\Users\Ben\Documents\UBC\EECE284-rover\code\anaxagoras\pid.c:5: int sensor_left = 0;
	clr	a
	mov	_sensor_left,a
	mov	(_sensor_left + 1),a
;	C:\Users\Ben\Documents\UBC\EECE284-rover\code\anaxagoras\pid.c:6: int sensor_right = 0;
	clr	a
	mov	_sensor_right,a
	mov	(_sensor_right + 1),a
;	C:\Users\Ben\Documents\UBC\EECE284-rover\code\anaxagoras\pid.c:9: double tape_left = 0, tape_right = 0;
	mov	_tape_left,#0x00
	mov	(_tape_left + 1),#0x00
	mov	(_tape_left + 2),#0x00
	mov	(_tape_left + 3),#0x00
;	C:\Users\Ben\Documents\UBC\EECE284-rover\code\anaxagoras\pid.c:9: 
	mov	_tape_right,#0x00
	mov	(_tape_right + 1),#0x00
	mov	(_tape_right + 2),#0x00
	mov	(_tape_right + 3),#0x00
;	C:\Users\Ben\Documents\UBC\EECE284-rover\code\anaxagoras\pid.c:17: int time = 1, time_step; // track number of interations since the start of this error
	mov	_time,#0x01
	clr	a
	mov	(_time + 1),a
	; The linker places a 'ret' at the end of segment R_DINIT.
;--------------------------------------------------------
; code
;--------------------------------------------------------
	rseg R_CSEG
;------------------------------------------------------------
;Allocation info for local variables in function 'run_rep'
;------------------------------------------------------------
;fudge                     Allocated to registers 
;speed_change              Allocated to registers 
;sloc0                     Allocated with name '_run_rep_sloc0_1_0'
;------------------------------------------------------------
;	C:\Users\Ben\Documents\UBC\EECE284-rover\code\anaxagoras\pid.c:20: void run_rep() {
;	-----------------------------------------
;	 function run_rep
;	-----------------------------------------
_run_rep:
	using	0
;	C:\Users\Ben\Documents\UBC\EECE284-rover\code\anaxagoras\pid.c:28: if (analogs[0] > tape_left) {
	mov	dpl,_analogs
	mov	dph,(_analogs + 1)
	lcall	___sint2fs
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
	mov	r5,a
	push	_tape_left
	push	(_tape_left + 1)
	push	(_tape_left + 2)
	push	(_tape_left + 3)
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,r5
	lcall	___fsgt
	mov	r2,dpl
	mov	a,sp
	add	a,#0xfc
	mov	sp,a
	mov	a,r2
	jz	L002002?
;	C:\Users\Ben\Documents\UBC\EECE284-rover\code\anaxagoras\pid.c:29: sensor_left = 1;
	mov	_sensor_left,#0x01
	clr	a
	mov	(_sensor_left + 1),a
	sjmp	L002003?
L002002?:
;	C:\Users\Ben\Documents\UBC\EECE284-rover\code\anaxagoras\pid.c:32: sensor_left = 0;
	clr	a
	mov	_sensor_left,a
	mov	(_sensor_left + 1),a
L002003?:
;	C:\Users\Ben\Documents\UBC\EECE284-rover\code\anaxagoras\pid.c:34: if (analogs[1] > tape_right) {
	mov	dpl,(_analogs + 0x0002)
	mov	dph,((_analogs + 0x0002) + 1)
	lcall	___sint2fs
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
	mov	r5,a
	push	_tape_right
	push	(_tape_right + 1)
	push	(_tape_right + 2)
	push	(_tape_right + 3)
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,r5
	lcall	___fsgt
	mov	r2,dpl
	mov	a,sp
	add	a,#0xfc
	mov	sp,a
	mov	a,r2
	jz	L002005?
;	C:\Users\Ben\Documents\UBC\EECE284-rover\code\anaxagoras\pid.c:35: sensor_right = 1;
	mov	_sensor_right,#0x01
	clr	a
	mov	(_sensor_right + 1),a
	sjmp	L002006?
L002005?:
;	C:\Users\Ben\Documents\UBC\EECE284-rover\code\anaxagoras\pid.c:38: sensor_right = 0;
	clr	a
	mov	_sensor_right,a
	mov	(_sensor_right + 1),a
L002006?:
;	C:\Users\Ben\Documents\UBC\EECE284-rover\code\anaxagoras\pid.c:42: if (sensor_left && sensor_right) error = 0;
	mov	a,_sensor_left
	orl	a,(_sensor_left + 1)
	jz	L002019?
	mov	a,_sensor_right
	orl	a,(_sensor_right + 1)
	jz	L002019?
	mov	_error,#0x00
	mov	(_error + 1),#0x00
	mov	(_error + 2),#0x00
	mov	(_error + 3),#0x00
	sjmp	L002020?
L002019?:
;	C:\Users\Ben\Documents\UBC\EECE284-rover\code\anaxagoras\pid.c:43: else if (sensor_left && !sensor_right) error = -1;
	mov	a,_sensor_left
	orl	a,(_sensor_left + 1)
	jz	L002015?
	mov	a,_sensor_right
	orl	a,(_sensor_right + 1)
	jnz	L002015?
	mov	_error,a
	mov	(_error + 1),a
	mov	(_error + 2),#0x80
	mov	(_error + 3),#0xBF
	sjmp	L002020?
L002015?:
;	C:\Users\Ben\Documents\UBC\EECE284-rover\code\anaxagoras\pid.c:44: else if (!sensor_left && sensor_right) error = 1;
	mov	a,_sensor_left
	orl	a,(_sensor_left + 1)
	jnz	L002011?
	mov	a,_sensor_right
	orl	a,(_sensor_right + 1)
	jz	L002011?
	mov	_error,#0x00
	mov	(_error + 1),#0x00
	mov	(_error + 2),#0x80
	mov	(_error + 3),#0x3F
	sjmp	L002020?
L002011?:
;	C:\Users\Ben\Documents\UBC\EECE284-rover\code\anaxagoras\pid.c:46: if (error_last > 0) error = 5;
	clr	c
	clr	a
	subb	a,_error_last
	clr	a
	xrl	a,#0x80
	mov	b,(_error_last + 1)
	xrl	b,#0x80
	subb	a,b
	jnc	L002008?
	mov	_error,#0x00
	mov	(_error + 1),#0x00
	mov	(_error + 2),#0xA0
	mov	(_error + 3),#0x40
	sjmp	L002020?
L002008?:
;	C:\Users\Ben\Documents\UBC\EECE284-rover\code\anaxagoras\pid.c:47: else error = -5;
	mov	_error,#0x00
	mov	(_error + 1),#0x00
	mov	(_error + 2),#0xA0
	mov	(_error + 3),#0xC0
L002020?:
;	C:\Users\Ben\Documents\UBC\EECE284-rover\code\anaxagoras\pid.c:51: if (error != error_last) {
	mov	dpl,_error_last
	mov	dph,(_error_last + 1)
	lcall	___sint2fs
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
	mov	r5,a
	push	ar2
	push	ar3
	push	ar4
	push	ar5
	mov	dpl,_error
	mov	dph,(_error + 1)
	mov	b,(_error + 2)
	mov	a,(_error + 3)
	lcall	___fseq
	mov	r2,dpl
	mov	a,sp
	add	a,#0xfc
	mov	sp,a
	mov	a,r2
	jnz	L002023?
;	C:\Users\Ben\Documents\UBC\EECE284-rover\code\anaxagoras\pid.c:52: error_step = error_last; // record the error value
	mov	_error_step,_error_last
	mov	(_error_step + 1),(_error_last + 1)
;	C:\Users\Ben\Documents\UBC\EECE284-rover\code\anaxagoras\pid.c:53: time_step = time;
	mov	_time_step,_time
	mov	(_time_step + 1),(_time + 1)
;	C:\Users\Ben\Documents\UBC\EECE284-rover\code\anaxagoras\pid.c:54: time = 1;
	mov	_time,#0x01
	clr	a
	mov	(_time + 1),a
L002023?:
;	C:\Users\Ben\Documents\UBC\EECE284-rover\code\anaxagoras\pid.c:58: d_error = (float) fudge*(float) (error - error_step) / (float) (time + time_step);
	mov	dpl,_error_step
	mov	dph,(_error_step + 1)
	lcall	___sint2fs
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
	mov	r5,a
	push	ar2
	push	ar3
	push	ar4
	push	ar5
	mov	dpl,_error
	mov	dph,(_error + 1)
	mov	b,(_error + 2)
	mov	a,(_error + 3)
	lcall	___fssub
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
	mov	r5,a
	mov	a,sp
	add	a,#0xfc
	mov	sp,a
	push	ar2
	push	ar3
	push	ar4
	push	ar5
	mov	dptr,#0x0000
	mov	b,#0x20
	mov	a,#0x41
	lcall	___fsmul
	mov	_run_rep_sloc0_1_0,dpl
	mov	(_run_rep_sloc0_1_0 + 1),dph
	mov	(_run_rep_sloc0_1_0 + 2),b
	mov	(_run_rep_sloc0_1_0 + 3),a
	mov	a,sp
	add	a,#0xfc
	mov	sp,a
	mov	a,_time_step
	add	a,_time
	mov	dpl,a
	mov	a,(_time_step + 1)
	addc	a,(_time + 1)
	mov	dph,a
	lcall	___sint2fs
	mov	r6,dpl
	mov	r7,dph
	mov	r2,b
	mov	r3,a
	push	ar6
	push	ar7
	push	ar2
	push	ar3
	mov	dpl,_run_rep_sloc0_1_0
	mov	dph,(_run_rep_sloc0_1_0 + 1)
	mov	b,(_run_rep_sloc0_1_0 + 2)
	mov	a,(_run_rep_sloc0_1_0 + 3)
	lcall	___fsdiv
	mov	_d_error,dpl
	mov	(_d_error + 1),dph
	mov	(_d_error + 2),b
	mov	(_d_error + 3),a
	mov	a,sp
	add	a,#0xfc
	mov	sp,a
;	C:\Users\Ben\Documents\UBC\EECE284-rover\code\anaxagoras\pid.c:65: time++;
	inc	_time
	clr	a
	cjne	a,_time,L002046?
	inc	(_time + 1)
L002046?:
;	C:\Users\Ben\Documents\UBC\EECE284-rover\code\anaxagoras\pid.c:68: error_last = error;
	mov	dpl,_error
	mov	dph,(_error + 1)
	mov	b,(_error + 2)
	mov	a,(_error + 3)
	lcall	___fs2sint
	mov	_error_last,dpl
	mov	(_error_last + 1),dph
	ret
	rseg R_CSEG

	rseg R_XINIT

	rseg R_CONST

	CSEG

end
