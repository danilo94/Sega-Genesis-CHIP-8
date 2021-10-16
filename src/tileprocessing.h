#ifndef TILEPROCESSING_INCLUDE_H
#define TILEPROCESSING_INCLUDE_H
#include "config.h"
#include <genesis.h>

void initBasicTiles();
void initTiles();
void processGraphics(unsigned char *gfx);
void drawTile(int i,int x,int y, bool changePlane,unsigned char *gfx);
#endif
