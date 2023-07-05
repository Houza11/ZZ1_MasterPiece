#include "base.h"

bool vs_inside_grid(int x, int y)
{
    return x >= 0 && x < vs_nb_colonne_x && y >= 0 &&  y < vs_nb_ligne_y;
}

bool vs_will_damage(game_arg arg, int x, int y)
{
    get_game_state(vs);
    return vs_inside_grid(x,y) ? (((vs_grid_damage[x][y] << 4) & 0b1111) != 0) : false;
}

bool vs_can_damage(game_arg arg, int x, int y)
{
    get_game_state(vs);
    return vs_inside_grid(x,y) ? ((vs_grid_damage[x][y] & 0b1111) != 0) : VS_INPUT_SOL;
}

int vs_grid_wall_get(game_arg arg, int x, int y)
{
    get_game_state(vs);
    return vs_inside_grid(x,y) ? (vs_grid_wall[x][y]) : VS_INPUT_SOL;
}

void vs_init_grid(game_arg arg)
{
    get_game_state(vs);

    repeat(x, vs_nb_colonne_x)
    {
        repeat(y, vs_nb_ligne_y)
        {
            vs_grid_wall[x][y] = vs_wall_sol;
            vs_grid_damage[x][y] = vs_damage_none;
        }
    }
}

void vs_load(game_arg arg)
{
    get_game_state(vs);

    vs_players[0].direction = vs_entity_dir_up;
    vs_players[0].x = vs_nb_colonne_x /2;
    vs_players[0].y = 0;

    vs_players[1].direction = vs_entity_dir_down;
    vs_players[1].x = vs_nb_colonne_x /2;
    vs_players[1].y = vs_nb_ligne_y-1;

    repeat(i, vs_max_player)
    {
        vs_players[i].state = vs_entity_state_normal; 
    }

    if(dstate != null)
    {

    }

    if(need_reset)
    {

    }else
    {
        //game_ordi_configure(the_game, egg_nvb_ligne, EGG_INPUT_MAX_RANGE, 1, EGG_OUTPUT_MOVE_RANGE, 10);
        dstate->grass   = texture_create(c,"asset/fond.png");
        dstate->archere = texture_create(c,"asset/archere.png");
        dstate->damage  = texture_create(c,"asset/damage.png");
        vs_init_grid(arg);
    }
}

// décharge tout sauf le mutable state
void vs_unload(game_arg arg)
{
    get_game_state(vs);
    texture_free(dstate->grass);
    texture_free(dstate->archere);
    texture_free(dstate->damage);
}

void vs_unload_mutable(game_arg arg)
{
    get_game_state(vs);
}

void* vs_clone_mutable(game_arg arg)
{
    get_game_state(vs);
    vs_mutable_state* copy = create(vs_mutable_state);
    memccpy(copy, mstate, 1, sizeof(vs_mutable_state));
    return (void*)copy;
}

void vs_set_default_input(game_arg arg)
{
    get_game_state(vs);
    output_single_value(VS_OUTPUT_DO_NOTHINGS);
}

void vs_entity_dead(game_arg arg, int entity_idx)
{
    get_game_state(vs);
    vs_players[entity_idx].state = vs_entity_state_dead;
}

bool vs_check_receive_damage(game_arg arg, int entity_idx)
{
    get_game_state(vs);
    if(vs_can_damage(arg, vs_players[entity_idx].x, vs_players[entity_idx].y))
    {
        vs_entity_dead(arg, entity_idx);
        return true;
    }
    return false;
}

void vs_update(game_arg arg)
{
    get_game_state(vs);

    if(current_game_state != GAME_STATE_RUNNING) return;


    
    vs_set_default_input(arg);
    game_get_input(c,the_game, current_entity);

    vs_output player_input = tab_first_value(entity_input);
    unused(player_input);
    current_entity->score += 1;
}

#define vs_lerp lerpf

void vs_display_player(game_arg arg, vs_entity* p)
{
    get_game_state(vs);

    int direction_y_offset = 0;
    switch (p->direction)
    {
        case vs_entity_dir_down: direction_y_offset = 0; break;
        case vs_entity_dir_up:   direction_y_offset = 4; break;
        case vs_entity_dir_right:direction_y_offset = 2; break;
        case vs_entity_dir_left: direction_y_offset = 6; break;
        default: break;
    }

    int line = 0;
    int nb_frame = 1;
    int fps = 1;
    switch (p->state)
    {
        case vs_entity_state_dead: fps = 2; nb_frame = 2; line = 1; break;
        case vs_entity_state_load_bow: fps = -1; nb_frame = 5; line = 4; break;
        case vs_entity_state_attack_sword: fps = 1; nb_frame = 1; line = 0; break;
        case vs_entity_state_normal: fps = 2; nb_frame = 2; line = 0; break;
        default: break;
    }

    int frame = (c->timer / frequence_s(fps)) % nb_frame;
    rect src = rectangle(32*frame,32*(line+direction_y_offset),32,32);
    rectf dest = rectanglef(p->x-0.5, p->y-0.5,2,2);

    pen_texture(c, dstate->archere, src, dest);
}

void vs_draw(game_arg arg)
{
    get_game_state(vs);

    float coef = draw_coef;
    unused(coef);

    float offset = 1;
    rectf area = rectanglef(-offset,-offset, vs_nb_colonne_x+2*offset, vs_nb_ligne_y+2*offset);
    area = camera_push_focus_fullscreen(c, area);
    
    for(int x = floor(area.x); x < ceiling(area.w)+1; x++)
    {
        for(int y = floor(area.y); y < ceiling(area.h)+1; y++)
        {
            rect fond_rect = texture_rect(dstate->grass);
            fond_rect.w /= 2;
            fond_rect.h /= 2;
            int parite = (x+y+10000) % 2;
            fond_rect.x = fond_rect.w *parite;
            fond_rect.y = fond_rect.h * vs_inside_grid(x,y);
            pen_texture(c,dstate->grass,fond_rect,rectanglef(x,y,1,1));
        }
    }

    repeat(y, vs_nb_ligne_y)
    {
        repeat(x, vs_nb_colonne_x)
        {
            repeat(i, vs_nb_player)
            {
                vs_entity* p = &(vs_players[i]);
                if(p->y == y)
                {
                    vs_display_player(arg, p);
                }
            }
        }
    }

    camera_pop(c);

    if(current_game_state == GAME_STATE_GAME_OVER){
         pen_text_at_center(c, "game over", window_width(c)/2, window_height(c)/2, FONT_SIZE_NORMAL, 0.5, 0.5);
         //pen_formatted_text_at_center(c,window_width(c)/2, window_height(c)/2, FONT_SIZE_NORMAL, 0.5, 0.5, "%.1f", current_entity->score);
    }

}

char vs_rule_output_to_char(int output)
{
    return "X^V><BA"[output];
}
char vs_rule_input_to_char(int input)
{
    return "X.M!?Ee"[input];
}

void vs_draw_rule(game_arg arg, entity* e, rule* r, int idx)
{
    get_game_state(vs);
    unused(idx);
    unused(e);
    unused(r);
}

void vs_player_input(game_arg arg, entity* e)
{
    get_game_state(vs);
    unused(e);

    output_single_value(VS_OUTPUT_DO_NOTHINGS);

    if(input_up(c))
    {
        output_single_value(VS_OUTPUT_MOVE_UP); return;
    }
    if(input_down(c))
    {
        output_single_value(VS_OUTPUT_MOVE_DOWN); return;
    }
    if(input_right(c))
    {
        output_single_value(VS_OUTPUT_MOVE_RIGHT); return;
    }
    if(input_left(c))
    {
        output_single_value(VS_OUTPUT_MOVE_LEFT); return;
    }
}

bool vs_rule_match(game_arg arg, entity* e, rule* r)
{
    get_game_state(vs);
    /*
    tab_as_array(r->input, rule_in);
    unused(rule_in_size);

    repeat(y, egg_nb_ligne)
    {
        if(rule_in[y] == EGG_INPUT_OSEF) continue;

        // distance pour le prochain osbtacle
        int dx = EGG_INPUT_MAX_RANGE;
        repeat(x, EGG_INPUT_MAX_RANGE+1) // -1 because of the Osef symbol
        {
            if(can_damage(grid_get(arg, (y+mstate->player_y) % egg_nb_ligne, x+offset_animation_bonus)))
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
    */

    unused(e);
    unused(r);
    return false;
}

void vs_printf(game_arg arg)
{
    unused(arg);
    printf("VerSUS game\n");
}