#include "boomrange.h"
#include "boom.h"
#include "boom2.h"
#include "boarder.h"
#include "charater.h"
#include "charac2.h"
#include "obstacle.h"
#include "obstacle1.h"
#include "boom.h"
#include "heart.h"
#include "..\\global.h"
#include "../shapes/Rectangle.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
/*
   [Boomrange function]
*/
Elements *New_Boomrange(int label, int x, int y)
{
    Boomrange *pDerivedObj = (Boomrange *)malloc(sizeof(Boomrange));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/boomeffect.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x - 8;
    pDerivedObj->y = y - 3;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + 10,
                                        pDerivedObj->y + 14,
                                        pDerivedObj->x + 64.1,
                                        pDerivedObj->y + 62);
    pDerivedObj->timer = al_create_timer(0.28);
    al_start_timer(pDerivedObj->timer);     
    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/contury1.wav");
    pDerivedObj->remain_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->remain_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->remain_Sound, al_get_default_mixer()); 
    ALLEGRO_SAMPLE *sample2 = al_load_sample("assets/sound/godtonedie1.wav");
    pDerivedObj->remain2_Sound = al_create_sample_instance(sample2);
    al_set_sample_instance_playmode(pDerivedObj->remain2_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->remain2_Sound, al_get_default_mixer());                                  
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Character_L;
    pObj->inter_obj[pObj->inter_len++] = Character2_L;
    pObj->inter_obj[pObj->inter_len++] = Obstacle_L;
    pObj->inter_obj[pObj->inter_len++] = Obstacle1_L;
    pObj->inter_obj[pObj->inter_len++] = Boarder_L;
    pObj->inter_obj[pObj->inter_len++] = Boom_L;
    pObj->inter_obj[pObj->inter_len++] = Boom2_L;
    pObj->inter_obj[pObj->inter_len++] = Boomrange_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Boomrange_update;
    pObj->Interact = Boomrange_interact;
    pObj->Draw = Boomrange_draw;
    pObj->Destroy = Boomrange_destory;

    return pObj;
}
void Boomrange_update(Elements *self)
{
    Boomrange *Obj = ((Boomrange *)(self->pDerivedObj));
    if (al_get_timer_count(Obj->timer) >= 0.28 )
    {
        self->dele = (self); 
    }
}
void _Boomrange_update_position(Elements *self, int dx, int dy) {}
void Boomrange_interact(Elements *self, Elements *tar)
{
    Boomrange *Obj = ((Boomrange *)(self->pDerivedObj));
    if (tar->label == Character_L) {
        Character *chara = ((Character *)(tar->pDerivedObj));

        if (chara->hitbox->overlap(chara->hitbox, Obj->hitbox) && !chara->invincible) {  
            remain--;
            chara->invincible = true;
            chara->invincible_start_time = al_get_time();
            al_play_sample_instance(Obj->remain2_Sound);
            printf("Character hit! Remaining lives: %d\n", remain);
        }
    }
    else if (tar->label == Character2_L) {
        Character2 *chara2 = ((Character2 *)(tar->pDerivedObj));

        if (chara2->hitbox->overlap(chara2->hitbox, Obj->hitbox) && !chara2->invincible) {  
            remain2--;
            chara2->invincible = true;
            chara2->invincible_start_time = al_get_time();
            al_play_sample_instance(Obj->remain_Sound);
            printf("Character hit! Remaining lives: %d\n", remain2);
        }
    }
    else if (tar->label == Obstacle_L)
    {
        Obstacle *obs = ((Obstacle *)(tar->pDerivedObj));
        if (obs->hitbox->overlap(obs->hitbox, Obj->hitbox)) {  
            self->dele = true;
        }       
    }
    else if (tar->label == Obstacle1_L)
    {
        Obstacle1 *obs = ((Obstacle1 *)(tar->pDerivedObj));
        if (obs->hitbox->overlap(obs->hitbox, Obj->hitbox)) {  
            self->dele = true;
            tar->dele = true;
        }       
    }
    else if (tar->label == Boom_L)
    {
        Boom *obs = ((Boom *)(tar->pDerivedObj));
        if (obs->hitbox->overlap(obs->hitbox, Obj->hitbox)) {  
            obs->instant = true;
        }       
    }
    else if (tar->label == Boom2_L)
    {
        Boom2 *obs = ((Boom2 *)(tar->pDerivedObj));
        if (obs->hitbox->overlap(obs->hitbox, Obj->hitbox)) {  
            obs->instant = true;
        }       
    }
    else if (tar->label == Boarder_L)
    {
        Boarder *obs = ((Boarder *)(tar->pDerivedObj));
        if (obs->hitbox->overlap(obs->hitbox, Obj->hitbox) || obs->hitbox2->overlap(obs->hitbox2, Obj->hitbox)) {  
            self->dele = true;
        }       
    }
}
void Boomrange_draw(Elements *self)
{
    Boomrange *Obj = ((Boomrange *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, ALLEGRO_FLIP_HORIZONTAL);
    // al_draw_rectangle(Obj->x + 14,
    //                     Obj->y + 16,
    //                     Obj->x + 68.1,
    //                     Obj->y + 64, al_map_rgb(255, 0, 0), 2);
}
void Boomrange_destory(Elements *self)
{
    Boomrange *Obj = ((Boomrange *)(self->pDerivedObj));
    
    al_destroy_bitmap(Obj->img);
    al_destroy_timer(Obj->timer);
    al_destroy_sample_instance(Obj->remain_Sound);
    al_destroy_sample_instance(Obj->remain2_Sound);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
