#include <allegro5/allegro_primitives.h>
#include "video.h"
#include "../global.h"
#include <stdbool.h>

#define FRAME_DURATION 0.1
#define TOTAL_FRAME 62

/*
   [Video function]
*/

Scene *New_Video(int label)
{
    Video *pDerivedObj = (Video *)malloc(sizeof(Video));
    Scene *pObj = New_Scene(label);

    pDerivedObj->total_frame = TOTAL_FRAME;
    pDerivedObj->frame = (ALLEGRO_BITMAP **)malloc(sizeof(ALLEGRO_BITMAP *) * pDerivedObj->total_frame);
    
    for (int i = 0; i < pDerivedObj->total_frame; i++) {
        char filepath[1000];
        snprintf(filepath, sizeof(filepath), "assets/video/%d.png", i + 1);
        pDerivedObj->frame[i] = al_load_bitmap(filepath);
        if (!pDerivedObj->frame[i]) {
            fprintf(stderr, "Failed to load bitmap: %s\n", filepath);
            pDerivedObj->frame[i] = al_create_bitmap(1, 1); // 創建一個1x1的空白位圖作為占位符
            al_clear_to_color(al_map_rgb(0, 0, 0)); // 清空位圖為黑色
        }
    }
    
    pDerivedObj->font = al_load_ttf_font("assets/font/Pixellettersfull-BnJ5.ttf", 48, 0);
    if (!pDerivedObj->font) {
        fprintf(stderr, "Failed to load font.\n");
    }

    pDerivedObj->song = al_load_sample("assets/sound/ls5b0-poo7o.mp3");
    if (!pDerivedObj->song) {
        fprintf(stderr, "Failed to load sound.\n");
    }

    al_reserve_samples(20);

    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    pDerivedObj->timer = al_create_timer(FRAME_DURATION);
    pDerivedObj->current_frame = 0;
    al_start_timer(pDerivedObj->timer);
    pObj->pDerivedObj = pDerivedObj;
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
    Video *Obj = (Video *)(self->pDerivedObj);
    if (Obj->frame[Obj->current_frame]) {
        al_draw_bitmap(Obj->frame[Obj->current_frame], 0, 0, 0);
    } else {
        fprintf(stderr, "Frame %d is NULL.\n", Obj->current_frame);
    }
}

void Video_destroy(Scene *self)
{
    Video *Obj = (Video *)(self->pDerivedObj);
    for (int i = 0; i < Obj->total_frame; i++) {
        if (Obj->frame[i]) {
            al_destroy_bitmap(Obj->frame[i]);
        }
    }
    
    al_destroy_timer(Obj->timer);
    //al_destroy_sample(Obj->song);
    free(Obj);
    free(self);
}
