#include "charater.h"
#include "..\\global.h"
#include "Obstacle.h"
#include "Boom.h"
#include "guidemap.h"
#include "../scene/sceneManager.h"
#include "projectile.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro_primitives.h>
/*
   [Character function]
*/
Elements *New_Character(int label)
{
    Character *pDerivedObj = (Character *)malloc(sizeof(Character));
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
    // load effective soundW
    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/atk_sound.wav");
    pDerivedObj->atk_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->atk_Sound, al_get_default_mixer());

    // initial the geometric information of character
     pDerivedObj->width = pDerivedObj->gif_status[0]->width - 280;
    pDerivedObj->height = pDerivedObj->gif_status[0]->height - 270;
    pDerivedObj->x = 182 + 16;
    pDerivedObj->y = 233 - 45;
    pDerivedObj->xx = 2;
    pDerivedObj->yy = 2;
    pDerivedObj->currentx = 185;
    pDerivedObj->currenty = 234;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y + 50,
                                        pDerivedObj->x + 53,
                                        pDerivedObj->y + 85);
    pDerivedObj->hitbox2 = New_Rectangle(pDerivedObj->currentx,
                                         pDerivedObj->currenty,
                                         pDerivedObj->currentx + 80,
                                         pDerivedObj->currenty + 52);

    pDerivedObj->dir = 1; // 1, 2, 3, 4  [下,左,右,上]
    // initial the animation component
    pDerivedObj->state = STOP;
    pDerivedObj->needstop = false;
    pDerivedObj->new_boom = false;
    pObj->inter_obj[pObj->inter_len++] = Obstacle_L;
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Draw = Character_draw;
    pObj->Update = Character_update;
    pObj->Interact = Character_interact;
    pObj->Destroy = Character_destory;
    return pObj;
}
void Character_update(Elements *self)
{
    // use the idea of finite state machine to deal with different state
    Character *chara = ((Character *)(self->pDerivedObj));
   
    if (chara->state == STOP || chara->needstop == true)
    {
        if (key_state[ALLEGRO_KEY_SPACE])
        {
            chara->state = ATK;
        }
        
        else if (key_state[ALLEGRO_KEY_S])
        {
            chara->dir = 1;
            chara->state = MOVE; 
            if(chara->needstop == true)
                _Character_update_position(self, 0, 0);          
        }
        else if (key_state[ALLEGRO_KEY_W])
        {
            chara->dir = 4;
            chara->state = MOVE;
            if(chara->needstop == true)
                _Character_update_position(self, 0, 0);
        }
        else if (key_state[ALLEGRO_KEY_A])
        {
            chara->dir = 2;
            chara->dir1 = false;
            chara->state = MOVE;
            if(chara->needstop == true)
                _Character_update_position(self, 0, 0);
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->dir = 3;
            chara->dir1 = true;
            chara->state = MOVE;
            if(chara->needstop == true)
                _Character_update_position(self, 0, 0);
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
        else if (key_state[ALLEGRO_KEY_A])
        {
            chara->dir = 2;
            chara->dir1 = false;
            if (!chara->needstop) { // 只有在不需要停止时才更新位置
                _Character_update_position(self, -2, 0);
            }
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_S])
        {
            chara->dir = 1;
            if (!chara->needstop) {
                _Character_update_position(self, 0, 2);
            }
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_W])
        {
            chara->dir = 4;
            chara->dir1 = true;
            if (!chara->needstop) {
                _Character_update_position(self, 0, -2);
            }     
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->dir = 3;
            if (!chara->needstop) {
                _Character_update_position(self, 2, 0);
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
            chara->new_boom = false;
        }
        if (chara->gif_status[ATK]->display_index == 1 && chara->new_boom == false)
        {
            Elements *boom;
            boom = New_Boom(Boom_L,
                                chara->currentx + 5,
                                chara->currenty - 20,
                                3);
            
            
            _Register_elements(scene, boom);
            chara->new_boom = true;
        }
    }
    
}
void Character_draw(Elements *self)
{
    // with the state, draw corresponding image
    Character *chara = ((Character *)(self->pDerivedObj));
    ALLEGRO_BITMAP *frame = algif_get_bitmap(chara->gif_status[chara->state], al_get_time());
    al_draw_rectangle(chara->x,
                        chara->y + 50,
                        chara->x + 53,
                        chara->y + 85, al_map_rgb(255, 0, 0), 2);
    al_draw_rectangle(chara->currentx,
                        chara->currenty,
                        chara->currentx + 80,
                        chara->currenty + 52, al_map_rgb(0, 255, 0), 2);
    if (frame)
    {
        al_draw_bitmap(frame, chara->x, chara->y,0);
    }
    if (chara->state == ATK && chara->gif_status[chara->state]->display_index == 2)
    {
        al_play_sample_instance(chara->atk_Sound);
    }
}
void Character_destory(Elements *self)
{
    Character *Obj = ((Character *)(self->pDerivedObj));
    al_destroy_sample_instance(Obj->atk_Sound);
    for (int i = 0; i < 3; i++)
        algif_destroy_animation(Obj->gif_status[i]);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

void _Character_update_position(Elements *self, int dx, int dy)
{
    Character *chara = ((Character *)(self->pDerivedObj));   
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
    int gamex[10] ={28, 105, 185, 260, 337, 415, 492, 570, 647, 725};
    int gamey[9] ={182, 234, 285, 337, 388, 440, 491, 543};
    int detactx[12] ={67, 144, 221, 298, 375, 452, 529, 606, 683, 760, 837};
    int detacty[11] ={157, 208, 259, 310, 361, 412, 463, 514, 565, 616, 667};

    int min_dist_x = abs(chara->x + 25 - detactx[0]);
    chara->currentx = detactx[0];
    chara->xx = 0;
    for (int i = 1; i < 11; i++)
    {
        int dist_x = abs(chara->x + 25 - detactx[i]);
        if (dist_x < min_dist_x)
        {
            min_dist_x = dist_x;
            chara->currentx = gamex[i];
        }
    }

    // Find nearest y grid position
    int min_dist_y = abs(chara->y + 67 - detacty[0]);
    chara->currenty = detacty[0];
    chara->yy = 0;
    for (int i = 1; i < 10; i++)
    {
        int dist_y = abs(chara->y + 67 - detacty[i]);
        if (dist_y < min_dist_y)
        {
            min_dist_y = dist_y;
            chara->currenty = gamey[i-1];
        }
    }

    
    // Update currentx and currenty to the nearest grid positions

}

void Character_interact(Elements *self, Elements *tar) {
    Character *obj = ((Character *)(self->pDerivedObj));
    Obstacle *obstacle = ((Obstacle *)(tar->pDerivedObj));     

    if(obstacle->hitbox->overlap(obstacle->hitbox, obj->hitbox)) 
    {
        obj->needstop = true;
    }
     for(int i = 0; i < 3; i++) {
        if(obj->needstop) {
            // Adjust character's position
            _Character_update_position(self, 0, 0);
            
            // Check for collision again after adjustment
            if (obstacle->hitbox->overlap(obstacle->hitbox, obj->hitbox)) {
                obj->needstop = true; // If collision still occurs, keep the character stopped
            } else {
                obj->needstop = false; // If collision resolved, resume character's movement
            }
            
            // Return after adjusting position and resolving collision
            return;
        } else {
            // If no collision, break out of the loop
            break;
        }
    }
}


