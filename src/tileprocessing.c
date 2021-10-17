#include "tileprocessing.h"
 const u32 tile1[8] =
{
    0x11110000,
    0x11110000,
    0x11110000,
    0x11110000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000
};
const u32 tile2[8] = 
{
    0x00001111,
    0x00001111,
    0x00001111,
    0x00001111,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
};
const u32 tile3[8] = 
{
    0x11111111,
    0x11111111,
    0x11111111,
    0x11111111,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
};

const u32 tile4[8] =
{
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x11110000,
    0x11110000,
    0x11110000,
    0x11110000
};
 const u32 tile5[8] = 
{
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00001111,
    0x00001111,
    0x00001111,
    0x00001111,
};
const u32 tile6[8] = 
{
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x11111111,
    0x11111111,
    0x11111111,
    0x11111111,
};

const u32 tile7[8]={
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x11111111,
};
const u32 tile8[8]={
    0x00000001,
    0x00000001,
    0x00000001,
    0x00000001,
    0x00000001,
    0x00000001,
    0x00000001,
    0x00000001,
};
const u32 tile9[8]={
    0x10000000,
    0x10000000,
    0x10000000,
    0x10000000,
    0x10000000,
    0x10000000,
    0x10000000,
    0x10000000,
};
const u32 tile10[8]={
    0x11111111,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
};

void initLogo(){

    VDP_setPalette(PAL3,logo.palette->data);
    VDP_drawBitmap(VDP_BG_A,&logo,12,0);
}

void initTiles(){
    VDP_setPaletteColor(1, RGB24_TO_VDPCOLOR(0x32FF66)); //Green
    VDP_setPaletteColor(0, RGB24_TO_VDPCOLOR(0x000000));
    VDP_loadTileData(tile1,TILE1,1,DMA_QUEUE);
    VDP_loadTileData(tile2,TILE2,1,DMA_QUEUE);
    VDP_loadTileData(tile3,TILE3,1,DMA_QUEUE);
    VDP_loadTileData(tile4,TILE4,1,DMA_QUEUE);
    VDP_loadTileData(tile5,TILE5,1,DMA_QUEUE);
    VDP_loadTileData(tile6,TILE6,1,DMA_QUEUE);
    VDP_loadTileData(tile7,TILE7,1,DMA_QUEUE);
    VDP_loadTileData(tile8,TILE8,1,DMA_QUEUE);
    VDP_loadTileData(tile9,TILE9,1,DMA_QUEUE);
    VDP_loadTileData(tile10,TILE10,1,DMA_QUEUE);
}

void processGraphics(unsigned char *gfx){
          int i=0;
          int ii=X0;
          int j=Y0;
          bool changeRow=TRUE;
          for (i=0; i<64*32; i+=2){
              if (i%64==0){
                  if (!changeRow){
                  j++;
                  }
                  ii=X0;
                  changeRow = !changeRow;
              }
              else{
                  ii++;
              }
              drawTile(i,ii,j,changeRow,gfx);
          }
}

void drawTile(int i,int x,int y, bool changePlane,unsigned char *gfx){
        u8 tileToDraw;
        u8 bgToDraw;
        if (changePlane){
            bgToDraw = BG_A;
        }
        else{
            bgToDraw = BG_B;
        }
        u8 pos1 = gfx[i];
        u8 pos2 = gfx[i+1];

        if (pos1 == 1 && pos2 == 1){
            if(bgToDraw==BG_A){
                tileToDraw = TILE3;
            }
            else{
                tileToDraw = TILE6;
            }
        }

        if (pos1 == 1 && pos2 == 0){
            if (bgToDraw==BG_A){
                tileToDraw = TILE1;
            }
            else{
                tileToDraw = TILE4;
            }
        }
        if (pos1 == 0 && pos2 == 1){
            if (bgToDraw==BG_A){
                tileToDraw = TILE2;
            }
            else{
                tileToDraw = TILE5;                
            }
        }
        if (pos1 == 0 && pos2 == 0){
                tileToDraw = TILE0;
        }       
        VDP_setTileMapXY(bgToDraw,tileToDraw,x,y);
}

void drawBorder(){

    for (int i=0; i<32; i++){
        VDP_setTileMapXY(BG_A,TILE7,(X0+i),Y0);
        VDP_setTileMapXY(BG_A,TILE10,(X0+i),Y0+17
        );
    }
    for (int i=0; i<16; i++){
        VDP_setTileMapXY(BG_A,TILE8,X0-1,(Y0+i)+1);
        VDP_setTileMapXY(BG_A,TILE9,X0+32,(Y0+i)+1);
    }
}