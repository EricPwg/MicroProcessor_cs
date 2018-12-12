#include "../inc/stm32l476xx.h"


int state;
int count;

void delay(){
	int t = 0;
	for (int i=10000;i>=0;i--)t++ ;
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
	//MAX7219Send(1, s);
	if(s == 0) count = 13;
	else if(s == 1) count = 12;
	else if(s == 2) count = 11;
	else if(s == 3) count = 10;
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
	//MAX7219Send(2, s);
	if(s == 0) count = 14;
	else if(s == 1) count = 9;
	else if(s == 2) count = 6;
	else if(s == 3) count = 3;
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
	//MAX7219Send(3, s);
	if(s == 0) count = 0;
	else if(s == 1) count = 8;
	else if(s == 2) count = 5;
	else if(s == 3) count = 2;
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
	//MAX7219Send(4, s);
	if(s == 0) count = 15;
	else if(s == 1) count = 7;
	else if(s == 2) count = 4;
	else if(s == 3) count = 1;
	EXTI -> PR1 &= EXTI_PR1_PIF4;
	EXTI->IMR1 |= EXTI_IMR1_IM1;
	EXTI->IMR1 |= EXTI_IMR1_IM2;
	EXTI->IMR1 |= EXTI_IMR1_IM3;
	EXTI->IMR1 |= EXTI_IMR1_IM4;
	EXTI->IMR1 |= EXTI_IMR1_IM13;
}

void EXTI15_10_IRQHandler(){
	EXTI->IMR1 &= EXTI_IMR1_IM1;
	EXTI->IMR1 &= EXTI_IMR1_IM2;
	EXTI->IMR1 &= EXTI_IMR1_IM3;
	EXTI->IMR1 &= EXTI_IMR1_IM4;
	EXTI -> PR1 &= EXTI_PR1_PIF13;

	TIM_TypeDef *timer = TIM3;
	timer -> CR1 &= ~TIM_CR1_CEN;

	EXTI -> PR1 &= EXTI_PR1_PIF4;
	EXTI->IMR1 |= EXTI_IMR1_IM1;
	EXTI->IMR1 |= EXTI_IMR1_IM2;
	EXTI->IMR1 |= EXTI_IMR1_IM3;
	EXTI->IMR1 |= EXTI_IMR1_IM4;
	EXTI->IMR1 |= EXTI_IMR1_IM13;
}

void SysTick_Handler(void) {
	if(count < 0) return;
	if(count == 0){
		TIM_TypeDef *timer = TIM3;
		timer -> CR1 |= TIM_CR1_CEN;
	}
	count--;
}

void PWM_channel_init(TIM_TypeDef *timer){
	timer->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1; // 0110 =>  PWM mode 1
	timer->CCR1 = 50; //PWM = 50%
	timer->CCER |= TIM_CCER_CC1E;

	timer->CR1 |= TIM_CR1_ARPE; //ARR buffer
	timer->EGR = TIM_EGR_UG;
}

void Timer_init(TIM_TypeDef *timer){
	timer->PSC = (uint32_t)153;  // Do
	timer->ARR = (uint32_t)99;
	timer->EGR = TIM_EGR_UG;
}

void GPIO_init_AF(){
	RCC->AHB2ENR |= 0x1 << 1; // GPIOB enable AHB clk
	GPIOB->MODER |= GPIO_MODER_MODE4_1;	 //PB4 AF mode
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL4_1; //AF2 (TIM3_CH1)
}


int main()
{
	GPIO_init_AF();
	count = 0;
	uint32_t* SYST_CSR = (uint32_t *)0xe000e010;
	uint32_t* SYST_RVR = (uint32_t *)0xe000e014;
	uint32_t* SYST_CVR = (uint32_t *)0xe000e018;
	uint32_t* SYST_CALIB = (uint32_t *)0xe000e01c;
	*SYST_RVR = 3999999;
	*SYST_CSR |= 0x7;

	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM3EN;
	TIM_TypeDef *timer = TIM3;
	Timer_init(timer);
	PWM_channel_init(timer);
	timer -> CR1 &= ~TIM_CR1_CEN;

	state = 0;
	//seven_seg_GPIO_init();
	//max7219_init();
 EXTI_config();
 NVIC_config();

 init_GPIO();
 GPIOC -> BSRR = (1 << 9);
 //MAX7219Send(11, 4);
 //MAX7219Send(1, 0);
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
