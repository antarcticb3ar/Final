#ifndef Boarder_H_INCLUDED
#define Boarder_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Boarder object]
*/
typedef struct _Boarder
{
    int x, y;          // the position of image
    Shape *hitbox, *hitbox2;//, *hitbox3, *hitbox4; // the hitbox of object
} Boarder;
Elements *New_Boarder(int label, int x, int y);
void Boarder_update(Elements *self);
void Boarder_interact(Elements *self, Elements *tar);
void Boarder_draw(Elements *self);
void Boarder_destory(Elements *self);
#endif
