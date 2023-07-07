#include "base.h"

/*
no opti, fast compile : -O0
lot of opti, slow compile : -O4

// ajouter -lm pour linux

gcc -O5 -fdiagnostics-color=always -g ./src/*.c ./src/betterC/*.c ./src/context/*.c ./src/util/*.c ./src/collection/*.c ./src/scene/*.c ./src/ordi/*.c ./src/game/*.c -Wall -Wextra -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o ./bin/main.exe

gcc -O0 -fdiagnostics-color=always -g ./src/*.c ./src/betterC/*.c ./src/context/*.c ./src/util/*.c ./src/collection/*.c ./src/scene/*.c ./src/ordi/*.c ./src/game/*.c -Wall -Wextra -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o ./bin/main.exe
./bin/main.exe
gource
*/

#define current_game (((c)->_global_state)->g)

void global_state_load(context* c)
{
    unused(c);
    gs = create(the_global_state);
    current_game = null;
}
void global_state_unload(context* c)
{
    unused(c);
    game_unload(c, current_game);

    free(gs);
    gs = null;
}

void global_state_update(context* c)
{
    unused(c);
}


void global_state_draw(context* c)
{
    pen_color(c, rgb(93,39,137));
    pen_clear(c);
}

void global_state_draw_foreground(context* c)
{
    camera_push_set(c, camera_default());
    pen_formatted_text_at_center(c, 0, window_height(c), FONT_SIZE_SMALL, 0, 1, "%i fps", c->fps);
    pen_formatted_text_at_center(c, window_width(c), window_height(c), FONT_SIZE_SMALL, 1, 1, "%i malloc", memory_get_nb_alloc());
    
    if(c->paused)
    {
        pen_text_at_center(c, "paused (P)", window_width(c), window_height(c)-FONT_SIZE_SMALL, FONT_SIZE_SMALL, 1, 1);
    }
    camera_pop(c);
}

void global_state_printf(context* c)
{
    unused(c);
}

bool global_state_event(context* c, event* ev)
{
    unused(c);
    unused(ev);
    
    switch (ev->type)
    {
        //mousePress(ev->button.);
        case SDL_KEYDOWN: //case SDL_KEYUP:
        {
            switch (ev->key.keysym.sym)
            {
                case SDLK_ESCAPE: c->should_exit = true; break;
                case SDLK_j: scene_set(c, jeu); return true;
                case SDLK_d: scene_printf(c, (scene*)(c->scene)); return true;
                default: break;
            }
        } break;
        default: break;
    }

    return false;
}