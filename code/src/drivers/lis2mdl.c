#include "../../config.h"

struct LisData sLis = {0};

void initLis(void) {
    twiStart();

    twiWriteByte(LIS_ADDRESS | MASTER_TX);
    
    twiWriteByte(LIS_CONFIG_A | LIS_AUTO_INC); //Write REG_A/B/C
    twiWriteByte(0x00); //Continiuous mode
    twiWriteByte(0x00); //Default
    twiWriteByte(0x10); //Enable BDU
    
    /*
    twiStart();
    twiWriteByte(LIS_OFFSET_LX | MASTER_TX);
    twiWriteByte(0x00);
    */
    
    twiStop();
}

void lisRead(struct LisData* _psLis) {
    twiStart();

    twiWriteByte(LIS_ADDRESS | MASTER_TX);
    twiWriteByte(LIS_DATA_LX | LIS_AUTO_INC);

    twiStart();

    twiWriteByte(LIS_ADDRESS | MASTER_RX);

    _psLis->x = twiReadByteAck();
    _psLis->x |= twiReadByteAck() <<8;

    _psLis->y = twiReadByteAck();
    _psLis->y |= twiReadByteAck() <<8;

    _psLis->z = twiReadByteAck();
    _psLis->z |= twiReadByteNack() <<8;

    twiStop();
}
