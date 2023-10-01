/**
 ******************************************************************************
 * @file    spi.h
 * @author  truongdv
 * @version 1.0
 * @date
 * @brief
 * @history
 ******************************************************************************/
 
#ifndef __SPI_H
#define __SPI_H
 
#include "memory_map_stm32f411xe.h"

/* Exported types ------------------------------------------------------------*/

typedef struct{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_SclkSpeed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;
	uint8_t SPI_BitOutFirst;
}SPI_Config_t;

typedef void(*SPI_IrqCallBack)(SPI_TypeDef *pSPIx);

typedef struct{
	uint32_t typeOfIRQ;
	
}SPI_IRQConfig_t;
 
typedef struct {
	SPI_TypeDef* pSPIx;
	SPI_Config_t SPIConfig;
	SPI_IRQConfig_t IRQConfig;
}SPI_Handle_t;


/* Exported macro ------------------------------------------------------------*/

/*
	FLAG set or reset
*/
#define FLAG_SET				SET
#define FLAG_RESET				RESET

/*
	SPI Device Mode Select
*/
#define SPI_MASTER_MODE 		1
#define SPI_SLAVE_MODE 			0


/*
	SPI Bus Config
*/
#define SPI_BUS_FD				0
#define SPI_BUS_HD				1
#define SPI_BUS_SIMPLEX_RXONLY	2

/*
	SPI Clock Config
*/
#define SPI_FCLK_DIV_2			0
#define SPI_FCLK_DIV_4			1
#define SPI_FCLK_DIV_8			2
#define SPI_FCLK_DIV_16			3
#define SPI_FCLK_DIV_32			4
#define SPI_FCLK_DIV_64			5
#define SPI_FCLK_DIV_128		6
#define SPI_FCLK_DIV_256		7	

/*
	SPI Data Frame Format Config
*/

#define SPI_DFF_8BITS			0
#define SPI_DFF_16BITS			1

/*
	SPI Clock Polarity
*/
#define SPI_CPOL_LOW			0
#define SPI_CPOL_HIGH			1

/*
	SPI Clock Phase
*/
#define SPI_CPHA_FIRST			0
#define SPI_CPHA_SECOND			1

/*
	SPI Slave management 
*/
#define SPI_SSM_DISABLE			0
#define SPI_SSM_ENABLE			1

/*
	SPI Frame format		
*/
#define SPI_MSB_FIRST			0
#define SPI_LSB_FIRST			1


/*
	FLAG name	
*/
#define SPI_TXE_FLAG			(1U << 1)
#define SPI_RXNE_FLAG			(1U << 0)
#define SPI_BUSY_FLAG			(1U << 7)
#define SPI_OVR_FLAG			(1U << 6)

/*
	Disable mask of interrup SPI	
*/

#define SPI_TXEIE				(1U << 7)
#define SPI_RXNEIE				(1U << 6)
#define SPI_ERRIE				(1U << 5)

/*
	Vector interrupt spi	
*/
#define SPI1_IRQ_NUMBER			35
#define SPI2_IRQ_NUMBER			36
#define SPI3_IRQ_NUMBER			51
#define SPI4_IRQ_NUMBER			84
#define SPI5_IRQ_NUMBER			85

/*
	Macro function to work with flag 
*/

/* Get flag */
#define __SPI_GET_FLAG(pSPIx, flagName)		(((pSPIx->SR) & flagName) != RESET)
	
/* Clear OVR flag */
#define __SPI_CLR_OVR_FLAG(pSPIx)			do{ uint16_t dummyData = pSPIx->DR; (void)dummyData; }while(0)



/* Exported functions ------------------------------------------------------- */

void SPI_PeriClockControl(SPI_TypeDef *pSPIx, uint8_t EnOrDi);

void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_TypeDef *pSPIx);

void SPI_Enable(SPI_Handle_t *pSPIHandle);
void SPI_Disable(SPI_Handle_t *pSPIHandle);

void SPI_SendData(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t size);
void SPI_RecieveData(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t size);
void SPI_Recieve_OneByte(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer);

uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t size);
uint8_t SPI_RecieveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t size);

void SPI_IRQInterrupt_Config(SPI_Handle_t *SPIHandle,uint8_t IRQNumber, uint8_t EnOrDi);
void SPI_IRQPiority_Config(uint8_t IRQNumber, uint8_t piority);

void SPI_IRQ_Handler(SPI_Handle_t *pSPIx);

#endif  /* __SPI_H */    
 