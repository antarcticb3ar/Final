#ifndef CHARAC2_H_INCLUDED
#define CHARAC2_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "element.h"
#include "../shapes/Shape.h"
#include "../algif5/src/algif.h"
#include <stdbool.h>

/*
   [character object]
*/
typedef enum Charac2Type
{
    STOP2 = 0,
    MOVE2,
    ATK2
} Charac2Type;
typedef struct _Charac2
{
    int x, y;
    int width, height;              // the width and height of image
    int dir;          // 1, 2, 3, 4  [下,左,右,上]
    bool dir1;
    int state;                      // the state of character
    bool needstop;
    ALGIF_ANIMATION *gif_status[3]; // gif for each state. 0: stop, 1: move, 2:attack
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    int anime;      // counting the time of animation
    int anime_time; // indicate how long the animation
    bool new_proj;
    Shape *hitbox; // the hitbox of object
} Charac2;
Elements *New_Charac2(int label);
void _Charac2_update_position(Elements *self, int dx, int dy);
void Charac2_update(Elements *self);
void Charac2_interact(Elements *self, Elements *target);
void Charac2_draw(Elements *self);
void Charac2_destory(Elements *self);

#endif
