.syntax unified
	.cpu cortex-m4
	.thumb
.data
	leds: .byte 0x0c
	code: .byte 0x1
.text
	.global main
	.equ RCC_AHB2ENR, 	 0x4002104C
	.equ GPIOB_MODER, 	 0x48000400
	.equ GPIOB_OTYPER,   0x48000404
	.equ GPIOB_OSPEEDR,  0x48000408
	.equ GPIOB_PUPDR,    0x4800040C
	.equ GPIOB_ODR,      0x48000414

	.equ GPIOC_MODER, 	 0x48000800
	.equ GPIOC_OTYPER,   0x48000804
	.equ GPIOC_OTYPER,   0x48000804
	.equ GPIOC_OSPEEDR,  0x48000808
	.equ GPIOC_PUPDR,    0x4800080C
	.equ GPIOC_IDR,      0x48000810
	.equ bssr1,   		 0x18
	.equ X, 			 0x3e8
	.equ Y,				 0x3e8
main:
	BL   GPIO_init
	//MOVS R5, #0      //r5 is the shift counter


Loop:
	ldr r1, =GPIOB_ODR
	movs r2, #0x78
	str r2, [r1]
	//TODO: Write the display pattern into leds variable
	//b LEDBlink
	movs r7, #0
	bl ReadButtom
	bl ReadSwitch
	cmp r7, #0
	beq Loop
	cmp r6, #0
	beq not_same
	bl LEDBlink
	bl LEDBlink
not_same:
	bl LEDBlink
	mov r7, #0
	b Loop

ReadSwitch:
	ldr r1, =GPIOC_IDR
	ldr r2, [r1]
	movs r0, #0xF
	ands r2, r2, r0
	ldr r0, =code
	ldr r1, [r0]
	eor r0, r1, r2
	cmp r0, #0xF
	beq same
	mov r6, #0
	bx lr
same:
	mov r6, #1
	bx lr

GPIO_init:
	//TODO: Initial LED GPIO pins as output
	//enable ahb3 clk
	movs r0, #6	//GPIOB, GPIOC
	ldr r1, =RCC_AHB2ENR
	str r0, [r1]

	//set PB3,4,5,6 as output mode
	movs r0, #0x1540
	ldr r1, =GPIOB_MODER
	ldr r2, [r1]
	and r2, #0xFFFFC03F
	orrs r2, r2, r0
	str r2, [r1]

	//set high speed mode
	movs r0, #0x2a80
	ldr r1, =GPIOB_OSPEEDR
	str r0, [r1]

	movs r0, #0
	ldr r1, =GPIOC_MODER
	ldr r2, [r1]
	str r0, [r1]

	bx lr
LEDBlink:
	push {lr}
	//TODO: Display LED by leds
	ldr r1, =GPIOB_ODR
	movs r2, #0
	str r2, [r1]
	bl Delay
	movs r2, #0x78
	str r2, [r1]
	bl Delay
	pop {lr}
	bx lr
Delay:
	//TODO: Write a delay 1 sec function
	ldr r3, =X
L1:
	ldr r4, =Y
L2:
	subs r4, #1
	bne L2
	subs r3, #1
	bne L1
	bx lr

ReadButtom:
	movs r3, #1000
	movs r4, #0
Debounce_loop:
	subs r3, #1
	beq end_loop
	ldr r1, =GPIOC_IDR
	ldr r2, [r1]
	movs r0, #0x2000
	ands r2, r2, r0
	bne no_add
	add r4, r4, #1
no_add:
	b Debounce_loop
end_loop:
	cmp r4, #500
	bgt change_mode
	bx lr
change_mode:
	mov r7, #1
	bx lr
