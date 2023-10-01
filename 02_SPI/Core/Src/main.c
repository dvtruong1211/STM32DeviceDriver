#include "gpio.h"
#include "main.h"
#include "spi.h"



GPIO_Handle_t led ;
GPIO_Handle_t button ;

GPIO_Handle_t SCK1 ;
GPIO_Handle_t MOSI1 ;
GPIO_Handle_t MISO1 ;
GPIO_Handle_t NSS1 ;

GPIO_Handle_t SCK2 ;
GPIO_Handle_t MOSI2 ;
GPIO_Handle_t MISO2 ;
GPIO_Handle_t NSS2 ;

SPI_Handle_t spi1;
SPI_Handle_t spi2;

static void MX_GPIO_Init(void);
static void MX_SPI_Init(void);

uint8_t rxBuffer[12]; 

int main(void){
	MX_GPIO_Init();
	MX_SPI_Init();
	uint8_t txBuffer[12] = "daovantruong";
	NSS_ENABLE();
	
	while(1)
	{
		/* Loop */
		if(!ISBUTTON_PRESSED())
		{
			for(uint32_t i = 0; i < 500000; i++);
			NSS_DISABLE();
			SPI_SendData(&spi1, txBuffer, 12);
			NSS_ENABLE();
			for(uint32_t i = 0; i < 50000; i++);
		}
		if(rxBuffer[0] == 'd' && rxBuffer[1]== 'a'&& rxBuffer[11] == 'g')
		{
			LED_ON();
		}
	}
	
	return 0;
}

static void MX_GPIO_Init(void){
	
	memset(&MOSI1.GPIO_PinConfig, 0, sizeof(MOSI1.GPIO_PinConfig));
	memset(&MISO1.GPIO_PinConfig, 0, sizeof(MISO1.GPIO_PinConfig));
	memset(&SCK1.GPIO_PinConfig, 0, sizeof(SCK1.GPIO_PinConfig));
	memset(&NSS1.GPIO_PinConfig, 0, sizeof(NSS1.GPIO_PinConfig));
	
	memset(&MOSI2.GPIO_PinConfig, 0, sizeof(MOSI1.GPIO_PinConfig));
	memset(&MISO2.GPIO_PinConfig, 0, sizeof(MISO1.GPIO_PinConfig));
	memset(&SCK2.GPIO_PinConfig, 0, sizeof(SCK1.GPIO_PinConfig));
	memset(&NSS2.GPIO_PinConfig, 0, sizeof(NSS1.GPIO_PinConfig));
	
	/* Config LedPin */
	led.Gpiox = GPIOD;
	led.GPIO_PinConfig.pinNumber = 12;
	led.GPIO_PinConfig.pinMode = OUTPUT_MODE;
	led.GPIO_PinConfig.pinOpType = PUSH_PULL;
	GPIO_Init(&led);
	
	/* Config Button */
	button.Gpiox = GPIOA;
	button.GPIO_PinConfig.pinNumber = GPIO_PIN_1;
	button.GPIO_PinConfig.pinMode = INPUT_MODE;
	button.GPIO_PinConfig.pinPuPdControl = PULL_UP;
	button.GPIO_PinConfig.pinOpType = PUSH_PULL;
	GPIO_Init(&button);
	
	/* Config pin of SPI1 */
	MOSI1.Gpiox = GPIOB;
	MOSI1.GPIO_PinConfig.pinNumber = GPIO_PIN_5;
	MOSI1.GPIO_PinConfig.pinMode = ALT_MODE;
	MOSI1.GPIO_PinConfig.pinAltFunMode = AF5;
	GPIO_Init(&MOSI1);
	
	MISO1.Gpiox = GPIOB;
	MISO1.GPIO_PinConfig.pinNumber = GPIO_PIN_4;
	MISO1.GPIO_PinConfig.pinMode = ALT_MODE;
	MISO1.GPIO_PinConfig.pinAltFunMode = AF5;
	GPIO_Init(&MISO1);
	
	SCK1.Gpiox = GPIOB;
	SCK1.GPIO_PinConfig.pinNumber = GPIO_PIN_3;
	SCK1.GPIO_PinConfig.pinMode = ALT_MODE;
	SCK1.GPIO_PinConfig.pinAltFunMode = AF5;
	GPIO_Init(&SCK1);
	
	NSS1.Gpiox = GPIOB;
	NSS1.GPIO_PinConfig.pinNumber = GPIO_PIN_2;
	NSS1.GPIO_PinConfig.pinMode = OUTPUT_MODE;
	NSS1.GPIO_PinConfig.pinOpType = PUSH_PULL;
	GPIO_Init(&NSS1);
	
	/* Config pin of SPI2 */
	MOSI2.Gpiox = GPIOB;
	MOSI2.GPIO_PinConfig.pinNumber = GPIO_PIN_15;
	MOSI2.GPIO_PinConfig.pinMode = ALT_MODE;
	MOSI2.GPIO_PinConfig.pinAltFunMode = AF5;
	GPIO_Init(&MOSI2);
	
	MISO2.Gpiox = GPIOB;
	MISO2.GPIO_PinConfig.pinNumber = GPIO_PIN_14;
	MISO2.GPIO_PinConfig.pinMode = ALT_MODE;
	MISO2.GPIO_PinConfig.pinAltFunMode = AF5;
	GPIO_Init(&MISO2);
	
	SCK2.Gpiox = GPIOB;
	SCK2.GPIO_PinConfig.pinNumber = GPIO_PIN_10;
	SCK2.GPIO_PinConfig.pinMode = ALT_MODE;
	SCK2.GPIO_PinConfig.pinAltFunMode = AF5;
	GPIO_Init(&SCK2);
	
	NSS2.Gpiox = GPIOB;
	NSS2.GPIO_PinConfig.pinNumber = GPIO_PIN_12;
	NSS2.GPIO_PinConfig.pinMode = ALT_MODE;
	NSS2.GPIO_PinConfig.pinAltFunMode = AF5;
	GPIO_Init(&NSS2);
}

static void MX_SPI_Init(void){
	
	memset(&spi1.SPIConfig, 0, sizeof(spi1.SPIConfig));
	memset(&spi2.SPIConfig, 0, sizeof(spi2.SPIConfig));
	
	spi1.pSPIx = SPI1;
	spi1.SPIConfig.SPI_DeviceMode = SPI_MASTER_MODE;
	spi1.SPIConfig.SPI_BusConfig = SPI_BUS_FD;
	spi1.SPIConfig.SPI_SclkSpeed = SPI_FCLK_DIV_2;
	spi1.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	spi1.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	spi1.SPIConfig.SPI_CPHA = SPI_CPHA_FIRST;
	spi1.SPIConfig.SPI_SSM = SPI_SSM_ENABLE;
	spi1.SPIConfig.SPI_BitOutFirst = SPI_MSB_FIRST;
	SPI_Init(&spi1);
	
	spi2.pSPIx = SPI2;
	spi2.SPIConfig.SPI_DeviceMode = SPI_SLAVE_MODE;
	spi2.SPIConfig.SPI_BusConfig = SPI_BUS_FD;
	spi2.SPIConfig.SPI_SclkSpeed = SPI_FCLK_DIV_2;
	spi2.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	spi2.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	spi2.SPIConfig.SPI_CPHA = SPI_CPHA_FIRST;
	spi2.SPIConfig.SPI_SSM = SPI_SSM_DISABLE;
	spi2.SPIConfig.SPI_BitOutFirst = SPI_MSB_FIRST;
	spi2.IRQConfig.typeOfIRQ = SPI_RXNEIE;
	SPI_Init(&spi2);
	/* Enable interrupt Recieve */
	SPI_IRQPiority_Config(SPI2_IRQ_NUMBER, 1);
	SPI_IRQInterrupt_Config(&spi2, SPI2_IRQ_NUMBER, ENABLE);
}

void SPI_RxCpCallBack(SPI_Handle_t *SPIHandle){
	static uint8_t tmp = 0;
	SPI_Recieve_OneByte(SPIHandle, &rxBuffer[tmp]);
	tmp ++;
}


 void SPI2_IRQHandler(void){
	SPI_IRQ_Handler(&spi2);
}







