#include "../inc/stm32l476xx.h"

extern void SimpleDelay();

# define D0_GPIO GPIOC
# define D1_GPIO GPIOC
# define D2_GPIO GPIOB
# define D3_GPIO GPIOA
# define D4_GPIO GPIOB
# define D5_GPIO GPIOB
# define D6_GPIO GPIOB
# define D7_GPIO GPIOA

# define RS_GPIO GPIOA
# define RW_GPIO GPIOC
# define E_GPIO GPIOB

# define D0_pin 0
# define D1_pin 1
# define D2_pin 0
# define D3_pin 4
# define D4_pin 5
# define D5_pin 4
# define D6_pin 10
# define D7_pin 8

# define RS_pin 9
# define RW_pin 7
# define E_pin 6

int state;

void GPIO_init(){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

	//GPIOA -> MODER = 0;
	//GPIOB -> MODER = 0;
	//GPIOC -> MODER = 0;

	D0_GPIO->MODER &= ~(3 << (D0_pin*2));
	D1_GPIO->MODER &= ~(3 << (D1_pin*2));
	D2_GPIO->MODER &= ~(3 << (D2_pin*2));
	D3_GPIO->MODER &= ~(3 << (D3_pin*2));
	D4_GPIO->MODER &= ~(3 << (D4_pin*2));
	D5_GPIO->MODER &= ~(3 << (D5_pin*2));
	D6_GPIO->MODER &= ~(3 << (D6_pin*2));
	D7_GPIO->MODER &= ~(3 << (D7_pin*2));

	D0_GPIO->MODER |= (1 << (D0_pin*2));
	D1_GPIO->MODER |= (1 << (D1_pin*2));
	D2_GPIO->MODER |= (1 << (D2_pin*2));
	D3_GPIO->MODER |= (1 << (D3_pin*2));
	D4_GPIO->MODER |= (1 << (D4_pin*2));
	D5_GPIO->MODER |= (1 << (D5_pin*2));
	D6_GPIO->MODER |= (1 << (D6_pin*2));
	D7_GPIO->MODER |= (1 << (D7_pin*2));

	RS_GPIO->MODER &= ~(3 << (RS_pin*2));
	RW_GPIO->MODER &= ~(3 << (RW_pin*2));
	E_GPIO->MODER  &= ~(3 << ( E_pin*2));
	RS_GPIO->MODER |= (1 << (RS_pin*2));
	RW_GPIO->MODER |= (1 << (RW_pin*2));
	E_GPIO->MODER  |= (1 << ( E_pin*2));

}

void send_lcd(int RS, int RW, int data){
	if(RS) RS_GPIO -> BSRR = (1 << RS_pin);
	else   RS_GPIO -> BRR  = (1 << RS_pin);
	if(RW) RW_GPIO -> BSRR = (1 << RW_pin);
	else   RW_GPIO -> BRR  = (1 << RW_pin);

	if (data % 2) D0_GPIO -> BSRR = (1 << D0_pin);
	else D0_GPIO -> BRR = (1 << D0_pin);
	data/=2;
	if (data % 2) D1_GPIO -> BSRR = (1 << D1_pin);
	else D1_GPIO -> BRR = (1 << D1_pin);
	data/=2;
	if (data % 2) D2_GPIO -> BSRR = (1 << D2_pin);
	else D2_GPIO -> BRR = (1 << D2_pin);
	data/=2;
	if (data % 2) D3_GPIO -> BSRR = (1 << D3_pin);
	else D3_GPIO -> BRR = (1 << D3_pin);
	data/=2;
	if (data % 2) D4_GPIO -> BSRR = (1 << D4_pin);
	else D4_GPIO -> BRR = (1 << D4_pin);
	data/=2;
	if (data % 2) D5_GPIO -> BSRR = (1 << D5_pin);
	else D5_GPIO -> BRR = (1 << D5_pin);
	data/=2;
	if (data % 2) D6_GPIO -> BSRR = (1 << D6_pin);
	else D6_GPIO -> BRR = (1 << D6_pin);
	data/=2;
	if (data % 2) D7_GPIO -> BSRR = (1 << D7_pin);
	else D7_GPIO -> BRR = (1 << D7_pin);
	data/=2;
	E_GPIO -> BSRR  = (1 << E_pin);
	SimpleDelay();
	E_GPIO -> BRR  = (1 << E_pin);
	SimpleDelay();
}

void display(int n){
	send_lcd(1, 0, (n%10)+48);
}

void SysTick_Handler(void) {
	send_lcd(0, 0, 16+12);
}

void SysTick_init(){
	uint32_t* SYST_CSR = (uint32_t *)0xe000e010;
	uint32_t* SYST_RVR = (uint32_t *)0xe000e014;
	uint32_t* SYST_CVR = (uint32_t *)0xe000e018;
	uint32_t* SYST_CALIB = (uint32_t *)0xe000e01c;
	*SYST_RVR = 1199999;
	*SYST_CSR |= 0x7;
}

void EXTI_config(){
	//Enable SYSCFG CLK
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	GPIOC -> MODER &= ~(3 << 13*2);
	//Select output bits
	SYSCFG->EXTICR[3] &= ~SYSCFG_EXTICR4_EXTI13;
	SYSCFG->EXTICR[3] |= (SYSCFG_EXTICR4_EXTI13_PC);

	//Enable interrupt
	EXTI->IMR1 |= EXTI_IMR1_IM13;
	//Enable Rising Edge
	EXTI->RTSR1 |= EXTI_FTSR1_FT13;
}

void NVIC_config(){
	//Enable NVIC**
	NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void EXTI15_10_IRQHandler(){
	EXTI -> PR1 &= EXTI_PR1_PIF13;

	//TIM_TypeDef *timer = TIM3;
	//timer -> CR1 &= ~TIM_CR1_CEN;
	send_lcd(0, 0, 1);
	send_lcd(0, 0, 2);
	if (state == 0){
		state = 1;
		send_lcd(0, 0, 1);
		send_lcd(0, 0, 2);
		send_lcd(1, 0, 0);
		send_lcd(1, 0, 1);
	}
	else if (state == 1){
		state = 0;
		display(0);
		display(4);
		display(1);
		display(1);
		display(0);
		display(3);
		display(6);
	}
	//send_lcd(0, 0, 16+12);

	EXTI -> PR1 &= EXTI_PR1_PIF4;

	EXTI->IMR1 |= EXTI_IMR1_IM13;
}

void self_def(){
	send_lcd(0, 0, 0x40);
	//

	send_lcd(1, 0, 0b01110);
	send_lcd(1, 0, 0b11110);
	send_lcd(1, 0, 0b01110);
	send_lcd(1, 0, 0b00011);
	send_lcd(1, 0, 0b00011);
	send_lcd(1, 0, 0b00011);
	send_lcd(1, 0, 0b00011);
	send_lcd(1, 0, 0b00011);
	//
	send_lcd(1, 0, 0b11100);
	send_lcd(1, 0, 0b01100);
	send_lcd(1, 0, 0b01100);
	send_lcd(1, 0, 0b00011);
	send_lcd(1, 0, 0b00111);
	send_lcd(1, 0, 0b11111);
	send_lcd(1, 0, 0b01110);
	send_lcd(1, 0, 0b01110);

	//

	//for (int j = 0; j<48; j++)
	//for (int i=0; i<8; i++) send_lcd(1, 0, i);

	send_lcd(0, 0, 0x80);
}

int main(){
	state = 0;
	GPIO_init();
	SysTick_init();
	EXTI_config();
	NVIC_config();

	send_lcd(0, 0, 1);
	send_lcd(0, 0, 2);
	send_lcd(0, 0, 12);
	send_lcd(0, 0, 48);

	self_def();

	display(0);
	display(4);
	display(1);
	display(1);
	display(0);
	display(3);
	display(6);
	//send_lcd(1, 0, 0);
	//send_lcd(1, 0, 1);
	//send_lcd(1, 0, 16+4);
	while(1);
}

