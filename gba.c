#include "gba.h"

volatile unsigned short *videoBuffer = (volatile unsigned short *)0x6000000;
u32 vBlankCounter = 0;

void waitForVBlank(void) {
  // TODO: IMPLEMENT

  // Loops until we're NOT in vBlank anymore:
  // Prevents counting one VBlank more than once if app is too fast
  while(SCANLINECOUNTER > 160);

  // Loops until in vBlank:
  while(SCANLINECOUNTER < 160);

  // Increment the vBlank counter:
  vBlankCounter++;
}

static int __qran_seed = 42;
static int qran(void) {
  __qran_seed = 1664525 * __qran_seed + 1013904223;
  return (__qran_seed >> 16) & 0x7FFF;
}

int randint(int min, int max) { return (qran() * (max - min) >> 15) + min; }

void setPixel(int row, int col, u16 color) {
  // TODO: IMPLEMENT
  // sets specific location in videoBuffer array to value 'color'
  videoBuffer[OFFSET(row, col, 240)] = color;  
}

void drawRectDMA(int row, int col, int width, int height, volatile u16 color) {
  // TODO: IMPLEMENT
  // draws a solid-color (fixed src) rectangle with DMA line by line
  DMA[3].src = &color;
  for (int i = 0; i < height; i++ ) {
    DMA[3].dst = &videoBuffer[(row + i) * WIDTH + col];  
    DMA[3].cnt = DMA_ON | DMA_SOURCE_FIXED | DMA_DESTINATION_INCREMENT | width;
  }
}

void drawFullScreenImageDMA(const u16 *image) {
  // TODO: IMPLEMENT
  // draws a full screen image with incremented src and dst pointers
  DMA[3].src = image;
  DMA[3].dst = videoBuffer;  
  DMA[3].cnt = DMA_ON | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT | (WIDTH * HEIGHT);
}

void drawImageDMA(int row, int col, int width, int height, const u16 *image) {
  // TODO: IMPLEMENT
  // draws an image with DMA line by line
  for (int i = 0; i < height; i++ ) {
    DMA[3].src = &image[i * width];
    DMA[3].dst = &videoBuffer[(row + i) * WIDTH + col]; 
    DMA[3].cnt = DMA_ON | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT | width;
  }
}

void fillScreenDMA(volatile u16 color) {
  // TODO: IMPLEMENT
  // fills the screen with a single color
  // draws a solid-color (fixed src) rectangle with DMA line by line
  DMA[3].src = &color;
  DMA[3].dst = videoBuffer;  
  DMA[3].cnt = DMA_ON | DMA_SOURCE_FIXED | DMA_DESTINATION_INCREMENT | (WIDTH * HEIGHT);
}

void drawChar(int row, int col, char ch, u16 color) {
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 8; j++) {
      if (fontdata_6x8[OFFSET(j, i, 6) + ch * 48]) {
        setPixel(row + j, col + i, color);
      }
    }
  }
}

void drawString(int row, int col, char *str, u16 color) {
  while (*str) {
    drawChar(row, col, *str++, color);
    col += 6;
  }
}

void drawCenteredString(int row, int col, int width, int height, char *str,
                        u16 color) {
  u32 len = 0;
  char *strCpy = str;
  while (*strCpy) {
    len++;
    strCpy++;
  }

  u32 strWidth = 6 * len;
  u32 strHeight = 8;

  int new_row = row + ((height - strHeight) >> 1);
  int new_col = col + ((width - strWidth) >> 1);
  drawString(new_row, new_col, str, color);
}