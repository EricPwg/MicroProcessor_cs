	.syntax unified
	.cpu cortex-m4
	.thumb


.data
	result: .word 0
	max_size: .word 0
.text
	.global Delay_1s
	.global GPIO_init
	.equ RCC_AHB2ENR, 	 0x4002104C
	.equ GPIOA_MODER,	 0x48000000
	.equ GPIOA_OTYPER,	 0x48000004
	.equ GPIOA_OSPEEDR,	 0x48000008
	.equ GPIOA_PUPDR,	 0x4800000c
	.equ GPIOA_ODR,		 0x48000014

	.equ GPIOC_MODER, 	 0x48000800
	.equ GPIOC_OTYPER,   0x48000804
	.equ GPIOC_OSPEEDR,  0x48000808
	.equ GPIOC_PUPDR,    0x4800080C
	.equ GPIOC_IDR,      0x48000810
	.equ X, 			 0x3e8
	.equ Y,				 0x3e8
GPIO_init:
	movs r0, #5
	ldr r1, =RCC_AHB2ENR
	str r0, [r1]
	//set PA5 as output mode
	movs r0, #0x400
	ldr r1, =GPIOA_MODER
	ldr r2, [r1]
	and r2, #0xFFFFF3FF
	orrs r2, r2, r0
	str r2, [r1]
	//set high speed mode
	movs r0, #0x800
	ldr r1, =GPIOA_OSPEEDR
	str r0, [r1]
	//set PC13 as input mode
	ldr r1, =GPIOC_MODER
	ldr r2, [r1]
	and r2, #0xF3FFFFFF
	str r2, [r1]
	bx lr
Delay_1s:
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



