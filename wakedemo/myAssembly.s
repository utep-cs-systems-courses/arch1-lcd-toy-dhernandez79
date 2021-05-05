
	.arch msp430g2553
	.p2align 1,0
	.text			;jt is constant

jt:
	.word option0		;jt 0
	.word option1		;jt 1
	.word option2		;jt 2
	.global assembly_method

assembly_method:
	;; parameters have variable state 0

	sub #2, r1		;allocate space for short variable
	mov #0, 0(r1)		;static variable note = 0

	cmp #3, r12		;state-3 does not borrow if state > 2
	jhs end			;jmp if state > 2

	cmp #0, r12		;borrow if state < 0
	jl end			;jmp if state < 0

	add r12, r12		;r12 = 2 times state
	mov jt(r12), r0

option0:
	mov #400, 0(r1)
	mov 0(r1), r12
	call #play_buzzer
	jmp end

option1:
	mov #500, 0(r1)
	mov 0(r1), r12
	call #play_buzzer
	jmp end

option2:
	mov #600, 0(r1)
	mov 0(r1), r12
	call #play_buzzer
	jmp end

end:
	add #2, r1
	pop r0
