#ifndef MAZE_H
#define MAZE_H

#define NORTH 0
#define EAST  1
#define SOUTH 2
#define WEST  3

#define CURRENT_TILE asMaze[sMouse.xPosition][sMouse.yPosition]

struct Tile {
    uint8_t distance;

    uint8_t xCoord, yCoord;

    uint8_t inBuffer;
    
    union {
        uint8_t aWall[4];

        struct {
            uint8_t nWall;
            uint8_t eWall;
            uint8_t sWall;
            uint8_t wWall;
        };
    };
};

struct Mouse {
    uint8_t xPosition;
    uint8_t yPosition;

    int8_t orientation;
};

extern struct Tile asMaze[10][10];
extern struct Mouse sMouse;

extern void initMaze(void);

#endif
