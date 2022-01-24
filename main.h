#ifndef MAIN_H
#define MAIN_H

#include "gba.h"

/* TODO: */
// Add any additional states you need for your app.
typedef enum {
  START,
  GAME,
  WIN,
  LOSE,
} GBAState;

/* TODO: */
// Necessary struct
typedef struct vcar {
	u16 row_last;
	u16 col_last;
	u16 row;
	u16 col;
} Vcar;

typedef struct mcar {
	u16 col_last;
	u16 row; // row doesn't change
	u16 col;
    u16 cc; //checks if can collide; 0false 1true
} Mcar;

void reset(u16 *score, Vcar *vcar, Mcar *mcar1, Mcar *mcar2, Mcar *mcar3, Mcar *mcar4);
int countMcars(void);
#endif