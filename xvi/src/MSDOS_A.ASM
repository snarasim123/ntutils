; Copyright (c) 1990,1991,1992 Chris and John Downey
_TEXT	segment word public 'CODE'
	db	"@(#)msdos_a.asm	2.1 (Chris & John Downey) 7/29/92"
	db	0
_TEXT	ends

;***
;
; program name:
;	xvi
; function:
;	PD version of UNIX "vi" editor, with extensions.
; module name:
;	msdos_a.asm
; module function:
;	Assembly language part of system interface module for MS-DOS.
;
;	This code has been assembled with Microsoft's Macro Assembler
;	(MASM) version 5.1, & is compatible with code generated by
;	MS-DOS C compilers using the normal large memory model calling
;	conventions. This includes the Microsoft & Zortech compilers.
;
;	The ignore_signals() routine installs handlers for keyboard &
;	critical error interrupts. Critical error interrupts are
;	generated for events like trying to access a diskette when
;	there isn't one in the drive, or it isn't formatted, etc. The
;	system's default interrupt handler just displays a message
;	followed by "Abort, Retry, Fail?", which destroys our editing
;	screen, & if the user presses 'a', the current process gets
;	killed without further warning. We don't want this to happen
;	to xvi, so we install our own handler, which just pretends the
;	user chose the "Ignore" option (or "Fail" on MS-DOS 3.0 or
;	later) by returning 0 (for "Ignore") or 3 (for "Fail") in the
;	AL register.
;
;	Note that most MS-DOS system calls, if issued from within a
;	critical error handler, will cause the system to crash
;	(because the system itself isn't re-entrant). 
; history:
;
;	STEVIE - ST Editor for VI Enthusiasts, Version 3.10
;	Originally by Tim Thompson (twitch!tjt)
;	Extensive modifications by Tony Andrews (onecom!wldrdg!tony)
;	Heavily modified by Chris & John Downey
;***

include 8086mm.inc

		public	_msdsignal
		public	_catch_signals
		public	_getchnw
		public	_dup
		public	_dup2

_TEXT		segment word public 'CODE'
		even
;
; Address of interrupt flag.
;
iflagaddr	label	dword
iflagoff	dw	?
iflagseg	dw	?

;
; Major MS-DOS version number.
;
sysversion	db	?

		assume	nothing
		assume	cs:_TEXT
_msdsignal:
		;
		; void msdsignal(unsigned char *flagp);
		;
		; Install interrupt handlers.
		;
		; This routine is called by ignore_signals() with the
		; address of the interrupt flag in flagp.
		;
		mov	bx, sp
		push	ds
		;
		; Store address of interrupt flag.
		;
	if DPTRSIZE eq 4
		lds	ax, ss:[bx + CPTRSIZE]
	else
		mov	ax, [bx + CPTRSIZE]
	endif
		mov	dx, ds
		mov	cx, cs
		mov	ds, cx
		assume	ds: _TEXT
		mov	iflagoff, ax
		mov	iflagseg, dx
		;
		; Get MS-DOS major version number.
		;
		mov	ah, 30h
		int	21h
		mov	sysversion, al
		;
		; Install keyboard interrupt handler.
		;
		mov	dx, offset kbd
		mov	ax, 2523h	; Keyboard interrupt is 23h.
		int	21h
		;
		; Install critical error handler.
		;
		mov	dx, offset criterr
		mov	ax, 2524h	; Critical error interrupt is 24h.
		int	21h
		pop	ds
		assume	ds: nothing
		C_ret

_catch_signals:
		;
		; void catch_signals(void);
		;
		; Set console break flag so that we can be interrupted
		; even when we're not waiting for console input.
		;
		mov	ax, 3301h
		mov	dl, 1
		int	21h
		C_ret

		assume	nothing
		assume	cs: _TEXT

criterr:			; Entry point for critical error interrupts.
		pushf
		sti
		clear	al
		cmp	sysversion, 3
		jb	ignore
		mov	al, 3
ignore:
		popf
		iret
kbd:				; Entry point for keyboard interrupts.
		push	ds
		push	bx
		;
		; Increment interrupt flag.
		;
		lds	bx, iflagaddr
		mov	byte ptr [bx], 1
		pop	bx
		pop	ds
		iret

		assume	nothing
		assume	cs: _TEXT
_getchnw:
		;
		; int getchnw();
		;
		; Return a character from standard input if one is
		; immediately available, otherwise -1.
		;
		mov	dl, 0ffh
		mov	ah, 6
		int	21h
		jz	notavail
		clear	ah
		C_ret
notavail:
		mov	ax, -1
		C_ret

_dup:
		;
		; int dup(int fd);
		;
		; Duplicate file descriptor.
		;
		push	bp
		mov	bp, sp
		mov	bx, [bp + CPTRSIZE + 2]
		mov	ah, 45h
		int	21h
		;
		; Return -1 if CF is set, otherwise new descriptor.
		;
		sbb	bx, bx
		or	ax, bx	; New descriptor is in AX.
		pop	bp
		C_ret

_dup2:
		;
		; int dup2(int fd1, int fd2);
		;
		; Duplicate file descriptor with specified new value.
		;
		push	bp
		mov	bp, sp
		mov	bx, [bp + CPTRSIZE + 2] ; Existing descriptor.
		mov	cx, [bp + CPTRSIZE + 4] ; New descriptor.
		mov	ah, 46h
		int	21h
		;
		; Return -1 if CF is set, otherwise 0.
		;
		sbb	ax, ax
		pop	bp
		C_ret

;
; The following code is untested because neither of us has access to
; an MS-DOS development system at the moment.
;
;			assume	nothing
;			assume	cs: _TEXT
;
;	setdta		proc	near
;			;
;			; Set DOS's Disk Transfer Address to the address
;			; pointed to by ss:bx. This is either a near or far
;			; pointer, depending on what C memory model we're
;			; using.
;			;
;			mov	ah, 1ah
;		if DPTRSIZE eq 2		; Small or medium memory model.
;			mov	dx, [bx]
;			int	21h
;		else
;			push	ds
;			lds	dx, ss:[bx]
;			int	21h
;			pop	ds
;		endif
;			ret
;	setdta		endp
;
;	_statfirst:
;			;
;			; int statfirst(char * name, struct dstat * info,
;			;		int attribute);
;			;
;			; Return information on a named file or the first file
;			; matching a given specification.
;			;
;			; This is like stat(2) on Unix except that it does
;			; pattern matching with '*' & '?' (in the base name
;			; only, not in any directory names). If there are
;			; multiple matches, statfirst() only returns
;			; information on the first one & statnext() can be
;			; called successively for subsequent ones.
;			;
;			; The base name is returned, in capital letters, in
;			; the dstat structure, together with some other
;			; information.
;			;
;			mov	bx, sp
;			add	bx, CPTRSIZE + DPTRSIZE
;			;
;			; ss:bx now points to our struct dstat pointer.
;			;
;			call	setdta
;		if DPTRSIZE eq 2
;			mov	dx, [bx - DPTRSIZE]
;			mov	cx, [bx + DPTRSIZE]
;		else
;			lds	dx, ss:[bx - DPTRSIZE]
;			mov	cx, ss:[bx + DPTRSIZE]
;		endif
;			mov	ah, 4eh
;			int	21h
;			sbb	ax, ax
;			C_ret
;
;	_statnext:
;			;
;			; int statnext(struct dstat *info);
;			;
;			; See above.
;			;
;			mov	bx, sp
;			add	bx, CPTRSIZE
;			;
;			; ss:bx now points to our struct dstat pointer.
;			;
;			call	setdta
;			mov	ah, 4fh
;			int	21h
;			sbb	ax, ax
;			C_ret
_TEXT		ends
		end
