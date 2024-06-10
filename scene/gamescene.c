#include "gamescene.h"
#include "../global.h"
/*
   [GameScene function]
*/
Scene *New_GameScene(int label)
{
    GameScene *pDerivedObj = (GameScene *)malloc(sizeof(GameScene));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->background = al_load_bitmap("assets/image/newmap.png");
    pObj->pDerivedObj = pDerivedObj;
    // register element
    _Register_elements(pObj, New_Character2(Character2_L));
    _Register_elements(pObj, New_Character(Character_L));
    _Register_elements(pObj, New_Boarder(Boarder_L, 167.9, 55));
    _Register_elements(pObj, New_Boarder(Boarder_L, 167.9, 571));
    _Register_elements(pObj, New_Boarder(Boarder_L, 704.7, 55));
    //_Register_elements(pObj, New_Teleport(Teleport_L));
    //_Register_elements(pObj, New_Tree(Tree_L));
    
    // int gamex[17] ={167.9, 235, 302.1, 369.2, 436.3, 503.4, 570.5, 637.6, 704.7, 771.8, 838.9, 906, 973.1, 1040.2, 1107.3, 1176.4, 1241.5, 1308.6};
    // int gamey[15] ={55, 119.5, 184, 248.5, 313, 377.5, 442, 506.5, 571, 635.5, 700, 764.5, 829, 893.5, 958};
    // for(int i = 0;i<15;i++) {
    //     _Register_elements(pObj, New_Obstacle(Obstacle_L, 235 + i * 67.1, 55));
    //     _Register_elements(pObj, New_Obstacle(Obstacle_L, 235 , 55 + i * 64.7));
    //     _Register_elements(pObj, New_Obstacle(Obstacle_L, 1178.4, 55 + i * 64.7));
    //     _Register_elements(pObj, New_Obstacle(Obstacle_L, 235  + i * 67.1, 958));
    // }
    for(int i = 0;i<5;i += 2) {
        for(int j = 0;j<5;j += 2) {
            _Register_elements(pObj, New_Obstacle(Obstacle_L, 304.2 + i * 67.3, 184 + j * 64.7));
        }
    }
    for(int i = 0;i<7;i++) {
        for(int j = 0;j<4;j += 2) {
        _Register_elements(pObj, New_Obstacle1(Obstacle1_L, 371.5 + j * 67.3, 119.3 + i * 64.6)); 
        if(i<4)
            _Register_elements(pObj, New_Obstacle1(Obstacle1_L, 438.8, 119.3 + i * 2 * 64.6));
        
        }
    }
    for(int i = 0;i<3;i++) {
        _Register_elements(pObj, New_Obstacle1(Obstacle1_L, 236.9, 248.7 + i * 64.6));
        _Register_elements(pObj, New_Obstacle1(Obstacle1_L, 637.6, 248.7 + i * 64.6));
    }
    for(int i = 0;i<3;i += 2) {
        _Register_elements(pObj, New_Obstacle1(Obstacle1_L, 304.2, 248.7 + i * 64.6));
        _Register_elements(pObj, New_Obstacle1(Obstacle1_L, 570.5, 248.7 + i * 64.6));
    }    
    //_Register_elements(pObj, New_Guidemap(Guidemap_L));
    _Register_elements(pObj, New_Heart(Heart_L, 20, 20));
    _Register_elements(pObj, New_Heart2(Heart2_L, 800, 20));
    // setting derived object function
    pObj->Update = game_scene_update;
    pObj->Draw = game_scene_draw;
    pObj->Destroy = game_scene_destroy;
    return pObj;
}
void game_scene_update(Scene *self)
{
    // update every element
    // if (remain == 0) {
    //     self->scene_end = true;
    //     window = 0;
    // }

    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        allEle.arr[i]->Update(allEle.arr[i]);
    }
    
    // run interact for every element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        // run every interact object
        for (int j = 0; j < ele->inter_len; j++)
        {
            int inter_label = ele->inter_obj[j];
            ElementVec labelEle = _Get_label_elements(self, inter_label);
            for (int i = 0; i < labelEle.len; i++)
            {
                ele->Interact(ele, labelEle.arr[i]);
            } 
        }
    }
    // remove element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        if (ele->dele)
            _Remove_elements(self, ele);
    }
    
}    
void game_scene_draw(Scene *self)
{
    void game_scene_draw(Scene *self)
{    
    static bool drawDeath = false;
    static Elements *deadCharacter = NULL;

    GameScene *gs = ((GameScene *)(self->pDerivedObj));
    ElementVec allEle = _Get_all_elements(self);

    // Check if any character is dead
    if (!drawDeath) {
        for (int i = 0; i < allEle.len; i++) {
            Elements *ele = allEle.arr[i];
            if (ele->label == Character_L || ele->label == Character2_L) {
                Character *chara = (Character *)(ele->pDerivedObj);
                if (chara->state == DIED) {
                    drawDeath = true;
                    deadCharacter = ele;
                    break;
                }
            }
        }
    }

    if (drawDeath) {
        // Draw black background
        //al_draw_bitmap(gs->black, 0, 0, 0); 
        
        // Draw only the dead character
        if (deadCharacter) {
            deadCharacter->Draw(deadCharacter);
        }
    } else {
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_bitmap(gs->background, 0, 0, 0);
        for (int i = 0; i < allEle.len; i++)
        {
            Elements *ele = allEle.arr[i];
            ele->Draw(ele);
        }
    }
}
}
void game_scene_destroy(Scene *self)
{
    GameScene *Obj = ((GameScene *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background;
    al_destroy_bitmap(background);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Destroy(ele);
    }
    free(Obj);
    free(self);
}