/**
 ******************************************************************************
 * @file    gpio.h
 * @author  truongdv
 * @version 1.0
 * @date
 * @brief
 * @history
 ******************************************************************************/

#ifndef __GPIO_H
#define __GPIO_H

#include "memory_map_stm32f411xe.h"

#define GPIO_PIN_SET	SET
#define GPIO_PIN_RESET	RESET

/*
	GPIO pin number
*/
#define GPIO_PIN_0		0
#define GPIO_PIN_1		1
#define GPIO_PIN_2		2
#define GPIO_PIN_3		3
#define GPIO_PIN_4		4
#define GPIO_PIN_5		5
#define GPIO_PIN_6		6
#define GPIO_PIN_7		7
#define GPIO_PIN_8		8
#define GPIO_PIN_9		9
#define GPIO_PIN_10		10
#define GPIO_PIN_11		11
#define GPIO_PIN_12		12
#define GPIO_PIN_13		13
#define GPIO_PIN_14		14
#define GPIO_PIN_15		15

/*
	GPIO pin mode
*/
#define INPUT_MODE		0
#define OUTPUT_MODE		1
#define ALT_MODE		2
#define ANALOG_MODE		3
#define IT_FT_MODE		4
#define	IT_RT_MODE		5
#define IT_RFT_MODE		6

/*
	GPIO pin speed
*/
#define LOW_SPEED		0
#define MEDIUM_SPEED	1
#define FAST_SPEED		2
#define HIGH_SPEDD		3

/*
	GPIO pin pull up, pull down
*/
#define NO_PULL			0
#define PULL_UP			1
#define PULL_DOWN		2
#define RESERVED		3

/*
	GPIO pin output type
*/
#define PUSH_PULL		0
#define OPEN_DRAIN		1

/*
	GPIO pin alternate function mode
*/

#define AF0 			0
#define AF1 			1
#define AF2 			2
#define AF3 			3
#define AF4 			4
#define AF5 			5
#define AF6 			6
#define AF7 			7
#define AF8 			8
#define AF9 			9
#define AF10 			10
#define AF11 			11
#define AF12			12
#define AF13			13
#define AF14			14
#define AF15			15

/*
	Position of EXTI number
*/

#define IRQ_NO_EXTI0		6
#define IRQ_NO_EXTI1		7
#define IRQ_NO_EXTI2		8
#define IRQ_NO_EXTI3		9
#define IRQ_NO_EXTI4		10
#define IRQ_NO_EXTI9_5		23
#define IRQ_NO_EXTI15_10	40




typedef struct {
	uint8_t pinNumber;
	uint8_t pinMode;
	uint8_t pinSpeed;
	uint8_t pinPuPdControl;
	uint8_t pinOpType;
	uint8_t pinAltFunMode;
}GPIO_PinConfig_t;

typedef struct{
	GPIO_TypeDef *Gpiox;
	GPIO_PinConfig_t GPIO_PinConfig;
}GPIO_Handle_t;

/* 
	gpio_pin.Gpiox = GPIOD;
	gpio_pin.GPIO_PinConfig.pinNumber = GPIO_PIN_0;
	gpio_pin.GPIO_PinConfig.pinMode = OUTPUT_MODE;
	gpio_pin.GPIO_PinConfig.pinSpeed = PUSH_PULL;
	gpio_pin.GPIO_PinConfig.pinPuPdControl = NO_PULL;
	gpio_pin.GPIO_PinConfig.pinOpType = PUSH_PULL;
	gpio_pin.GPIO_PinConfig.pinAltFunMode = AF0;

 */

void GPIO_ClockControl(GPIO_TypeDef* gpiox, uint8_t value);

void GPIO_Init(GPIO_Handle_t *gpioHander);
void GPIO_DeInit(GPIO_TypeDef *gpiox);

uint8_t GPIO_ReadPin(GPIO_TypeDef* gpiox, uint8_t pinNumber);
uint16_t GPIO_ReadPort(GPIO_TypeDef* gpiox);

void GPIO_WritePin(GPIO_TypeDef *gpiox, uint8_t pinNumber, uint8_t value);
void GPIO_WritePort(GPIO_TypeDef *gpiox, uint16_t value);
void GPIO_PinToggle(GPIO_TypeDef *gpiox, uint8_t pinNumber);

void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t state);
void GPIO_IRQPiorityConfig(uint8_t IRQNumber, uint8_t piority);
void GPIO_IRQ_ClearPanding(uint8_t pinNumber);


#endif /* __GPIO_H */
