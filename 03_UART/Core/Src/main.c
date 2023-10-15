/**
 ******************************************************************************
 * @file    led.c
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
#include "main.h"
#include "uart.h"
#include "rcc.h"
#include "string.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/

 /*******************************************************************************
 * Variables
 ******************************************************************************/
GPIO_Handle_t usart_gpio;
GPIO_Handle_t led;
GPIO_Handle_t button;
USART_Handler_t uart1;



uint8_t Buffer[12] ;
uint8_t count = 0;
uint8_t count_cpt= 0;
uint8_t count_txe = 0;


/*******************************************************************************
 * Prototypes 
 ******************************************************************************/
static void MX_GPIO_Init(void);
static void MX_USART_Init(void);

/*******************************************************************************
 * Code
 ******************************************************************************/

int main(void)
{
	MX_GPIO_Init();
	MX_USART_Init();
	USART_PeriControl(USART1, ENABLE);
	USART_IRQPiorityConfig(USART1_IRQ_NUMBER, ENABLE);
	USART_IRQConfig(USART1_IRQ_NUMBER, 1);


	
	while(1)
	{
		for(uint32_t i = 0; i < 1000000; i++);
		while(USART_SendDataIT(&uart1, Buffer, 4) != USART_READY);
		
	}
	
	return 0;
}

void USART1_IRQHandler(void)
{
	USART_IRQHandler(&uart1);
}

void USART_ApplicationEventCallback(USART_Handler_t *pUSARTHandle, uint8_t Event)
{
	if(Event == USART_EVENT_RX_CMPLT)
	{
		USART_ReceiveDataIT(pUSARTHandle, Buffer, 1);
		count ++;
	}
	if(Event == USART_EVENT_TX_CMPLT)
	{
		count_cpt ++;
	}

	if(Event == USART_EVENT_TX_TXE)
	{
		count_txe ++;
	}
}

static void MX_GPIO_Init(void)
{
	usart_gpio.Gpiox = GPIOA;
	usart_gpio.GPIO_PinConfig.pinMode = ALT_MODE;
	usart_gpio.GPIO_PinConfig.pinSpeed = LOW_SPEED;
	usart_gpio.GPIO_PinConfig.pinPuPdControl = NO_PULL;
	usart_gpio.GPIO_PinConfig.pinOpType = PUSH_PULL;
	usart_gpio.GPIO_PinConfig.pinAltFunMode = AF7;

	/* Init Tx pin*/
	usart_gpio.GPIO_PinConfig.pinNumber = GPIO_PIN_15; 
	GPIO_Init(&usart_gpio);

	/* Init Rx pin*/
	usart_gpio.GPIO_PinConfig.pinNumber = GPIO_PIN_10;
	GPIO_Init(&usart_gpio);

	led.Gpiox = GPIOD;
	led.GPIO_PinConfig.pinMode = OUTPUT_MODE;
	led.GPIO_PinConfig.pinSpeed = LOW_SPEED;
	led.GPIO_PinConfig.pinPuPdControl = NO_PULL;
	led.GPIO_PinConfig.pinOpType = PUSH_PULL;
	/* Init led1 pin*/
	led.GPIO_PinConfig.pinNumber = GPIO_PIN_12;
	GPIO_Init(&led);
	/* Init led2 pin*/
	led.GPIO_PinConfig.pinNumber = GPIO_PIN_13;
	GPIO_Init(&led);
	/* Init led3 pin*/
	led.GPIO_PinConfig.pinNumber = GPIO_PIN_14;
	GPIO_Init(&led);

	button.Gpiox = GPIOB;
	button.GPIO_PinConfig.pinMode = INPUT_MODE;
	button.GPIO_PinConfig.pinSpeed = LOW_SPEED;
	button.GPIO_PinConfig.pinPuPdControl = PULL_UP;
	button.GPIO_PinConfig.pinOpType = PUSH_PULL;
	button.GPIO_PinConfig.pinNumber = GPIO_PIN_1;
	/* Init button pin*/
	GPIO_Init(&button);


}

static void MX_USART_Init(void)
{
	uart1.pUSARTx = USART1;
	uart1.USART_Config.USART_Mode = USART_MODE_TXRX;
	uart1.USART_Config.USART_Baudrate = USART_BAUD_115200;
	uart1.USART_Config.USART_NoOfStopBit = USART_STOPBITS_1;
	uart1.USART_Config.USART_WordLength = USART_WORDLEN_8;
	uart1.USART_Config.USART_ParityControl = USART_PARITY_DISABLE;
	uart1.USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_DISABLE;
	/* Init UART1 */
	USART_Init(&uart1);
	
}

uint8_t my_strcmp(const uint8_t *s1, const uint8_t *s2) 
{
    while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2) 
	{
        s1++;
        s2++;
    }

    if (*s1 == *s2) 
	{
        return 0; // Chuỗi giống nhau
    } 
	else if (*s1 < *s2)
	{
        return -1; // Chuỗi s1 nhỏ hơn s2
    } 
	else 
	{
        return 1; // Chuỗi s1 lớn hơn s2
    }
}





/******************************************************************************/






