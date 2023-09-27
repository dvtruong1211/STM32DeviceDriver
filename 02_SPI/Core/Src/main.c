#include "gpio.h"
#include "main.h"
#include "spi.h"


GPIO_Handle_t led;

GPIO_Handle_t SCK1;
GPIO_Handle_t MOSI1;
GPIO_Handle_t MISO1;
GPIO_Handle_t NSS1;

GPIO_Handle_t SCK2;
GPIO_Handle_t MOSI2;
GPIO_Handle_t MISO2;
GPIO_Handle_t NSS2;

SPI_Handle_t spi1;
SPI_Handle_t spi2;

static void MX_GPIO_Init(void);
static void MX_SPI_Init(void);


int main(void){
	
	
	
	
	while(1)
	{
		/* Loop */
	}
	
	return 0;
}

static void MX_GPIO_Init(void){
	/* Config LedPin */
	led.Gpiox = GPIOD;
	led.GPIO_PinConfig.pinNumber = 12;
	led.GPIO_PinConfig.pinMode = OUTPUT_MODE;
	led.GPIO_PinConfig.pinOpType = PUSH_PULL;
	GPIO_Init(&led);
	
	/* Config pin of SPI1 */
	MOSI1.Gpiox = GPIOA;
	MOSI1.GPIO_PinConfig.pinNumber = 7;
	MOSI1.GPIO_PinConfig.pinMode = ALT_MODE;
	MOSI1.GPIO_PinConfig.pinAltFunMode = AF5;
	GPIO_Init(&MOSI1);
	
	MISO1.Gpiox = GPIOA;
	MISO1.GPIO_PinConfig.pinNumber = 6;
	MISO1.GPIO_PinConfig.pinMode = ALT_MODE;
	MISO1.GPIO_PinConfig.pinAltFunMode = AF5;
	GPIO_Init(&MISO1);
	
	SCK1.Gpiox = GPIOA;
	SCK1.GPIO_PinConfig.pinNumber = 5;
	SCK1.GPIO_PinConfig.pinMode = ALT_MODE;
	SCK1.GPIO_PinConfig.pinAltFunMode = AF5;
	GPIO_Init(&SCK1);
	
	NSS1.Gpiox = GPIOA;
	NSS1.GPIO_PinConfig.pinNumber = 4;
	NSS1.GPIO_PinConfig.pinMode = OUTPUT_MODE;
	NSS1.GPIO_PinConfig.pinOpType = PUSH_PULL;
	GPIO_Init(&NSS1);
	
	/* Config pin of SPI2 */
	MOSI2.Gpiox = GPIOC;
	MOSI2.GPIO_PinConfig.pinNumber = 3;
	MOSI2.GPIO_PinConfig.pinMode = ALT_MODE;
	MOSI2.GPIO_PinConfig.pinAltFunMode = AF6;
	GPIO_Init(&MOSI2);
	
	MISO2.Gpiox = GPIOC;
	MISO2.GPIO_PinConfig.pinNumber = 2;
	MISO2.GPIO_PinConfig.pinMode = ALT_MODE;
	MISO2.GPIO_PinConfig.pinAltFunMode = AF6;
	GPIO_Init(&MISO2);
	
	SCK2.Gpiox = GPIOB;
	SCK2.GPIO_PinConfig.pinNumber = 10;
	SCK2.GPIO_PinConfig.pinMode = ALT_MODE;
	SCK2.GPIO_PinConfig.pinAltFunMode = AF6;
	GPIO_Init(&SCK2);
	
	NSS2.Gpiox = GPIOB;
	NSS2.GPIO_PinConfig.pinNumber = 12;
	NSS2.GPIO_PinConfig.pinMode = ALT_MODE;
	NSS2.GPIO_PinConfig.pinAltFunMode = AF6;
	GPIO_Init(&NSS2);
}

static void MX_SPI_Init(void){
	spi1.
	
}






