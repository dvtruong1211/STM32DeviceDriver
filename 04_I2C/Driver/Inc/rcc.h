/**
 ******************************************************************************
 * @file    template.h
 * @author  truongdv
 * @version 1.0
 * @date    
 * @brief   
 * @history
 ******************************************************************************/


#ifndef __RCC_H
#define __RCC_H

/* Includes ------------------------------------------------------------------*/
#include "memory_map_stm32f411xe.h"

/* Exported types ------------------------------------------------------------*/
typedef enum{
    RCC_AHB_DIV_2 = 8,
    RCC_AHB_DIV_4,
    RCC_AHB_DIV_8,
    RCC_AHB_DIV_16,
    RCC_AHB_DIV_32,
    RCC_AHB_DIV_64,
    RCC_AHB_DIV_128,
    RCC_AHB_DIV_256
}AHB_PreScaler_e;


typedef enum{
    RCC_ABP1_DIV_2 = 4,
    RCC_ABP1_DIV_4,
    RCC_APB1_DIV_8,
    RCC_APB1_DIV_16,
}APB1_PreScaler_e;

typedef enum{
    RCC_ABP2_DIV_2 = 4,
    RCC_ABP2_DIV_4,
    RCC_APB2_DIV_8,
    RCC_APB2_DIV_16,
}APB2_PreScaler_e;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
uint32_t RCC_GetPCLK1(void);
uint32_t RCC_GetPCLK2(void);


#endif /* __RCC_H */