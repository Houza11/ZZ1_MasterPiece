#ifndef GAME_H
#define GAME_H
#include "base.h"

struct game_arg
{
    context* c;
    game* g;
};


// bool is over
typedef void* (*game_clone_fn)  (game_arg arg);
typedef void  (*game_fn)        (game_arg arg);
typedef void  (*game_draw_rule_fn)(game_arg arg, rule* r);

typedef void  (*game_get_input_fn)(game_arg arg, entity* e);

// write the output in the g->mutable_state
typedef bool  (*game_rule_match_fn)(game_arg arg, entity* e, rule* r);

#define GAME_STATE_RUNNING             0
#define GAME_STATE_GAME_OVER           1
#define GAME_STATE_REACH_MAX_RECURSION 2

// internal mutable state
struct game_mutable
{
    // mutable data
    game_state state;
    rectf draw_dest;

    entity* current_entity;

    // currrent player or cpu input
    tab*    input;
    int     _nb_update;
    float   draw_coef;
};

struct game
{
    // immutable data
    game_type*    type;
    game_mutable* internal_mutable_state;

    void* immutable_state;
    void* mutable_state;
    void* draw_state;
};

// immutable data about the game
struct game_type
{
//  int32 name;

    game_fn                 update;
    game_fn                 draw;
    game_draw_rule_fn       draw_rule;

    game_clone_fn           clone_mutable;
    game_fn                 unload_mutable;

    // immutable_state + mutable_state + draw_state
    game_fn                 load;
    game_fn                 unload;

    game_get_input_fn       player_input;
    game_rule_match_fn      rule_match;
    // rule_input

    int condition_input_size;
    int condition_input_max_range;

    int condition_output_size;
    int condition_output_max_range;

    // >= 1
    int nb_behavior;
    entity* best_entity;

    // of entity
    //vec*  generation;

    // false: minimize, true: maximize
    bool maximize_score;
    bool is_loaded;
};


#define game_create(name, condition_input_size, condition_input_max_range, condition_output_size, condition_output_max_range, nb_behavior)\
    game_create_arg(\
        c,\
        sizeof( name ## _immutable_state),\
        sizeof( name ## _mutable_state),\
        sizeof( name ## _draw_state),\
        name ## _update,\
        name ## _draw,\
        name ## _draw_rule,\
        name ## _clone_mutable,\
        name ## _unload_mutable,\
        name ## _load,\
        name ## _unload,\
        name ## _player_input,\
        name ## _rule_match,\
        condition_input_size,\
        condition_input_max_range,\
        condition_output_size,\
        condition_output_max_range,\
        nb_behavior /* nb behavior*/\
    )

game* game_create_arg(
    context* c,
    size_t sizeof_immutable_state,
    size_t sizeof_mutable_state,
    size_t sizeof_draw_state,
    game_fn update,
    game_fn draw,
    game_draw_rule_fn draw_rule,
    game_clone_fn clone_mutable,
    game_fn unload_mutable,
    game_fn load,
    game_fn unload,
    game_get_input_fn player_input,
    game_rule_match_fn rule_match,
    int condition_input_size,
    int condition_input_max_range,
    int condition_output_size,
    int condition_output_max_range,
    int nb_behavior);

game_arg game_arg_create(context* c, game* g);

void  game_update(context* c, game* g, int ups);
void  game_update_fixed(context* c, game* g);
void  game_load(context* c, game* g);
void  game_reset(context* c, game* g);
void  game_unload(context* c, game* g);
void  game_draw(context* c, game* g);
void  game_draw_rule(context* c, game* g, rule* r);
game* game_clone(context* c, game* g);

void game_get_input(context* c, game* g, entity* e);
void game_get_player_input(context* c, game* g, entity* e);
bool game_rule_match(context* c, game* g, entity* e, rule* r);

entity* game_optimize(context* c, game* g);
void    game_set_entity_type(game* g, entity_type type);
#endif