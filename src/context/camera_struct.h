#ifndef CONTEXT_CAMERA_STRUCT_H
#define CONTEXT_CAMERA_STRUCT_H
#include "base.h"

struct camera_state
{
    float x;
    float y;
    float scale_x;
    float scale_y;
    bool can_scroll;
    bool can_zoom;
};
#endif