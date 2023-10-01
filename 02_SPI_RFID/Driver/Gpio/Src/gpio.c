/**
 ******************************************************************************
 * @file    gpio.c
 * @author  truongdv
 * @version 1.0
 * @date    
 * @brief   
 * @history
 ******************************************************************************/


 /*******************************************************************************
 * Include
 ******************************************************************************/
#include "gpio.h"



/*******************************************************************************
 * Code
 ******************************************************************************/
void GPIO_ClockControl(GPIO_TypeDef* gpiox, uint8_t value){
	if(value == ENABLE)
	{
		if(gpiox == GPIOA)
			GPIOA_CLOCK_ENABLE();
		else if(gpiox == GPIOB)
			GPIOB_CLOCK_ENABLE();
		else if(gpiox == GPIOC)
			GPIOC_CLOCK_ENABLE();
		else if(gpiox == GPIOD)
			GPIOD_CLOCK_ENABLE();
		else if(gpiox == GPIOE)
			GPIOE_CLOCK_ENABLE();
		else if(gpiox == GPIOH)
			GPIOH_CLOCK_ENABLE();
	}
}

void GPIO_Init(GPIO_Handle_t *gpioHander){
	/* Enable clock for GPIO */
	GPIO_ClockControl(gpioHander->Gpiox, ENABLE);
	
	/* Config the mode of the gpio */
	if(gpioHander->GPIO_PinConfig.pinMode <= ANALOG_MODE)
	{
		/* -----------------------------Normal mode---------------------------------------------------- */
		gpioHander->Gpiox->MODER &= ~(0x03 << (2*gpioHander->GPIO_PinConfig.pinNumber) );
		gpioHander->Gpiox->MODER |= (gpioHander->GPIO_PinConfig.pinMode << (2*gpioHander->GPIO_PinConfig.pinNumber));
	}
	else
	{
		/* ---------------------------------Interrupt mode ----------------------------------------------------*/
		
		/* Set pin as a input pin */
		gpioHander->Gpiox->MODER &= ~(0x03 << (2*gpioHander->GPIO_PinConfig.pinNumber) );
		gpioHander->Gpiox->MODER |= (INPUT_MODE << (2*gpioHander->GPIO_PinConfig.pinNumber));
		
		/* Config the rasing or falling interrupt mode */
		if(gpioHander->GPIO_PinConfig.pinMode == IT_FT_MODE)
		{
			EXTI->FTSR |= (1U << gpioHander->GPIO_PinConfig.pinNumber);
			EXTI->RTSR &= ~(1U << gpioHander->GPIO_PinConfig.pinNumber);
		}
		else if(gpioHander->GPIO_PinConfig.pinMode == IT_RT_MODE)
		{
			EXTI->FTSR &= ~(1U << gpioHander->GPIO_PinConfig.pinNumber);
			EXTI->RTSR |= (1U << gpioHander->GPIO_PinConfig.pinNumber);
		}
		else if(gpioHander->GPIO_PinConfig.pinMode == IT_RFT_MODE)
		{
			EXTI->FTSR |= (1U << gpioHander->GPIO_PinConfig.pinNumber);
			EXTI->RTSR |= (1U << gpioHander->GPIO_PinConfig.pinNumber);
		}
		
		/* Config the EXTI connect to gpio pin */
		SYSCFG_CLOCK_ENABLE();
		if(gpioHander->GPIO_PinConfig.pinNumber > GPIO_PIN_11)
		{
			SYSCFG->EXTICR[3] &= ~( 0x0f << (4 * (gpioHander->GPIO_PinConfig.pinNumber % 12 )));
			if(gpioHander->Gpiox == GPIOA)
			{
				SYSCFG->EXTICR[3] |= ( 0x00 << (4 * (gpioHander->GPIO_PinConfig.pinNumber % 12 )));
			}
			else if(gpioHander->Gpiox ==GPIOB)
			{
				SYSCFG->EXTICR[3] |= ( 0x01 << (4 * (gpioHander->GPIO_PinConfig.pinNumber % 12 )));
			}
			else if(gpioHander->Gpiox == GPIOC)
			{
				SYSCFG->EXTICR[3] |= ( 0x02 << (4 * (gpioHander->GPIO_PinConfig.pinNumber % 12 )));
			}
			else if(gpioHander->Gpiox == GPIOD)
			{
				SYSCFG->EXTICR[3] |= ( 0x03 << (4 * (gpioHander->GPIO_PinConfig.pinNumber % 12 )));
			}
			else if(gpioHander->Gpiox == GPIOE)
			{
				SYSCFG->EXTICR[3] |= ( 0x04 << (4 * (gpioHander->GPIO_PinConfig.pinNumber % 12 )));
			}
			else if(gpioHander->Gpiox == GPIOH)
			{
				SYSCFG->EXTICR[3] |= ( 0x07 << (4 * (gpioHander->GPIO_PinConfig.pinNumber % 12 )));
			}
		}
		else if(gpioHander->GPIO_PinConfig.pinNumber > GPIO_PIN_7)
		{
			SYSCFG->EXTICR[2] &= ~( 0x0f << (4 * (gpioHander->GPIO_PinConfig.pinNumber % 8 )));
			if(gpioHander->Gpiox == GPIOA)
			{
				SYSCFG->EXTICR[2] |= ( 0x00 << (4 * (gpioHander->GPIO_PinConfig.pinNumber % 8 )));
			}
			else if(gpioHander->Gpiox == GPIOB)
			{
				SYSCFG->EXTICR[2] |= ( 0x01 << (4 * (gpioHander->GPIO_PinConfig.pinNumber % 8 )));
			}
			else if(gpioHander->Gpiox == GPIOC)
			{
				SYSCFG->EXTICR[2] |= ( 0x02 << (4 * (gpioHander->GPIO_PinConfig.pinNumber % 8 )));
			}
			else if(gpioHander->Gpiox == GPIOD)
			{
				SYSCFG->EXTICR[2] |= ( 0x03 << (4 * (gpioHander->GPIO_PinConfig.pinNumber % 8 )));
			}
			else if(gpioHander->Gpiox == GPIOE)
			{
				SYSCFG->EXTICR[2] |= ( 0x04 << (4 * (gpioHander->GPIO_PinConfig.pinNumber % 8 )));
			}
			else if(gpioHander->Gpiox == GPIOH)
			{
				SYSCFG->EXTICR[2] |= ( 0x07 << (4 * (gpioHander->GPIO_PinConfig.pinNumber % 8 )));
			}
		}
		else if(gpioHander->GPIO_PinConfig.pinNumber > GPIO_PIN_3)
		{
			SYSCFG->EXTICR[1] &= ~( 0x0f << (4 * (gpioHander->GPIO_PinConfig.pinNumber % 4 )));
			if(gpioHander->Gpiox == GPIOA)
			{
				SYSCFG->EXTICR[1] |= ( 0x00 << (4 * (gpioHander->GPIO_PinConfig.pinNumber % 4 )));
			}
			else if(gpioHander->Gpiox == GPIOB)
			{
				SYSCFG->EXTICR[1] |= ( 0x01 << (4 * (gpioHander->GPIO_PinConfig.pinNumber % 4 )));
			}
			else if(gpioHander->Gpiox == GPIOC)
			{
				SYSCFG->EXTICR[1] |= ( 0x02 << (4 * (gpioHander->GPIO_PinConfig.pinNumber % 4 )));
			}
			else if(gpioHander->Gpiox == GPIOD)
			{
				SYSCFG->EXTICR[1] |= ( 0x03 << (4 * (gpioHander->GPIO_PinConfig.pinNumber % 4 )));
			}
			else if(gpioHander->Gpiox == GPIOE)
			{
				SYSCFG->EXTICR[1] |= ( 0x04 << (4 * (gpioHander->GPIO_PinConfig.pinNumber % 4 )));
			}
			else if(gpioHander->Gpiox == GPIOH)
			{
				SYSCFG->EXTICR[1] |= ( 0x07 << (4 * (gpioHander->GPIO_PinConfig.pinNumber % 4 )));
			}
		}
		else
		{
			SYSCFG->EXTICR[0] &= ~( 0x0f << (4 * (gpioHander->GPIO_PinConfig.pinNumber )));
			if(gpioHander->Gpiox == GPIOA)
			{
				SYSCFG->EXTICR[0] |= ( 0x00 << (4 * (gpioHander->GPIO_PinConfig.pinNumber )));
			}
			else if(gpioHander->Gpiox == GPIOB)
			{
				SYSCFG->EXTICR[0] |= ( 0x01 << (4 * (gpioHander->GPIO_PinConfig.pinNumber )));
			}
			else if(gpioHander->Gpiox == GPIOC)
			{
				SYSCFG->EXTICR[0] |= ( 0x02 << (4 * (gpioHander->GPIO_PinConfig.pinNumber )));
			}
			else if(gpioHander->Gpiox == GPIOD)
			{
				SYSCFG->EXTICR[0] |= ( 0x03 << (4 * (gpioHander->GPIO_PinConfig.pinNumber )));
			}
			else if(gpioHander->Gpiox == GPIOE)
			{
				SYSCFG->EXTICR[0] |= ( 0x04 << (4 * (gpioHander->GPIO_PinConfig.pinNumber )));
			}
			else if(gpioHander->Gpiox == GPIOH)
			{
				SYSCFG->EXTICR[0] |= ( 0x07 << (4 * (gpioHander->GPIO_PinConfig.pinNumber )));
			}
	
			}
		/* Enable mask EXTI corresponding */
		EXTI->IMR |= (1U << gpioHander->GPIO_PinConfig.pinNumber);
	}
	
	/* Config the speed of GPIO */
	gpioHander->Gpiox->OSPEEDR &= ~(0x03 << (2*gpioHander->GPIO_PinConfig.pinNumber) );
	gpioHander->Gpiox->OSPEEDR |= (gpioHander->GPIO_PinConfig.pinSpeed << (2*gpioHander->GPIO_PinConfig.pinNumber));
	
	/* Config the pull up pull down mode*/
	if(gpioHander->GPIO_PinConfig.pinPuPdControl == RESERVED)
	{
		gpioHander->Gpiox->PUPDR &= ~(0x03 << (2*gpioHander->GPIO_PinConfig.pinNumber) );
	}
	else
	{
		gpioHander->Gpiox->PUPDR &= ~(0x03 << (2*gpioHander->GPIO_PinConfig.pinNumber) );
		gpioHander->Gpiox->PUPDR |= (gpioHander->GPIO_PinConfig.pinPuPdControl << (2*gpioHander->GPIO_PinConfig.pinNumber));
	}
	
	/* Config the the pin as output push-pull or open-drain */
	gpioHander->Gpiox->OTYPER &= ~(0x01 << (gpioHander->GPIO_PinConfig.pinNumber) );
	gpioHander->Gpiox->OTYPER |= (gpioHander->GPIO_PinConfig.pinOpType << (gpioHander->GPIO_PinConfig.pinNumber));
	
	/* Config the alternate function mode */
	if(gpioHander->GPIO_PinConfig.pinMode == ALT_MODE)
	{
		if(gpioHander->GPIO_PinConfig.pinNumber <= 7)
		{
			gpioHander->Gpiox->AFR[0] &= ~(0x0f << (4*gpioHander->GPIO_PinConfig.pinNumber));
			gpioHander->Gpiox->AFR[0] |= (gpioHander->GPIO_PinConfig.pinAltFunMode << (4*gpioHander->GPIO_PinConfig.pinNumber));
		}
		else
		{
			gpioHander->Gpiox->AFR[1] &= ~(0x0f << (4*(gpioHander->GPIO_PinConfig.pinNumber % 8)));
			gpioHander->Gpiox->AFR[1] |= (gpioHander->GPIO_PinConfig.pinAltFunMode << (4*(gpioHander->GPIO_PinConfig.pinNumber % 8)));
		} 
	}
		
}

void GPIO_DeInit(GPIO_TypeDef *gpiox){
	if(gpiox == GPIOA)
			GPIOA_CLOCK_RESET();
		else if(gpiox == GPIOB)
			GPIOB_CLOCK_RESET();
		else if(gpiox == GPIOC)
			GPIOC_CLOCK_RESET();
		else if(gpiox == GPIOD)
			GPIOD_CLOCK_RESET();
		else if(gpiox == GPIOE)
			GPIOE_CLOCK_RESET();
		else if(gpiox == GPIOH)
			GPIOH_CLOCK_RESET();
}

uint8_t GPIO_ReadPin(GPIO_TypeDef* gpiox, uint8_t pinNumber){
	uint32_t state = (gpiox->IDR & (1U << pinNumber));
	if(state)
		return 1;
	return 0;
}

uint16_t GPIO_ReadPort(GPIO_TypeDef* gpiox){
	uint16_t value = (uint16_t)gpiox->IDR;
	return value;
}

void GPIO_WritePin(GPIO_TypeDef *gpiox, uint8_t pinNumber, uint8_t value){
	if(value == GPIO_PIN_SET)
	{
		gpiox->ODR |= (1U << pinNumber);
	}
	else if(value == GPIO_PIN_RESET)
	{
		gpiox->ODR &= ~(1U << pinNumber);
	}
	
}

void GPIO_WritePort(GPIO_TypeDef *gpiox, uint16_t value){
	gpiox->ODR = value;
}
void GPIO_PinToggle(GPIO_TypeDef *gpiox, uint8_t pinNumber){
	gpiox->ODR ^= (1U << pinNumber);
}

void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t state){
	if(state == ENABLE)
	{
		if(IRQNumber < 32)
		{
			NVIC->ISER[0] |= (1U << IRQNumber);
		}
		else if(IRQNumber >= 32  && IRQNumber < 64)
		{
			NVIC->ISER[1] |= (1U << (IRQNumber % 32));
		}
		else if(IRQNumber >= 64  && IRQNumber < 96)
		{
			NVIC->ISER[2] |= (1U << (IRQNumber % 64));
		}
	}
	else
	{
		if(IRQNumber < 32)
		{
			NVIC->ICER[0] |= (1U << IRQNumber);
		}
		else if(IRQNumber >= 32  && IRQNumber < 64)
		{
			NVIC->ICER[1] |= (1U << (IRQNumber % 32));
		}
		else if(IRQNumber >= 64  && IRQNumber < 96)
		{
			NVIC->ICER[2] |= (1U << (IRQNumber % 64));
		}
	}
}
void GPIO_IRQPiorityConfig(uint8_t IRQNumber, uint8_t piority){
	NVIC->IP[IRQNumber] &= ~(0x0f << 4);
	NVIC->IP[IRQNumber] |=  (piority << 4);
}
void GPIO_IRQ_ClearPending(uint8_t pinNumber){
	if(EXTI->PR & (1U << pinNumber))
	{
		EXTI->PR |= (1U << pinNumber);
	}
}



/***********************************************/