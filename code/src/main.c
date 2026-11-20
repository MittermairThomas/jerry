#include "../config.h"

void foo(void);

int main(void) {
    //DEC/DEF 
    //char sData[16] = {'\0'};

    //int16_t dist = 0;
    //INIT
    //initDebug();
    //error(INIT);
    
    //initMaze();
    
    initUart(RXON);
    rxCall = foo;
    //initTwi();
    
    //initTimer();
    //initStepper();
    //initLis();
    //initVl53();

    //clearDebug();
    //---
    
    //stepperSetDir(BACKWARD);
   
    while (1) {
    }

    while(1);
    return 0;
}

void foo(void) {
    uartWrite("Hello\r\n\0");
}
