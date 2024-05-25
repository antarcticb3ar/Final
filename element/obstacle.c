#include "obstacle.h"
#include "../shapes/Rectangle.h"
/*
   [Obstacle function]
*/
Elements *New_Obstacle(int label)
{
    Obstacle *pDerivedObj = (Obstacle *)malloc(sizeof(Obstacle));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/Obstacle.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 200;
    pDerivedObj->y = 300;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);                                   
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Obstacle_update;
    pObj->Interact = Obstacle_interact;
    pObj->Draw = Obstacle_draw;
    pObj->Destroy = Obstacle_destory;
    return pObj;
}
void Obstacle_update(Elements *self) {}
void Obstacle_interact(Elements *self, Elements *tar) {}
void Obstacle_draw(Elements *self)
{
    Obstacle *Obj = ((Obstacle *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Obstacle_destory(Elements *self)
{
    Obstacle *Obj = ((Obstacle *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
