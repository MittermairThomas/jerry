#include "../../config.h"

//DEF
struct Stepper sStepperRight;
struct Stepper sStepperLeft;

uint8_t moveDir = STAND;

void pStep(struct Stepper* _psStepper);
void nStep(struct Stepper* _psStepper);
void step(struct Stepper* _psStepper);
//---  

void initStepper(void) {
    //Initialisierung der pins ect.
    sStepperRight = (struct Stepper) {
        .aPins = {PD4, PD5, PD6, PD7},

        .pPort = &PORTD,
        .stepCounter = 0
    };
    
    //Pins auf ausgang setzen + startposition
    *(sStepperRight.pPort) |= (1<<sStepperRight.aIn1) | (1<<sStepperRight.aIn2) |
                            (1<<sStepperRight.bIn1) | (1<<sStepperRight.bIn2);

    *(sStepperRight.pPort) |= (1<<sStepperRight.aIn1) | (1<<sStepperRight.bIn2);
    
    //Wie bein stepperRight
    sStepperLeft = (struct Stepper) {
        .aPins = {PB0, PB1, PB2, PB3},

        .pPort = &PORTB,
        .stepCounter = 0
    };

    *(sStepperLeft.pPort) |= (1<<sStepperLeft.aIn1) | (1<<sStepperLeft.aIn2) |
                           (1<<sStepperLeft.bIn1) | (1<<sStepperLeft.bIn2);

    *(sStepperLeft.pPort) |= (1<<sStepperLeft.aIn1) | (1<<sStepperLeft.bIn2);

}

void stepperSetDir(uint8_t _dir) {
    switch (_dir) {
        case STAND:
        case FORWARD:
        case BACKWARD:
        case ROTATE_CW:
        case ROTATE_CCW:
            moveDir = _dir;
            break;
        
        default: //Falscher input
            moveDir = STAND;
            break;
    }
}

void pStep(struct Stepper* _psStepper) {
    if(++(_psStepper->stepCounter) >= 4)
        _psStepper->stepCounter = 0;

    step(_psStepper);
}

void nStep(struct Stepper* _psStepper) {
    if(--(_psStepper->stepCounter) >= 4)
        _psStepper->stepCounter = 3;

    step(_psStepper);
}

void step(struct Stepper* _psStepper) {
    switch (_psStepper->stepCounter) {
        case 0:
            *(_psStepper->pPort) |= 1<<_psStepper->bIn1;
            *(_psStepper->pPort) &= ~(1<<_psStepper->bIn2);
            break;

         case 1:
            *(_psStepper->pPort) |= 1<<_psStepper->aIn2;
            *(_psStepper->pPort) &= ~(1<<_psStepper->aIn1);
            break;

        case 2:
            *(_psStepper->pPort) |= 1<<_psStepper->bIn2;
            *(_psStepper->pPort) &= ~(1<<_psStepper->bIn1);
            break;

        case 3:
            *(_psStepper->pPort) |= 1<<_psStepper->aIn1;
            *(_psStepper->pPort) &= ~(1<<_psStepper->aIn2);
            break; 
    }
}

void advance(void) {
    stepperSetDir(FORWARD);
}
