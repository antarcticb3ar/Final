#include "boom.h"
#include "obstacle.h"
#include "obstacle1.h"
#include "boomrange.h"
#include "charater.h"
#include "charac2.h"
#include "../global.h"
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
    pDerivedObj->nextRange = 1;

    pDerivedObj->stopRight = false;
    pDerivedObj->stopLeft = false;
    pDerivedObj->stopUp = false;
    pDerivedObj->stopDown = false;

    pDerivedObj->timer = al_create_timer(1.2);
    pDerivedObj->exploded = false;
    pDerivedObj->characteron1 = true;
    pDerivedObj->characteron2 = true;
    
    al_start_timer(pDerivedObj->timer);                                     
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Obstacle_L;
    pObj->inter_obj[pObj->inter_len++] = Obstacle1_L;
    pObj->inter_obj[pObj->inter_len++] = Character_L;
    pObj->inter_obj[pObj->inter_len++] = Character2_L;
    pObj->inter_obj[pObj->inter_len++] = Boomrange_L;
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
    if (al_get_timer_count(Obj->timer) >= 1.2 || Obj->instant) // Timer reached 1.5 seconds
    {
        // Create a Boomrange object when the bomb is about to be destroyed
        if (!Obj->exploded)
        {
            Elements *boomrange;
            boomrange = New_Boomrange(Boomrange_L, Obj->x, Obj->y);
            _Register_elements(scene, boomrange);
            int i = 1;
            boomrange = New_Boomrange(Boomrange_L, Obj->x + 67.1 * i, Obj->y);
            _Register_elements(scene, boomrange);
            boomrange = New_Boomrange(Boomrange_L, Obj->x - 65.5* i, Obj->y);
            _Register_elements(scene, boomrange);
            boomrange = New_Boomrange(Boomrange_L, Obj->x, Obj->y + 67.1 * i);
            _Register_elements(scene, boomrange);
            boomrange = New_Boomrange(Boomrange_L, Obj->x, Obj->y - 65.5 * i);
            _Register_elements(scene, boomrange);
            quality++;
            if (power1 == 2)
            {
                if (!Obj->stopUp)
                {
                    int newY = Obj->y - 65.5 * Obj->nextRange;
                    if(newY > 55) {
                        boomrange = New_Boomrange(Boomrange_L, Obj->x, newY);
                        _Register_elements(scene, boomrange);
                    }
                }

                if (!Obj->stopDown)
                {
                    int newY = Obj->y + 67.1 * Obj->nextRange;
                    if(newY < 506.5){
                        boomrange = New_Boomrange(Boomrange_L, Obj->x, newY);
                        _Register_elements(scene, boomrange);
                    }
                }
                if (!Obj->stopRight)
                {
                    int newX = Obj->x + 67.1 * Obj->nextRange;
                    if(newX < 637.6){
                        boomrange = New_Boomrange(Boomrange_L, newX, Obj->y);
                        _Register_elements(scene, boomrange);
                    }
                }

                if (!Obj->stopLeft)
                {
                    int newX = Obj->x - 65.5 * Obj->nextRange;
                    if(newX > 235) {
                        boomrange = New_Boomrange(Boomrange_L, newX, Obj->y);
                        _Register_elements(scene, boomrange);
                    }
                }
            }
        }
        Obj->exploded = true;
        self->dele = true; // Mark the bomb for deletion
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
        if (Obj->characteron1 && Obj->hitbox->overlap(Obj->hitbox, chara->hitbox))
        {
            Obj->characteron1 = true;
        }
        else
        {
            Obj->characteron1 = false;
            // 处理角色与炸弹的碰撞
            if (Obj->hitbox->overlap(Obj->hitbox, chara->hitbox))
            {
                chara->needstop = true;
            }
        }
    }
    else if (tar->label == Character2_L)
    {
        Character2 *chara2 = ((Character2 *)(tar->pDerivedObj));
             
        // 如果角色在炸弹上方，则允许角色站在炸弹上
        if (Obj->characteron2 && Obj->hitbox->overlap(Obj->hitbox, chara2->hitbox))
        {
            Obj->characteron2 = true;
        }
        else
        {
            Obj->characteron2 = false;
            // 处理角色与炸弹的碰撞
            if (Obj->hitbox->overlap(Obj->hitbox, chara2->hitbox))
            {
                chara2->needstop = true;
            }
        }
    }
    else if (tar->label == Obstacle_L)
    {
        Obstacle *obs = ((Obstacle *)(tar->pDerivedObj));
        
        if(power1 == 2) {
            int new = Obj->nextRange - 1;
            if (!Obj->stopUp){
                int newY = Obj->y - 65.5 * new;
                Obj->hitbox2 = New_Rectangle(Obj->x+4,newY + 14,Obj->x + 62.1,newY + 64);
                if (Obj->hitbox2->overlap(Obj->hitbox2, obs->hitbox)) {
                    Obj->stopUp = true;
                free(Obj->hitbox2);
                }
            }
            if (!Obj->stopDown){
                int newY = Obj->y + 65.5 * new;
                Obj->hitbox2 = New_Rectangle(Obj->x+4,newY + 14,Obj->x + 62.1,newY + 64);
                if (Obj->hitbox2->overlap(Obj->hitbox2, obs->hitbox)) {
                    Obj->stopDown = true;
                free(Obj->hitbox2); 
                }
            }
            if (!Obj->stopRight){
                int newX = Obj->x + 67.1 * new;
                Obj->hitbox2 = New_Rectangle(newX+4,Obj->y + 14,newX + 62.1,Obj->y + 64);
                if (Obj->hitbox2->overlap(Obj->hitbox2, obs->hitbox)) {
                    Obj->stopRight = true;
                free(Obj->hitbox2);  
                }
            }
            if (!Obj->stopLeft){
                int newX = Obj->x - 67.1 * new;
                Obj->hitbox2 = New_Rectangle(newX+4,Obj->y + 14,newX + 62.1,Obj->y + 64);
                if (Obj->hitbox2->overlap(Obj->hitbox2, obs->hitbox)) {
                    Obj->stopLeft = true;
                    free(Obj->hitbox2); 
                }
            }
            
        }
        
    }
    else if (tar->label == Obstacle1_L)
    {
        Obstacle1 *obs = ((Obstacle1 *)(tar->pDerivedObj));
        
        if(power1 == 2) {
            int new = Obj->nextRange - 1;
            if (!Obj->stopUp){
                int newY = Obj->y - 65.5 * new;
                Obj->hitbox2 = New_Rectangle(Obj->x+4,newY + 14,Obj->x + 62.1,newY + 64);
                if (Obj->hitbox2->overlap(Obj->hitbox2, obs->hitbox)) {
                    Obj->stopUp = true;
                free(Obj->hitbox2);
                }
            }
            if (!Obj->stopDown){
                int newY = Obj->y + 65.5 * new;
                Obj->hitbox2 = New_Rectangle(Obj->x+4,newY + 14,Obj->x + 62.1,newY + 64);
                if (Obj->hitbox2->overlap(Obj->hitbox2, obs->hitbox)) {
                    Obj->stopDown = true;
                free(Obj->hitbox2); 
                }
            }
            if (!Obj->stopRight){
                int newX = Obj->x + 67.1 * new;
                Obj->hitbox2 = New_Rectangle(newX+4,Obj->y + 14,newX + 62.1,Obj->y + 64);
                if (Obj->hitbox2->overlap(Obj->hitbox2, obs->hitbox)) {
                    Obj->stopRight = true;
                free(Obj->hitbox2);  
                }
            }
            if (!Obj->stopLeft){
                int newX = Obj->x - 67.1 * new;
                Obj->hitbox2 = New_Rectangle(newX+4,Obj->y + 14,newX + 62.1,Obj->y + 64);
                if (Obj->hitbox2->overlap(Obj->hitbox2, obs->hitbox)) {
                    Obj->stopLeft = true;
                    free(Obj->hitbox2); 
                }
            }
            
        }
        
    }
    else if (tar->label == Boomrange_L)
    {
        Boomrange *obs = ((Boomrange *)(tar->pDerivedObj));
        
        if(power1 == 2) {
            int new = Obj->nextRange - 1;
            if (!Obj->stopUp){
                int newY = Obj->y - 65.5 * new;
                Obj->hitbox2 = New_Rectangle(Obj->x+4,newY + 14,Obj->x + 62.1,newY + 64);
                if (Obj->hitbox2->overlap(Obj->hitbox2, obs->hitbox)) {
                    Obj->stopUp = true;
                free(Obj->hitbox2);
                }
            }
            if (!Obj->stopDown){
                int newY = Obj->y + 65.5 * new;
                Obj->hitbox2 = New_Rectangle(Obj->x+4,newY + 14,Obj->x + 62.1,newY + 64);
                if (Obj->hitbox2->overlap(Obj->hitbox2, obs->hitbox)) {
                    Obj->stopDown = true;
                free(Obj->hitbox2); 
                }
            }
            if (!Obj->stopRight){
                int newX = Obj->x + 67.1 * new;
                Obj->hitbox2 = New_Rectangle(newX+4,Obj->y + 14,newX + 62.1,Obj->y + 64);
                if (Obj->hitbox2->overlap(Obj->hitbox2, obs->hitbox)) {
                    Obj->stopRight = true;
                free(Obj->hitbox2);  
                }
            }
            if (!Obj->stopLeft){
                int newX = Obj->x - 67.1 * new;
                Obj->hitbox2 = New_Rectangle(newX+4,Obj->y + 14,newX + 62.1,Obj->y + 64);
                if (Obj->hitbox2->overlap(Obj->hitbox2, obs->hitbox)) {
                    Obj->stopLeft = true;
                    free(Obj->hitbox2); 
                }
            }
            
        }
        
    }
}
void Boom_draw(Elements *self)
{
    Boom *Obj = ((Boom *)(self->pDerivedObj));
    ALLEGRO_BITMAP *frame = algif_get_bitmap(Obj->img, al_get_time());
    if (frame)
    {
        al_draw_bitmap(frame, Obj->x, Obj->y,0);
    }
    //int newX = Obj->x + 67.1 * Obj->nextRange;
    //al_draw_rectangle(newX+4,Obj->y + 14,newX + 62.1,Obj->y + 64, al_map_rgb(255, 0, 0), 2);
    
}
void Boom_destory(Elements *self)
{
    Boom *Obj = ((Boom *)(self->pDerivedObj));
    //al_destroy_sample_instance(Obj->atk_Sound);
    algif_destroy_animation(Obj->img);
    al_destroy_timer(Obj->timer);
    free(Obj->hitbox);
    free(Obj->hitbox2);
    free(Obj);
    free(self);
}


