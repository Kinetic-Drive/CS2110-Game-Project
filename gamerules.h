#ifndef GAMERULES_H
#define GAMERULES_H

#include "gba.h"
#include "main.h"
#include "images/mcar.h"
#include "images/vcar.h"

#define COLL_WIDTH ( (MAELSTROM_CAR_WIDTH + V_CAR_WIDTH) / 2 )
#define COLL_HEIGHT ( (MAELSTROM_CAR_HEIGHT + V_CAR_HEIGHT) / 2 )

typedef enum {
	CONSTANT,
    COLLIDED,
} COLLISION;

extern int myMcars[4];

void resetVcar(Vcar *vcar);
void resetMcar(Mcar *mcar1,Mcar *mcar2,Mcar *mcar3,Mcar *mcar4);
void createMcar(Mcar *mcar);
void movingVcar(Vcar *vcar, u16 *score);
void movingMcar(Mcar *mcar, u16*);
COLLISION collision1(Vcar *vcar);
int absDiff(int, int);

#endif