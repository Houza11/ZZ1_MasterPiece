#ifndef GAME_EGG
#define GAME_EGG
#include "base.h"

typedef int egg_output;
#define EGG_OUTPUT_DO_NOTHINGS 0
#define EGG_OUTPUT_MOVE_UP     1
#define EGG_OUTPUT_MOVE_DOWN   2
#define EGG_OUTPUT_MOVE_RANGE  3

typedef int egg_input;
// 0 : Don't Care
// 1-3 : Range
// 
#define EGG_INPUT_OSEF      0

#define EGG_RULE_BASED_ON_RANGE

#ifdef EGG_RULE_BASED_ON_RANGE
#define EGG_INPUT_MAX_RANGE 6
#define EGG_RULE_USE_DENSITY
#else
#define EGG_INPUT_MAX_RANGE 4
#endif

typedef struct
{
    int nb_colonne;
    vec* /* of vec* of EGG_obstacle */ grid;
} egg_immutable_state;

#define EGG_NB_COLONNE (istate->nb_colonne)
#define EGG_NB_LIGNE 5
#define egg_nb_colonne (istate->nb_colonne)
#define egg_nb_ligne 5

#define egg_grid (istate->grid)

typedef int8 obstacle;
#define EGG_OBSTACLE_NONE  0
#define EGG_OBSTACLE_ARROW 1

#define EGG_OBSTACLE_ENTRY -1
#define EGG_OBSTACLE_EXIT  -2

typedef struct
{
    // is_wall[nb_colonne][nb_ligne] aka [x][y]
    //bool** is_walls;
    int nb_tour;
    int player_y;
    int player_x;
} egg_mutable_state;

typedef struct
{
    texture* fond;
    sprite_sheet* sprite_archere_walk;
    sprite_sheet* sprite_archere_idle;
    sprite_sheet* sprite_archere_mort;
    sprite_sheet* sprite_fleche;
    sprite_sheet* sprite_portail_haut;
    animation* personnage_walk;
    animation* personnage_idle;
    animation* personnage_mort;
    sprite_sheet* sprite_robot_walk;
    sprite_sheet* sprite_robot_mort;
    animation* robot_walk;
    animation* robot_mort;
    animation* fleche;
    animation* portail_haut;
    texture* arbalete;
    float player_y;
    float* arbalete_size;
} egg_draw_state;

void egg_load(game_arg arg);
void egg_unload(game_arg arg);

void  egg_unload_mutable(game_arg arg);
void* egg_clone_mutable(game_arg arg);

void egg_update(game_arg arg);
void egg_draw(game_arg arg);
void egg_draw_rule(game_arg arg, entity* e, rule* r, int idx);

void egg_player_input(game_arg arg, entity* e);
bool egg_rule_match(game_arg arg, entity* e, rule* r);


void egg_grid_set(game_arg arg, int ligne, int colonne, obstacle val);
obstacle egg_grid_get(game_arg arg, int ligne, int colonne);
void egg_grid_push_colonne(game_arg arg, vec* v);

char egg_rule_output_to_char(int output);
char egg_rule_input_to_char(int input);
void egg_printf(game_arg arg);

#endif