#include "../../config.h"

void initTwi(void) {
    TWBR0 = 72; //100kHz
    TWSR0 = 0;
    TWCR0 = 1<<TWEN;
}

void twiStart(void) {
    TWCR0 = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    while(!(TWCR0 & 1<<TWINT));
}

void twiStop(void) {
    TWCR0 = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);

    //while(!(TWCR & 1<<TWSTO));
}

void twiWriteByte(uint8_t _data) {
    TWDR0 = _data;

    TWCR0 = (1<<TWINT) | (1<<TWEN);
    while(!(TWCR0 & 1<<TWINT));
}

uint8_t twiReadByteAck(void) {
    TWCR0 = (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
    while(!(TWCR0 & 1<<TWINT));

    return TWDR0;
}

uint8_t twiReadByteNack(void) {
    TWCR0 = (1<<TWINT) | (1<<TWEN);
    while(!(TWCR0 & 1<<TWINT));

    return TWDR0;
}

void writeReg(uint8_t _address, uint8_t _reg, uint8_t _data) {
    twiStart();
    twiWriteByte(_address | MASTER_TX);
    
    twiWriteByte(_reg);
    twiWriteByte(_data);

    twiStop();
}
