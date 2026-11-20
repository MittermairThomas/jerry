#ifndef TIMER_H
#define TIMER_H

//PS 1024
#define TIMER1_PS (1<<CS12)|(1<<CS10)

extern uint8_t displayNum;

extern void initTimer(void);

#endif
