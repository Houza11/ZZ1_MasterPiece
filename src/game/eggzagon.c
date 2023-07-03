#include "base.h"


bool inside_grid(game_arg arg, int ligne, int colonne)
{
    get_game_state(eggzagon);
    return ligne >= 0 && ligne < EGG_NB_LIGNE && colonne >= 0 && colonne < egg_grid->length;
}

obstacle grid_get(game_arg arg, int ligne, int colonne)
{
    get_game_state(eggzagon);
    if(inside_grid(arg, ligne, colonne))
    {
        return (obstacle)vec_get(vec_get(egg_grid, vec*, colonne), obstacle, ligne);
    }else
    {
        return 0;
    }
}

void grid_set(game_arg arg, int ligne, int colonne, obstacle val)
{
    get_game_state(eggzagon);
    check(inside_grid(arg, ligne, colonne));
    vec_set(vec_get(egg_grid, vec*, colonne), obstacle, ligne, val);
}

void grid_push_colonne(game_arg arg, vec* colonne_will_be_copied)
{
    get_game_state(eggzagon);
    vec_push(egg_grid, vec*, vec_clone(colonne_will_be_copied));
}

void init_grid(game_arg arg)
{
    get_game_state(eggzagon);
    egg_grid = vec_empty(vec*);
    //repeat(i, state_imut->nb_colonne)
    while(egg_grid->length < 1000)
    {
        int j = 0;
        while(j < EGG_NB_LIGNE)
        {
            j += pattern_add(arg, 0);
        }
    }
}

void eggzagon_load(game_arg arg)
{
    get_game_state(eggzagon);

    if(need_reset)
    {
        todo;
    }
    //game_type->is_loaded

    init_grid(arg);

    mstate->nb_tour = 0;
    mstate->player_pos_y = 0;
    mstate->grille_x = 0;
}

// décharge tout sauf le mutable state
void eggzagon_unload(game_arg arg)
{
    get_game_state(eggzagon);

    repeat(i, egg_grid->length)
    {
        vec_free_lazy(vec_get(egg_grid, vec*, i));
    }
    vec_free_lazy(egg_grid);
    egg_grid = null;
}

void eggzagon_unload_mutable(game_arg arg)
{
    get_game_state(eggzagon);
}

void* eggzagon_clone_mutable(game_arg arg)
{
    get_game_state(eggzagon);

    eggzagon_mutable_state* copy = create(eggzagon_mutable_state);
    /*
    //copy->grid = create_array(vec*, copy->grid->nb_colonne);

    repeat(i, state_imut->nb_colonne)
    {
        copy->is_walls[i] = create_array(bool, cstate->nb_ligne);
        memcpy(copy->is_walls[i], mstate->is_walls[i],  state_imut->nb_ligne);
    }*/

    copy->nb_tour = mstate->nb_tour;
    copy->player_pos_y = mstate->player_pos_y;
    copy->grille_x = mstate->grille_x;

    return (void*)copy;
}

void eggzagon_update(game_arg arg)
{
    get_game_state(eggzagon);

    if(gstate != GAME_STATE_RUNNING) return;
    
    mstate->nb_tour++;

    // les murs tombent

    vec_free_lazy(vec_get(egg_grid, vec*,  0));
    vec_remove_at(egg_grid, 0);

    if(egg_grid->length < istate->nb_colonne)
    {
        vec* colonne2add = vec_empty(obstacle);
        repeat(i, EGG_NB_LIGNE)
        {
            vec_push(colonne2add, obstacle, rand()%2);
        }
        vec_push(egg_grid, vec*, colonne2add);
        // generer la grille
        //todo;
    }

    game_get_input(c,the_game, current_entity);

    EGGZAGON_OUTPUT player_input = tab_first_value(entity_input);
    
    switch (player_input)
    {
        case EGGZAGON_OUTPUT_MOVE_RIGHT: mstate->player_pos_y++; break;
        case EGGZAGON_OUTPUT_MOVE_LEFT : mstate->player_pos_y--; break;
        default: break;
    }
    mstate->player_pos_y = (mstate->player_pos_y+istate->nb_colonne)%istate->nb_colonne;
    //printf("%i\n", (, 0));
    //mstate->player_posX

    //todo;
}

void eggzagon_draw(game_arg arg)
{
    get_game_state(eggzagon);

    //float coef = draw_coef;

    rectf area = rectanglef(0,0, istate->nb_colonne, EGG_NB_LIGNE+1);
    camera_push_focus_fullscreen(c, area);

    repeat(x, istate->nb_colonne)
    {
        repeat(y, EGG_NB_LIGNE)
        {
            pen_color(c, grid_get(arg, y, x) ? color_red : color_white);
            //pen_rect(c, rectanglef(64*x, -64*(y-coef), 48, 48));
            pen_rect(c, rectanglef(x+0.05, y+0.05, 0.9, 0.9));
        }
    }
    pen_color(c, color_green);
    pen_rect(c, rectanglef(mstate->player_pos_y, EGG_NB_LIGNE, 1, 1));

    camera_pop(c);
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

    output_single_value(EGGZAGON_OUTPUT_DO_NOTHINGS);

    if(input_right(c))
    {
        output_single_value(EGGZAGON_OUTPUT_MOVE_RIGHT);
        return;
    }
    if(input_left(c))
    {
        output_single_value(EGGZAGON_OUTPUT_MOVE_LEFT);
        return;
    }
}

void eggzagon_set_default_input(game_arg arg)
{
    get_game_state(eggzagon);
    output_single_value(EGGZAGON_OUTPUT_DO_NOTHINGS);
}

bool eggzagon_rule_match(game_arg arg, entity* e, rule* r)
{
    get_game_state(eggzagon);
    eggzagon_set_default_input(arg);

    unused(e);
    unused(r);
    return false;
}