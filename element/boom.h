#ifndef Boom_H_INCLUDED
#define Boom_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Boom object]
*/
typedef struct _Boom
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    int l;             // the long of Boom
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} Boom;
Elements *New_Boom(int label, int x, int y, int l);
void Boom_update(Elements *self);
void Boom_interact(Elements *self, Elements *tar);
void Boom_draw(Elements *self);
void Boom_destory(Elements *self);
void _Boom_update_position(Elements *self, int dx, int dy);
#endif
