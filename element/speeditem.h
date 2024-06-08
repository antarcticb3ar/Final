#ifndef Speeditem_H_INCLUDED
#define Speeditem_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include <stdbool.h>
#include <allegro5/allegro.h>
/*
   [Speeditem object]
*/
typedef struct _Speeditem
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    bool eaten1, eaten2;
    bool newborn;
    ALLEGRO_BITMAP *img;
    Shape *hitbox;//, *hitbox3, *hitbox4; // the hitbox of object
    ALLEGRO_TIMER *timer, *timer2, *newborntime;
} Speeditem;
Elements *New_Speeditem(int label, int x, int y);
void Speeditem_update(Elements *self);
void Speeditem_interact(Elements *self, Elements *tar);
void Speeditem_draw(Elements *self);
void Speeditem_destory(Elements *self);
#endif
