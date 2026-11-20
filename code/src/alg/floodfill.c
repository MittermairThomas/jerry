#include "../../config.h"

struct Tile* aRingBuffer[100] = {0};
uint8_t head = 0;
uint8_t tail = 0;

void advance(int8_t _dir) {
    //Blockierende schleife bis die mause den
    //Zielwinkel erreicht
    switch (_dir - mouse.orientation) {
        case -2:
        case 2:

            break;

        case -1:

            break;

        case 0:

            break;

        case 1:

            break;

        default:
            return;
    }

    //Ein feld nach forme fahren
}

//Wände suchen
void scanWalls(void) {
    uint16_t lWall = 0, fWall = 0, rWall = 0;

    lWall = vl53GetDist(&left);
    fWall = vl53GetDist(&front); 
    rWall = vl53GetDist(&right);

    switch (sMouse.orientation) {
        case NORTH:
            CURRENT_TILE.wWall = (lWall < 20) ? 1 : 0;
            CURRENT_TILE.nWall = (fWall < 20) ? 1 : 0;
            CURRENT_TILE.eWall = (rWall < 20) ? 1 : 0;

            break;

        case EAST:
            CURRENT_TILE.nWall = (lWall < 20) ? 1 : 0;
            CURRENT_TILE.eWall = (fWall < 20) ? 1 : 0;
            CURRENT_TILE.sWall = (rWall < 20) ? 1 : 0;

            break;

        case SOUTH:
            CURRENT_TILE.eWall = (lWall < 20) ? 1 : 0;
            CURRENT_TILE.sWall = (fWall < 20) ? 1 : 0;
            CURRENT_TILE.wWall = (rWall < 20) ? 1 : 0;
            
            break;

        case WEST:
            CURRENT_TILE.sWall = (lWall < 20) ? 1 : 0;
            CURRENT_TILE.wWall = (fWall < 20) ? 1 : 0;
            CURRENT_TILE.nWall = (rWall < 20) ? 1 : 0;
  
            break;

        default:
            break;
    }
}

void addToBuffer(struct Tile* _psTile) {
    if (_psTile->inBuffer)
        return;

    _psTile->inBuffer = 1;

    aRingBuffer[tail++] = _psTile;
    tail %= 100;
}

struct Tile* pullFromBuffer(void) {
    struct Tile* ret = aRingBuffer[head++];
    head = head %100;
    
    ret->inBuffer = 0;
    return ret;
}

void floodfill(void) {
    uint8_t i = 0;
    uint8_t minDistance = 255;

    struct Tile* apTmpTileBuffer[4] = {NULL};
    
    //Ring array buffer emty
    while (head != tail) {
        struct Tile* psTile = pullFromBuffer();
    
        //Check for overflow and fine smallest distance of neighbor tile not blocked by a wall
        if (psTile->xCoord > 0 && !psTile->wWall) {
            apTmpTileBuffer[0] = &asMaze[psTile->xCoord - 1][psTile->yCoord];

            minDistance = asMaze[psTile->xCoord - 1][psTile->yCoord].distance; 
        }

        if (psTile->xCoord < 9 && !psTile->eWall) {
            apTmpTileBuffer[1] = &asMaze[psTile->xCoord + 1][psTile->yCoord];

            if (minDistance > asMaze[psTile->xCoord + 1][psTile->yCoord].distance)
                minDistance = asMaze[psTile->xCoord + 1][psTile->yCoord].distance;
        }

        if (psTile->yCoord > 0 && !psTile->nWall) {
            apTmpTileBuffer[2] = &asMaze[psTile->xCoord][psTile->yCoord - 1];
        
            if (minDistance > asMaze[psTile->xCoord][psTile->yCoord - 1].distance)
                minDistance = asMaze[psTile->xCoord][psTile->yCoord - 1].distance;
        }

        if (psTile->yCoord < 9 && !psTile->sWall) {
            apTmpTileBuffer[3] = &asMaze[psTile->xCoord][psTile->yCoord + 1];

            if (minDistance > asMaze[psTile->xCoord][psTile->yCoord + 1].distance)
                minDistance = asMaze[psTile->xCoord][psTile->yCoord + 1].distance;
        }
        
        //Change number and add new tiles to buffer
        if (minDistance >= psTile->distance && psTile->distance != 0) {
            psTile->distance = minDistance + 1;

            for (i = 0; i < 4; i++) {
                if (apTmpTileBuffer[i] != NULL)
                    addToBuffer(apTmpTileBuffer[i]); 
            }
        }
        
        minDistance = 255;
        for (i = 0; i < 4; i++)
            apTmpTileBuffer[i] = NULL;
    }
}
