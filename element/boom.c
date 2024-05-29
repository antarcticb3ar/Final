#include "boom.h"
#include "boomrange.h"
#include "charater.h"
#include "../shapes/Circle.h"
#include "../scene/sceneManager.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
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
    pDerivedObj->img = algif_new_gif("assets/image/boom.gif", 1.5);
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->q = q;
    pDerivedObj->l = 3;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + 2,
                                        pDerivedObj->y + 10,
                                        pDerivedObj->x + 66.1,
                                        pDerivedObj->y + 68);
    pDerivedObj->instant = false;                                        

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
    if (al_get_timer_count(Obj->timer) >= 1.5 || Obj->instant) // Timer reached 1.5 seconds
    {
        // Create a Boomrange object when the bomb is about to be destroyed
        
        //for(int i = 0;i < 2/*Obj->l*/;i++) {
            Elements *boomrange; 
            boomrange = New_Boomrange(Boomrange_L,
                                            Obj->x,
                                            Obj->y);
            int i = 1;
             _Register_elements(scene, boomrange);
            boomrange = New_Boomrange(Boomrange_L, Obj->x + 67.1 * i, Obj->y);
            _Register_elements(scene, boomrange);
            boomrange = New_Boomrange(Boomrange_L, Obj->x - 65.5* i, Obj->y);
            _Register_elements(scene, boomrange);
            boomrange = New_Boomrange(Boomrange_L, Obj->x, Obj->y + 67.1 * i);
            _Register_elements(scene, boomrange);
            boomrange = New_Boomrange(Boomrange_L, Obj->x, Obj->y - 65.5 * i);
            _Register_elements(scene, boomrange); // Assuming _Register_elements adds the object to the scene
        
            

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
    else if (tar->label == Character2_L)
    {
        Character2 *chara = ((Character2 *)(tar->pDerivedObj));
             
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
    ALLEGRO_BITMAP *frame = algif_get_bitmap(Obj->img, al_get_time());
    if (frame)
    {
        al_draw_bitmap(frame, Obj->x, Obj->y,0);
    }

    al_draw_rectangle(Obj->x + 2,
                        Obj->y + 10,
                        Obj->x + 66.1,
                        Obj->y + 68, al_map_rgb(255, 0, 0), 2);
    
}
void Boom_destory(Elements *self)
{
    Boom *Obj = ((Boom *)(self->pDerivedObj));
    //al_destroy_sample_instance(Obj->atk_Sound);
    algif_destroy_animation(Obj->img);
    al_destroy_timer(Obj->timer);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
