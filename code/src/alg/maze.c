#include "../../config.h"

//NOTES
/*
mouse.orientation speichert die richtung in der der Kopf zeigt
*/

/*
Maze:
     N
    ____
W  |__ _  E
   |_|__
     S
*/



struct Tile asMaze[10][10] = {0};
struct Mouse sMouse = {0};

void initMaze(void) {
    //Maus initialisieren
    sMouse.xPosition = 0;
    sMouse.yPosition = 0;
    sMouse.orientation = EAST;

    uint8_t i = 0;
    uint8_t j = 0;

    //Manhattendistazen berechnen & wände auf 0 setzen
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            asMaze[j][i].distance = 8 - i - j;
            asMaze[j][9 - i].distance = 8 - i - j;
            asMaze[9 - j][i].distance = 8 - i - j;
            asMaze[9 - j][9 - i].distance = 8 - i - j;
        }
    }

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            asMaze[j][i].xCoord = j;
            asMaze[j][i].yCoord = i;
        }
    }
}
