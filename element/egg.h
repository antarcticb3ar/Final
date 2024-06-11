#ifndef Egg_H_INCLUDED
#define Egg_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include <allegro5/allegro_image.h>
#include "../algif5/src/algif.h"
/*
   [Egg object]
*/
typedef struct _Egg
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    int v;             // the velocity of projectile
    ALLEGRO_BITMAP *img;
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_QUEUE *event_queue; // the event queue for timer events
    Shape *hitbox; // the hitbox of object
} Egg;

Elements *New_Egg(int label, int x, int y, int v);
void Egg_update(Elements *self);
void Egg_interact(Elements *self, Elements *tar);
void Egg_draw(Elements *self);
void Egg_destory(Elements *self);
void _Egg_update_position(Elements *self, int dx, int dy);

#endif