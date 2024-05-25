#include "boomrange.h"
#include "boom.h"
#include "../shapes/Rectangle.h"
#include <allegro5/allegro.h>
/*
   [Boomrange function]
*/
Elements *New_Boomrange(int label, int x, int y, int l)
{
    Boomrange *pDerivedObj = (Boomrange *)malloc(sizeof(Boomrange));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/boomeffect.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->l = l;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);
    pDerivedObj->timer = al_create_timer(0.5);
    al_start_timer(pDerivedObj->timer);                                     
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Tree_L;
    pObj->inter_obj[pObj->inter_len++] = Floor_L;
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
    if (al_get_timer_count(Obj->timer) >= 0.5)
    {
        self->dele = (self); 
    }
}
void _Boomrange_update_position(Elements *self, int dx, int dy) {}
void Boomrange_interact(Elements *self, Elements *tar)
{
    // Boomrange *Obj = ((Boomrange *)(self->pDerivedObj));
    // if (tar->label == Floor_L)
    // {
        
    // }
    // else if (tar->label == Tree_L)
    // {
        
    // }
}
void Boomrange_draw(Elements *self)
{
    Boomrange *Obj = ((Boomrange *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, ALLEGRO_FLIP_HORIZONTAL);
    
}
void Boomrange_destory(Elements *self)
{
    Boomrange *Obj = ((Boomrange *)(self->pDerivedObj));
    
    al_destroy_bitmap(Obj->img);
    al_destroy_timer(Obj->timer);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
