#ifndef GUIDEMAP_H_INCLUDED
#define GUIDEMAP_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Guidemap object]
*/
typedef struct _Guidemap
{
    int x, y;          // the position of image
    int width;
    int height;
    Shape *hitbox; // the hitbox of object
} Guidemap;
Elements *New_Guidemap(int label);
void Guidemap_update(Elements *self);
void Guidemap_interact(Elements *self, Elements *tar);
void Guidemap_draw(Elements *self);
void Guidemap_destory(Elements *self);

#endif
