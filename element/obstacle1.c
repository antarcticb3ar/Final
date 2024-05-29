#include "obstacle1.h"
#include "../shapes/Rectangle.h"
#include <allegro5/allegro_primitives.h>
/*
   [Obstacle1 function]
*/
Elements *New_Obstacle1(int label, int x, int y)
{
    Obstacle1 *pDerivedObj = (Obstacle1 *)malloc(sizeof(Obstacle1));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/Obstacle.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x, pDerivedObj->y, pDerivedObj->x + 67.1, pDerivedObj->y + 65.5);                                                                                                                                                                       
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Obstacle1_update;
    pObj->Interact = Obstacle1_interact;
    pObj->Draw = Obstacle1_draw;
    pObj->Destroy = Obstacle1_destory;
    return pObj;
}
void Obstacle1_update(Elements *self) {}
void Obstacle1_interact(Elements *self, Elements *tar) {}
void Obstacle1_draw(Elements *self)
{
    Obstacle1 *Obj = ((Obstacle1 *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Obstacle1_destory(Elements *self)
{
    Obstacle1 *Obj = ((Obstacle1 *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    //free(Obj->hitbox3);
    //free(Obj->hitbox4);
    free(Obj);
    free(self);
}
