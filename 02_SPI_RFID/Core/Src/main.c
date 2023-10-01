#include "gpio.h"
#include "main.h"
#include "spi.h"
#include "rfid.h"

SPI_Handle_t spi1;

GPIO_Handle_t MOSI1;
GPIO_Handle_t MISO1;
GPIO_Handle_t SCK1;
GPIO_Handle_t NSS1;

static void MX_GPIO_Init(void);
static void MX_SPI_Init(void);

uint8_t cardCode[MAX_LEN];


int main(void){
	
	MX_GPIO_Init();
	MX_SPI_Init();
	NSS_ENABLE();
	MFRC522_Init();
	
	
	while(1)
	{
		if(!MFRC522_Request(PICC_REQIDL, cardCode))
		{
			if(!MFRC522_Anticoll(cardCode))
			{
				/* To do ..... */
			}
		}
		
		
	}
	
	return 0;
}

static void MX_GPIO_Init(void){
	
	memset(&MOSI1.GPIO_PinConfig, 0, sizeof(MOSI1.GPIO_PinConfig));
	memset(&MISO1.GPIO_PinConfig, 0, sizeof(MISO1.GPIO_PinConfig));
	memset(&SCK1.GPIO_PinConfig, 0, sizeof(SCK1.GPIO_PinConfig));
	memset(&NSS1.GPIO_PinConfig, 0, sizeof(NSS1.GPIO_PinConfig));
	
	
	
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
	
}

static void MX_SPI_Init(void){
	
	memset(&spi1.SPIConfig, 0, sizeof(spi1.SPIConfig));
	
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
	
}

 void *memset(void *ptr, int value, size_t num) {
    unsigned char *p = ptr;
    for (size_t i = 0; i < num; i++) {
        *p++ = (unsigned char)value;
    }
    return ptr;
}









