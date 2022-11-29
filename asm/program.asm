
section .text
	global _program:

_program:

	push	3
	push	2

	pop		r10
	pop		r11
	mov		rax,	r11
	imul	r10
	mov		r11,	rax
	push	r11

	pop		r11
	mov		rax,	r11
	ret