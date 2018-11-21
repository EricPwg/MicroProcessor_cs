#include "stm32l476xx.h"
extern void GPIO_init();
extern void max7219_init();
extern void MAX7219Send(unsigned char address, unsigned char data);
int main()
{
	GPIO_init();
	max7219_init();
	MAX7219Send(11, 6);
	while(1){
		MAX7219Send(7, 0);
		MAX7219Send(6, 4);
		MAX7219Send(5, 1);
		MAX7219Send(4, 1);
		MAX7219Send(3, 0);
		MAX7219Send(2, 3);
		MAX7219Send(1, 6);
	}

	

}
