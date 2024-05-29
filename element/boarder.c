#include "boarder.h"
#include "../shapes/Rectangle.h"
#include <allegro5/allegro_primitives.h>
/*
   [Boarder function]
*/
Elements *New_Boarder(int label, int x, int y)
{
    Boarder *pDerivedObj = (Boarder *)malloc(sizeof(Boarder));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x, pDerivedObj->y, pDerivedObj->x + 570.5, pDerivedObj->y + 63); 
    pDerivedObj->hitbox2 = New_Rectangle(pDerivedObj->x, pDerivedObj->y, pDerivedObj->x + 67.1, pDerivedObj->y + 506.5);                                                                                                                                                                       
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Boarder_update;
    pObj->Interact = Boarder_interact;
    pObj->Draw = Boarder_draw;
    pObj->Destroy = Boarder_destory;
    return pObj;
}
void Boarder_update(Elements *self) {}
void Boarder_interact(Elements *self, Elements *tar) {}
void Boarder_draw(Elements *self)
{
}
void Boarder_destory(Elements *self)
{
    Boarder *Obj = ((Boarder *)(self->pDerivedObj));
    free(Obj->hitbox);
    free(Obj->hitbox2);
    //free(Obj->hitbox3);
    //free(Obj->hitbox4);
    free(Obj);
    free(self);
}
