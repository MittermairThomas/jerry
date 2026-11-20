#ifndef ERROR_H
#define ERROR_H

#include <stdint.h>

#define NO_ERROR 0x00
//Keine Meldung

#define INIT 0x01
//UMC initialisiert Sensoren, Schnittstellen ect.

extern void initDebug(void);

extern void clearDebug(void);
extern void error(uint8_t _error);
extern void displayInt16(uint16_t _input);

#endif
