#ifndef HEART2_H_INCLUDED
#define HEART2_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Heart2 object]
*/
typedef struct _Heart2
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    int remain; //剩下多少血
    ALLEGRO_BITMAP *img;
    ALLEGRO_TIMER *timer;
    Shape *hitbox; // the hitbox of object
} Heart2;
Elements *New_Heart2(int label, int x, int y);
void Heart2_update(Elements *self);
void Heart2_interact(Elements *self, Elements *tar);
void Heart2_draw(Elements *self);
void Heart2_destory(Elements *self);

#endif
