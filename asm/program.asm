
section .text
	global _program:

_program:

	push	4
	push	2

	pop		r10
	pop		r11

	cmp		r10,	0
	jne		pow_0

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

	push	6
	push	2

	pop		r10
	pop		r11

	cmp		r10,	0
	jne		pow_1

	mov		rax,	1
	jmp		pow_end_1

	pow_1:

		mov		rax,	r11
		mov		r12,	1

	pow_loop_1:

		cmp		r12,	r10
		je		pow_end_1

		inc		r12
		imul	r11

		jmp		pow_loop_1

	pow_end_1:

		mov	r11,	rax
		push	r11


	pop		r10
	pop		r11

	sub		r11,	r10
	push	r11
	push	3

	pop		r10
	pop		r11

	add		r11,	r10
	push	r11

	pop		r11
	mov		rax,	r11
	ret