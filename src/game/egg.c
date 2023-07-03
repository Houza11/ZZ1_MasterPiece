#include "base.h"


bool inside_grid(game_arg arg, int ligne, int colonne)
{
    get_game_state(egg);
    return ligne >= 0 && ligne < egg_nb_ligne && colonne >= 0 && colonne < egg_grid->length;
}

obstacle grid_get(game_arg arg, int ligne, int colonne)
{
    get_game_state(egg);
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
    get_game_state(egg);
    check(inside_grid(arg, ligne, colonne));
    vec_set(vec_get(egg_grid, vec*, colonne), obstacle, ligne, val);
}

void grid_push_colonne(game_arg arg, vec* v)
{
    get_game_state(egg);
    vec_push(egg_grid, vec*, v);
}

void init_grid(game_arg arg)
{
    get_game_state(egg);
    egg_grid = vec_empty(vec*);
    
    while(egg_grid->length < istate->nb_colonne)
    {
        int j = 0;
        while(j < egg_nb_ligne)
        {
            j += pattern_add(arg, -1);
        }
    }
}

void egg_load(game_arg arg)
{
    get_game_state(egg);

    if(need_reset)
    {
        todo;
    }
    //game_type->is_loaded
    istate->nb_colonne = 100;
    init_grid(arg);
    mstate->nb_tour = 0;
    
    dstate->fond = texture_create(c,"asset/fond.png");
    dstate->fleche = texture_create(c,"asset/fleche.png");

    mstate->player_y = 0;
    mstate->player_x = 0;
}

// décharge tout sauf le mutable state
void egg_unload(game_arg arg)
{
    get_game_state(egg);
    texture_free(dstate->fleche);
    texture_free(dstate->fond);

    repeat(i, egg_grid->length)
    {
        vec_free_lazy(vec_get(egg_grid, vec*, i));
    }
    vec_free_lazy(egg_grid);
    egg_grid = null;
}

void egg_unload_mutable(game_arg arg)
{
    get_game_state(egg);
}

void* egg_clone_mutable(game_arg arg)
{
    get_game_state(egg);

    egg_mutable_state* copy = create(egg_mutable_state);
    /*
    //copy->grid = create_array(vec*, copy->grid->nb_colonne);

    repeat(i, state_imut->nb_colonne)
    {
        copy->is_walls[i] = create_array(bool, cstate->nb_ligne);
        memcpy(copy->is_walls[i], mstate->is_walls[i],  state_imut->nb_ligne);
    }*/

    copy->nb_tour = mstate->nb_tour;
    copy->player_y = mstate->player_y;
    copy->player_x = mstate->player_x;

    return (void*)copy;
}

void egg_update(game_arg arg)
{
    get_game_state(egg);

    if(gstate != GAME_STATE_RUNNING) return;
    
    if(grid_get(arg, mstate->player_y, mstate->player_x) == EGG_OBSTACLE_ARROW)
    {
        gstate = GAME_STATE_GAME_OVER;
        // game over
    }

    mstate->nb_tour++;

    // les murs tombent

    mstate->player_x++;

    /*
    vec_free_lazy(vec_get(egg_grid, vec*,  0));
    vec_remove_at(egg_grid, 0);

    if(egg_grid->length < istate->nb_colonne)
    {
        vec* colonne2add = vec_empty(obstacle);
        repeat(i, egg_nb_ligne)
        {
            vec_push(colonne2add, obstacle, rand()%2);
        }
        vec_push(egg_grid, vec*, colonne2add);
        // generer la grille
        //todo;
    }*/

    game_get_input(c,the_game, current_entity);

    egg_output player_input = tab_first_value(entity_input);
    
    switch (player_input)
    {
        case EGG_OUTPUT_MOVE_DOWN: mstate->player_y++; break;
        case EGG_OUTPUT_MOVE_UP : mstate->player_y--; break;
        default: break;
    }
    mstate->player_y = (mstate->player_y+egg_nb_ligne)%egg_nb_ligne;
    //printf("%i\n", (, 0));
    //mstate->player_posX

    //todo;
}

void egg_draw(game_arg arg)
{
    get_game_state(egg);

    float coef = draw_coef;

    int nb_ligne = egg_nb_ligne;
    int nb_colonne = 3*egg_nb_ligne;

    rectf area = rectanglef(0,0, nb_colonne, nb_ligne);
    camera_push_focus_fullscreen(c, area);

    repeat(x, nb_colonne)
    {
        repeat(y, nb_ligne)
        {
            rect fond_rect = texture_rect(dstate->fond);
            fond_rect.w /= 2;
            //if()
            pen_texture(c,dstate->fond,fond_rect,rectanglef(x-coef,y,1,1));
        }
    }

    repeat(x, nb_colonne)
    {
        repeat(y, nb_ligne)
        {
            //pen_color(c, grid_get(arg, y, x) ? color_red : color_white);
            //pen_rect(c, rectanglef(64*x, -64*(y-coef), 48, 48));
            //pen_rect(c, rectanglef(x+0.05, -y+0.05, 0.9, 0.9));
            
            if(grid_get(arg, y,x+mstate->player_x) == EGG_OBSTACLE_ARROW)
            {
                pen_texture(c,dstate->fleche,texture_rect(dstate->fleche), rectanglef(x-coef, y, 0.9, 0.9));
            }
        }
    }
    pen_color(c, color_green);
    pen_rect(c, rectanglef(0, mstate->player_y, 1, 1));

    camera_pop(c);

    
}

void egg_draw_rule(game_arg arg, rule* r)
{
    rule_printf(r);
    get_game_state(egg);
    unused(r);
}

void egg_player_input(game_arg arg, entity* e)
{
    get_game_state(egg);
    unused(e);

    output_single_value(EGG_OUTPUT_DO_NOTHINGS);

    if(input_up(c))
    {
        output_single_value(EGG_OUTPUT_MOVE_UP);
        return;
    }
    if(input_down(c))
    {
        output_single_value(EGG_OUTPUT_MOVE_DOWN);
        return;
    }
}

void egg_set_default_input(game_arg arg)
{
    get_game_state(egg);
    output_single_value(EGG_OUTPUT_DO_NOTHINGS);
}

bool egg_rule_match(game_arg arg, entity* e, rule* r)
{
    get_game_state(egg);
    egg_set_default_input(arg);

    unused(e);
    unused(r);
    return false;
}