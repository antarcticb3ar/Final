#ifndef SCENEMANAGER_H_INCLUDED
#define SCENEMANAGER_H_INCLUDED
#include "scene.h"
extern Scene *scene;
typedef enum SceneType
{
    Video_L = 0,
    Menu_L,
    GameScene_L,
    End_L
} SceneType;
void create_scene(SceneType);

#endif