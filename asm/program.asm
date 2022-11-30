
section .text
	global _program:

_program:

	push	5
	push	2

	pop		r10
	pop		r11
	mov		rax,	r11
	idiv	r10
	mov		r11,	rdx
	push	r11

	pop		r11
	mov		rax,	r11
	ret