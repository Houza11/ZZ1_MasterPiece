#include "base.h"

time timer_since_launch(context* c) { return c->timer; }
time timer_scene(context* c) { return context_get_current_scene(c)->info.time; }