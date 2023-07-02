#ifndef GAME_H
#define GAME_H
#include "../base.h"

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
typedef bool  (*game_rule_match_fn)(game_state* g, entity* e, rule* r);

#define GAME_STATE_RUNNING             0
#define GAME_STATE_END_OF_GAME         1
#define GAME_STATE_REACH_MAX_RECURSION 2

struct game_mutable
{
    // mutable data
    game_state state;
    rectf draw_dest;

    entity* current_ordi;
    field(tab*, current_ordi_output, current_input);
    int nb_turn;

    vec* /* of behavior */ behaviors;
    behavior best_behavior;
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

    // false: minimize, true: maximize
    bool maximize_score;
};


#define game_create(name, condition_input_size, condition_input_max_range, condition_output_size, condition_output_max_range)\
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
        30, /* nb behavior*/\
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

#endif