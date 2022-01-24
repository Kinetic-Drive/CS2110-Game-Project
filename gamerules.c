#include "gamerules.h"

void resetVcar(Vcar *vcar) {
    vcar->row = HEIGHT/2 - V_CAR_HEIGHT/2;
    vcar->col = V_CAR_WIDTH/2;
}

void resetMcar(Mcar *mcar1,Mcar *mcar2,Mcar *mcar3,Mcar *mcar4) {
    mcar1 -> col = WIDTH;
    mcar2 -> col = WIDTH;
    mcar3 -> col = WIDTH;
    mcar4 -> col = WIDTH;
}
void createMcar(Mcar *mcar) {
    mcar->col = WIDTH - MAELSTROM_CAR_WIDTH/2;
    mcar->cc = 1;
}

// moves player's car (vcar) based on controls
void movingVcar(Vcar *vcar, u16 *score) {
    vcar -> row_last = vcar -> row;
    vcar -> col_last = vcar -> col;
    if (KEY_DOWN(BUTTON_RIGHT, BUTTONS)) {
        if (vcar->col < 190) {
            vcar->col += 2;
        }
    }

    if (KEY_DOWN(BUTTON_LEFT, BUTTONS)) {
        if (vcar->col > 2) {
            vcar->col -= 2;
        }
    }

    if (KEY_DOWN(BUTTON_UP, BUTTONS)) {
        if (vcar->row > 5) {
            vcar->row -= 5;
        }
    }

    if (KEY_DOWN(BUTTON_DOWN, BUTTONS)) {
        if (vcar->row < 123) {
        	vcar->row += 3;
        }
    }
    if (vcar -> col >= 230 - V_CAR_WIDTH && vcar -> row >= 150 - V_CAR_HEIGHT) {//& vcar -> col_last < 195 - V_CAR_WIDTH)) {
            (*score) += 1;
        }
}

// moves enemy car leftward
void movingMcar(Mcar *mcar, u16 *score) {
    mcar -> col_last = mcar -> col; //*mcar.col_last = (*mcar).col
    if (mcar -> cc != 0) {
        if (mcar -> col < MAELSTROM_CAR_WIDTH/2) {
            mcar -> cc = 0;
            (*score) += 1;
        } else {
            mcar -> col += -(*score/5 + 1);
        }
    }
}

COLLISION collision1(Vcar *vcar) {
    COLLISION c = CONSTANT; 
    for (int i = 0; i < 4; i ++) { // checking all cars
        int car = myMcars[i];
        if (((Mcar*)car)->cc == 1) {
            if (absDiff(vcar->row, ((Mcar*)car)->row) < COLL_HEIGHT) { // if too close, horiz
                if (absDiff(vcar->col, ((Mcar*)car)->col) < COLL_WIDTH) { // if too close, vert
                    c = COLLIDED;
                    break;
                }
            }
        }
    }
    return c;
}

int absDiff(int a, int b) {
    return (a-b < 0 ? b-a : a-b);
}