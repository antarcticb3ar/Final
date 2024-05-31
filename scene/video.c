#include <allegro5/allegro_primitives.h>
#include "video.h"
#include "../global.h"
#include <stdbool.h>
#define FRAME_DURATION 0.1
#define TOTAL_FRAME 35
/*
   [Video function]
*/

Scene *New_Video(int label)
{
    Video *pDerivedObj = (Video *)malloc(sizeof(Video));
    Scene *pObj = New_Scene(label);

    pDerivedObj->total_frame = TOTAL_FRAME;
    pDerivedObj->frame = (ALLEGRO_BITMAP **)malloc(sizeof(ALLEGRO_BITMAP *) *pDerivedObj->total_frame);
    for(int i = 0; i < pDerivedObj->total_frame; i++){
    char filepath[1000];
    snprintf(filepath, sizeof(filepath), "assets/video/%d.png", i+1);
    pDerivedObj->frame[i] = al_load_bitmap(filepath);
    }    
    
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/Pixellettersfull-BnJ5.ttf", 48, 0);
    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/ls5b0-poo7o.mp3");
    al_reserve_samples(20);

    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    pDerivedObj->timer = al_create_timer(FRAME_DURATION);
    pDerivedObj->current_frame = 0;
    al_start_timer(pDerivedObj->timer);
    pObj->pDerivedObj = pDerivedObj;
    
    // Setting derived object functions
    pObj->Update = Video_update;
    pObj->Draw = Video_draw;
    pObj->Destroy = Video_destroy;
    
    return pObj;
}
void Video_update(Scene *self)
{
    Video *Obj = (Video *)(self->pDerivedObj);
    
    
    if (al_get_timer_count(Obj->timer) >= Obj->current_frame) {
        Obj->current_frame++;
        if (Obj->current_frame >= Obj->total_frame) {
            self->scene_end = true;
            window = 1;
        }
    }
}
void Video_draw(Scene *self)
{
    Video *Obj = ((Video *)(self->pDerivedObj));   
    al_draw_bitmap(Obj->frame[Obj->current_frame], 0, 0, 0);
    /*al_draw_bitmap(Obj->background, 0, 0, 0);
    al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->title_x, Obj->title_y, ALLEGRO_ALIGN_CENTRE, "Press 'Enter'");
    for (int i = 0; i < Obj->option_count; i++)
    {
        ALLEGRO_COLOR color = (i == Obj->current_option) ? al_map_rgb(255, 0, 0) : al_map_rgb(0, 0, 0);
        al_draw_text(Obj->font, color, Obj->option_x, Obj->option_y_start + i * Obj->option_spacing, ALLEGRO_ALIGN_CENTRE, Obj->options[i]);
    }
    

    al_play_sample_instance(Obj->sample_instance);*/

}
void Video_destroy(Scene *self)
{
    Video *Obj = (Video *)(self->pDerivedObj);
    for(int i = 0; i < Obj->total_frame; i++) {
        al_destroy_bitmap(Obj->frame[i]);
    }
    
    al_destroy_timer(Obj->timer);
    //al_destroy_sample(Obj->song);
    free(Obj);
    free(self);
}
