#include "charac2.h"
#include "..\\global.h"
#include "Obstacle.h"
#include "../scene/sceneManager.h"
#include "projectile.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
#include "projectile.h"
#include <stdio.h>
#include <stdbool.h>
/*
   [Character function]
*/
Elements *New_Charac2(int label)
{
    Charac2 *pDerivedObj = (Charac2 *)malloc(sizeof(Charac2));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    // load character images
    char state_string[3][10] = {"stop", "move", "attack"};
    
    for (int i = 0; i < 3; i++)
    {
        char buffer[50];
        sprintf(buffer, "assets/image/chara_%s.gif", state_string[i]);
        pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    }
    // load effective sound
    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/atk_sound.wav");
    pDerivedObj->atk_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->atk_Sound, al_get_default_mixer());

    // initial the geometric information of character
     pDerivedObj->width = pDerivedObj->gif_status[0]->width;
    pDerivedObj->height = pDerivedObj->gif_status[0]->height;
    pDerivedObj->x = 300;
    pDerivedObj->y = HEIGHT - pDerivedObj->height - 60;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + 2 * pDerivedObj->width / 3,
                                        pDerivedObj->y + 2 * pDerivedObj->height / 3);
    pDerivedObj->dir = 1; // 1, 2, 3, 4  [下,左,右,上]
    // initial the animation component
    pDerivedObj->state = STOP;
    pDerivedObj->needstop = false;
    pDerivedObj->new_proj = false;
    pObj->inter_obj[pObj->inter_len++] = Obstacle_L;
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Draw = Charac2_draw;
    pObj->Update = Charac2_update;
    pObj->Interact = Charac2_interact;
    pObj->Destroy = Charac2_destory;
    return pObj;
}
void Charac2_update(Elements *self)
{
    // use the idea of finite state machine to deal with different state
    Charac2 *chara = ((Charac2 *)(self->pDerivedObj));
   
    if (chara->state == STOP || chara->needstop == true)
    {
        if (key_state[ALLEGRO_KEY_SPACE])
        {
            chara->state = ATK;
        }
        
        else if (key_state[ALLEGRO_KEY_K])
        {
            chara->dir = 1;
            chara->state = MOVE; 
            if(chara->needstop == true)
                _Charac2_update_position(self, 0, 0);          
        }
        else if (key_state[ALLEGRO_KEY_I])
        {
            chara->dir = 4;
            chara->state = MOVE;
            if(chara->needstop == true)
                _Charac2_update_position(self, 0, 0);
        }
        else if (key_state[ALLEGRO_KEY_J])
        {
            chara->dir = 2;
            chara->dir1 = false;
            chara->state = MOVE;
            if(chara->needstop == true)
                _Charac2_update_position(self, 0, 0);
        }
        else if (key_state[ALLEGRO_KEY_L])
        {
            chara->dir = 3;
            chara->dir1 = true;
            chara->state = MOVE;
            if(chara->needstop == true)
                _Charac2_update_position(self, 0, 0);
        }
        else
        {
            chara->state = STOP;
        }
    }
    else if (chara->state == MOVE )
    {
            if (key_state[ALLEGRO_KEY_SPACE])
        {
            chara->state = ATK;
        }
        else if (key_state[ALLEGRO_KEY_J])
        {
            chara->dir = 2;
            chara->dir1 = false;
            if (!chara->needstop) { // 只有在不需要停止时才更新位置
                _Charac2_update_position(self, -2, 0);
            }
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_K])
        {
            chara->dir = 1;
            if (!chara->needstop) {
                _Charac2_update_position(self, 0, 2);
            }
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_I])
        {
            chara->dir = 4;
            chara->dir1 = true;
            if (!chara->needstop) {
                _Charac2_update_position(self, 0, -2);
            }     
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_L])
        {
            chara->dir = 3;
            if (!chara->needstop) {
                _Charac2_update_position(self, 2, 0);
            }        
            chara->state = MOVE;
        }
        if (chara->needstop) {
            chara->state = STOP; // 如果需要停止，将状态设置为停止
        }
        if (chara->gif_status[chara->state]->done)
            chara->state = STOP;
    }
    else if (chara->state == ATK)
    {
        if (chara->gif_status[chara->state]->done)
        {
            chara->state = STOP;
            chara->new_proj = false;
        }
        if (chara->gif_status[ATK]->display_index == 2 && chara->new_proj == false)
        {
            Elements *pro;
            if (chara->dir == 1)
            {
                pro = New_Projectile(Projectile_L,
                                    chara->x + chara->width - 100,
                                    chara->y + 10,
                                    5);
            }
            else
            {
                pro = New_Projectile(Projectile_L,
                                    chara->x - 50,
                                    chara->y + 10,
                                    -5);
            }
            _Register_elements(scene, pro);
            chara->new_proj = true;
        }
    }
    
}
void Charac2_draw(Elements *self)
{
    // with the state, draw corresponding image
    Charac2 *chara = ((Charac2 *)(self->pDerivedObj));
    ALLEGRO_BITMAP *frame = algif_get_bitmap(chara->gif_status[chara->state], al_get_time());
    if (frame)
    {
        al_draw_bitmap(frame, chara->x, chara->y, ((chara->dir1) ? ALLEGRO_FLIP_HORIZONTAL : 0));
    }
    if (chara->state == ATK && chara->gif_status[chara->state]->display_index == 2)
    {
        al_play_sample_instance(chara->atk_Sound);
    }
}
void Charac2_destory(Elements *self)
{
    Charac2 *Obj = ((Charac2 *)(self->pDerivedObj));
    al_destroy_sample_instance(Obj->atk_Sound);
    for (int i = 0; i < 3; i++)
        algif_destroy_animation(Obj->gif_status[i]);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

void _Charac2_update_position(Elements *self, int dx, int dy)
{
    Charac2 *chara = ((Charac2 *)(self->pDerivedObj));   
    int new_x = chara->x + dx;
    int new_y = chara->y + dy;
    if (new_x < 0 || new_x + chara->width > WIDTH || new_y < 0 || new_y + chara->height > HEIGHT)
    {
        // If moving out of bounds, don't update the position
        return;
    }
    
    // Check collisions with obstacles
    // If there's a collision, revert the position update
    for(int i = 0;i<3;i++)
    {
        if(chara->needstop)
        {     
            if(chara->dir == 4) 
            {
                chara->y += 2;
                chara->hitbox->update_center_y(chara->hitbox, 2);
                chara->needstop = false; 
                return;
            }
            else if(chara->dir == 3) 
            {
                chara->x -= 2;
                chara->hitbox->update_center_x(chara->hitbox, -2);
                chara->needstop = false;   
                return;
            }
            else if(chara->dir == 2) 
            {
                chara->x += 2;
                chara->hitbox->update_center_x(chara->hitbox, 2);
                chara->needstop = false;   
                return;
            }
            else if(chara->dir == 1) 
            {
                chara->y -= 2;
                chara->hitbox->update_center_y(chara->hitbox, -2);
                chara->needstop = false;   
                return;
            }            
        }
        else break;
    }
    // Temporarily update position to check for collisions
    chara->x += dx;
    chara->y += dy;
    chara->hitbox->update_center_x(chara->hitbox, dx);
    chara->hitbox->update_center_y(chara->hitbox, dy);

    
    
       
}

void Charac2_interact(Elements *self, Elements *tar) {
    Charac2 *obj = ((Charac2 *)(self->pDerivedObj));
    Obstacle *obstacle = ((Obstacle *)(tar->pDerivedObj));     

    if(obstacle->hitbox->overlap(obstacle->hitbox, obj->hitbox)) 
    {
        obj->needstop = true;
    }
     for(int i = 0; i < 3; i++) {
        if(obj->needstop) {
            // Adjust character's position
            _Charac2_update_position(self, 0, 0);
            
            // Check for collision again after adjustment
            if (obstacle->hitbox->overlap(obstacle->hitbox, obj->hitbox)) {
                obj->needstop = true; // If collision still occurs, keep the Charac2 stopped
            } else {
                obj->needstop = false; // If collision resolved, resume Charac2's movement
            }
            
            // Return after adjusting position and resolving collision
            return;
        } else {
            // If no collision, break out of the loop
            break;
        }
    }
}


