#ifndef UART_H
#define UART_H

#include "../../config.h"

#ifndef F_CPU
#error F_CPU not defined
#endif

#ifndef BAUTRATE
#error BAUTRATE not defined
#endif

#include <stdint.h>

#define RXOFF 0
#define RXON 1

extern volatile uint8_t txFlag;
//Set to 1 when a new String can be send, if 0 usart is occupied

extern char rxBuffer[32];
//When a string is sednd to mc, it will be conataned in rxBuffer

extern void initUart(uint8_t _rxEn); //if _exEn is 1, sending is enabled
extern uint8_t uartWrite(char* _txStr); //Sends a string IF possibile, else returns 1
extern void (*rxCall)(void);
//Can be poinet to any funktion of the form "void func(void)",
//will be called when string is recived

extern void intToStr(int32_t _num, char* _str, uint8_t _base);

#endif
