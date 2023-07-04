#ifndef GAME_EGGZAGON
#define GAME_EGGZAGON
#include "base.h"

typedef int EGGZAGON_OUTPUT;
#define EGGZAGON_OUTPUT_DO_NOTHINGS 0
#define EGGZAGON_OUTPUT_MOVE_UP  1
#define EGGZAGON_OUTPUT_MOVE_DOWN   2

#define EGGZAGON_OUTPUT_MOVE_RANGE  3

typedef int EGGZAGON_INPUT;
#define EGGZAGON_INPUT_OSEF 0

#define egg_grid (istate->grid)

typedef struct
{
    int nb_ligne;
    int nb_colonne;
    vec* /* of vec* of eggzagon_obstacle */ grid;
} eggzagon_immutable_state;

typedef int8 obstacle;
#define EGG_OBSTACLE_NONE  0
#define EGG_OBSTACLE_ARROW 1

typedef struct
{
    // is_wall[nb_colonne][nb_ligne] aka [x][y]
    //bool** is_walls;
    int nb_tour;
    int player_pos_y;
    int grille_x;
} eggzagon_mutable_state;

typedef struct
{
    int dummy;
    texture* fond;
    texture* fleche;
    sprite_sheet* sprite;
    animation* personnage;

    
} eggzagon_draw_state;

void eggzagon_load(game_arg arg);
void eggzagon_unload(game_arg arg);

void  eggzagon_unload_mutable(game_arg arg);
void* eggzagon_clone_mutable(game_arg arg);

void eggzagon_update(game_arg arg);
void eggzagon_draw(game_arg arg);
void eggzagon_draw_rule(game_arg arg, rule* r);

void eggzagon_player_input(game_arg arg, entity* e);
bool eggzagon_rule_match(game_arg arg, entity* e, rule* r);


void grid_set(game_arg arg, int ligne, int colonne, obstacle val);
obstacle grid_get(game_arg arg, int ligne, int colonne);
void grid_push_colonne(game_arg arg, vec* colonne_will_be_copied);

#endif