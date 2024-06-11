#include <allegro5/allegro_primitives.h>
#include "setting.h"
#include <stdbool.h>

/*
   [Setting function]
*/

Scene *New_Setting(int label)
{
    Setting *pDerivedObj = (Setting *)malloc(sizeof(Setting));
    Scene *pObj = New_Scene(label);

    pDerivedObj->background = al_load_bitmap("assets/image/setting.png");
    if (!pDerivedObj->background) {
        fprintf(stderr, "Failed to load background image.\n");
        free(pDerivedObj);
        free(pObj);
        return NULL;
    }
    
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/Pixellettersfull-BnJ5.ttf", 48, 0);
    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/ls5b0-poo7o.mp3");
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2 + 90;
    pDerivedObj->option_x = WIDTH / 2;
    pDerivedObj->option_y_start = HEIGHT / 2 + 80;
    pDerivedObj->option_spacing = 30;
    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.1);
    pObj->pDerivedObj = pDerivedObj;
    pDerivedObj->options[0] = "back";
    pDerivedObj->current_option = 0;
    
    pObj->pDerivedObj = pDerivedObj;
    
    // Setting derived object functions
    pObj->Update = setting_update;
    pObj->Draw = setting_draw;
    pObj->Destroy = setting_destroy;
    
    return pObj;
    // setting derived object function
    pObj->Update = setting_update;
    pObj->Draw = setting_draw;
    pObj->Destroy = setting_destroy;
    return pObj;
}
void setting_update(Scene *self)
{
    Setting *Obj = (Setting *)(self->pDerivedObj);
    if (key_state[ALLEGRO_KEY_M])
    {
        if (Obj->current_option == 0) 
        {
            self->scene_end = true;
            window = 1;
        }
    }
    return;
}
void setting_draw(Scene *self)
{
    Setting *Obj = ((Setting *)(self->pDerivedObj));   
    
    al_draw_bitmap(Obj->background, 0, 0, 0);
    al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->title_x, Obj->title_y, ALLEGRO_ALIGN_CENTRE, "Press 'm' to be back.");
    for (int i = 0; i < Obj->option_count; i++)
    {
        ALLEGRO_COLOR color = (i == Obj->current_option) ? al_map_rgb(255, 0, 0) : al_map_rgb(0, 0, 0);
        al_draw_text(Obj->font, color, Obj->option_x, Obj->option_y_start + i * Obj->option_spacing, ALLEGRO_ALIGN_CENTRE, Obj->options[i]);
    }
    

    al_play_sample_instance(Obj->sample_instance);
}
void setting_destroy(Scene *self)
{
    Setting *Obj = (Setting *)(self->pDerivedObj);
    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    al_destroy_bitmap(Obj->background);
    free(Obj);
    free(self);
}
