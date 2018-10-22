
//Q1

	.syntax unified
	.cpu cortex-m4
	.thumb
.data
	result: .byte 0
	str: .asciz "Hello World!"
.text
	.global main
	.equ X, 0x55AA
	.equ Y, 0xAA55
hamm:
	eor R0, R0, R1
	#16 bits  0000,0000,0000,0000
 	mov r3, #16
	mov r5, #0
	mov r6, #2
loop16:
	sub r3, #1
	ands r4, r0, #0x8000
	cmp r4, #0x8000
	bne test
	add r5, r5, #1
test:
	mul r0, r0, r6
	cmp r3, #0
	beq finish
	b loop16
finish:
	str r5, [R2]

	bx lr
main:
	ldr r0, =X
	ldr r1, =Y
	ldr R2, =result
	bl hamm
	L:B L



/*
//Q2
	.syntax unified
	.cpu cortex-m4
	.thumb
.data

.text
	.global main
	.equ N, 80
fib:
	cmp r0, #1
	blt outRange
	cmp R0, #100
	bgt outRange

	mov r1, #1
	mov r2, #1
	sub r0, #1

loop:
	add r3, r1, r2
	mov r1, r2
	mov r2, r3
	cmp r1, r2  //if r1 > r2 , then overflow
	bhi overFlow
	sub r0, #1
	cmp r0, #0
	bne loop
	mov r4, r1
	bx lr
outRange:
	mov r4, #-1
	bx lr
overFlow:
	mov r4, #-2
	bx lr
main:
	mov r0, #N
	bl fib
L:  b L

*/

/*
//Q3
	.syntax unified
	.cpu cortex-m4
	.thumb
.data
	arr1: .byte 0x19, 0x34, 0x14, 0x32, 0x52, 0x23, 0x61, 0x29
	arr2: .byte 0x18, 0x17, 0x33, 0x16, 0xFA, 0x20, 0x55, 0xAC
.text
	.global main
	.equ N, 80
do_sort:
		mov r1, #7  //i
outer_loop:
	cmp r1, #0
	beq finish
	mov r2, #0   //j
inner_loop:
	cmp r2, r1
	bge outer_loop2
	mov r3, r2
	ldrb r4, [r0, r3]   //arr[j]
	add r6, r3, #1
	ldrb r5, [r0, r6]	//arr[j+1]
	cmp r4, r5
	blt no_swap
	strb r4, [r0, r6]
	strb r5, [r0, r3]
no_swap:
	add r2, #1
	b inner_loop
outer_loop2:
	sub r1, #1
	b outer_loop
finish:
	bx lr
main:
	ldr r0, =arr1
	bl do_sort
	ldr r0, =arr2
	bl do_sort
L:  b L

*/
