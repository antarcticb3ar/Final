#include "global.h"
#include "shapes/Shape.h"
#include <stdbool.h>
// variables for global usage
const double FPS = 80.0;
const int WIDTH = 900;

const int HEIGHT = 640;
int window = 0;
int remain = 1;
int remain2 = 3;
int quality = 2;
int quality2 = 2;
double speed1 = 1;
double speed2 = 1;
int power1 = 1;
int power2 = 1;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_EVENT event;
ALLEGRO_TIMER *fps = NULL;
bool key_state[ALLEGRO_KEY_MAX] = {false};
bool mouse_state[ALLEGRO_MOUSE_MAX_EXTRA_AXES] = {false};
Point mouse;
bool debug_mode = true;
