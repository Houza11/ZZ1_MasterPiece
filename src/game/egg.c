#include "base.h"

bool can_damage(int id)
{
    return id == EGG_OBSTACLE_ARROW;
}

bool inside_grid(game_arg arg, int ligne, int colonne)
{
    get_game_state(egg);
    return ligne >= 0 && ligne < egg_nb_ligne && colonne >= 0 && colonne < egg_grid->length;
}

// regular ge, the the origin of the grid
obstacle grid_get_fixed(game_arg arg, int ligne, int colonne)
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

//relative to the player
obstacle grid_get(game_arg arg, int ligne, int colonne)
{
    get_game_state(egg);
    return grid_get_fixed(arg, ligne, colonne+mstate->player_x);
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

    repeat(i, 10)
    {
        pattern_add_empty_line(arg);
    }
    
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
    }else
    {
        game_ordi_configure(the_game, egg_nb_ligne, EGG_INPUT_MAX_RANGE, 1, EGG_OUTPUT_MOVE_RANGE, 10);
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

void egg_set_default_input(game_arg arg)
{
    get_game_state(egg);
    output_single_value(EGG_OUTPUT_DO_NOTHINGS);
}

bool check_receive_damage(game_arg arg, int offset_y, int offset_x)
{
    get_game_state(egg);
    if(can_damage(grid_get(arg, ((mstate->player_y+offset_y)+egg_nb_ligne)%egg_nb_ligne, offset_x)))
    {
        gstate = GAME_STATE_GAME_OVER;
        // game over
        return true;
    }
    return false;
}


void egg_update(game_arg arg)
{
    get_game_state(egg);

    if(gstate != GAME_STATE_RUNNING) return;
    
    egg_set_default_input(arg);
    game_get_input(c,the_game, current_entity);

    egg_output player_input = tab_first_value(entity_input);
    
    switch (player_input)
    {
        case EGG_OUTPUT_MOVE_DOWN: mstate->player_y++; break;
        case EGG_OUTPUT_MOVE_UP  : mstate->player_y--; break;
        default: break;
    }
    mstate->player_y = (mstate->player_y+egg_nb_ligne)%egg_nb_ligne;
    if(check_receive_damage(arg, 0, 0)) return;

    mstate->player_x++;
    mstate->nb_tour++;

    if(check_receive_damage(arg, 0, 0)) return;

    current_entity->score += 1;
    
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
            int parite = (x+y) % 2;
            fond_rect.x = fond_rect.w *parite;
            pen_texture(c,dstate->fond,fond_rect,rectanglef(x,y,1,1));
        }
    }

    repeat(x, nb_colonne)
    {
        repeat(y, nb_ligne)
        {
            if(grid_get(arg, y,x) == EGG_OBSTACLE_ARROW)
            {
                rect arrow_fond_rect = texture_rect(dstate->fleche);
                arrow_fond_rect.w /= 4;

                pen_texture(c,dstate->fleche, arrow_fond_rect, rectanglef(x-coef, y, 0.9, 0.9));
            }
        }
    }
    pen_color(c, color_green);
    pen_rect(c, rectanglef(0, mstate->player_y, 1, 1));

    pen_formatted_text_at_center(c, 0, 0, FONT_SIZE_NORMAL, 0, 0, "%f", current_entity->score);

    camera_pop(c);
}

char egg_rule_output_to_char(int output)
{
    return ">^v"[output];
}
char egg_rule_input_to_char(int input)
{
    return "X0123456789"[input];
}

void egg_draw_rule(game_arg arg, entity* e, rule* r, int idx)
{
    get_game_state(egg);
    unused(idx);
    unused(e);
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



bool egg_rule_match(game_arg arg, entity* e, rule* r)
{
    get_game_state(egg);

    tab_as_array(r->input, rule_in);
    unused(rule_in_size);

    repeat(y, egg_nb_ligne)
    {
        if(rule_in[y] == EGG_INPUT_OSEF) continue;

        // distance pour le prochain osbtacle
        int dx = EGG_INPUT_MAX_RANGE;
        repeat(x, EGG_INPUT_MAX_RANGE) // -1 because of the Osef symbol
        {
            if(can_damage(grid_get(arg, (y+mstate->player_y) % egg_nb_ligne, x)))
            {
                dx = x;
                break;;
            }
        }
        //dx += 2; //d in [1, EGG_INPUT_MAX_RANGE]

        if(dx >= rule_in[y])
        {
            return false;
        }
    }

    // match
    output_single_value(tab_first_value(r->output));

    unused(e);
    unused(r);
    return true;
}

void egg_printf(game_arg arg)
{
    unused(arg);
    printf("eggzagon game\n");
}