#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED
#include "scene.h"
#include "../element/element.h"
#include "../element/charater.h"
#include "../element/charac2.h"
#include "../element/floor.h"
#include "../element/teleport.h"
#include "../element/tree.h"
#include "../element/projectile.h"
#include "../element/obstacle.h"
#include "../element/obstacle1.h"
#include "../element/boom.h"
#include "../element/boom2.h"
#include "../element/boomrange.h"
#include "../element/guidemap.h"
#include "../element/heart.h"
#include "../element/heart2.h"
#include "../element/boarder.h"
#include "../element/qualityitem.h"
#include "../element/speeditem.h"
#include "../element/poweritem.h"
#include "../element/egg.h"
/*
   [game scene object]
*/
typedef enum EleType
{
    Floor_L,
    Teleport_L,
    Tree_L,   
    Projectile_L,
    Boomrange_L,   
    Obstacle_L,
    Obstacle1_L,
    Boarder_L,
    Qualityitem_L,
    Poweritem_L,
    Speeditem_L,    
    Character_L,
    Character2_L,
    Boom_L,
    Boom2_L,
    Egg_L, 
    Guidemap_L,
    Heart_L,
    Heart2_L
    
} EleType;
typedef struct _GameScene
{
    ALLEGRO_BITMAP *background;

} GameScene;
Scene *New_GameScene(int label);
void game_scene_update(Scene *self);
void game_scene_draw(Scene *self);
void game_scene_destroy(Scene *self);

#endif
