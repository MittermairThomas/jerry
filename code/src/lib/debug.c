#include "../../config.h"

void initDebug(void) {
    DDRE |= 0x0F;

    PORTE &= ~(0x0F);
}

void clearDebug(void) {
    PORTE &= ~(0x0F);
}

void error(uint8_t _error) {
    if (_error > 0x0F)
        return;
    
    clearDebug();
    PORTE |= _error;
}

void displayInt16(uint16_t _input) {
    displayNum = _input;

    TCCR1B |= TIMER1_PS;
}
