
section .text
	global _program:

_program:

	push	-4000
	push	3

	pop		r10
	pop		r11

	add		r11,	r10
	push	r11

	pop		r11
	mov		rax,	r11
	ret