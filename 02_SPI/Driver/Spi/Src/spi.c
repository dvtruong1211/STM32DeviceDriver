/**
 ******************************************************************************
 * @file    spi.c
 * @author  truongdv
 * @version 1.0
 * @date
 * @brief
 * @history
 ******************************************************************************/
 
 /*******************************************************************************
 * Include
 ******************************************************************************/
#include "spi.h"


/*******************************************************************************
 * Code
 ******************************************************************************/

void SPI_PeriClockControl(SPI_TypeDef *pSPIx, uint8_t EnOrDi){
	if(EnOrDi == ENABLE)
	{
		if(pSPIx == SPI1)
			SPI1_CLOCK_ENABLE();
		else if(pSPIx == SPI2)
			SPI2_CLOCK_ENABLE();
		else if(pSPIx == SPI3)
			SPI3_CLOCK_ENABLE();
		else if(pSPIx == SPI4)
			SPI4_CLOCK_ENABLE();
		else if(pSPIx == SPI5)
			SPI5_CLOCK_ENABLE();
	}
	else
	{
		/* Do something */
	}
}

void SPI_Init(SPI_Handle_t *pSPIHandle){
	SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);
	//uint32_t temp = 0;
	
	/* Config the device mode */
	if(pSPIHandle->SPIConfig.SPI_DeviceMode == SPI_MASTER_MODE)
	{
		pSPIHandle->pSPIx->CR1  |= (1U << 2);
	}
	else if(pSPIHandle->SPIConfig.SPI_DeviceMode == SPI_SLAVE_MODE)
	{
		pSPIHandle->pSPIx->CR1  &= ~(1U << 2);
	}
	
	/* Config the Bus */
	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_FD)
	{
		pSPIHandle->pSPIx->CR1 &=~ (1U << 15); 
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_HD)
	{
		pSPIHandle->pSPIx->CR1 |= (1U << 15); 
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_SIMPLEX_RXONLY)
	{
		pSPIHandle->pSPIx->CR1 &=~ (1U << 15); 
		pSPIHandle->pSPIx->CR1 |= (1U << 10);
	}
		
	
	/* Config the clock speed */
	if(pSPIHandle->SPIConfig.SPI_SclkSpeed == SPI_FCLK_DIV_2)
	{
		pSPIHandle->pSPIx->CR1 &=~ (0x07U << 3);
		pSPIHandle->pSPIx->CR1 |=  (0x00U << 3);
	}
	else if(pSPIHandle->SPIConfig.SPI_SclkSpeed == SPI_FCLK_DIV_4)
	{
		pSPIHandle->pSPIx->CR1 &=~ (0x07U << 3);
		pSPIHandle->pSPIx->CR1 |=  (0x01U << 3);
	}
	else if(pSPIHandle->SPIConfig.SPI_SclkSpeed == SPI_FCLK_DIV_8)
	{
		pSPIHandle->pSPIx->CR1 &=~ (0x07U << 3);
		pSPIHandle->pSPIx->CR1 |=  (0x02U << 3);
	}
	else if(pSPIHandle->SPIConfig.SPI_SclkSpeed == SPI_FCLK_DIV_16)
	{
		pSPIHandle->pSPIx->CR1 &=~ (0x07U << 3);
		pSPIHandle->pSPIx->CR1 |=  (0x03U << 3);
	}
	else if(pSPIHandle->SPIConfig.SPI_SclkSpeed == SPI_FCLK_DIV_32)
	{
		pSPIHandle->pSPIx->CR1 &=~ (0x07U << 3);
		pSPIHandle->pSPIx->CR1 |=  (0x04U << 3);
	}
	else if(pSPIHandle->SPIConfig.SPI_SclkSpeed == SPI_FCLK_DIV_64)
	{
		pSPIHandle->pSPIx->CR1 &=~ (0x07U << 3);
		pSPIHandle->pSPIx->CR1 |=  (0x05U << 3);
	}
	else if(pSPIHandle->SPIConfig.SPI_SclkSpeed == SPI_FCLK_DIV_128)
	{
		pSPIHandle->pSPIx->CR1 &=~ (0x07U << 3);
		pSPIHandle->pSPIx->CR1 |=  (0x06U << 3);
	}
	else if(pSPIHandle->SPIConfig.SPI_SclkSpeed == SPI_FCLK_DIV_256)
	{
		pSPIHandle->pSPIx->CR1 &=~ (0x07U << 3);
		pSPIHandle->pSPIx->CR1 |=  (0x07U << 3);
	}
	
	/* Config data frame format */
	if(pSPIHandle->SPIConfig.SPI_DFF == SPI_DFF_8BITS)
	{
		pSPIHandle->pSPIx->CR1 &=~ (1U << 11);
	}
	else if(pSPIHandle->SPIConfig.SPI_DFF == SPI_DFF_16BITS)
	{
		pSPIHandle->pSPIx->CR1 |= (1U << 11);
	}
	
	/* Config CPOL */
	if(pSPIHandle->SPIConfig.SPI_CPOL == SPI_CPOL_LOW)
	{
		pSPIHandle->pSPIx->CR1 &= ~(1U << 1);
	}
	else if(pSPIHandle->SPIConfig.SPI_CPOL == SPI_CPOL_HIGH)
	{
		pSPIHandle->pSPIx->CR1 |= (1U << 1);
	}
	
	/* Config CPHA */
	if(pSPIHandle->SPIConfig.SPI_CPHA == SPI_CPHA_FIRST)
	{
		pSPIHandle->pSPIx->CR1 &= ~(1U << 0);
	}
	else if(pSPIHandle->SPIConfig.SPI_CPHA == SPI_CPHA_SECOND)
	{
		pSPIHandle->pSPIx->CR1 |= (1U << 0);
	}
	
	/* Config software slave select management */
	if(pSPIHandle->SPIConfig.SPI_SSM == SPI_SSM_DISABLE)
	{
		pSPIHandle->pSPIx->CR1 &= ~(1U << 9);
	}
	else if(pSPIHandle->SPIConfig.SPI_SSM == SPI_SSM_ENABLE)
	{
		pSPIHandle->pSPIx->CR1 |= (1U << 8);
		pSPIHandle->pSPIx->CR1 |= (1U << 9);
	}
	
	/* Config bit out first*/
	if(pSPIHandle->SPIConfig.SPI_BitOutFirst == SPI_MSB_FIRST)
	{
		pSPIHandle->pSPIx->CR1 &= ~(1U << 7);
	}
	else if(pSPIHandle->SPIConfig.SPI_BitOutFirst == SPI_LSB_FIRST)
	{
		pSPIHandle->pSPIx->CR1 |= (1U << 7);
	}
	SPI_Enable(pSPIHandle);
	
}

void SPI_DeInit(SPI_TypeDef *pSPIx){
	/* Do something */
}

void SPI_Enable(SPI_Handle_t *pSPIHandle){
	/* Enable the SPIx*/
	pSPIHandle->pSPIx->CR1 |= (1U << 6);
}

void SPI_Disable(SPI_Handle_t *pSPIHandle){
	/* Disable the SPIx*/
	pSPIHandle->pSPIx->CR1 &=~ (1U << 6);
}

void SPI_SendData(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t size){
	for(uint32_t i = 0; i < size; i++)
	{
		/* Doi co busy tat */
		while(__SPI_GET_FLAG(pSPIHandle->pSPIx, SPI_BUSY_FLAG)); 
		
		while(__SPI_GET_FLAG(pSPIHandle->pSPIx, SPI_OVR_FLAG))
		{
			__SPI_CLR_OVR_FLAG(pSPIHandle->pSPIx);
		}
		/* Transmit data */
		if(pSPIHandle->SPIConfig.SPI_DFF == SPI_DFF_16BITS)
		{
			while(__SPI_GET_FLAG(pSPIHandle->pSPIx, SPI_TXE_FLAG) == RESET);
			pSPIHandle->pSPIx->DR = *((uint16_t*)pTxBuffer);
			i += 1;
			pTxBuffer += 2;
		}
		else if(pSPIHandle->SPIConfig.SPI_DFF == SPI_DFF_8BITS)
		{
			while(__SPI_GET_FLAG(pSPIHandle->pSPIx, SPI_TXE_FLAG) == RESET);
			pSPIHandle->pSPIx->DR = *(pTxBuffer+i);
		}
	}
}

void SPI_RecieveData(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t size){
	for(uint32_t i = 0; i < size; i++)
	{
		/* Doi co busy tat */
		while(__SPI_GET_FLAG(pSPIHandle->pSPIx, SPI_BUSY_FLAG)); 
		/* Recieve data */
		if(pSPIHandle->SPIConfig.SPI_DFF == SPI_DFF_16BITS)
		{
			while(__SPI_GET_FLAG(pSPIHandle->pSPIx, SPI_RXNE_FLAG) == RESET);
			*((uint16_t*)pRxBuffer) = pSPIHandle->pSPIx->DR;
			i++;
			pRxBuffer += 2;
		}
		else if(pSPIHandle->SPIConfig.SPI_DFF == SPI_DFF_8BITS)
		{
			while(__SPI_GET_FLAG(pSPIHandle->pSPIx, SPI_RXNE_FLAG) == RESET);
			*(pRxBuffer+i) = (uint8_t)pSPIHandle->pSPIx->DR;
		}
	}
}

void SPI_Recieve_OneByte(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer){
	while(__SPI_GET_FLAG(pSPIHandle->pSPIx, SPI_BUSY_FLAG)); 
		/* Recieve data */
	if(pSPIHandle->SPIConfig.SPI_DFF == SPI_DFF_16BITS)
	{
		while(__SPI_GET_FLAG(pSPIHandle->pSPIx, SPI_RXNE_FLAG) == RESET);
		*((uint16_t*)pRxBuffer) = pSPIHandle->pSPIx->DR;
	}
	else if(pSPIHandle->SPIConfig.SPI_DFF == SPI_DFF_8BITS)
	{
		while(__SPI_GET_FLAG(pSPIHandle->pSPIx, SPI_RXNE_FLAG) == RESET);
		*pRxBuffer = (uint8_t)pSPIHandle->pSPIx->DR;
	}
}

void SPI_IRQInterrupt_Config(SPI_Handle_t *SPIHandle,uint8_t IRQNumber, uint8_t EnOrDi){
	/* Disable mask of interrupt */
	if(SPIHandle->IRQConfig.typeOfIRQ == SPI_TXEIE)
	{
		SPIHandle->pSPIx->CR2 |= SPI_TXEIE;
	}
	if(SPIHandle->IRQConfig.typeOfIRQ == SPI_RXNEIE)
	{
		SPIHandle->pSPIx->CR2 |= SPI_RXNEIE;
	}
	if(SPIHandle->IRQConfig.typeOfIRQ == SPI_ERRIE)
	{
		SPIHandle->pSPIx->CR2 |= SPI_ERRIE;
	}
	
	if(EnOrDi == ENABLE)
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
	else if(EnOrDi = DISABLE)
	{
		if(IRQNumber >= 64 )
		{
			NVIC->ICER[2] |= (1U << (IRQNumber % 64));
		}
		else if(IRQNumber >= 32)
		{
			NVIC->ICER[1] |= (1U << (IRQNumber % 32));
		}
		else if(IRQNumber >= 0)
		{
			NVIC->ICER[0] |= (1U << (IRQNumber));
		}
	}
}

void SPI_IRQPiority_Config(uint8_t IRQNumber, uint8_t piority){
	NVIC->IP[IRQNumber] &= ~(0x0f << 4);
	NVIC->IP[IRQNumber] |=  (piority << 4);
}

__attribute__((weak)) void SPI_TxCpCallBack(SPI_Handle_t *SPIHandle){
	
}

__attribute__((weak)) void SPI_RxCpCallBack(SPI_Handle_t *SPIHandle){
	
}

__attribute__((weak)) void SPI_ErrorCallBack(SPI_Handle_t *SPIHandle){
	
}



void SPI_IRQ_Handler(SPI_Handle_t *SPIHandle){
	if( (SPIHandle->pSPIx->CR2 & SPI_TXEIE) && (SPIHandle->pSPIx->SR && SPI_TXE_FLAG) )
	{
		SPI_TxCpCallBack(SPIHandle);
		return;
	}
	if( (SPIHandle->pSPIx->CR2 & SPI_RXNEIE) && (SPIHandle->pSPIx->SR && SPI_RXNE_FLAG) )
	{
		SPI_RxCpCallBack(SPIHandle);
		return;
	}
	if( (SPIHandle->pSPIx->CR2 & SPI_ERRIE) && (SPIHandle->pSPIx->SR && SPI_OVR_FLAG) )
	{
		SPI_ErrorCallBack(SPIHandle);
		return;
	}
}



/***********************************************/