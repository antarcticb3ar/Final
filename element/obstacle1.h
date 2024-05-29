#ifndef OBSTACLE1_H_INCLUDED
#define OBSTACLE1_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Obstacle1 object]
*/
typedef struct _Obstacle1
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    Shape *hitbox, *hitbox2;//, *hitbox3, *hitbox4; // the hitbox of object
} Obstacle1;
Elements *New_Obstacle1(int label, int x, int y);
void Obstacle1_update(Elements *self);
void Obstacle1_interact(Elements *self, Elements *tar);
void Obstacle1_draw(Elements *self);
void Obstacle1_destory(Elements *self);
#endif
