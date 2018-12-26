	.syntax unified
	.cpu cortex-m4
	.thumb
.data
	student_id: .byte 0, 4, 1, 1, 0, 8, 1

.text

	.global seven_seg_GPIO_init
	.global max7219_init
	.global MAX7219Send
	.global Delay_half_s
	.global SimpleDelay
	.equ RCC_AHB2ENR, 	 0x4002104C
	.equ GPIOB_MODER, 	 0x48000400
	.equ GPIOB_OTYPER,   0x48000404
	.equ GPIOB_OSPEEDR,  0x48000408
	.equ GPIOB_PUPDR,    0x4800040C
	.equ GPIOB_ODR,      0x48000414

	.equ GPIOB_BASE, 	 0x48000400
	.equ GPIOB_BSRR_OFFSET,	 0x18		//set = 1
	.equ GPIOB_BRR_OFFSET, 	 0x28		//reset = 0

	.equ DECODE_MODE, 	0x9
	.equ INTENSITY,	0xa
	.equ SCAN_LIMIT,	0xb
	.equ SHUTDOWN,	0xc
	.equ DISPLAY_TEST,	0xf
	.equ DATA, 1<<3 //PB3
	.equ LOAD, 1<<4 //PB4
	.equ CLOCK, 1<<5 //PB5
	.equ X, 			 0x1f
	.equ Y,				 0x1f



seven_seg_GPIO_init:
	movs r2, #2
	ldr r1, =RCC_AHB2ENR
	ldr r0, [r1]
	orrs r0, r0, r2
	str r0, [r1]
	//set PB3,4,5 as output mode
	movs r0, #0x540
	ldr r1, =GPIOB_MODER
	ldr r2, [r1]
	and r2, #0xFFFFF03F
	orrs r2, r2, r0
	str r2, [r1]
	//set high speed mode
	movs r0, #0xa80
	ldr r1, =GPIOB_OSPEEDR
	str r0, [r1]
	bx lr
Display0toF: //TODO: Display 0 to F at first digit on 7-SEG LED. Display one
	mov r0, #7			//ADDRESS
	ldrb r1, [r9, r2]		//DATA
	BL MAX7219Send
	add r2, r2, #1
	mov r0, #6			//ADDRESS
	ldrb r1, [r9, r2]		//DATA
	BL MAX7219Send
	add r2, r2, #1
	mov r0, #5			//ADDRESS
	ldrb r1, [r9, r2]		//DATA
	BL MAX7219Send
	add r2, r2, #1
	mov r0, #4			//ADDRESS
	ldrb r1, [r9, r2]		//DATA
	BL MAX7219Send
	add r2, r2, #1
	mov r0, #3			//ADDRESS
	ldrb r1, [r9, r2]		//DATA
	BL MAX7219Send
	add r2, r2, #1
	mov r0, #2			//ADDRESS
	ldrb r1, [r9, r2]		//DATA
	BL MAX7219Send
	add r2, r2, #1
	mov r0, #1			//ADDRESS
	ldrb r1, [r9, r2]		//DATA
	BL MAX7219Send
	add r2, r2, #1

	//add r2, r2, #1
	//cmp r2, #6
	//bne Display0toF
	bx lr

MAX7219Send: //input parameter: r0 is ADDRESS , r1 is DATA //TODO: Use this function to send a message to max7219
	push {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, lr}
	lsl r0, r0, #8
	add r0, r0, r1				//r0 is the 16bits
	ldr r1, =#GPIOB_BASE
	ldr r2, =#LOAD
	ldr r3, =#DATA
	ldr r4, =#CLOCK
	ldr r5, =#GPIOB_BSRR_OFFSET		// set bit 1
	ldr r6, =#GPIOB_BRR_OFFSET   // set bit 0
	mov r7, #16//r7 = i
.max7219send_loop:
	mov r8, #1
	sub r9, r7, #1
	lsl r8, r8, r9
	str r4, [r1,r6]
	tst r0, r8
	beq .bit_not_set
	str r3, [r1,r5]
	b .if_done
.bit_not_set:
	str r3, [r1,r6]
.if_done:
	str r4, [r1,r5]
	subs r7, r7, #1
	bgt .max7219send_loop
	str r2, [r1,r6]
	str r2, [r1,r5]
	pop {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, pc}
	bx lr
max7219_init: //TODO: Initialize max7219 registers
	push {r0, r1, r2, lr}
	ldr r0, =#DECODE_MODE
	ldr r1, =#0xff
	bl MAX7219Send
	ldr r0, =#DISPLAY_TEST
	ldr r1, =#0x0
	bl MAX7219Send
	ldr r0, =#SCAN_LIMIT
	ldr r1, =#0x0
	bl MAX7219Send
	ldr r0, =#INTENSITY
	ldr r1, =#0xA
	bl MAX7219Send
	ldr r0, =#SHUTDOWN
	ldr r1, =#0x1
	bl MAX7219Send
	pop {r0, r1, r2, pc}
	bx lr


SimpleDelay:
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
