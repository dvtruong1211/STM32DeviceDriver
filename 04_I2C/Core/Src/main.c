#include "memory_map_stm32f411xe.h"
#include "gpio.h"
#include "main.h"

static void MX_GPIO_Init(void);

uint8_t a = 0;

GPIO_Handle_t button1 ;
GPIO_Handle_t led;
GPIO_Handle_t led1;
GPIO_Handle_t led2 ;
GPIO_Handle_t led3;
GPIO_Handle_t led5;
GPIO_Handle_t led4;


int main(void){
	
	GPIO_Handle_t button1;
	
	MX_GPIO_Init();
	GPIO_WritePin(GPIOB, 2, GPIO_PIN_SET);
	GPIO_WritePin(GPIOD, 12, GPIO_PIN_SET);
	GPIO_WritePin(GPIOD, 13, GPIO_PIN_SET);
	GPIO_WritePin(GPIOD, 14, GPIO_PIN_SET);
	GPIO_WritePin(GPIOD, 15, GPIO_PIN_SET);
	GPIO_WritePin(GPIOC, 0, GPIO_PIN_SET);
	
	
	while(1);
	
	return 0;
}

static void MX_GPIO_Init(void){
	
	button1.Gpiox = GPIOA;
	button1.GPIO_PinConfig.pinNumber = 0;
	button1.GPIO_PinConfig.pinMode = IT_FT_MODE;
	GPIO_Init(&button1);
	GPIO_IRQInterruptConfig(IRQ_NO_EXTI0, ENABLE);
	GPIO_IRQPiorityConfig(IRQ_NO_EXTI0, 15);
	
	led.Gpiox = GPIOB;
	led.GPIO_PinConfig.pinNumber = 2;
	led.GPIO_PinConfig.pinMode = OUTPUT_MODE;
	led.GPIO_PinConfig.pinOpType = PUSH_PULL;
	GPIO_Init(&led);
	
	led5.Gpiox = GPIOC;
	led5.GPIO_PinConfig.pinNumber = 0;
	led5.GPIO_PinConfig.pinMode = OUTPUT_MODE;
	//led5.GPIO_PinConfig.pinOpType = PUSH_PULL;
	GPIO_Init(&led5);
	
	led1.Gpiox = GPIOD;
	led1.GPIO_PinConfig.pinNumber = 12;
	led1.GPIO_PinConfig.pinMode = OUTPUT_MODE;
	led1.GPIO_PinConfig.pinOpType = PUSH_PULL;
	GPIO_Init(&led1);
	
	led2.Gpiox = GPIOD;
	led2.GPIO_PinConfig.pinNumber = 13;
	led2.GPIO_PinConfig.pinMode = OUTPUT_MODE;
	led2.GPIO_PinConfig.pinOpType = PUSH_PULL;
	GPIO_Init(&led2);
	
	led3.Gpiox = GPIOD;
	led3.GPIO_PinConfig.pinNumber = 14;
	led3.GPIO_PinConfig.pinMode = OUTPUT_MODE;
	led3.GPIO_PinConfig.pinOpType = PUSH_PULL;
	GPIO_Init(&led3);
	
	led4.Gpiox = GPIOD;
	led4.GPIO_PinConfig.pinNumber = 15;
	led4.GPIO_PinConfig.pinMode = OUTPUT_MODE;
	led4.GPIO_PinConfig.pinOpType = PUSH_PULL;
	GPIO_Init(&led4);
}

void delay(void){
	for(int i = 0; i < 50000; i++);
}


void EXTI0_IRQHandler(void){
	 delay();
	 a++;
	 GPIO_PinToggle(GPIOB, GPIO_PIN_2);
	 GPIO_IRQ_ClearPanding(0);
 }




