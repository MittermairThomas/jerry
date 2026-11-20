#ifndef LIS2MDL_H
#define LIS2MDL_H

#include <stdint.h>

#define LIS_ADDRESS (0x1E <<1)

//Adressen
#define LIS_CONFIG_A 0x60
#define LIS_CONFIG_B 0x61
#define LIS_CONFIG_C 0x62

#define LIS_DATA_LX  0x68
#define LIS_DATA_HX  0x69
#define LIS_DATA_LY  0x6A
#define LIS_DATA_HY  0x6B
#define LIS_DATA_LZ  0x6C
#define LIS_DATA_HZ  0x6D

#define LIS_OFFSET_LX 0x45
#define LIS_OFFSET_HX 0x46

#define LIS_AUTO_INC 0x80

struct LisData {
    int16_t x;
    int16_t y;
    int16_t z;
};

extern struct LisData sLis;

extern void initLis(void);

extern void lisRead(struct LisData* _psLis);

#endif
