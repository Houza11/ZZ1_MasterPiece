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

    int j = 0;
    while(j < egg_nb_colonne)
    {
        j += pattern_add(arg, -1);
    }
}

void egg_load(game_arg arg)
{
    get_game_state(egg);

    mstate->nb_tour = 0;
    mstate->player_y = egg_nb_ligne/2;
    if(need_reset)
    {
      
        mstate->player_x = 0;
        dstate->player_y = mstate->player_y;
    }else
    {
        game_ordi_configure(the_game, egg_nb_ligne, EGG_INPUT_MAX_RANGE, 1, EGG_OUTPUT_MOVE_RANGE, 10);
        dstate->fond = texture_create(c,"asset/fond.png");
        dstate->arbalete = texture_create(c,"asset/arbalete.png");
        dstate->sprite_archere_walk=sprite_sheet_create(c,"asset/archere_walk.png",32,32);
        dstate->sprite_archere_idle=sprite_sheet_create(c,"asset/archere_base.png",32,32);
        dstate->sprite_archere_mort=sprite_sheet_create(c,"asset/mort.png",32,32);
        dstate->sprite_fleche=sprite_sheet_create(c,"asset/fleche.png",16,16);
        dstate->personnage_walk = animation_create(dstate->sprite_archere_walk,frequence_s(10));
        dstate->personnage_idle = animation_create(dstate->sprite_archere_idle,frequence_s(5));
        dstate->personnage_mort = animation_create(dstate->sprite_archere_mort,frequence_s(2));
        dstate->fleche = animation_create(dstate->sprite_fleche,frequence_s(10));

        istate->nb_colonne = 100;
        init_grid(arg);
    }
    //game_type->is_loaded
}

// décharge tout sauf le mutable state
void egg_unload(game_arg arg)
{
    get_game_state(egg);
    texture_free(dstate->fond);
    texture_free(dstate->arbalete);
    sprite_sheet_free(dstate->sprite_archere_walk);
    sprite_sheet_free(dstate->sprite_archere_idle);
    sprite_sheet_free(dstate->sprite_fleche);
    animation_free(dstate->personnage_walk);
    animation_free(dstate->personnage_idle);
    animation_free(dstate->fleche);

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
        current_game_state = GAME_STATE_GAME_OVER;
        // game over
        return true;
    }
    return false;
}


void egg_update(game_arg arg)
{
    get_game_state(egg);

    if(current_game_state != GAME_STATE_RUNNING) return;
    
    egg_set_default_input(arg);
    game_get_input(c,the_game, current_entity);

    egg_output player_input = tab_first_value(entity_input);
    mstate->player_x++;
    
    switch (player_input)
    {
        case EGG_OUTPUT_MOVE_DOWN: mstate->player_y++; break;
        case EGG_OUTPUT_MOVE_UP  : mstate->player_y--; break;
        default: break;
    }
    mstate->player_y = (mstate->player_y+egg_nb_ligne)%egg_nb_ligne;
    if(check_receive_damage(arg, 0, 0)) return;

    mstate->nb_tour++;

    if(check_receive_damage(arg, 0, 0)) return;

    current_entity->score += 1;
    
}

//#define egg_lerp lerpf
#define egg_lerp lerpf

void egg_draw(game_arg arg)
{

    get_game_state(egg);

    float coef = draw_coef;

    int nb_ligne = egg_nb_ligne;
    int nb_colonne = 3*egg_nb_ligne;
    int colonne_arbalete = nb_colonne-1;

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

    repeat(y,nb_ligne){
        rect arbalete_fond_rect = texture_rect(dstate->arbalete);
        float taille = 1;// = 1+ abs(4*sin(pi*(second(c->timer)+from_s(y/(float)nb_ligne))))*0.25;
        if(grid_get(arg, y, colonne_arbalete) == EGG_OBSTACLE_ARROW)
        {
            taille = 1.2;
        }

        int recul = grid_get(arg, y, colonne_arbalete-1) == EGG_OBSTACLE_ARROW ? 1 : 0;        
        pen_texture_at_center(c,dstate->arbalete,arbalete_fond_rect,colonne_arbalete+0.5 +1/8.0f*(coef*recul),y+0.5,taille/24,taille/24, 0.5, 0.5);
    }
    repeat(x, nb_colonne-1)
    {
        repeat(y, nb_ligne)
        {
            if(grid_get(arg, y,x) == EGG_OBSTACLE_ARROW)
            {
            
                int arrow_old_x = x+1;
                int arrow_new_x = x;
                float lerp = egg_lerp(arrow_old_x, arrow_new_x, coef);

                pen_animation(c,dstate->fleche,rectanglef(lerp, y, 0.9, 0.9),c->timer,0);
            }
        }
    }

    dstate->player_y = moyenne_ponderee(dstate->player_y, mstate->player_y, 0.85);

    //float lerp = egg_lerp(arrow_old_x, arrow_new_x, coef);
    
    bool perso_base = abs(mstate->player_y-gstate->player_y) < 1/32.0f;
    bool vers_le_haut = mstate->player_y-gstate->player_y < 0;
    
    if(current_game_state == GAME_STATE_GAME_OVER)
    {
        pen_animation(c,dstate->personnage_mort,rectanglef(0, dstate->player_y, 1, 1),c->timer,0);

    } 
    else if(perso_base)
    {
        pen_animation(c,dstate->personnage_idle,rectanglef(0, dstate->player_y, 1, 1),c->timer,2);
    }else {

        pen_animation(c,dstate->personnage_walk,rectanglef(0, dstate->player_y, 1, 1),c->timer,(vers_le_haut ? 4:0));
    }

   // pen_color(c, color_green);
    //pen_rect(c, rectanglef(0, mstate->player_y, 1, 1));

    pen_formatted_text_at_center(c, 0, 0, FONT_SIZE_NORMAL, 0, 0, "%f", current_entity->score);
    pen_formatted_text_at_center(c, 0, FONT_SIZE_NORMAL, FONT_SIZE_NORMAL, 0, 0, "%.2f", coef);
    pen_formatted_text_at_center(c, 0, 2*FONT_SIZE_NORMAL, FONT_SIZE_NORMAL, 0, 0, "%i", mstate->nb_tour);

    camera_pop(c);

    if(current_game_state == GAME_STATE_GAME_OVER){
         pen_formatted_text_at_center(c,window_width(c)/2, window_height(c)/2, FONT_SIZE_NORMAL, 0.5, 0.5, "%.1f", current_entity->score);
    }

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
                dx = x+1;
                break;;
            }
        }
        //dx += 2; //d in [1, EGG_INPUT_MAX_RANGE]

        if(dx >= rule_in[y])
        {
            return false;
        }
    }

    //dstate->player_y
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