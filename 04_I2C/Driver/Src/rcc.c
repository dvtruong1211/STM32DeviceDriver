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

uint32_t RCC_GetPCLK1(void)
{
    uint32_t pclk1;
    uint32_t clksrc;
    uint32_t sysclk,hclk;

    clksrc = ((RCC->CFGR >> 2) & 0x03U);
    if( clksrc == 0)
    {
        sysclk = 16000000;
    }
    else if(clksrc == 1)
    {
        sysclk = 8000000;
    }

    uint32_t tmp1;
    tmp1 = ((RCC->CFGR >> 4) & 0x0FU);

    if((AHB_PreScaler_e)tmp1 == RCC_AHB_DIV_2)
        hclk = sysclk/2;
    else if((AHB_PreScaler_e)tmp1 ==  RCC_AHB_DIV_4)
        hclk = sysclk/4;
    else if((AHB_PreScaler_e)tmp1 ==  RCC_AHB_DIV_8)
        hclk = sysclk/8;
    else if((AHB_PreScaler_e)tmp1 ==  RCC_AHB_DIV_16)
        hclk = sysclk/16;
    else if((AHB_PreScaler_e)tmp1 ==  RCC_AHB_DIV_32)
        hclk = sysclk/32;
    else if((AHB_PreScaler_e)tmp1 ==  RCC_AHB_DIV_64)
        hclk = sysclk/64;
    else if((AHB_PreScaler_e)tmp1 ==  RCC_AHB_DIV_128)
        hclk = sysclk/128;
    else if((AHB_PreScaler_e)tmp1 ==  RCC_AHB_DIV_256)
        hclk = sysclk/256;
    else
        hclk = sysclk;
    
    uint32_t tmp2;
    tmp2 =  ((RCC->CFGR >> 10) & 0x07U);

    if((APB1_PreScaler_e)tmp2 == RCC_ABP1_DIV_2)
        pclk1 = hclk/2;
    else if((APB1_PreScaler_e)tmp2 ==  RCC_ABP1_DIV_4)
        pclk1 = hclk/4;
    else if((APB1_PreScaler_e)tmp2 ==  RCC_APB1_DIV_8)
        pclk1 = hclk/8;
    else if((APB1_PreScaler_e)tmp2 ==  RCC_APB1_DIV_16)
        pclk1 = hclk/16;
    else 
        pclk1 = hclk;

    return pclk1;
}

uint32_t RCC_GetPCLK2(void)
{
    uint32_t pclk2;
    uint32_t clksrc;
    uint32_t sysclk,hclk;

    clksrc = ((RCC->CFGR >> 2) & 0x03U);
    if( clksrc == 0)
    {
        sysclk = 16000000;
    }
    else if(clksrc == 1)
    {
        sysclk = 8000000;
    }

    uint32_t tmp1;
    tmp1 = ((RCC->CFGR >> 4) & 0x0FU);

    if((AHB_PreScaler_e)tmp1 == RCC_AHB_DIV_2)
        hclk = sysclk/2;
    else if((AHB_PreScaler_e)tmp1 ==  RCC_AHB_DIV_4)
        hclk = sysclk/4;
    else if((AHB_PreScaler_e)tmp1 ==  RCC_AHB_DIV_8)
        hclk = sysclk/8;
    else if((AHB_PreScaler_e)tmp1 ==  RCC_AHB_DIV_16)
        hclk = sysclk/16;
    else if((AHB_PreScaler_e)tmp1 ==  RCC_AHB_DIV_32)
        hclk = sysclk/32;
    else if((AHB_PreScaler_e)tmp1 ==  RCC_AHB_DIV_64)
        hclk = sysclk/64;
    else if((AHB_PreScaler_e)tmp1 ==  RCC_AHB_DIV_128)
        hclk = sysclk/128;
    else if((AHB_PreScaler_e)tmp1 ==  RCC_AHB_DIV_256)
        hclk = sysclk/256;
    else
        hclk = sysclk;
    
    uint32_t tmp2;
    tmp2 =  ((RCC->CFGR >> 10) & 0x07U);

    if((APB2_PreScaler_e)tmp2 == RCC_ABP2_DIV_2)
        pclk2 = hclk/2;
    else if((APB2_PreScaler_e)tmp2 ==  RCC_ABP2_DIV_2)
        pclk2 = hclk/4;
    else if((APB2_PreScaler_e)tmp2 ==  RCC_ABP2_DIV_2)
        pclk2 = hclk/8;
    else if((APB2_PreScaler_e)tmp2 ==  RCC_ABP2_DIV_2)
        pclk2 = hclk/16;
    else 
        pclk2 = hclk;

    return pclk2;
}


/******************************************************************************/

