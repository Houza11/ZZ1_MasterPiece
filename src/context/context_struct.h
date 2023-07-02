#ifndef THE_CONTEXT_H
#define THE_CONTEXT_H
#include "base.h"

#define FONT_PATH "asset/Milky Mania.ttf"

// Utiliser de préférence les fonction associé au contexte pour y acceder
typedef struct
{
    // windows and screen related
    SDL_Renderer* renderer;
    int screen_width;
    int screen_height;

    float window_ratio_width_div_height;
    float window_ratio_height_div_width;

    SDL_Window* window;
    int window_width;
    int window_height;

    int window_x;
    int window_y;

    // input related
    int mouse_x;
    int mouse_y;
    int32 mouse_flag;

    int mouse_old_x;
    int mouse_old_y;

    int mouse_delta_x;
    int mouse_delta_y;

    bool action_right;
    bool action_old_right;
    bool action_left;
    bool action_old_left;
    bool action_up;
    bool action_old_up;
    bool action_down;
    bool action_old_down;

    bool mouse_left_button_down;

    int32 mouse_old_flag;
    const Uint8* kb_state;

    time timer; // since the beginning of the program
    int  nb_update;

    vec* /* of scene */ scenes;
    void* scene;

    float  camera_x;
    float  camera_y;
    float  camera_scale_x;
    float  camera_scale_y;
    bool   camera_can_zoom;
    bool   camera_can_scroll;

    uint32 pen_mode;
    int    pen_nb_rectangle;

    bool should_exit;

    texture* _pen_font;

    the_global_state* _global_state;
} context;
#endif