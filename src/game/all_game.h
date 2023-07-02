#include "../base.h"

// constant state, immutable
#define state_imut game_immutable_state
#define cstate  game_immutable_state
#define istate  game_immutable_state

#define state_mut  game_mutable_state
#define mstate  game_mutable_state

#define state_draw game_draw_state
#define dstate game_draw_state

// internal mutable state
#define imstate  game_intern_mutable


#define gstate imstate->state

#define entity_input (game_intern_mutable->input)
#define output_single_value(v) tab_set(entity_input, 0, v)

#define get_game_state(name)\
context* c = (arg.c);\
game* the_game = (arg.g);\
game_mutable* game_intern_mutable = the_game->internal_mutable_state;\
game_type* game_type = the_game->type;\
name ## _immutable_state * game_immutable_state = (name ## _immutable_state *)(the_game->immutable_state);\
name ## _mutable_state * game_mutable_state = (name ## _mutable_state *)(the_game->mutable_state);\
name ## _draw_state * game_draw_state = (name ## _draw_state *)(the_game->draw_state);\
unused(arg);\
unused(the_game);\
unused(game_mutable_state);\
unused(game_draw_state);\
unused(game_immutable_state);\
unused(game_intern_mutable);\
unused(game_type);\
unused(c);\


// recupère : scene* sce, state* s, scene_info* info, event* ev , (+ malloc également automatiquement la structure nommé "state" et l'associe à la scene)
#define obtenir_game_state get_game_state

#include "eggzagon.h"