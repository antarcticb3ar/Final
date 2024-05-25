#include "boom.h"
#include "boomrange.h"
#include "../shapes/Circle.h"
#include "../scene/sceneManager.h"
#include <allegro5/allegro.h>
/*
   [Boom function]
*/
Elements *New_Boom(int label, int x, int y, int q)
{
    Boom *pDerivedObj = (Boom *)malloc(sizeof(Boom));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/boom.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->q = q;
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x + pDerivedObj->width / 2,
                                     pDerivedObj->y + pDerivedObj->height / 2,
                                     min(pDerivedObj->width, pDerivedObj->height) / 2);
    pDerivedObj->timer = al_create_timer(1.5);
    al_start_timer(pDerivedObj->timer);                                     
    // setting the interact object
    // pObj->inter_obj[pObj->inter_len++] = Tree_L;
    // pObj->inter_obj[pObj->inter_len++] = Floor_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Boom_update;
    pObj->Interact = Boom_interact;
    pObj->Draw = Boom_draw;
    pObj->Destroy = Boom_destory;

    return pObj;
}
void Boom_update(Elements *self)
{
    Boom *Obj = ((Boom *)(self->pDerivedObj));
    if (al_get_timer_count(Obj->timer) >= 1.5) // Timer reached 1.5 seconds
    {
        // Create a Boomrange object when the bomb is about to be destroyed
        Elements *boomrange = New_Boomrange(Boomrange_L,
                                            Obj->x,
                                            Obj->y,
                                            3);
        _Register_elements(scene, boomrange); // Assuming _Register_elements adds the object to the scene

        self->dele = (self); // Mark the bomb for deletion
    }
}
void _Boom_update_position(Elements *self, int dx, int dy) {}
void Boom_interact(Elements *self, Elements *tar)
{
    // Boom *Obj = ((Boom *)(self->pDerivedObj));
    // if (tar->label == Floor_L)
    // {
        
    // }
    // else if (tar->label == Tree_L)
    // {
        
    // }
}
void Boom_draw(Elements *self)
{
    Boom *Obj = ((Boom *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, ALLEGRO_FLIP_HORIZONTAL);
    
}
void Boom_destory(Elements *self)
{
    Boom *Obj = ((Boom *)(self->pDerivedObj));
    
    al_destroy_bitmap(Obj->img);
    al_destroy_timer(Obj->timer);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
