#include <allegro5/allegro_primitives.h>
#include "menu.h"
#include <stdbool.h>

/*
   [Menu function]
*/

Scene *New_Menu(int label)
{
    Menu *pDerivedObj = (Menu *)malloc(sizeof(Menu));
    Scene *pObj = New_Scene(label);
          
    //pDerivedObj->video = al_open_video("assets/sound/intro.mp4");
    pDerivedObj->background = al_load_bitmap("assets/image/menu.png");
    
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/Pixellettersfull-BnJ5.ttf", 48, 0);
    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/ls5b0-poo7o.mp3");
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2 - 50;
    pDerivedObj->option_x = WIDTH / 2;
    pDerivedObj->option_y_start = HEIGHT / 2;
    pDerivedObj->option_spacing = 30;
    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.1);
    pObj->pDerivedObj = pDerivedObj;
    pDerivedObj->options[0] = "start";
    pDerivedObj->options[1] = "setting";
    pDerivedObj->options[2] = "exit";
    pDerivedObj->option_count = 3;
    pDerivedObj->current_option = 0;
    
    pObj->pDerivedObj = pDerivedObj;
    
    // Setting derived object functions
    pObj->Update = menu_update;
    pObj->Draw = menu_draw;
    pObj->Destroy = menu_destroy;
    
    return pObj;
    // setting derived object function
    pObj->Update = menu_update;
    pObj->Draw = menu_draw;
    pObj->Destroy = menu_destroy;
    return pObj;
}
void menu_update(Scene *self)
{
    Menu *Obj = (Menu *)(self->pDerivedObj);
    
    static bool key_w_down = false; // Track if W key is pressed
    
    if (key_state[ALLEGRO_KEY_W] && !key_w_down)
    {
        Obj->current_option = (Obj->current_option - 1 + Obj->option_count) % Obj->option_count;
        key_w_down = true; // Mark W key as pressed
    }
    else if (!key_state[ALLEGRO_KEY_W])
    {
        key_w_down = false; // Reset the state when W key is released
    }
    
    static bool key_s_down = false; // Track if S key is pressed
    
    if (key_state[ALLEGRO_KEY_S] && !key_s_down)
    {
        Obj->current_option = (Obj->current_option + 1) % Obj->option_count;
        key_s_down = true; // Mark S key as pressed
    }
    else if (!key_state[ALLEGRO_KEY_S])
    {
        key_s_down = false; // Reset the state when S key is released
    }
    
    // Select option
    if (key_state[ALLEGRO_KEY_ENTER])
    {
        if (Obj->current_option == 0) // Start Game
        {
            self->scene_end = true;
            window = 1; // Assuming window 1 is the game scene
        }
        else if (Obj->current_option == 1) // Settings
        {
            // Handle settings
        }
        else if (Obj->current_option == 2) // Exit
        {
            exit(0); // Exit the game
        }
    }
    return;
}
void menu_draw(Scene *self)
{
    Menu *Obj = ((Menu *)(self->pDerivedObj));   
    
    al_draw_bitmap(Obj->background, 0, 0, 0);
    al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->title_x, Obj->title_y, ALLEGRO_ALIGN_CENTRE, "Press 'Enter'");
    for (int i = 0; i < Obj->option_count; i++)
    {
        ALLEGRO_COLOR color = (i == Obj->current_option) ? al_map_rgb(255, 0, 0) : al_map_rgb(0, 0, 0);
        al_draw_text(Obj->font, color, Obj->option_x, Obj->option_y_start + i * Obj->option_spacing, ALLEGRO_ALIGN_CENTRE, Obj->options[i]);
    }
    

    al_play_sample_instance(Obj->sample_instance);
}
void menu_destroy(Scene *self)
{
    Menu *Obj = (Menu *)(self->pDerivedObj);
    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    al_destroy_bitmap(Obj->background);
    free(Obj);
    free(self);
}
