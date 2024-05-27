#include "boom.h"
#include "boomrange.h"
#include "charater.h"
#include "../shapes/Circle.h"
#include "../scene/sceneManager.h"
#include "../shapes/Rectangle.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

/*
   [Boom function]
*/
Elements *New_Boom(int label, int x, int y, int q)
{
    Boom *pDerivedObj = (Boom *)malloc(sizeof(Boom));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/boom.png");
    pDerivedObj->x = x;
    printf("%d\n", x);
    pDerivedObj->y = y;
    printf("%d\n", y);
    pDerivedObj->q = q;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x -3,
                                        pDerivedObj->y + 25,
                                        pDerivedObj->x + 71,
                                        pDerivedObj->y + 67);

    pDerivedObj->timer = al_create_timer(1.5);
    pDerivedObj->characteron = true;
    al_start_timer(pDerivedObj->timer);                                     
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Obstacle_L;
    pObj->inter_obj[pObj->inter_len++] = Character_L;
    //pObj->inter_obj[pObj->inter_len++] = Floor_L;
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
        
        //for(int i = 0;i < 2/*Obj->l*/;i++) {
            Elements *boomrange; 
            boomrange = New_Boomrange(Boomrange_L,
                                            Obj->x,
                                            Obj->y);
            int i = 1;
            _Register_elements(scene, boomrange);
            boomrange = New_Boomrange(Boomrange_L, Obj->x + 77.5 * i, Obj->y);
            _Register_elements(scene, boomrange);
            boomrange = New_Boomrange(Boomrange_L, Obj->x - 77.5 * i, Obj->y);
            _Register_elements(scene, boomrange);
            boomrange = New_Boomrange(Boomrange_L, Obj->x, Obj->y + 51.5 * i);
            _Register_elements(scene, boomrange);
            boomrange = New_Boomrange(Boomrange_L, Obj->x, Obj->y - 51.5 * i);
            _Register_elements(scene, boomrange); // Assuming _Register_elements adds the object to the scene
        
    //}

        self->dele = (self); // Mark the bomb for deletion
    }
}
void _Boom_update_position(Elements *self, int dx, int dy) {}
void Boom_interact(Elements *self, Elements *tar)
{
    Boom *Obj = ((Boom *)(self->pDerivedObj));
    if (tar->label == Character_L)
    {
        Character *chara = ((Character *)(tar->pDerivedObj));
             
        // 如果角色在炸弹上方，则允许角色站在炸弹上
        if (Obj->characteron && Obj->hitbox->overlap(Obj->hitbox, chara->hitbox))
        {
            Obj->characteron = true;
        }
        else
        {
            Obj->characteron = false;
            // 处理角色与炸弹的碰撞
            if (Obj->hitbox->overlap(Obj->hitbox, chara->hitbox))
            {
                chara->needstop = true;
            }
        }
    }
    // else if (tar->label == Tree_L)
    // {
        
    // }
}
void Boom_draw(Elements *self)
{
    Boom *Obj = ((Boom *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
    al_draw_rectangle(Obj->x - 3,
                        Obj->y + 25,
                        Obj->x + 71,
                        Obj->y + 67, al_map_rgb(255, 0, 0), 2);
    
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
