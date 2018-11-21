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

void delay(){
	int t = 0;
	for (int i=1000;i>=0;i--)t++ ;
}

int keypad_scan() {
	int r = 0;
	GPIOC->BSRR = X0;
	GPIOC->BRR = X1;
	GPIOC->BRR = X2;
	GPIOC->BRR = X3;
	if(GPIOB->IDR & Y0){
		r |= (1 << 1);
	}
	if(GPIOB->IDR & Y1){
		r |= (1 << 2);
	}
	if(GPIOB->IDR & Y2){
		r |= (1 << 3);
	}
	if(GPIOB->IDR & Y3){
		r |= (1 << 10);
	}
	GPIOC->BRR = X0;
	delay();
	GPIOC->BRR = X0;
	GPIOC->BSRR = X1;
	GPIOC->BRR = X2;
	GPIOC->BRR = X3;
	if(GPIOB->IDR & Y0){
		r |= (1 << 4);
	}
	if(GPIOB->IDR & Y1){
		r |= (1 << 5);
	}
	if(GPIOB->IDR & Y2){
		r |= (1 << 6);
	}
	if(GPIOB->IDR & Y3){
		r |= (1 << 11);
	}
	GPIOC->BRR = X1;
	delay();
	GPIOC->BRR = X0;
	GPIOC->BRR = X1;
	GPIOC->BSRR = X2;
	GPIOC->BRR = X3;
	if(GPIOB->IDR & Y0){
		r |= (1 << 7);
	}
	if(GPIOB->IDR & Y1){
		r |= (1 << 8);
	}
	if(GPIOB->IDR & Y2){
		r |= (1 << 9);
	}
	if(GPIOB->IDR & Y3){
		r |= (1 << 12);
	}
	GPIOC->BRR = X2;
	delay();
	GPIOC->BRR = X0;
	GPIOC->BRR = X1;
	GPIOC->BRR = X2;
	GPIOC->BSRR = X3;
	if(GPIOB->IDR & Y0){
		r |= (1 << 15);
	}
	if(GPIOB->IDR & Y1){
		r |= 1;
	}
	if(GPIOB->IDR & Y2){
		r |= (1 << 14);
	}
	if(GPIOB->IDR & Y3){
		r |= (1 << 13);
	}
	GPIOC->BRR = X3;
	delay();
	return r;
}

void Send_int(int n){
	if (n == 0){
		MAX7219Send(1, 0);
		MAX7219Send(11, 0);
		return;
	}
	int t = 0;
	while(n > 0){
		MAX7219Send(t+1, n%10);
		n /= 10;
		t++;
	}
	MAX7219Send(11, t-1);
}

int main()
{

	GPIO_init();
	max7219_init();
	keypad_init();
	//Send_int(10);
	int state = 0;
	int sum = 0;
	while(1){
		int last_sum = sum;
		int t = keypad_scan();
		int change_state = (~state)&t;
		state = t;
		int i;


		for (i=0; i<14; i++){
			if (change_state%2 == 1){
				Send_int(i);
				sum += i;
			}
			change_state = (change_state>>1);
		}
		if (change_state > 0) sum = 0;
		sum = (sum > 99999999) ? last_sum : sum;
		Send_int(sum);
	}

}
