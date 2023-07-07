#ifndef VERSUS_EGG
#define VERSUS_EGG
#include "base.h"

typedef int vs_output;

#define VS_OUTPUT_DO_NOTHINGS 0
#define VS_OUTPUT_MOVE_UP     1
#define VS_OUTPUT_MOVE_DOWN   2
#define VS_OUTPUT_MOVE_RIGHT  3
#define VS_OUTPUT_MOVE_LEFT   4
#define VS_OUTPUT_MOVE_BOW    5
#define VS_OUTPUT_MOVE_SWORD  6

#define VS_OUTPUT_MOVE_RANGE  7

typedef int vs_input;

#define VS_INPUT_OSEF          0
#define VS_INPUT_SOL           (VS_INPUT_OSEF+1)
#define VS_INPUT_OUT_OF_ARENA  (VS_INPUT_OSEF+2)
#define VS_INPUT_FUTUR_DAMAGE  (VS_INPUT_OSEF+3)
#define VS_INPUT_ENEMY_NORMAL  (VS_INPUT_OSEF+5)

//#define VS_INPUT_DAMAGE        (VS_INPUT_OSEF+99)

//#define VS_INPUT_MUR           6

//#define VS_INPUT_ENEMY_BOW_LOADING 6
/*
#define VS_INPUT_ENEMY_RIGHT 5
#define VS_INPUT_ENEMY_LEFT  6
#define VS_INPUT_ENEMY_UP    7
#define VS_INPUT_ENEMY_DOWN  8
*/
#define VS_INPUT_MAX_RANGE   (VS_INPUT_ENEMY_NORMAL+1)
#define VS_INPUT_SIZE (vision_size*vision_size)

#define vs_nb_colonne_x 9
#define vs_nb_ligne_y   9

typedef struct
{
    int grid_wall[vs_nb_colonne_x][vs_nb_ligne_y];
} vs_immutable_state;

#define vs_grid_wall (istate->grid_wall)

typedef int vs_entity_state;
#define vs_entity_state_dead         0
#define vs_entity_state_normal       1
#define vs_entity_state_load_bow     VS_OUTPUT_MOVE_BOW
#define vs_entity_state_attack_sword VS_OUTPUT_MOVE_SWORD
#define vs_entity_state_win          9


typedef int vs_entity_dir;
#define vs_entity_dir_up    VS_OUTPUT_MOVE_UP
#define vs_entity_dir_down  VS_OUTPUT_MOVE_DOWN
#define vs_entity_dir_right VS_OUTPUT_MOVE_RIGHT
#define vs_entity_dir_left  VS_OUTPUT_MOVE_LEFT
/*
#define vs_entity_dir_right_down  5
#define vs_entity_dir_right_up    6
#define vs_entity_dir_left_down   7
#define vs_entity_dir_left_up     8
*/

#define vs_bow_loading_time 2
typedef struct
{
    int x;
    int y;
    vs_entity_state state;
    vs_entity_dir direction;
    int var_0;
}vs_entity;

typedef struct
{
    float x;
    float y;
}vs_entity_draw;

#define VS_DAMAGE VS_INPUT_DAMAGE
#define VS_FUTUR_DAMAGE VS_INPUT_FUTUR_DAMAGE

// impair
#define vision_size 7
#define half_vision_size 3

typedef struct
{
    int grid_input[VS_INPUT_SIZE];
}vs_vision;


typedef struct
{
    vs_vision vision;
    vs_output output;
}vs_situation;

#define vs_max_player 4
#define vs_nb_player 4

typedef struct
{
    vs_entity players[vs_max_player];
    // crazy bool stuff. d u l r
    int16 grid_damage[vs_nb_colonne_x][vs_nb_ligne_y];
    vs_vision ordi_vision;
} vs_mutable_state;

//#define vs_entities (mstate->entities)
#define vs_players (mstate->players)

#define vs_grid_damage (mstate->grid_damage)
#define vs_damage_none 0
#define vs_wall_sol    VS_INPUT_SOL
#define vs_wall_wall   VS_INPUT_WALL

typedef struct
{
    texture* grass;
    texture* dance;
    texture* archere;
    texture* damage;
    vs_entity_draw players_graphic[vs_max_player];

    // of vs_situation. For p2
    vec* situations;
} vs_draw_state;

void vs_load(game_arg arg);
void vs_unload(game_arg arg);

void  vs_unload_mutable(game_arg arg);
void* vs_clone_mutable(game_arg arg);

void vs_update(game_arg arg);
void vs_draw(game_arg arg);
void vs_draw_rule(game_arg arg, entity* e, rule* r, int idx);

void vs_player_input(game_arg arg, entity* e);
void vs_ordi_input_init(game_arg arg);
bool vs_rule_match(game_arg arg, entity* e, rule* r);

char vs_rule_output_to_char(int output);
char vs_rule_input_to_char(int input);
void vs_printf(game_arg arg);
#endif