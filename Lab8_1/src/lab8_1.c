#include "stm32l476xx.h"
extern void Delay_1s();
extern void GPIO_init();
void SystemClock_Config(){
	/* turn the PLL off */
	RCC->CR &= ~RCC_CR_PLLON;
	while (RCC->CR & RCC_CR_PLLRDY);
	/* turn the HSI16 on*/
	RCC->CR |= RCC_CR_HSION;
	while ((RCC->CR & RCC_CR_HSIRDY) == 0);
	/* set the RCC_PLLCFGR */
	RCC->PLLCFGR = 0x03000c22; //16mhz
	/* turn the PLL on */
	RCC->CR |= RCC_CR_PLLON;
	while ((RCC->CR & RCC_CR_PLLRDY) == 0);
	/* switch the SYSCLK to PLL */
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
	/* set the HPRE */
	RCC->CFGR &= ~RCC_CFGR_HPRE;
	RCC->CFGR |= RCC_CFGR_HPRE_DIV4; //system clk is 4mhz now

}
void SysTick_Handler(void) {
	if(GPIOA->ODR & 0x00000020)
		GPIOA->BRR = (1<<5);
	else GPIOA->BSRR = (1<<5);
}
int main(){
	SystemClock_Config();
	GPIO_init();
	GPIOA->BSRR = (1<<5);
	uint32_t* SYST_CSR = (uint32_t *)0xe000e010;
	uint32_t* SYST_RVR = (uint32_t *)0xe000e014;
	uint32_t* SYST_CVR = (uint32_t *)0xe000e018;
	uint32_t* SYST_CALIB = (uint32_t *)0xe000e01c;
	*SYST_RVR = 11999999;
	*SYST_CSR |= 0x7;
	while(1){
		//GPIOA->BSRR = (1<<5);
		//Delay_1s();
		//GPIOA->BRR = (1<<5);
		//Delay_1s();

	}

}

