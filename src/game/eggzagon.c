#include "base.h"

void eggzagon_load(game_arg arg)
{
    get_game_state(eggzagon);

    mstate->is_walls = create_array(bool*, istate->nb_colonne);
    repeat(i, state_imut->nb_colonne)
    {
        mstate->is_walls[i] = create_array(bool, cstate->nb_ligne);
    }
    mstate->nb_tour = 0;
    mstate->player_posX = 0;
}

// décharge tout sauf le mutable state
void eggzagon_unload(game_arg arg)
{
    get_game_state(eggzagon);
}

void eggzagon_unload_mutable(game_arg arg)
{
    get_game_state(eggzagon);

    repeat(i, state_imut->nb_colonne)
    {
        free(mstate->is_walls[i]);
    }
    free(mstate->is_walls);
}

void* eggzagon_clone_mutable(game_arg arg)
{
    get_game_state(eggzagon);

    eggzagon_mutable_state* copy = create(eggzagon_mutable_state);
    copy->is_walls = create_array(bool*, istate->nb_colonne);

    repeat(i, state_imut->nb_colonne)
    {
        copy->is_walls[i] = create_array(bool, cstate->nb_ligne);
        memcpy(copy->is_walls[i], mstate->is_walls[i],  state_imut->nb_ligne);
    }

    copy->nb_tour = mstate->nb_tour;
    copy->player_posX = mstate->player_posX;

    return (void*)copy;
}

void eggzagon_update(game_arg arg)
{
    get_game_state(eggzagon);

    mstate->nb_tour++;

    // les murs tombent

    repeat(x, state_imut->nb_colonne)
    {
        repeat(y, state_imut->nb_ligne-1)
        {
            mstate->is_walls[x][y] = mstate->is_walls[x][y+1];
        }
    }

    int y_max = istate->nb_ligne-1;

    // remplis la dernière ligne de 0
    repeat(x, state_imut->nb_colonne)
    {
        mstate->is_walls[x][y_max] = 0;
    }

    int nb_wall = 1;
    repeat(i, nb_wall)
    {
        mstate->is_walls[mstate->nb_tour%istate->nb_colonne][y_max] = 0;
    }
}

void eggzagon_draw(game_arg arg)
{
    get_game_state(eggzagon);

    repeat(x, istate->nb_colonne)
    {
        repeat(y, istate->nb_ligne)
        {
            pen_color(c, mstate->is_walls[x][y] ? color_red : color_white);
            pen_rect(c, rectanglef(64*x, 64*y, 48, 48));
        }
    }
    pen_color(c, color_green);
    pen_rect(c, rectanglef(64* mstate->player_posX, 64*(-1), 48, 48));
}

void eggzagon_draw_rule(game_arg arg, rule* r)
{
    rule_printf(r);
    get_game_state(eggzagon);
    unused(r);
}

void eggzagon_player_input(game_arg arg, entity* e)
{
    
    get_game_state(eggzagon);
    unused(e);
}

bool eggzagon_rule_match(game_arg arg, entity* e, rule* r)
{
    get_game_state(eggzagon);
    unused(e);
    unused(r);
    return false;
}