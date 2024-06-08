#ifndef Poweritem_H_INCLUDED
#define Poweritem_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include <stdbool.h>
#include <allegro5/allegro.h>
/*
   [Poweritem object]
*/
typedef struct _Poweritem
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    bool eaten1, eaten2;
    bool newborn;
    ALLEGRO_BITMAP *img;
    Shape *hitbox;//, *hitbox3, *hitbox4; // the hitbox of object
    ALLEGRO_TIMER *timer, *timer2, *newborntime;
} Poweritem;
Elements *New_Poweritem(int label, int x, int y);
void Poweritem_update(Elements *self);
void Poweritem_interact(Elements *self, Elements *tar);
void Poweritem_draw(Elements *self);
void Poweritem_destory(Elements *self);
#endif
