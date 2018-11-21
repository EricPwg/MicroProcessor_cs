#include "stm32l476xx.h"
#define X0 1<<9
#define X1 1<<8
#define X2 1<<6
#define X3 1<<5
#define Y0 1<<1
#define Y1 1<<15
#define Y2 1<<14
#define Y3 1<<13

extern void GPIO_init();
extern void max7219_init();
extern void MAX7219Send(unsigned char address, unsigned char data);
void keypad_init() {
	RCC->AHB2ENR |= 0x06;
	
	//PB 13, 14, 15, 1 => input  //0000 0011 1111 1111 1111 1111 1111 0011
								 //1010 1000 0000 0000 0000 0000 0000 1000
	GPIOB->MODER &= 0x03fffff3;
	//PULL DOWN input
	GPIOB->PUPDR &= 0x03fffff3;
	GPIOB->PUPDR |= 0xA8000008;
	//PC 5, 6, 8, 9 => output 	  //0000 0000 0000 0101 0001 0100 0000 0000
	GPIOC->MODER = 0x00051400;
	
	
	//medium speed mode
	GPIOB->OSPEEDR &= 0x03fffff3;
	GPIOB->OSPEEDR |= 0x54000004;
	
	GPIOC->OSPEEDR = 0x00051400;	
}
char keypad_scan() {
	
}

int main()
{

	GPIO_init();
	max7219_init();
	keypad_init();
	while(1){
	GPIOC->BSRR = X0;
	GPIOC->BRR = X1;
	GPIOC->BRR = X2;
	GPIOC->BRR = X3;
	if(GPIOB->IDR & Y0){
		MAX7219Send(11, 0); //scan_limit
		MAX7219Send(1, 1);
	}
	if(GPIOB->IDR & Y1){
		MAX7219Send(11, 0); //scan_limit
		MAX7219Send(1, 2);
	}
	if(GPIOB->IDR & Y2){
		MAX7219Send(11, 0); //scan_limit
		MAX7219Send(1, 3);
	}
	if(GPIOB->IDR & Y3){
		MAX7219Send(11, 1); //scan_limit
		MAX7219Send(2, 1);
		MAX7219Send(1, 0);
	}
	GPIOC->BRR = X0;
	GPIOC->BSRR = X1; 
	GPIOC->BRR = X2;
	GPIOC->BRR = X3;
	if(GPIOB->IDR & Y0){
		MAX7219Send(11, 0); //scan_limit
		MAX7219Send(1, 4);
	}
	if(GPIOB->IDR & Y1){
		MAX7219Send(11, 0); //scan_limit
		MAX7219Send(1, 5);
	}
	if(GPIOB->IDR & Y2){
		MAX7219Send(11, 0); //scan_limit
		MAX7219Send(1, 6);
	}
	if(GPIOB->IDR & Y3){
		MAX7219Send(11, 1); //scan_limit
		MAX7219Send(2, 1);
		MAX7219Send(1, 1);
	}
	GPIOC->BRR = X0;
	GPIOC->BRR = X1;
	GPIOC->BSRR = X2;
	GPIOC->BRR = X3;
	if(GPIOB->IDR & Y0){
		MAX7219Send(11, 0); //scan_limit
		MAX7219Send(1, 7);
	}
	if(GPIOB->IDR & Y1){
		MAX7219Send(11, 0); //scan_limit
		MAX7219Send(1, 8);
	}
	if(GPIOB->IDR & Y2){
		MAX7219Send(11, 0); //scan_limit
		MAX7219Send(1, 9);
	}
	if(GPIOB->IDR & Y3){
		MAX7219Send(11, 1); //scan_limit
		MAX7219Send(2, 1);
		MAX7219Send(1, 2);
	}
	GPIOC->BRR = X0;
	GPIOC->BRR = X1;
	GPIOC->BRR = X2;
	GPIOC->BSRR = X3;
	if(GPIOB->IDR & Y0){
		MAX7219Send(11, 1); //scan_limit
		MAX7219Send(2, 1);
		MAX7219Send(1, 5);
	}
	if(GPIOB->IDR & Y1){
		MAX7219Send(11, 0); //scan_limit
		MAX7219Send(1, 0);
	}
	if(GPIOB->IDR & Y2){
		MAX7219Send(11, 1); //scan_limit
		MAX7219Send(2, 1);
		MAX7219Send(1, 4);
	}
	if(GPIOB->IDR & Y3){
		MAX7219Send(11, 1); //scan_limit
		MAX7219Send(2, 1);
		MAX7219Send(1, 3);
	}
	}

}
