#include "../inc/stm32l476xx.h"

extern void Delay_half_s();
extern void seven_seg_GPIO_init();
extern void max7219_init();
extern void MAX7219Send(unsigned char address, unsigned char data);

int state;

void delay(){
	int t = 0;
	for (int i=10000;i>=0;i--)t++ ;
}

void blink(int n){
	for (int i=0; i<n;i++){
		GPIOC -> BRR = (1 << 9);
		Delay_half_s();
		GPIOC -> BSRR = (1 << 9);
		Delay_half_s();
	}
	GPIOC -> BSRR = (1 << 9);
}

void init_GPIO(){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

	GPIOC -> MODER &= ~(0xC0FFC00);
	GPIOC -> MODER |= (0x1055400);

	GPIOC -> MODER &= ~(0x3FC);
	//GPIOC -> MODER |= (0x154);

	GPIOC -> PUPDR &= ~(0x3FC);
	GPIOC -> PUPDR |= (0x2A8);
}
void EXTI_config(){
	//Enable SYSCFG CLK
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	//Select output bits
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI1;
	SYSCFG->EXTICR[0] |= (SYSCFG_EXTICR1_EXTI1_PC);
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI2;
	SYSCFG->EXTICR[0] |= (SYSCFG_EXTICR1_EXTI2_PC);
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI3;
	SYSCFG->EXTICR[0] |= (SYSCFG_EXTICR1_EXTI3_PC);
	SYSCFG->EXTICR[1] &= ~SYSCFG_EXTICR2_EXTI4;
	SYSCFG->EXTICR[1] |= (SYSCFG_EXTICR2_EXTI4_PC);
	SYSCFG->EXTICR[3] &= ~SYSCFG_EXTICR4_EXTI13;
	SYSCFG->EXTICR[3] |= (SYSCFG_EXTICR4_EXTI13_PC);

	//Enable interrupt
	EXTI->IMR1 |= EXTI_IMR1_IM1;
	EXTI->IMR1 |= EXTI_IMR1_IM2;
	EXTI->IMR1 |= EXTI_IMR1_IM3;
	EXTI->IMR1 |= EXTI_IMR1_IM4;
	EXTI->IMR1 |= EXTI_IMR1_IM13;
	//Enable Rising Edge
	EXTI->FTSR1 |= EXTI_RTSR1_RT1;
	EXTI->FTSR1 |= EXTI_RTSR1_RT2;
	EXTI->FTSR1 |= EXTI_RTSR1_RT3;
	EXTI->FTSR1 |= EXTI_RTSR1_RT4;
	EXTI->FTSR1 |= EXTI_RTSR1_RT13;
}
void NVIC_config(){
	//Enable NVIC**
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);
	NVIC_EnableIRQ(EXTI3_IRQn);
	NVIC_EnableIRQ(EXTI4_IRQn);
	NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void EXTI1_IRQHandler(void){
	int s = state;
	EXTI->IMR1 &= EXTI_IMR1_IM1;
	EXTI->IMR1 &= EXTI_IMR1_IM2;
	EXTI->IMR1 &= EXTI_IMR1_IM3;
	EXTI->IMR1 &= EXTI_IMR1_IM4;
	EXTI->IMR1 &= EXTI_IMR1_IM13;
	//MAX7219Send(1, s);
	if(s == 0) blink(13);
	else if(s == 1) blink(12);
	else if(s == 2) blink(11);
	else if(s == 3) blink(10);
	EXTI -> PR1 &= EXTI_PR1_PIF1;
	EXTI->IMR1 |= EXTI_IMR1_IM1;
	EXTI->IMR1 |= EXTI_IMR1_IM2;
	EXTI->IMR1 |= EXTI_IMR1_IM3;
	EXTI->IMR1 |= EXTI_IMR1_IM4;
	EXTI->IMR1 |= EXTI_IMR1_IM13;
}

void EXTI2_IRQHandler(void){
	int s = state;
	EXTI->IMR1 &= EXTI_IMR1_IM1;
	EXTI->IMR1 &= EXTI_IMR1_IM2;
	EXTI->IMR1 &= EXTI_IMR1_IM3;
	EXTI->IMR1 &= EXTI_IMR1_IM4;
	EXTI->IMR1 &= EXTI_IMR1_IM13;
	MAX7219Send(2, s);
	if(s == 0) blink(14);
	else if(s == 1) blink(9);
	else if(s == 2) blink(6);
	else if(s == 3) blink(3);
	//MAX7219Send(1, 2);
	EXTI -> PR1 &= EXTI_PR1_PIF2;
	EXTI->IMR1 |= EXTI_IMR1_IM1;
	EXTI->IMR1 |= EXTI_IMR1_IM2;
	EXTI->IMR1 |= EXTI_IMR1_IM3;
	EXTI->IMR1 |= EXTI_IMR1_IM4;
	EXTI->IMR1 |= EXTI_IMR1_IM13;
}

void EXTI3_IRQHandler(void){
	int s = state;
	EXTI->IMR1 &= EXTI_IMR1_IM1;
	EXTI->IMR1 &= EXTI_IMR1_IM2;
	EXTI->IMR1 &= EXTI_IMR1_IM3;
	EXTI->IMR1 &= EXTI_IMR1_IM4;
	EXTI->IMR1 &= EXTI_IMR1_IM13;
	MAX7219Send(3, s);
	if(s == 0) blink(0);
	else if(s == 1) blink(8);
	else if(s == 2) blink(5);
	else if(s == 3) blink(2);
	EXTI -> PR1 &= EXTI_PR1_PIF3;
	EXTI->IMR1 |= EXTI_IMR1_IM1;
	EXTI->IMR1 |= EXTI_IMR1_IM2;
	EXTI->IMR1 |= EXTI_IMR1_IM3;
	EXTI->IMR1 |= EXTI_IMR1_IM4;
	EXTI->IMR1 |= EXTI_IMR1_IM13;
}

void EXTI4_IRQHandler(void){
	int s = state;
	EXTI->IMR1 &= EXTI_IMR1_IM1;
	EXTI->IMR1 &= EXTI_IMR1_IM2;
	EXTI->IMR1 &= EXTI_IMR1_IM3;
	EXTI->IMR1 &= EXTI_IMR1_IM4;
	EXTI->IMR1 &= EXTI_IMR1_IM13;
	MAX7219Send(4, s);
	if(s == 0) blink(15);
	else if(s == 1) blink(7);
	else if(s == 2) blink(4);
	else if(s == 3) blink(1);
	EXTI -> PR1 &= EXTI_PR1_PIF4;
	EXTI->IMR1 |= EXTI_IMR1_IM1;
	EXTI->IMR1 |= EXTI_IMR1_IM2;
	EXTI->IMR1 |= EXTI_IMR1_IM3;
	EXTI->IMR1 |= EXTI_IMR1_IM4;
	EXTI->IMR1 |= EXTI_IMR1_IM13;
}

void EXTI15_10_IRQHandler(){
	if(EXTI->PR1&EXTI_PR1_PIF13){
		MAX7219Send(5, 1);
		EXTI -> PR1 &= EXTI_PR1_PIF13;
	}
}

int main()
{
	state = 0;
	seven_seg_GPIO_init();
	max7219_init();
 EXTI_config();
 NVIC_config();

 init_GPIO();
 GPIOC -> BSRR = (1 << 9);
 MAX7219Send(11, 4);
 MAX7219Send(1, 0);
 while(1){
	 GPIOC -> BRR |= (1<<5);
	 GPIOC -> BRR |= (1<<6);
	 GPIOC -> BRR |= (1<<7);
	 GPIOC -> BRR |= (1<<8);

	 GPIOC -> BSRR |= (1<<5);
	 state = 0;
	 delay();
	 GPIOC -> BRR |= (1<<5);

	 GPIOC -> BSRR |= (1<<6);
	 state = 1;
	 delay();
	 GPIOC -> BRR |= (1<<6);

	 GPIOC -> BSRR |= (1<<7);
	 state = 2;
	 delay();
	 GPIOC -> BRR |= (1<<7);

	 GPIOC -> BSRR |= (1<<8);
	 state = 3;
	 delay();
	 GPIOC -> BRR |= (1<<8);
 }

 //MAX7219Send(1, 5);
}
