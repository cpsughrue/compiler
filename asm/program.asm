
section .text
	global _program:

_program:

	push	3
	push	2
	push	3

	pop		r10
	pop		r11

	; if the exponent is zero
	cmp		r10,	0
	je		zero_exponent_0

	; if exponent is greater than zero
	cmp		r10,	0
	jg		pow_0

	negative_exponent_0:
		mov		rax, 0
		jmp		pow_end_0

	zero_exponent_0:
		mov		rax,	1
		jmp		pow_end_0

	pow_0:

		mov		rax,	r11
		mov		r12,	1

	pow_loop_0:

		cmp		r12,	r10
		je		pow_end_0

		inc		r12
		imul	r11

		jmp		pow_loop_0

	pow_end_0:

		mov	r11,	rax
		push	r11


	pop		r10
	pop		r11

	add		r11,	r10
	push	r11

	pop		r11
	mov		rax,	r11
	ret