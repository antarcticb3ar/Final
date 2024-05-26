#ifndef VIDEO_SCENE_H_INCLUDED
#define VIDEO_SCENE_H_INCLUDED

#include "scene.h"
#include <allegro5/allegro_video.h>

/*
   [Video Scene object]
*/
typedef struct _VideoScene
{
    ALLEGRO_VIDEO *video;
    bool video_end;
} VideoScene;

Scene *New_Video(int label);
void video_update(Scene *self);
void video_draw(Scene *self);
void video_destroy(Scene *self);

#endif