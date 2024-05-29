#include "video.h"
#include <stdbool.h>

/*
   [Video Scene function]
*/
Scene *New_Video(int label)
{
    VideoScene *pDerivedObj = (VideoScene *)malloc(sizeof(VideoScene));
    Scene *pObj = New_Scene(label);

    // Load video file
    pDerivedObj->video = al_open_video("assets/video/intro.mp4");
    if (!pDerivedObj->video) {
        fprintf(stderr, "Failed to open video file.\n");
        free(pDerivedObj);
        free(pObj);
        return NULL;
    }

    // Start video playback
    al_start_video(pDerivedObj->video, al_get_default_mixer());

    pDerivedObj->video_end = false;
    pObj->pDerivedObj = pDerivedObj;

    // Setting derived object functions
    pObj->Update = video_update;
    pObj->Draw = video_draw;
    pObj->Destroy = video_destroy;

    return pObj;
}

void video_update(Scene *self)
{
    VideoScene *Obj = (VideoScene *)(self->pDerivedObj);

    // Check if video has ended
    if (!Obj->video_end && !al_is_video_playing(Obj->video)) {
        Obj->video_end = true;
        // Handle end of video, e.g., transition to the next scene
    }
}

void video_draw(Scene *self)
{
    VideoScene *Obj = (VideoScene *)(self->pDerivedObj);

    // Draw video frame
    if (al_is_video_playing(Obj->video)) {
        ALLEGRO_BITMAP *frame = al_get_video_frame(Obj->video);
        if (frame) {
            al_draw_bitmap(frame, 0, 0, 0);
        }
    }
}

void video_destroy(Scene *self)
{
    VideoScene *Obj = (VideoScene *)(self->pDerivedObj);
    if (Obj->video) {
        al_close_video(Obj->video);
    }
    free(Obj);
    free(self);
}
