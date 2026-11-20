#ifndef CONFIG_H
#define CONFIG_H

//---DEFINES---
#define F_CPU    16000000UL
#define BAUTRATE 9600UL

//---INCLUDES---
#include "headers/drivers/lis2mdl.h"
#include "headers/drivers/vl53l1x.h"
#include "headers/drivers/stepper.h"
#include "headers/drivers/timer.h"

#include "headers/alg/maze.h"
#include "headers/alg/floodfill.h"

#include "headers/lib/debug.h"
#include "headers/lib/uart.h"
#include "headers/lib/twi.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <stddef.h>

#include <util/delay.h>

#endif
