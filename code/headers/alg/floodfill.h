#ifndef FLOODFILL_H
#define FLOODFILL_H

extern void scanWalls(void);

extern void addToBuffer(struct Tile* _psTile);
extern struct Tile* puffFromBuffer(void);

#endif
