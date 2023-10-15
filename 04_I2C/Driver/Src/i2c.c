/**
 ******************************************************************************
 * @file    i2c.c
 * @author  truongdv
 * @version 1.0
 * @date    
 * @brief   
 * @history
 ******************************************************************************/
/*******************************************************************************
 * Include
 ******************************************************************************/
#include "i2c.h"
#include "gcc.h"


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
void I2C_PeriClkControl(I2C_TypeDef* pI2Cx, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)
    {
        if(pI2Cx == I2C1)
            I2C1_CLOCK_ENABLE();
        else if(pI2Cx == I2C2)
            I2C2_CLOCK_ENABLE();
        else if(pI2Cx == I2C3)
            I2C3_CLOCK_ENABLE(); 
    }
    else 
    {
        if(pI2Cx == I2C1)
            I2C1_CLOCK_DISABLE();
        else if(pI2Cx == I2C2)
            I2C2_CLOCK_DISABLE();
        else if(pI2Cx == I2C3)
            I2C3_CLOCK_DISABLE(); 
    }
}

void I2C_PeriControl(I2C_TypeDef* pI2Cx, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)
        pI2Cx->CR1 |= (1U << CR1_PE);
    else
        pI2Cx->CR1 &=~ (1U << CR1_PE);
}

void I2C_Init(I2C_Handle_t *pI2CHandle)
{
    I2C_PeriClkControl(pI2CHandle->pI2Cx, ENABLE);

    /*  Enable acknowledge control*/
    pI2CHandle->pI2Cx->CR1 |= (1U << CR1_ACK);

    /* Config the frequency*/
    pI2CHandle->pI2Cx->CR2 &=~ (0x3FU << 0);
    pI2CHandle->pI2Cx->CR2 |= ((RCC_GetPCLK1() / 1000000) << 0);

    /* Config the addr*/
    pI2CHandle->pI2Cx->OAR1 |= (1U << 14);
    pI2CHandle->pI2Cx->OAR1 |= (pI2CHandle->I2CConfig.I2C_DeviceAddress << 14);

}



































/******************************************************************************/

