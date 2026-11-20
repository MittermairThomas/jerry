#include "../../config.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <string.h> 

volatile uint8_t txFlag = 1;

char internTxBuffer[32] = {'\0'}; //Contains String wich will be send
char rxBuffer[32] = {'\0'};

uint8_t internTxIndex = 0;
uint8_t internRxIndex = 0;
//Store position in strings

uint16_t internUbrr0 = 0; //Bautrate

void (*rxCall)(void);
//Points to function wich will be calles when string is recived

//Send byte
ISR(USART0_UDRE_vect) {
	UDR0 = internTxBuffer[internTxIndex++]; //Send next byte

	//End of String
	if (!internTxBuffer[internTxIndex]) {
		txFlag = 1; //Signals that new Sstring can be send
		internTxIndex = 0; //Go back to the start of string

		UCSR0B &= ~(1<<UDRIE0); //Disable Interrupt
	}
}

//Recive byte
ISR(USART0_RX_vect) {
	rxBuffer[internRxIndex] = UDR0; //Store recived byte in string

	//End of String
	if (rxBuffer[internRxIndex] == '\n') {
		rxBuffer[++internRxIndex] = '\0'; //Make shure that string ends with \0
		rxBuffer[31] = '\0'; //Make shure that short strings end with \0
	
		//Call funktion
		if (rxCall != NULL)
			rxCall();

		internRxIndex = -1; //Go back to start of string
	}

	internRxIndex++;
}

//Initialise USART
void initUart(uint8_t _rxEn) {
	internUbrr0 = (F_CPU/(16UL*BAUTRATE)) -1;
	UBRR0H = (uint8_t) (internUbrr0>>8);
	UBRR0L = (uint8_t) (internUbrr0 & 0xFF);
	UCSR0B = (1<<TXEN0); //Enable transmission
    UCSR0C = (1<<UCSZ00) | (1<<UCSZ01); //8-Bit, no parity
	
	//Enable resiving if given
	if (_rxEn)
		UCSR0B |= (1<<RXEN0) | (1<<RXCIE0);
	
	sei();
}

//Send String
uint8_t uartWrite(char* _txStr) {
	if (txFlag) {
		//Copy given string into buffer
		strncpy(internTxBuffer, _txStr, sizeof(internTxBuffer) -1);
		internTxBuffer[sizeof(internTxBuffer) -1] = '\0';
		
		txFlag = 0; //Stop other String from being send
		UCSR0B |= 1<<UDRIE0; //Enable Interrubt

		return 0; //Return 0 if sending works
	}

	return 1; //Return 1 if Sending has failed
}

void intToStr(int32_t _num, char* _str, uint8_t _base) {
    if (_base < 2)
        return;

    char strOutM[10];

    uint8_t negFlag = 0; //1 if input < 0
    uint8_t index = 0;
    uint8_t i; //Counter forloop

    if (_num < 0) {
        negFlag = 1;
        _num *= -1;
    }

    do {
        strOutM[index++] = _num %_base +'0';
        _num /= _base;
    } while (_num);

    if (negFlag)
        strOutM[index++] = '-';

    strOutM[index] = '\0';

    for (i = 0; i < index; i++) {
        _str[i] = strOutM[index - i -1]; 
    }

    _str[index++] = '\r';
    _str[index++] = '\n';
    _str[index] = '\0';
}
