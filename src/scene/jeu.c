#include "base.h"

typedef struct 
{
   int dummy;
   game* g;
}state;

#define current_game (s->g)

void scene_jeu_load(argument arg)
{
    obtenir_scene_state;

    // pour avoir 2 variables arg
    {
        current_game = game_create(egg);

        game_arg arg = game_arg_create(c, current_game);
        get_game_state(egg);
        game_load(c, the_game);
        game_set_entity_type(current_game, ENTITY_TYPE_PLAYER);
        //game_set_entity_type(current_game, ENTITY_TYPE_ORDI);
        #define current_entity current_game->internal_mutable_state->current_entity
        /*
        behavior* b = entity_behavior(current_entity);
        rule* r = behavior_get_rule(b, 0);
        tab_set(r->input, 0, 1);
        //tab_set(r->input, 0, EGG_INPUT_OSEF);
        tab_set(r->input, 1, EGG_INPUT_OSEF);
        tab_set(r->input, 2, EGG_INPUT_OSEF);
        tab_set(r->input, 3, EGG_INPUT_OSEF);
        tab_set(r->input, 4, EGG_INPUT_OSEF);

        tab_set(r->output, 0, EGG_OUTPUT_MOVE_UP);*/
    }
}

void scene_jeu_unload(argument arg) 
{
    obtenir_scene_state;
    game_unload(c, current_game);
}

void scene_jeu_update(argument arg) 
{ 
    obtenir_scene_state;
    game_update(c, current_game, 3.5);
}

void scene_jeu_draw(argument arg)
{
    obtenir_scene_state;
    //pen_text_at_center(c, "le jeu", window_width(c)/2, window_height(c)/2, FONT_SIZE_NORMAL, 0.5, 0.5);

    game_draw(c, current_game);
}

bool scene_jeu_event (argument arg) 
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
                //case SDLK_g: game_train_best_ordi(c, current_game); break;
                default: break;
            }
        } break;
        default: break;
    }
    return false;
}

void scene_jeu_printf(argument arg)
{
    obtenir_scene_state;
    game_printf(c, current_game);
    //printf("J'ai perdu au jeu \n");
}