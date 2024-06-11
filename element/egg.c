#include "egg.h"
#include "boom2.h"
#include "../shapes/Circle.h"
#include "boomrange.h"

/*
   [Egg function]
*/
Elements *New_Egg(int label, int x, int y, int v)
{
    Egg *pDerivedObj = (Egg *)malloc(sizeof(Egg));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/egg.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->v = v;
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x + pDerivedObj->width / 2,
                                     pDerivedObj->y + pDerivedObj->height / 2,
                                     min(pDerivedObj->width, pDerivedObj->height) / 2);
    pDerivedObj->timer = al_create_timer(0.07);
    pDerivedObj->event_queue = al_create_event_queue();
    al_register_event_source(pDerivedObj->event_queue, al_get_timer_event_source(pDerivedObj->timer));
    al_start_timer(pDerivedObj->timer);


    // setting derived object function
    pObj->inter_obj[pObj->inter_len++] = Boomrange_L;
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Egg_update;
    pObj->Interact = Egg_interact;
    pObj->Draw = Egg_draw;
    pObj->Destroy = Egg_destory;

    return pObj;
}

void Egg_update(Elements *self)
{
    Egg *Obj = ((Egg *)(self->pDerivedObj));
    ALLEGRO_EVENT event;
    while (al_get_next_event(Obj->event_queue, &event))
    {
        if (event.type == ALLEGRO_EVENT_TIMER)
        {
            _Egg_update_position(self, 0, Obj->v);
        }
    }
}

void _Egg_update_position(Elements *self, int dx, int dy)
{
    Egg *Obj = ((Egg *)(self->pDerivedObj));
    Obj->x += dx;
    Obj->y += dy;

    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}

void Egg_interact(Elements *self, Elements *tar)
{
    Egg *Obj = ((Egg *)(self->pDerivedObj));
    if (tar->label == Boomrange_L)
    {
        Boomrange *obs = ((Boomrange *)(tar->pDerivedObj));
        if (obs->hitbox->overlap(obs->hitbox, Obj->hitbox)) {  
            self->dele = true;
        }
    }
}

void Egg_draw(Elements *self)
{
    Egg *Obj = ((Egg *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}

void Egg_destory(Elements *self)
{
    Egg *Obj = ((Egg *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    al_destroy_timer(Obj->timer);
    al_destroy_event_queue(Obj->event_queue);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
