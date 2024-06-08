#include "obstacle1.h"
#include "boomrange.h"
#include "qualityitem.h"
#include "speeditem.h"
#include "poweritem.h"
#include "../shapes/Rectangle.h"
#include "../scene/sceneManager.h"
#include <allegro5/allegro_primitives.h>
#include <stdlib.h> // For rand and srand
#include <time.h>   // For time
#include <stdint.h>
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
    pObj->inter_obj[pObj->inter_len++] = Boomrange_L;
    pDerivedObj->random_seed = (uintptr_t)pDerivedObj; // 使用对象地址作为随机种子
    // 设置随机种子
    srand(pDerivedObj->random_seed);
    // 生成隨機數random1
    pDerivedObj->interacted = false;                                                                                                                                               
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Obstacle1_update;
    pObj->Interact = Obstacle1_interact;
    pObj->Draw = Obstacle1_draw;
    pObj->Destroy = Obstacle1_destory;
    return pObj;
}
void Obstacle1_update(Elements *self) {
    Obstacle1 *Obj = ((Obstacle1 *)(self->pDerivedObj));

    Obj->random = rand() % 5; // 生成隨機數
}
void Obstacle1_interact(Elements *self, Elements *tar) {
    Obstacle1 *Obj = ((Obstacle1 *)(self->pDerivedObj));
    if (!Obj->interacted && tar->label == Boomrange_L) // 確保只執行一次
    {
        Boomrange *obs = ((Boomrange *)(tar->pDerivedObj));
        if (obs->hitbox->overlap(obs->hitbox, Obj->hitbox)) {  
            tar->dele = true;
            self->dele = true;
            Obj->interacted = true; 
            if(Obj->random == 0) {
                Elements *qualityitem; 
                qualityitem = New_Qualityitem(Qualityitem_L,
                                            Obj->x+12,
                                            Obj->y+11);
                _Register_elements(scene, qualityitem);                                            
            }
            else if(Obj->random == 1) {
                Elements *poweritem; 
                poweritem = New_Poweritem(Poweritem_L,
                                            Obj->x+12,
                                            Obj->y+11);
                _Register_elements(scene, poweritem);                                                 
            }
            else if(Obj->random == 2){
                Elements *speeditem; 
                speeditem = New_Speeditem(Speeditem_L,
                                            Obj->x+12,
                                            Obj->y+11);
                _Register_elements(scene, speeditem);                                             
            }
        }       
    }
}
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
