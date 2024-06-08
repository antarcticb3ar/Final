#ifndef Qualityitem_H_INCLUDED
#define Qualityitem_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include <stdbool.h>
#include <allegro5/allegro.h>
/*
   [Qualityitem object]
*/
typedef struct _Qualityitem
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    bool eaten1, eaten2;
    bool newborn;
    ALLEGRO_BITMAP *img;
    Shape *hitbox;//, *hitbox3, *hitbox4; // the hitbox of object
    ALLEGRO_TIMER *timer, *timer2, *newborntime;
} Qualityitem;
Elements *New_Qualityitem(int label, int x, int y);
void Qualityitem_update(Elements *self);
void Qualityitem_interact(Elements *self, Elements *tar);
void Qualityitem_draw(Elements *self);
void Qualityitem_destory(Elements *self);
#endif
