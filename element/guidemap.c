#include "guidemap.h"
#include "../shapes/Rectangle.h"
#include <allegro5/allegro_primitives.h>
/*
   [Guidemap function]
*/
Elements *New_Guidemap(int label)
{
    Guidemap *pDerivedObj = (Guidemap *)malloc(sizeof(Guidemap));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->x = 105; // 493
    pDerivedObj->y = 182; // 387
    pDerivedObj->width = 80; //x間隔77
    pDerivedObj->height = 52; //y間隔51
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);                                   
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Guidemap_update;
    pObj->Interact = Guidemap_interact;
    pObj->Draw = Guidemap_draw;
    pObj->Destroy = Guidemap_destory;
    return pObj;
}
void Guidemap_update(Elements *self) {}
void Guidemap_interact(Elements *self, Elements *tar) {}
void Guidemap_draw(Elements *self)
{
    Guidemap *Obj = ((Guidemap *)(self->pDerivedObj));
    for(int i = 0;i<9;i++) {
        for(int j = 0;j<8;j++) {
            al_draw_rectangle(Obj->x,
                            Obj->y,
                            Obj->x + Obj->width + 77 * i,
                            Obj->y + Obj->height + 51 * j, al_map_rgb(255, 0, 0), 2);
        }
    }
    
}
void Guidemap_destory(Elements *self)
{
    Guidemap *Obj = ((Guidemap *)(self->pDerivedObj));
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
