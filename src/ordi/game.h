#ifndef GAME_H
#define GAME_H
#include "base.h"

#define game_name_string_size 32

struct game_arg
{
    context* c;
    game* g;
};


// bool is over
typedef void* (*game_clone_fn)  (game_arg arg);
typedef void  (*game_fn)        (game_arg arg);
typedef void  (*game_draw_rule_fn)(game_arg arg, entity* e, rule* r, int idx);

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

    // player or ordi
    entity* current_entity;

    entity* best_ordi;
    // of ordi*
    vec* generation;
    int nb_generation;

    int generation_idx_training;
    int generation_current_idx_nb_update;
    int generation_update_per_entity;

    // currrent player or cpu input
    tab*    input;
    int     _nb_update;
    float   draw_coef;

    float gen_delta_score;

    float best_score_player;
    float best_score_ordi;
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

    things_to_char_fn       input_to_char;
    things_to_char_fn       output_to_char;
    game_fn                 printf;
    // rule_input

    int condition_input_size;
    int condition_input_max_range;

    int condition_output_size;
    int condition_output_max_range;

    int total_entities_generated;
    // >= 1
    int nb_behavior;

    // of entity
    //vec*  generation;

    // false: minimize, true: maximize
    bool maximize_score;
    bool is_loaded;

    char name[game_name_string_size];
};

#define game_create(name)\
    game_create_arg(\
        c,\
        #name,\
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
        name ## _rule_input_to_char,\
        name ## _rule_output_to_char,\
        name ## _printf\
    )

game* game_create_arg(
    context* c,
    char name[game_name_string_size],
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
    things_to_char_fn input_to_char,
    things_to_char_fn output_to_char,
    game_fn printf
    );

game_arg game_arg_create(context* c, game* g);

void  game_update(context* c, game* g, int ups);
void  game_update_fixed(context* c, game* g);
void  game_load(context* c, game* g);
void  game_reset(context* c, game* g);
void  game_unload(context* c, game* g);
void  game_draw(context* c, game* g);
void  game_printf(context* c, game* g);
game* game_clone(context* c, game* g);

void game_get_input(context* c, game* g, entity* e);
void game_get_player_input(context* c, game* g, entity* e);
bool game_rule_match(context* c, game* g, entity* e, rule* r);

void game_set_entity_type(game* g, entity_type type);

void game_ordi_configure(game* g,
    int condition_input_size,
    int condition_input_max_range,
    int condition_output_size,
    int condition_output_max_range,
    int nb_behavior);

void game_internal_mutable_free(game_mutable* mut);
#endif