#include "obstacle.h"
#include "charater.h"
#include "charac2.h"
#include "boomrange.h"
#include "speeditem.h"
#include "../shapes/Rectangle.h"
#include "../global.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <stdio.h>
/*
   [Speeditem function]
*/
Elements *New_Speeditem(int label, int x, int y)
{
    Speeditem *pDerivedObj = (Speeditem *)malloc(sizeof(Speeditem));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/speeditem.png");
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
    pObj->Update = Speeditem_update;
    pObj->Interact = Speeditem_interact;
    pObj->Draw = Speeditem_draw;
    pObj->Destroy = Speeditem_destory;
    return pObj;
}
void Speeditem_update(Elements *self) {
    Speeditem *Obj = ((Speeditem *)(self->pDerivedObj));
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
void Speeditem_interact(Elements *self, Elements *tar) {
    Speeditem *Obj = ((Speeditem *)(self->pDerivedObj));
    if (tar->label == Character_L)
    {
        Character *obs = ((Character *)(tar->pDerivedObj));
        if (obs->hitbox->overlap(obs->hitbox, Obj->hitbox)) {  
            if(!Obj->eaten1) { 
                free(Obj->hitbox);
                Obj->hitbox = New_Rectangle(0, 0, 0, 0);              
                Obj->eaten1 = true;
                speed2 = speed2 + 1;
                if(speed2 >= 4)
                    speed2 = 4;
                al_rest(0.01);
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
                speed1 = speed1 + 1;
                if(speed1 >= 4)
                    speed1 = 4;
                al_rest(0.01);
            }
            self->dele = true;

        }       
    }
    if (tar->label == Boomrange_L&& !Obj->newborn)
    {
        Boomrange *obs = ((Boomrange *)(tar->pDerivedObj));
        if (obs->hitbox->overlap(obs->hitbox, Obj->hitbox)) {  
            self->dele = true;
        }       
    }
}
void Speeditem_draw(Elements *self)
{
    Speeditem *Obj = ((Speeditem *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
    //al_draw_rectangle(Obj->x-5, Obj->y-5, Obj->x + 50, Obj->y + 40, al_map_rgb(0, 255, 0), 2);
}
void Speeditem_destory(Elements *self)
{
    Speeditem *Obj = ((Speeditem *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    al_destroy_timer(Obj->timer);
    al_destroy_timer(Obj->timer2);
    al_destroy_timer(Obj->newborntime);
    free(Obj);
    free(self);
}
