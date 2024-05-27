#ifndef HEART_H_INCLUDED
#define HEART_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Heart object]
*/
typedef struct _Heart
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    int remain; //剩下多少血
    ALLEGRO_BITMAP *img;
    ALLEGRO_TIMER *timer;
    Shape *hitbox; // the hitbox of object
} Heart;
Elements *New_Heart(int label);
void Heart_update(Elements *self);
void Heart_interact(Elements *self, Elements *tar);
void Heart_draw(Elements *self);
void Heart_destory(Elements *self);

#endif
