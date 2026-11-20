#include "../../config.h"

uint8_t counter = 0;

uint16_t mask = 0x000F;
uint8_t displayNum = 0;

void initTimer(void) { 
    //Timer1 für errordisplay f-int ~1HZ
    TCCR1B = 0;
    OCR1AH = 0x0F; //OCR1A = 4000
    OCR1AL = 0xA0;
    TCCR1B |= 1<<WGM12; //CTC Mode
    TIMSK1 |= 1<<OCIE1A; //Interrupt on compare
    
    //Timer3 für stepper f-int 1kHz
    TCCR3B = (1<<CS31); //PS 8
    OCR3AH = 0x01; //OCR2A = 499
    OCR3AL = 0xF3;
    TCCR3B |= 1<<WGM32; //Reset on compare
    TIMSK3 = 1<<OCIE3A; //Interrupt on compare

    sei();
}

ISR(TIMER1_COMPA_vect) {
    error((displayNum & mask) >> (4* counter));

    counter++;
    mask = mask << 4;

    if (counter == 4) {
        counter = 0;
        mask = 0x000F;
        TCCR1B &= ~TIMER1_PS;
    }
}

ISR(TIMER3_COMPA_vect) {
    switch (moveDir) {
        case STAND:
            break;

        case FORWARD:
            nStep(&sStepperRight);
            pStep(&sStepperLeft);
            break;

        case BACKWARD:
            pStep(&sStepperRight);
            nStep(&sStepperLeft);
            break;

        case ROTATE_CW:
            pStep(&sStepperRight);
            pStep(&sStepperLeft);
            break;

        case ROTATE_CCW:
            nStep(&sStepperRight);
            nStep(&sStepperLeft);
            break;
    }
}
