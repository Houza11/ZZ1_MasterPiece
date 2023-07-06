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

    vec* action_bufferized_p1;

    bool mouse_left_button_down;

    int32 mouse_old_flag;
    const Uint8* kb_state;

    time timer; // since the beginning of the program
    int  nb_update;
    bool paused;

    vec* /* of scene */ scenes;
    void* scene;

    vec* /* of camera state */ cams;

    uint32 pen_mode;
    int    pen_nb_rectangle;

    bool should_exit;

    texture* _pen_font;

    the_global_state* _global_state;

    int fps;
    int fps_counter;
    time last_fps_tick;

    time update_tick_end;
} context;
#endif