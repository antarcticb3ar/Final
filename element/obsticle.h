#ifndef OBSTICLE_H_INCLUDED
#define OBSTICLE_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Obsticle object]
*/
typedef struct _Obsticle
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} Obsticle;
Elements *New_Obsticle(int label);
void Obsticle_update(Elements *self);
void Obsticle_interact(Elements *self, Elements *tar);
void Obsticle_draw(Elements *self);
void Obsticle_destory(Elements *self);

#endif
