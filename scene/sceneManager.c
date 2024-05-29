#include "sceneManager.h"
#include "menu.h"
#include "video.h"
#include "gamescene.h"
Scene *scene = NULL;
void create_scene(SceneType type)
{
    switch (type)
    {
    case Video_L:
        scene = New_Video(Video_L);
        break;
    case Menu_L:
        scene = New_Menu(Menu_L);
        break;   
    case GameScene_L:
        scene = New_GameScene(GameScene_L);
        break;
    // case End_L:
    //     scene = New_End(End_L);
    //     break;
    default:
        break;
    }
}