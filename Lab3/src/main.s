	.syntax unified
	.cpu cortex-m4
	.thumb
.data
	leds: .byte 0x0c
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
	MOVS R5, #0      //r5 is the shift counter
	movs r7, #1

Loop:
	//TODO: Write the display pattern into leds variable
    BL DisplayLED
	BL   Delay
	bl ReadButtom
	cmp r7, #0
	beq Loop
	add r5, #1
	ldr r3, =leds
	ldrb r2, [r3]
	cmp r5, #4
	bgt shift_right   //less then 4 => shift left
	lsl r2, #1
	strb r2, [r3]
	cmp r5, #8
	bne init_r5
	mov r5, #0
	b Loop
shift_right:
	lsr r2, #1
	strb r2, [r3]
	cmp r5, #8
	bne init_r5
	mov r5, #0
init_r5:
	B Loop

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
	//and r2, #0xFFFFC03F
	//orrs r2, r2, r0
	str r0, [r1]

	//set GPIOB_PUPDR  01: pull up   0001 0101 0100 0000
	//mov r0, #0x2C80    //pull down
	//mov r0, #0x1540
	//ldr r1, =GPIOB_PUPDR
	//ldr r2, [r1]
	//and r2, #0xFFFFC03F			//	 1100 0000 0011 1111
	//orrs r2, r2, r0
	//str r2, [r1]
	bx lr
DisplayLED:
	//TODO: Display LED by leds

	ldr r1, =GPIOB_ODR
	ldr r2, =leds
	ldrb r2, [r2]
	eor r2, 0x78
	strh r2, [r1]
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
	eor r7, #1
	bx lr


