#ifndef Obstacle_H_INCLUDED
#define Obstacle_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Obstacle object]
*/
typedef struct _Obstacle
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} Obstacle;
Elements *New_Obstacle(int label);
void Obstacle_update(Elements *self);
void Obstacle_interact(Elements *self, Elements *tar);
void Obstacle_draw(Elements *self);
void Obstacle_destory(Elements *self);

#endif
