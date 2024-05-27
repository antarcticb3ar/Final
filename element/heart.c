#include "Heart.h"
#include "../shapes/Rectangle.h"
/*
   [Heart function]
*/
Elements *New_Heart(int label)
{
    Heart *pDerivedObj = (Heart *)malloc(sizeof(Heart));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/heart.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 70;
    pDerivedObj->y = 20;
    pDerivedObj->remain = 3;

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Heart_update;
    pObj->Interact = Heart_interact;
    pObj->Draw = Heart_draw;
    pObj->Destroy = Heart_destory;
    return pObj;
}
void Heart_update(Elements *self) {}
void Heart_interact(Elements *self, Elements *tar) {}
void Heart_draw(Elements *self)
{
    Heart *Obj = ((Heart *)(self->pDerivedObj));
    for(int i = 0;i < Obj->remain;i++){
        al_draw_bitmap(Obj->img, Obj->x + i * 30, Obj->y, 0);
    }
    
}
void Heart_destory(Elements *self)
{
    Heart *Obj = ((Heart *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
