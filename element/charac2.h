#ifndef CHARATER2_H_INCLUDED
#define CHARATER2_H_INCLUDED
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

typedef struct _Character2
{
    int x, y;
    int width, height;              // the width and height of image
    int dir;          // 1, 2, 3, 4  [下,左,右,上]
    bool dir1;
    int state;                      // the state of Character2
    bool needstop;
    int currentx; //現在的x格的座標
    int currenty; //現在的y格的座標
    int remain; //剩下多少血
    bool invincible;
    double invincible_start_time;
    ALGIF_ANIMATION *gif_status[4]; // gif for each state. 0: stop, 1: move, 2:attack
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    ALLEGRO_TIMER *timer;
    bool new_boom;
    int anime;      // counting the time of animation
    int anime_time; // indicate how long the animation   
    Shape *hitbox; // the hitbox of object
    Shape *hitbox2; // the hitbox of need put boom
} Character2;
Elements *New_Character2(int label);
void _Character2_update_position(Elements *self, int dx, int dy);
void Character2_update(Elements *self);
void Character2_interact(Elements *self, Elements *target);
void Character2_draw(Elements *self);
void Character2_destory(Elements *self);

#endif
