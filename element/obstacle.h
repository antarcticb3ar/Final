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
    Shape *hitbox, *hitbox2;//, *hitbox3, *hitbox4; // the hitbox of object
} Obstacle;
Elements *New_Obstacle(int label, int x, int y);
void Obstacle_update(Elements *self);
void Obstacle_interact(Elements *self, Elements *tar);
void Obstacle_draw(Elements *self);
void Obstacle_destory(Elements *self);
#endif
