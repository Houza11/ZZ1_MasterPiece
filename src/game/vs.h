#ifndef VERSUS_EGG
#define VERSUS_EGG
#include "base.h"

#if 0
typedef int vs_output;
#define VS_OUTPUT_DO_NOTHINGS 0
#define VS_OUTPUT_MOVE_UP     1
#define VS_OUTPUT_MOVE_DOWN   2
#define VS_OUTPUT_MOVE_RANGE  3

typedef int vs_input;

#define VS_INPUT_OSEF          0
#define VS_INPUT_SOL           1
#define VS_INPUT_MUR           2
#define VS_INPUT_DAMAGE        3
#define VS_INPUT_FUTUR_DAMAGE  4

#define VS_INPUT_ENEMY_RIGHT 5
#define VS_INPUT_ENEMY_LEFT  6
#define VS_INPUT_ENEMY_UP    7
#define VS_INPUT_ENEMY_DOWN  8

#define VS_INPUT_MAX_RANGE   9

#define vs_nb_colonne_x 7
#define vs_nb_ligne_y   7

typedef struct
{
    int grid_wall[vs_nb_colonne_x][vs_nb_ligne_y];
} vs_immutable_state;

#define vs_grid (istate->grid)

typedef int vs_entity_state;
#define vs_entity_state_dead         0
#define vs_entity_state_normal       1
#define vs_entity_state_load_bow     0
#define vs_entity_state_attack_sword 0

typedef int vs_entity_dir;
#define vs_entity_dir_right 0
#define vs_entity_dir_left  1
#define vs_entity_dir_up    2
#define vs_entity_dir_down  3

typedef struct
{
    int x;
    int y;
    vs_entity_state state;
    vs_entity_dir direction;
}vs_entity;

#define VS_DAMAGE VS_INPUT_DAMAGE
#define VS_FUTUR_DAMAGE VS_INPUT_FUTUR_DAMAGE

typedef struct
{
    int grid_input[vs_nb_colonne_x][vs_nb_ligne_y];
}vs_vision;

typedef struct
{
    vs_vision vision;
    vs_output output;
}vs_situation;

#define vs_max_player 4
#define vs_nb_player 2

typedef struct
{
    vs_entity entities[vs_max_player];
    int grid_damage[vs_nb_colonne_x][vs_nb_ligne_y];
} vs_mutable_state;

typedef struct
{
    texture* grass;
    texture* archere;
    texture* damage;
} vs_draw_state;

void vs_load(game_arg arg);
void vs_unload(game_arg arg);

void  vs_unload_mutable(game_arg arg);
void* vs_clone_mutable(game_arg arg);

void vs_update(game_arg arg);
void vs_draw(game_arg arg);
void vs_draw_rule(game_arg arg, entity* e, rule* r, int idx);

void vs_player_input(game_arg arg, entity* e);
bool vs_rule_match(game_arg arg, entity* e, rule* r);


void grid_set(game_arg arg, int ligne, int colonne, obstacle val);
obstacle grid_get(game_arg arg, int ligne, int colonne);
void grid_push_colonne(game_arg arg, vec* v);

char egg_rule_output_to_char(int output);
char egg_rule_input_to_char(int input);
void egg_printf(game_arg arg);
#endif
#endif