#include "base.h"

typedef struct 
{
   int dummy;
   game* g;
}state;

void scene_jeu_load(argument arg)
{
    obtenir_scene_state;

    int nb_colonne = 4;
    int nb_ligne   = 3;
    int nb_entity = 10;

    // pour avoir 2 variables arg
    {
        s->g = game_create(eggzagon, nb_colonne, nb_ligne, 1, nb_ligne, nb_entity);
        game_arg arg = game_arg_create(c, s->g);
        get_game_state(eggzagon);

        game_immutable_state->nb_ligne = nb_ligne;
        game_immutable_state->nb_colonne = nb_colonne;
        game_load(c, the_game);
    }
}

void scene_jeu_unload(argument arg) 
{
    obtenir_scene_state;
    game_unload(c, s->g);
}

void scene_jeu_update(argument arg) 
{ 
    obtenir_scene_state;
}

void scene_jeu_draw(argument arg)
{
    obtenir_scene_state;
    pen_text_at_center(c, "le jeu", window_width(c)/2, window_height(c)/2, FONT_SIZE_NORMAL, 0.5, 0.5);
}

bool scene_jeu_event (argument arg) 
{ 
    obtenir_scene_state;
    return false;
}

void scene_jeu_printf(argument arg)
{
    obtenir_scene_state;
    printf("J'ai perdu au jeu \n");
}