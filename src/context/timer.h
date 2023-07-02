#ifndef TIMER_H
#define TIMER_H
#include "base.h"

// en ms

#define from_ms(ms) (ms)
#define from_s(s)   (s/1000)

#define frequence_s(fps)   (1000/(fps))

#define second(time) (time/1000.0f)
#define millisecond(time) ((float)time)

#define second_int(time) (time/1000)
#define millisecond_int(time) (time)

time timer_since_launch(context* c);
time timer_scene(context* c);

#endif