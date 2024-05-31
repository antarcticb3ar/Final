#ifndef video_H_INCLUDED
#define video_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

/*
   [video object]
*/
typedef struct _Video
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_TIMER *timer;
    ALLEGRO_BITMAP **frame;
    int current_frame;
    int total_frame;
} Video;
Scene *New_Video(int label);
void Video_update(Scene *self);
void Video_draw(Scene *self);
void Video_destroy(Scene *self);

#endif
