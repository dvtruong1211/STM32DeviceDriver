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
/*******************************************************************************
 * Definitions
 ******************************************************************************/

 /*******************************************************************************
 * Variables
 ******************************************************************************/
GPIO_Handle_t usart_gpio;
USART_Handler_t uart1;


uint8_t RxBuffer[10] = {0};

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
	uint8_t TxBuffer[10] = "--Start--";

	USART_SendData(&uart1, TxBuffer, 9);
	
	while(1)
	{
		USART_ReceiveData(&uart1, RxBuffer, 9);
	}
	
	return 0;
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
	usart_gpio.GPIO_PinConfig.pinNumber = GPIO_PIN_9; 
	GPIO_Init(&usart_gpio);

	/* Init Rx pin*/
	usart_gpio.GPIO_PinConfig.pinNumber = GPIO_PIN_10;
	GPIO_Init(&usart_gpio);
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





/******************************************************************************/






