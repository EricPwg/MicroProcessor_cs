	.syntax unified
	.cpu cortex-m4
	.thumb


.data
	result: .word 0
	max_size: .word 0
.text
	.global main
	m: .word 96
	n: .word 94


GCD:
	pop {r0, r1}
	cmp r1, #0
	beq finish_GCD

	udiv r2, r0, r1
	mls r2, r1, r2, r0
	push {lr, r1, r2}

	mov r3, sp
	sub r6, r4, r3
	cmp r3, r4
	bge NO_ADD1
	mov r7, r6
	NO_ADD1:

	bl GCD
	pop {lr}
	//mov lr, r3
	bx lr

finish_GCD:
	mov r5, r0
	bx lr

main:
	ldr r3, =m
	ldr r0, [r3]
	ldr r3, =n
	ldr r1, [r3]
	mov r7, #0
	mov r4, sp
	push {r0, r1}


	mov r3, sp
	sub r6, r4, r3
	cmp r3, r4
	bge NO_ADD
	mov r7, r6
	NO_ADD:

	bl GCD
	ldr r3, =result
	str r5, [r3]
	mov r2, #2
	ldr r3, =max_size
	str r7, [r3]
	L: B L
