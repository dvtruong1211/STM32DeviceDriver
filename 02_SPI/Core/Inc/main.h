//D:/Embedded/Embedded_SW/Driver_CMSIS/02_SPI
#ifndef __MAIN_H
#define __MAIN_H
#include "memory_map_stm32f411xe.h"
#include "string.h"



#define NSS_ENABLE()						GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET)
#define NSS_DISABLE()						GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET)


#define ISBUTTON_PRESSED()					GPIO_ReadPin(GPIOA, GPIO_PIN_1)

#define LED_ON()							GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET)
#define LED_OFF()							GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET)



 void *memset(void *ptr, int value, size_t num) {
    unsigned char *p = ptr;
    for (size_t i = 0; i < num; i++) {
        *p++ = (unsigned char)value;
    }
    return ptr;
}







#endif /* __MAIN_H */