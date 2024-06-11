#ifndef Setting_H_INCLUDED
#define Setting_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

/*
   [Setting object]
*/
typedef struct _Setting
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    int title_x, title_y;
    int option_x, option_y_start, option_spacing;
    char *options[1];
    int option_count;
    int current_option;
    ALLEGRO_BITMAP *background;
} Setting;
Scene *New_Setting(int label);
void setting_update(Scene *self);
void setting_draw(Scene *self);
void setting_destroy(Scene *self);

#endif
