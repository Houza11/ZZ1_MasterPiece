#include "base.h"

typedef struct 
{
   int dummy;
   game* g;
}state;

#define current_game (s->g)

void scene_versus_load(argument arg)
{
    obtenir_scene_state;

    // pour avoir 2 variables arg
    {
        current_game = game_create(vs);

        game_arg arg = game_arg_create(c, current_game);
        get_game_state(vs);
        game_load(c, the_game);
        game_set_entity_type(current_game, ENTITY_TYPE_PLAYER);
        //game_set_entity_type(current_game, ENTITY_TYPE_ORDI);
    }
}

void scene_versus_unload(argument arg) 
{
    obtenir_scene_state;
    game_unload(c, current_game);
}

void scene_versus_update(argument arg) 
{ 
    obtenir_scene_state;
    game_update(c, current_game, 2);
}

void scene_versus_draw(argument arg)
{
    obtenir_scene_state;
    //pen_text_at_center(c, "le jeu", window_width(c)/2, window_height(c)/2, FONT_SIZE_NORMAL, 0.5, 0.5);

    game_draw(c, current_game);
}

bool scene_versus_event (argument arg) 
{ 
    obtenir_scene_state;

    switch (ev->type)
    {
        //mousePress(ev->button.);
        case SDL_KEYDOWN: //case SDL_KEYUP:
        {
            switch (ev->key.keysym.sym)
            {
                case SDLK_a: game_set_entity_type(current_game, ENTITY_TYPE_PLAYER); break;;
                case SDLK_z: game_set_entity_type(current_game, ENTITY_TYPE_ORDI); break;
                case SDLK_r: game_reset(c, current_game); break;
                default: break;
            }
        } break;
        default: break;
    }
    return false;
}

void scene_versus_printf(argument arg)
{
    obtenir_scene_state;
    game_printf(c, current_game);
    printf("Versus \n");
}