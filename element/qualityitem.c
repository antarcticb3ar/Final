#include "obstacle.h"
#include "charater.h"
#include "charac2.h"
#include "boomrange.h"
#include "qualityitem.h"
#include "../shapes/Rectangle.h"
#include "../global.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <stdio.h>
/*
   [Qualityitem function]
*/
Elements *New_Qualityitem(int label, int x, int y)
{
    Qualityitem *pDerivedObj = (Qualityitem *)malloc(sizeof(Qualityitem));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/qualityitem.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x-5, pDerivedObj->y-5, pDerivedObj->x + 50, pDerivedObj->y + 40); 
    pDerivedObj->eaten1 = false;    
    pDerivedObj->eaten2 = false; 
    pDerivedObj->newborn = true;
    pDerivedObj->timer = al_create_timer(0.1); 
    pDerivedObj->timer2 = al_create_timer(0.1);
    pDerivedObj->newborntime = al_create_timer(2);
    al_start_timer(pDerivedObj->newborntime);                                                                                                                                                                 
    // setting derived object function
    pObj->inter_obj[pObj->inter_len++] = Character_L;
    pObj->inter_obj[pObj->inter_len++] = Character2_L;
    pObj->inter_obj[pObj->inter_len++] = Boomrange_L;
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Qualityitem_update;
    pObj->Interact = Qualityitem_interact;
    pObj->Draw = Qualityitem_draw;
    pObj->Destroy = Qualityitem_destory;
    return pObj;
}
void Qualityitem_update(Elements *self) {
    Qualityitem *Obj = ((Qualityitem *)(self->pDerivedObj));

    if (Obj->eaten1) {
        Obj->eaten1 = false;
    }
    if (Obj->eaten2) {
        Obj->eaten2 = false;
    }
    if (al_get_timer_count(Obj->newborntime) >= 1)
    {
        Obj->newborn = false; 
    }
}
void Qualityitem_interact(Elements *self, Elements *tar) {
    Qualityitem *Obj = ((Qualityitem *)(self->pDerivedObj));
    if (tar->label == Character_L)
    {
        Character *obs = ((Character *)(tar->pDerivedObj));
        if (obs->hitbox->overlap(obs->hitbox, Obj->hitbox)) {  
            if(!Obj->eaten1) { 
                free(Obj->hitbox);
                Obj->hitbox = New_Rectangle(0, 0, 0, 0);              
                Obj->eaten1 = true;
                quality = quality + 2;
            }
            self->dele = true;

        } 
              
    }
    if (tar->label == Character2_L)
    {
        Character2 *obs = ((Character2 *)(tar->pDerivedObj));
        if (obs->hitbox->overlap(obs->hitbox, Obj->hitbox)) {  
            if(!Obj->eaten2) {
                free(Obj->hitbox);
                Obj->hitbox = New_Rectangle(0, 0, 0, 0);                
                Obj->eaten2 = true;
                quality2 = quality2 + 2;
            }
            self->dele = true;
        }       
    }
    if (tar->label == Boomrange_L && !Obj->newborn)
    {
        Boomrange *obs = ((Boomrange *)(tar->pDerivedObj));
        if (obs->hitbox->overlap(obs->hitbox, Obj->hitbox)) {  
            self->dele = true;
        }       
    }
}
void Qualityitem_draw(Elements *self)
{
    Qualityitem *Obj = ((Qualityitem *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
    //al_draw_rectangle(Obj->x-5, Obj->y-5, Obj->x + 50, Obj->y + 40, al_map_rgb(0, 255, 0), 2);
}
void Qualityitem_destory(Elements *self)
{
    Qualityitem *Obj = ((Qualityitem *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    al_destroy_timer(Obj->timer);
    al_destroy_timer(Obj->timer2);
    al_destroy_timer(Obj->newborntime);
    free(Obj);
    free(self);
}
