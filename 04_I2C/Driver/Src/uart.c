/**
 ******************************************************************************
 * @file    uart.c
 * @author  truongdv
 * @version 1.0
 * @date    
 * @brief   
 * @history
 ******************************************************************************/


/*******************************************************************************
 * Include
 ******************************************************************************/
#include "uart.h"
#include "rcc.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

 /*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
void USART_PeriClockControl(USART_TypeDef *pUSARTx, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)
    {
        if(pUSARTx == USART1)
        {
            USART1_CLOCK_ENABLE();
        }
        else if(pUSARTx == USART2)
        {
            USART2_CLOCK_ENABLE();
        }
        else if(pUSARTx == USART6)
        {
            USART6_CLOCK_ENABLE();
        }
    }
    else
    {
        if(pUSARTx == USART1)
        {
            USART1_CLOCK_DISABLE();
        }
        else if(pUSARTx == USART2)
        {
            USART2_CLOCK_DISABLE();
        }
        else if(pUSARTx == USART6)
        {
            USART6_CLOCK_DISABLE();
        }
    }
}

void USART_Init(USART_Handler_t *pUSARTHandle)
{
    uint32_t tmp = 0;
    USART_PeriClockControl(pUSARTHandle->pUSARTx, ENABLE);

    /* Mode config */
    if(pUSARTHandle->USART_Config.USART_Mode == USART_MODE_TX)
    {
        tmp |= (1U << USART_CR1_TE);
    }
    else if(pUSARTHandle->USART_Config.USART_Mode == USART_MODE_RX)
    {
        tmp |= (1U << USART_CR1_RE);
    }
    else if(pUSARTHandle->USART_Config.USART_Mode == USART_MODE_TXRX)
    {
        tmp |= ( (1U << USART_CR1_TE)|(1U << USART_CR1_RE) );
    }

    /* Wordlength config */
    if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_8)
    {
        tmp &=~ (1U << USART_CR1_M);
    }
    else if (pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9)
    {
         tmp |= (1U << USART_CR1_M);
    }

    /* Parity config */
    if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
    {
        tmp &=~ (1U << USART_CR1_PCE);
    }
    else if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EVEN)
    {
        tmp |=  (1U << USART_CR1_PCE);
        tmp &=~  (1U << USART_CR1_PS);
    }
    else if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_ODD)
    {
        tmp |=  (1U << USART_CR1_PCE);
        tmp |=  (1U << USART_CR1_PS);
    }
    pUSARTHandle->pUSARTx->CR1 = tmp;

    /* Stopbits config */
    pUSARTHandle->pUSARTx->CR2 = (pUSARTHandle->USART_Config.USART_NoOfStopBit << 12);

    /* Hardware flow control config */
    if(pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_DISABLE)
    {
        pUSARTHandle->pUSARTx->CR3 &=~ (0x03U << USART_CR3_RTSE);
    }
    else if(pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS)
    {
        pUSARTHandle->pUSARTx->CR3 |= (1U << USART_CR3_CTSE);
    }
    else if(pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_RTS)
    {
        pUSARTHandle->pUSARTx->CR3 |= (1U << USART_CR3_RTSE);
    }
    else if(pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS)
    {
        pUSARTHandle->pUSARTx->CR3 |= ( (1U << USART_CR3_RTSE)|(1U << USART_CR3_CTSE) );
    }

    /* Baudrate setup */
    USART_SetBaudRate(pUSARTHandle->pUSARTx, pUSARTHandle->USART_Config.USART_Baudrate);


    pUSARTHandle->pTxBuffer = NULL;
    pUSARTHandle->pRxBuffer = NULL;
    pUSARTHandle->TxLen = 0;
    pUSARTHandle->RxLen = 0;
    pUSARTHandle->TxBusyState = USART_READY;
    pUSARTHandle->RxBusyState = USART_READY;
}

void USART_SetBaudRate(USART_TypeDef *pUSARTx, uint32_t BaudRate)
{
    uint32_t pclk;
    uint32_t usart_div;
    uint32_t m_part, f_part;

    if(pUSARTx == USART1 || pUSARTx == USART6)
    {
        pclk = RCC_GetPCLK2();
    }
    else if(pUSARTx == USART2)
    {
        pclk = RCC_GetPCLK1();
    }
    
    usart_div = (pclk * 100)/(16 * BaudRate);
    m_part = usart_div / 100;
    f_part = (((usart_div - m_part*100)* 16 + 50)/100);

    pUSARTx->BRR = ( (m_part << 4U)|(f_part << 0U) );

}

void USART_DeInit(USART_TypeDef *pUSARTx)
{
    if(pUSARTx == USART1)
    {
        USART1_CLOCK_RESET();  
    }
    else if(pUSARTx == USART2)
    {
        USART2_CLOCK_RESET();
    }
    else if(pUSARTx == USART6)
    {
        USART6_CLOCK_RESET();
    }
    
}

void USART_PeriControl(USART_TypeDef *pUSARTx, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)
    {
        pUSARTx->CR1 |= (1U << USART_CR1_UE);
    }
    else
    {
        pUSARTx->CR1 &=~ (1U << USART_CR1_UE);
    }
}

uint8_t USART_GetFlagStatus(USART_TypeDef *pUSARTx, uint8_t FlagName)
{
    return (pUSARTx->SR & FlagName);
}

void USART_SendData(USART_Handler_t *pUSARTHandle, uint8_t *TxBuffer, uint32_t len)
{
    for(uint32_t i = 0; i < len; i++)
    {
        while(!USART_GetFlagStatus(pUSARTHandle->pUSARTx,USART_TXE));
        pUSARTHandle->pUSARTx->DR = (uint8_t)(*TxBuffer & 0xFFU);
        TxBuffer++;
    }
    while(!USART_GetFlagStatus(pUSARTHandle->pUSARTx,USART_TC));
}

void USART_ReceiveData(USART_Handler_t *pUSARTHandle, uint8_t *RxBuffer, uint32_t len)
{
    for(uint32_t i = 0; i < len; i++)
    {
        while(!USART_GetFlagStatus(pUSARTHandle->pUSARTx,USART_RXNE));
        *RxBuffer = (uint8_t)(pUSARTHandle->pUSARTx->DR & 0xFFU);
        RxBuffer ++;
        // pUSARTHandle->pUSARTx->SR &=~ (1U << USART_SR_RXNE);
    }
}

void USART_ClearFlag(USART_TypeDef *pUSARTx, uint8_t FlagName)
{
    pUSARTx->SR &=~ (1U << FlagName);
}

void USART_IRQConfig(uint8_t IRQNumber, uint8_t EnOrDi)
{
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

void USART_IRQPiorityConfig(uint8_t IRQNumber, uint8_t Piority)
{
    NVIC->IP[IRQNumber] &= ~(0x0f << 4);
	NVIC->IP[IRQNumber] |=  (Piority << 4);
}

uint8_t USART_SendDataIT(USART_Handler_t *pUSARTHandle, uint8_t *TxBuffer, uint32_t len)
{
    uint8_t tx_state = pUSARTHandle->TxBusyState;
    if(tx_state != USART_BUSY_TX)
    {
        pUSARTHandle->TxLen = len;
        pUSARTHandle->pTxBuffer = TxBuffer;
        pUSARTHandle->TxBusyState = USART_BUSY_TX;

        pUSARTHandle->pUSARTx->CR1 |= (1U << USART_CR1_TXEIE);
        pUSARTHandle->pUSARTx->CR1 |= (1U << USART_CR1_TCIE);
    }
    return tx_state;
}

uint8_t USART_ReceiveDataIT(USART_Handler_t *pUSARTHandle, uint8_t *RxBuffer, uint32_t len)
{
    uint8_t rx_state = pUSARTHandle->RxBusyState;
    if(rx_state != USART_BUSY_RX)
    {
        pUSARTHandle->RxLen = len;
        pUSARTHandle->pRxBuffer = RxBuffer;
        pUSARTHandle->RxBusyState = USART_BUSY_RX;
        uint32_t tmp = pUSARTHandle->pUSARTx->DR;
        (void)tmp;
        pUSARTHandle->pUSARTx->CR1 |= (1U << USART_CR1_RXNEIE);
    }
    return rx_state;
}

void USART_IRQHandler(USART_Handler_t *pUSARTHandle)
{
    uint32_t tmp1, tmp2;

    /* Transmit complete interrupt */
    tmp1 = (pUSARTHandle->pUSARTx->SR & (1U << USART_SR_TC));
    tmp2 = (pUSARTHandle->pUSARTx->CR1 & (1U << USART_CR1_TCIE));
    if(tmp1 && tmp2)
    {
        if(pUSARTHandle->TxBusyState == USART_BUSY_TX)
        {
            if(pUSARTHandle->TxLen == 0)
            {
                pUSARTHandle->pUSARTx->SR  &=~ (1U << USART_SR_TC);
                pUSARTHandle->pUSARTx->CR1 &=~ (1U << USART_CR1_TCIE);
                pUSARTHandle->TxBusyState = USART_READY;
                pUSARTHandle->pTxBuffer = NULL;
                pUSARTHandle->TxLen = 0;

                USART_ApplicationEventCallback(pUSARTHandle, USART_EVENT_TX_CMPLT);
            }
        }
    }

    /* Transmit data register empty interrupt */
    tmp1 = (pUSARTHandle->pUSARTx->SR & (1U << USART_SR_TXE));
    tmp2 = (pUSARTHandle->pUSARTx->CR1 & (1U << USART_CR1_TXEIE));
    if(tmp1 && tmp2)
    {
        if(pUSARTHandle->TxBusyState == USART_BUSY_TX)
        {
            if(pUSARTHandle->TxLen > 0)
            {
                pUSARTHandle->pUSARTx->DR = (uint8_t)(*pUSARTHandle->pTxBuffer & 0xFFU);
                pUSARTHandle->pTxBuffer ++;
                pUSARTHandle->TxLen --;
                USART_ApplicationEventCallback(pUSARTHandle, USART_EVENT_TX_TXE);
            }
            if (pUSARTHandle->TxLen == 0)
            {
                pUSARTHandle->pUSARTx->CR1 &=~ (1U << USART_CR1_TXEIE);
            }
        }
    }

    /* Receive data complete interrupt */
    tmp1 = (pUSARTHandle->pUSARTx->SR & (1U << USART_SR_RXNE));
    tmp2 = (pUSARTHandle->pUSARTx->CR1 & (1U << USART_CR1_RXNEIE));
    if(tmp1 && tmp2)
    {
        if(pUSARTHandle->RxBusyState == USART_BUSY_RX)
        {
            if(pUSARTHandle->RxLen > 0)
            {
                *(pUSARTHandle->pRxBuffer) = (uint8_t)(pUSARTHandle->pUSARTx->DR & 0xFFU);
                pUSARTHandle->pRxBuffer ++;
                pUSARTHandle->RxLen --;
            }
            if(pUSARTHandle->RxLen == 0)
            {
                pUSARTHandle->pUSARTx->CR1 &=~ (1U << USART_CR1_RXNEIE);
                pUSARTHandle->pRxBuffer = NULL;
                pUSARTHandle->RxLen = 0;
                pUSARTHandle->RxBusyState = USART_READY;

                USART_ApplicationEventCallback(pUSARTHandle, USART_EVENT_RX_CMPLT);
            }  
        }
    }

}






__attribute__((weak)) void USART_ApplicationEventCallback(USART_Handler_t *pUSARTHandle, uint8_t Event)
{

}














/******************************************************************************/