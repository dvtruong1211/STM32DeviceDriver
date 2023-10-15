/**
 ******************************************************************************
 * @file    template.h
 * @author  truongdv
 * @version 1.0
 * @date    
 * @brief   
 * @history
 ******************************************************************************/


#ifndef __I2C_H
#define __I2C_H

/* Includes ------------------------------------------------------------------*/
#include "memory_map_stm32f411xe.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
    uint8_t I2C_SCLSpeed;
    uint8_t I2C_DeviceAddress;
    uint8_t I2C_AckControl;
    uint8_t I2C_PMDutyCycle;

}I2C_Config_t;

typedef struct
{
    I2C_TypeDef *pI2Cx;
    I2C_Config_t I2CConfig;

    uint8_t *pTxBuffer;
    uint8_t *pRxBuffer;

    uint32_t TxLen;
    uint32_t RxLen;

    uint8_t DevAddr;
    uint32_t RxSize;
    uint8_t Sr;

}I2C_Handle_t;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/*Define CR1 register*/
#define CR1_PE              0U
#define CR1_SMBUS           1U
#define CR1_SMBTYPE         3U
#define CR1_ENARP           4U
#define CR1_ENPEC           5U
#define CR1_ENGC            6U
#define CR1_NOSTRETCH       7U
#define CR1_START           8U
#define CR1_STOP            9U
#define CR1_ACK             10U
#define CR1_POS             11U
#define CR1_PEC             12U
#define CR1_ALERT           13U
#define CR1_SWRST           15U

/*Define CR2 register*/
#define CR2_FREQ            0U
#define CR2_ITERREN         8U
#define CR2_ITEVTEN         9U
#define CR2_ITBUFEN         10U
#define CR2_DMAEN           11U
#define CR2_LAST            11U

/*Define OAR1 register*/
#define OAR1_ADD0           0U
#define OAR1_ADD_7_1        1U
#define OAR1_ADD_9_8        8U     
#define OAR1_ADDMODE        15U      


/*Define OAR2 register*/
#define OAR2_ENDUAL         0U
#define OAR2_ADD2_7_1       1U

/*Define SR1 register*/
#define SR1_SB              0U
#define SR1_ADDR            1U
#define SR1_BTF             2U
#define SR1_ADD10           3U
#define SR1_STOPF           4U
#define SR1_RXNE            6U
#define SR1_TXE             7U
#define SR1_BERR            8U
#define SR1_ARLO            9U
#define SR1_AF              10U
#define SR1_OVR             11U
#define SR1_PECERR          12U
#define SR1_TIMEOUT         14U
#define SR1_SMBALERT        15U


/*Define SR2 register*/
#define SR2_MSL             0U
#define SR2_BUSY            1U
#define SR2_TRA             2U
#define SR2_GENCALL         4U
#define SR2_SMBDEFAULT      5U
#define SR2_SMBHOST         6U
#define SR2_DUALF           7U
#define SR2_PEC             8U

/*Define CCR register*/
#define CCR_DUTY            14U
#define CCR_F_S             15U 


/* Define I2C state */
#define I2C_READY           0U
#define I2C_BUSY_IN_RX      1U
#define I2C_BUSY_IN_TX      2U


/* Define SCL Speed */
#define I2C_SCL_SPEED_SM    100000U
#define I2C_SCL_SPEED_FM4K  400000U

/* Define Ack control*/
#define I2C_ACK_ENABLE      1U
#define I2C_ACK_DISABLE     0U

/* Define fast mode duty cycle*/
#define I2C_FM_DUTY_2       0U
#define I2C_FM_DUTY_16_9    1U

/* Define status flag */
#define I2C_FLAG_TXE        (1U << SR1_TXE)
#define I2C_FLAG_RXNE       (1U << SR1_RXNE)
#define I2C_FLAG_SB         (1U << SR1_SB)
#define I2C_FLAG_OVR        (1U << SR1_OVR)
#define I2C_FLAG_AF         (1U << SR1_AF)
#define I2C_FLAG_ARLO       (1U << SR1_ARLO)
#define I2C_FLAG_BERR       (1U << SR1_BERR)
#define I2C_FLAG_STOPF      (1U << SR1_STOPF)
#define I2C_FLAG_ADD10      (1U << SR1_ADD10)
#define I2C_FLAG_BFT        (1U << SR1_BTF)
#define I2C_FLAG_ADDR       (1U << SR1_ADDR)
#define I2C_FLAG_TIMEOUT    (1U << SR1_TIMEOUT)


/* Appication event */
#define I2C_EV_TX_CMPLT     0U
#define I2C_EV_RX_CMPLT     1U
#define I2C_EV_STOP         2U



/* Exported functions ------------------------------------------------------- */

void I2C_PeriClkControl(I2C_TypeDef* pI2Cx, uint8_t EnOrDi);
void I2C_Init(I2C_Handle_t *pI2CHandle);
void I2C_DeInit(I2C_TypeDef* pI2Cx);


void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *TxBuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr);
void I2C_MasterRecieveData(I2C_Handle_t *pI2CHandle, uint8_t *RxBuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr);
void I2C_MasterSendDataIT(I2C_Handle_t *pI2CHandle, uint8_t *TxBuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr);
void I2C_MasterRecieveDataIT(I2C_Handle_t *pI2CHandle, uint8_t *RxBuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr);


void I2C_SlaveSendData(I2C_TypeDef* pI2Cx, uint8_t Data);
uint8_t I2C_SlaveRecieveData(I2C_TypeDef* pI2Cx);

void I2C_CloseSendData(I2C_Handle_t* pI2Cx);
void I2C_CloseRecieveData(I2C_Handle_t* pI2Cx);


void I2C_IRQConfig(uint8_t IRQNumber, uint8_t EnOrDi);
void I2C_IRQPiorityConfig(uint8_t IRQNumber, uint8_t Piority);

void I2C_EV_IRQHandling(I2C_Handle_t *pI2CHandle);
void I2C_ER_IRQHandling(I2C_Handle_t *pI2CHandle);

void I2C_PeriControl(I2C_TypeDef* pI2Cx, uint8_t EnOrDi);
uint8_t I2C_GetFlagStatus(I2C_TypeDef* pI2Cx, uint8_t FlagName);

void I2C_ManageAcking(I2C_TypeDef *pI2Cx, uint8_t EnorDi);
void I2C_GenerateStopConditon(I2C_TypeDef *pI2Cx);




#endif /* __I2C_H */