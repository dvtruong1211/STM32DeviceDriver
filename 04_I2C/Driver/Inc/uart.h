/**
 ******************************************************************************
 * @file    uart.h
 * @author  truongdv
 * @version 1.0
 * @date    
 * @brief   
 * @history
 ******************************************************************************/


#ifndef __UART_H
#define __UART_H

/* Includes ------------------------------------------------------------------*/
#include "memory_map_stm32f411xe.h"

/* Exported types ------------------------------------------------------------*/

typedef struct{
    uint8_t USART_Mode;
    uint32_t USART_Baudrate;
    uint8_t USART_NoOfStopBit;
    uint8_t USART_WordLength;
    uint8_t USART_ParityControl;
    uint8_t USART_HWFlowControl;

}USART_Config_t;


typedef struct{
    USART_TypeDef *pUSARTx;
    USART_Config_t USART_Config;
    uint8_t *pTxBuffer;
    uint8_t *pRxBuffer;
    uint32_t TxLen;
    uint32_t RxLen;
    uint8_t TxBusyState;
    uint8_t RxBusyState;

}USART_Handler_t;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* 
    Define macro bit in register of USART
*/

/* USART_SR*/
#define USART_SR_PE             0U
#define USART_SR_FE             1U
#define USART_SR_NF             3U
#define USART_SR_ORE            4U
#define USART_SR_RXNE           5U
#define USART_SR_TC             6U
#define USART_SR_TXE            7U
#define USART_SR_LBD            8U
#define USART_SR_CTS            9U

/* USART_CR1*/
#define USART_CR1_SBK           0U
#define USART_CR1_RWU           1U
#define USART_CR1_RE            2U
#define USART_CR1_TE            3U
#define USART_CR1_IDLEIE        4U
#define USART_CR1_RXNEIE        5U
#define USART_CR1_TCIE          6U
#define USART_CR1_TXEIE         7U
#define USART_CR1_PEIE          8U
#define USART_CR1_PS            9U      
#define USART_CR1_PCE           10U
#define USART_CR1_WAKE          11U
#define USART_CR1_M             12U
#define USART_CR1_UE            13U
#define USART_CR1_OVER8         15U

/* USART_CR2*/
#define USART_CR2_ADD           0U
#define USART_CR2_LBDL          5U
#define USART_CR2_LBDIE         6U   
#define USART_CR2_LBCL          8U
#define USART_CR2_CPHA          9U 
#define USART_CR2_CPOL          10U
#define USART_CR2_CLKEN         11U
#define USART_CR2_STOP          12U
#define USART_CR2_LINEN         14U

/* USART_CR3*/
#define USART_CR3_EIE           0U
#define USART_CR3_IREN          1U
#define USART_CR3_IRLP          2U
#define USART_CR3_HDSEL         3U
#define USART_CR3_NACK          4U
#define USART_CR3_SCEN          5U
#define USART_CR3_DMAR          6U
#define USART_CR3_DMAT          7U
#define USART_CR3_RTSE          8U
#define USART_CR3_CTSE          9U
#define USART_CR3_CTSIE         10U
#define USART_CR3_ONEBIT        11U


/* 
    Define macro to config the USART
*/

/* USART_Mode*/
#define USART_MODE_TX           0U
#define USART_MODE_RX           1U
#define USART_MODE_TXRX         2U


/* Config the BaudRate of the USART */
#define USART_BAUD_4800         4800U
#define USART_BAUD_9600         9600U
#define USART_BAUD_115200        115200U
         


/* Config number of the stop bit */
#define USART_STOPBITS_1        0U
#define USART_STOPBITS_0_5      1U
#define USART_STOPBITS_2        2U
#define USART_STOPBITS_1_5      3U


/* Config the word length of data */
#define USART_WORDLEN_8         0U
#define USART_WORDLEN_9         1U


/* Config the parity bit */
#define USART_PARITY_DISABLE    0U
#define USART_PARITY_EVEN       1U
#define USART_PARITY_ODD        2U


/* Config hardware flow control */
#define USART_HW_FLOW_CTRL_DISABLE  0U
#define USART_HW_FLOW_CTRL_CTS      1U
#define USART_HW_FLOW_CTRL_RTS      2U
#define USART_HW_FLOW_CTRL_CTS_RTS  3U

/* Flag */
#define USART_TXE               (1U << USART_SR_TXE)
#define USART_RXNE              (1U << USART_SR_RXNE)
#define USART_TC                (1U << USART_SR_TC)

/* Application state*/
#define USART_BUSY_TX           2U
#define USART_BUSY_RX           1U
#define USART_READY             0U


/* Event */
#define USART_EVENT_TX_CMPLT    0U
#define USART_EVENT_RX_CMPLT    1U
#define USART_EVENT_TX_TXE      8U
#define USART_EVENT_IDLE        2U
#define USART_EVENT_CTS         3U
#define USART_EVENT_PE          4U
#define USART_ERR_FE            5U
#define USART_ERR_NE            6U
#define USART_ERR_ORE           7U


/* USART IRQ number */
#define USART1_IRQ_NUMBER       37U
#define USART2_IRQ_NUMBER       38U    
#define USART6_IRQ_NUMBER       71U


/* Exported functions ------------------------------------------------------- */

void USART_PeriClockControl(USART_TypeDef *pUSARTx, uint8_t EnOrDi);

void USART_Init(USART_Handler_t *pUSARTHandle);
void USART_DeInit(USART_TypeDef *pUSARTx);

void USART_SetBaudRate(USART_TypeDef *pUSARTx, uint32_t BaudRate);

void USART_SendData(USART_Handler_t *pUSARTHandle, uint8_t *TxBuffer, uint32_t len);
void USART_ReceiveData(USART_Handler_t *pUSARTHandle, uint8_t *RxBuffer, uint32_t len);

uint8_t USART_SendDataIT(USART_Handler_t *pUSARTHandle, uint8_t *TxBuffer, uint32_t len);
uint8_t USART_ReceiveDataIT(USART_Handler_t *pUSARTHandle, uint8_t *RxBuffer, uint32_t len);

void USART_PeriControl(USART_TypeDef *pUSARTx, uint8_t EnOrDi);

uint8_t USART_GetFlagStatus(USART_TypeDef *pUSARTx, uint8_t FlagName);
void USART_ClearFlag(USART_TypeDef *pUSARTx, uint8_t FlagNam);

void USART_IRQConfig(uint8_t IRQNumber, uint8_t EnOrDi);
void USART_IRQPiorityConfig(uint8_t IRQNumber, uint8_t Piority);

void USART_ApplicationEventCallback(USART_Handler_t *pUSARTHandle, uint8_t Event);

void USART_IRQHandler(USART_Handler_t *pUSARTHandle);








#endif /* __UART_H */


