#include "charater.h"
#include "../global.h"
#include "obstacle.h"
#include "obstacle1.h"
#include "boarder.h"
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
    char state_string[5][10] = {"stop", "move", "attack", "died"};
    
    for (int i = 0; i < 4; i++)
    {
        char buffer[50];
        sprintf(buffer, "assets/image/chara_%s.gif", state_string[i]);
        pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    }
    // load effective soundW
    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/1ti1ti.wav");
    pDerivedObj->atk_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->atk_Sound, al_get_default_mixer());

    // initial the geometric information of character
     pDerivedObj->width = pDerivedObj->gif_status[0]->width - 280;
    pDerivedObj->height = pDerivedObj->gif_status[0]->height - 270;
    pDerivedObj->x = 302 + 16;
    pDerivedObj->y = 120 - 45;
    pDerivedObj->currentx = 302;
    pDerivedObj->currenty = 120;
    // pDerivedObj->x = 235; 
    // pDerivedObj->y = 55; 
    // pDerivedObj->width = 67; //range67.1
    // pDerivedObj->height = 65; //range64.5
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + 10,
                                        pDerivedObj->y + 55,
                                        pDerivedObj->x + 43,
                                        pDerivedObj->y + 80);
    pDerivedObj->hitbox2 = New_Rectangle(pDerivedObj->currentx,
                                         pDerivedObj->currenty,
                                         pDerivedObj->currentx + 67.7,
                                         pDerivedObj->currenty + 65.5);

    pDerivedObj->dir = 1; // 1, 2, 3, 4  [下,左,右,上]
    // initial the animation component
    pDerivedObj->state = STOP;
    pDerivedObj->needstop = false;
    pDerivedObj->new_boom = false;
    pDerivedObj->invincible = false;
    pDerivedObj->invincible_start_time = 0.0;
    pDerivedObj->timer = al_create_timer(0.1);
    pDerivedObj->new_boom = false;
    pObj->inter_obj[pObj->inter_len++] = Obstacle_L;
    pObj->inter_obj[pObj->inter_len++] = Obstacle1_L;
    pObj->inter_obj[pObj->inter_len++] = Boarder_L;
    pObj->inter_obj[pObj->inter_len++] = Boom_L;
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
    if (chara->invincible && (al_get_time() - chara->invincible_start_time >= 3.5)) {
        chara->invincible = false;
    }   
    if (chara->new_boom && al_get_timer_count(chara->timer) >= 0.1) {
        chara->new_boom = false;
    }  
    
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
            if(chara->invincible) {
                chara->state = DIED;
            } 
            if(chara->needstop == true)
                _Character_update_position(self, 0, 0);
            if(chara->invincible) {
                chara->state = DIED;
            } else chara->state = MOVE;          
        }
        else if (key_state[ALLEGRO_KEY_W])
        {
            chara->dir = 4;
            if(chara->needstop == true)
                _Character_update_position(self, 0, 0);
            if(chara->invincible) {
                chara->state = DIED;
            } else chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_A])
        {
            chara->dir = 2;
            chara->dir1 = false;
                      
            if(chara->needstop == true)
                _Character_update_position(self, 0, 0);
            if(chara->invincible) {
                chara->state = DIED;
            } else chara->state = MOVE; 
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->dir = 3;
            chara->dir1 = true;
            chara->state = MOVE;
            if(chara->invincible) {
                chara->state = DIED;
            }
            if(chara->needstop == true)
                _Character_update_position(self, 0, 0);
        }
        else
        {
            if(chara->invincible) {
                chara->state = DIED;
            } else
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
                _Character_update_position(self, -speed1, 0);
            }
            if(chara->invincible) {
                chara->state = DIED;
            } else
            chara->state = MOVE;
            
        }
        else if (key_state[ALLEGRO_KEY_S])
        {
            chara->dir = 1;
            if (!chara->needstop) {
                _Character_update_position(self, 0, speed1);
            }
            if(chara->invincible) {
                chara->state = DIED;
            } else
            chara->state = MOVE;
            
        }
        else if (key_state[ALLEGRO_KEY_W])
        {
            chara->dir = 4;
            chara->dir1 = true;
            if (!chara->needstop) {
                _Character_update_position(self, 0, -speed1);
            }   
            if(chara->invincible) {
                chara->state = DIED;
            } else
            chara->state = MOVE;
            
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->dir = 3;
            if (!chara->needstop) {
                _Character_update_position(self, speed1, 0);
            }    
            if(chara->invincible) {
                chara->state = DIED;
            } else   
            chara->state = MOVE;
            
        }
        if (chara->needstop) {
            chara->state = STOP; 
        }
        if (chara->gif_status[chara->state]->done)
            chara->state = STOP;

    }
     else if (chara->state == ATK)
    {
        if (chara->gif_status[chara->state]->done)
        {
            if(chara->invincible) {
                chara->state = DIED;
            }  
            else chara->state = STOP;       
        }
        if (quality >= 0 && !chara->new_boom  && chara->gif_status[ATK]->display_index == 1)
        {
            chara->new_boom = true; 
            al_start_timer(chara->timer); 
            Elements *boom;
            boom = New_Boom(Boom_L,
                                chara->currentx + 3,
                                chara->currenty - 6,
                                3);          
            _Register_elements(scene, boom); 
            quality--;                      
            printf("%d\n", quality);                      
        }
        else if (key_state[ALLEGRO_KEY_SPACE])
        {
            chara->state = ATK;
        }       
        else if (key_state[ALLEGRO_KEY_A])
        {
            chara->dir = 2;
            chara->dir1 = false;
            if (!chara->needstop) { // 只有在不需要停止时才更新位置
                _Character_update_position(self, -speed1, 0);
            }
        }
        else if (key_state[ALLEGRO_KEY_S])
        {
            chara->dir = 1;
            if (!chara->needstop) {
                _Character_update_position(self, 0, speed1);
            }        
        }
        else if (key_state[ALLEGRO_KEY_W])
        {
            chara->dir = 4;
            chara->dir1 = true;
            if (!chara->needstop) {
                _Character_update_position(self, 0, -speed1);
            }               
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->dir = 3;
            if (!chara->needstop) {
                _Character_update_position(self, speed1, 0);
            }        
        }
                 
    }
    else if(chara->state == DIED) {
        if(chara->invincible) {     
            if (key_state[ALLEGRO_KEY_SPACE])
            {
                chara->state = ATK;
            }
            
            else if (key_state[ALLEGRO_KEY_A])
            {
                chara->dir = 2;
                chara->dir1 = false;
                if (!chara->needstop) { // 只有在不需要停止时才更新位置
                    _Character_update_position(self, -speed1, 0);
                }
            }
            else if (key_state[ALLEGRO_KEY_S])
            {
                chara->dir = 1;
                if (!chara->needstop) {
                    _Character_update_position(self, 0, speed1);
                }        
            }
            else if (key_state[ALLEGRO_KEY_W])
            {
                chara->dir = 4;
                chara->dir1 = true;
                if (!chara->needstop) {
                    _Character_update_position(self, 0, -speed1);
                }               
            }
            else if (key_state[ALLEGRO_KEY_D])
            {
                chara->dir = 3;
                if (!chara->needstop) {
                    _Character_update_position(self, speed1, 0);
                }        
            }           
            else  {
                chara->state = DIED;
            }
        }
        else
            chara->state = STOP;
    }
      
}
void Character_draw(Elements *self)
{
    // with the state, draw corresponding image
    Character *chara = ((Character *)(self->pDerivedObj));
    ALLEGRO_BITMAP *frame = algif_get_bitmap(chara->gif_status[chara->state], al_get_time());

    // al_draw_rectangle(chara->x + 6,
    //                     chara->y + 50,
    //                     chara->x + 47,
    //                     chara->y + 85, al_map_rgb(255, 0, 0), 2);
    // al_draw_rectangle(chara->currentx,
    //                     chara->currenty,
    //                     chara->currentx + 67.5,
    //                     chara->currenty + 65.5, al_map_rgb(0, 255, 0), 2);
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
    free(Obj->timer);
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
                chara->y += speed1;
                chara->hitbox->update_center_y(chara->hitbox, speed1);
                chara->needstop = false; 
                return;
            }
            else if(chara->dir == 3) 
            {
                chara->x -= speed1;
                chara->hitbox->update_center_x(chara->hitbox, -speed1);
                chara->needstop = false;   
                return;
            }
            else if(chara->dir == 2) 
            {
                chara->x += speed1;
                chara->hitbox->update_center_x(chara->hitbox, speed1);
                chara->needstop = false;   
                return;
            }
            else if(chara->dir == 1) 
            {
                chara->y -= speed1;
                chara->hitbox->update_center_y(chara->hitbox, -speed1);
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
    // pDerivedObj->x = 235; 
    // pDerivedObj->y = 55; 
    // pDerivedObj->width = 67; //range67.1
    // pDerivedObj->height = 65; //range64.5 from guidemap
    int gamex[9] ={167.9, 235, 302.1, 369.2, 436.3, 503.4, 570.5, 637.6, 704.7};
    int gamey[9] ={55, 119.5, 184, 248.5, 313, 377.5, 442, 506.5, 571};
    int detx[9] ={201.45, 268.55, 335.65, 402.75, 469.85, 536.95, 604.05, 671.15, 738.25};
    int dety[9] ={87.25, 151.75, 216.25, 280.75, 345.25, 409.75, 474.25, 538.75, 603.25};
    int min_dist_x = abs(chara->x + 25 - dety[0]);
    chara->currentx = gamex[0];
    for (int i = 1; i <= 7; i++)
    {
        int dist_x = abs(chara->x + 25 - detx[i]);
        if (dist_x < min_dist_x)
        {
            min_dist_x = dist_x;
            chara->currentx = gamex[i];
        }
    }

    // Find nearest y grid position
    int min_dist_y = abs(chara->y + 67 - dety[0]);
    chara->currenty = gamey[0];
    for (int i = 1; i <= 7; i++)
    {
        int dist_y = abs(chara->y + 67 - dety[i]);
        if (dist_y < min_dist_y)
        {
            min_dist_y = dist_y;
            chara->currenty = gamey[i];
        }
    }

    
    // Update currentx and currenty to the nearest grid positions

}

void Character_interact(Elements *self, Elements *tar) {
    Character *obj = ((Character *)(self->pDerivedObj));       
     if (tar->label == Boom_L) 
    {
        Boom *boom = ((Boom *)(tar->pDerivedObj));
        for(int i = 0; i < 3; i++) {
            if(obj->needstop) {
                // Adjust character's position
                _Character_update_position(self, 0, 0);
                
                // Check for collision again after adjustment
                if (boom->hitbox->overlap(boom->hitbox, obj->hitbox)) {
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
     
    else if (tar->label == Obstacle_L) 
    {
        Obstacle *obstacle = ((Obstacle *)(tar->pDerivedObj));
        if (obstacle->hitbox->overlap(obstacle->hitbox, obj->hitbox))
            //obstacle->hitbox2->overlap(obstacle->hitbox2, obj->hitbox) )
            // obstacle->hitbox3->overlap(obstacle->hitbox3, obj->hitbox) ||
            // obstacle->hitbox4->overlap(obstacle->hitbox4, obj->hitbox)) 
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
    else if (tar->label == Obstacle1_L) 
    {
        Obstacle1 *obstacle = ((Obstacle1 *)(tar->pDerivedObj));
        if (obstacle->hitbox->overlap(obstacle->hitbox, obj->hitbox))
            //obstacle->hitbox2->overlap(obstacle->hitbox2, obj->hitbox) )
            // obstacle->hitbox3->overlap(obstacle->hitbox3, obj->hitbox) ||
            // obstacle->hitbox4->overlap(obstacle->hitbox4, obj->hitbox)) 
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
    else if (tar->label == Boarder_L) 
    {
        Boarder *boarder = ((Boarder *)(tar->pDerivedObj));
        if (boarder->hitbox->overlap(boarder->hitbox, obj->hitbox) ||
            boarder->hitbox2->overlap(boarder->hitbox2, obj->hitbox)) 
            // boarder->hitbox3->overlap(boarder->hitbox3, obj->hitbox) ||
            // boarder->hitbox4->overlap(boarder->hitbox4, obj->hitbox)) 
        {
            obj->needstop = true;
        }
        for(int i = 0; i < 3; i++) {
            if(obj->needstop) {
            // Adjust character's position
            _Character_update_position(self, 0, 0);
            
            // Check for collision again after adjustment
            if(boarder->hitbox->overlap(boarder->hitbox, obj->hitbox)
            ||
            boarder->hitbox2->overlap(boarder->hitbox2, obj->hitbox)) {
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
    
}


