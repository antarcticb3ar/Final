#ifndef BOOMRANGE_H_INCLUDED
#define BOOMRANGE_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Boomrange object]
*/
typedef struct _Boomrange
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    int l;             // the long of Boomrange
    ALLEGRO_BITMAP *img;
    ALLEGRO_TIMER *timer;
    Shape *hitbox; // the hitbox of object
} Boomrange;
Elements *New_Boomrange(int label, int x, int y, int l);
void Boomrange_update(Elements *self);
void Boomrange_interact(Elements *self, Elements *tar);
void Boomrange_draw(Elements *self);
void Boomrange_destory(Elements *self);
void _Boomrange_update_position(Elements *self, int dx, int dy);
#endif
