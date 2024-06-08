#ifndef Boom2_H_INCLUDED
#define Boom2_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "../algif5/src/algif.h"
#include "../shapes/Shape.h"
#include <stdbool.h>
/*
   [Boom2 object]
*/
typedef struct _Boom2
{
    int x, y;          // the position of image
    int q;             // the quantity of Boom2
    int l;             // the lengh of Boom2
    int newboom; 
    int nextRange;
    int soon;
    bool exploded;
    ALGIF_ANIMATION *img;
    ALLEGRO_TIMER *timer;
    bool characteron1, characteron2;
    bool instant;
    bool stopRight, stopLeft, stopUp, stopDown;
    Shape *hitbox, *hitbox2; // the hitbox of object
} Boom2;
Elements *New_Boom2(int label, int x, int y, int l);
void Boom2_update(Elements *self);
void Boom2_interact(Elements *self, Elements *tar);
void Boom2_draw(Elements *self);
void Boom2_destory(Elements *self);
void _Boom2_update_position(Elements *self, int dx, int dy);
#endif
