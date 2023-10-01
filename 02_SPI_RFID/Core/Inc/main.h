/* 
	D:/Embedded/Embedded_SW/Driver_CMSIS/02_SPI_RFID 
*/
#ifndef __MAIN_H
#define __MAIN_H
#include "memory_map_stm32f411xe.h"
#include <string.h>



#define NSS_ENABLE()						GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET)
#define NSS_DISABLE()						GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET)









 void *memset(void *ptr, int value, size_t num);






#endif /* __MAIN_H */