#include "heart.h"
#include "charater.h"
#include "charac2.h"
#include "../shapes/Rectangle.h"
/*
   [Heart2 function]
*/
Elements *New_Heart2(int label, int x, int y)
{
    Heart2 *pDerivedObj = (Heart2 *)malloc(sizeof(Heart2));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/heart.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = y;
   // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Heart2_update;
    pObj->Interact = Heart2_interact;
    pObj->Draw = Heart2_draw;
    pObj->Destroy = Heart2_destory;
    return pObj;
}
void Heart2_update(Elements *self) {
    //Heart2 *Obj = ((Heart2 *)(self->pDerivedObj));
    
}
void Heart2_interact(Elements *self, Elements *tar) {
}
void Heart2_draw(Elements *self)
{
    Heart2 *Obj = ((Heart2 *)(self->pDerivedObj));
    for(int i = 0;i < remain2;i++){
        al_draw_bitmap(Obj->img, Obj->x + i * 30, Obj->y, 0);
    }
    
}
void Heart2_destory(Elements *self)
{
    Heart2 *Obj = ((Heart2 *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
