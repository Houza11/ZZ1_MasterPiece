#include "base.h"

#define player vs_players[idx]

bool vs_inside_grid(int x, int y)
{
    return x >= 0 && x < vs_nb_colonne_x && y >= 0 &&  y < vs_nb_ligne_y;
}


int damage_create(int right, int left, int up, int down, int top)
{
    return ((right & 1) << 0) | ((left & 1) << 1) | ((up & 1) << 2) | ((down & 1) << 3) | ((top & 1) << 4);
}

int damage_later(int damage)
{
    return (damage << 5) & 0b1111100000;
}

int damage_update(int damage)
{
    return (damage >> 5);
}

float get_player_score(game_arg arg, int idx)
{
    get_game_state(vs);
    if(idx == 0)
    {
        return current_entity->score;
    }  
    return -1;
}

void set_player_score(game_arg arg, int idx, float val)
{
    get_game_state(vs);
    if(idx == 0)
    {
        current_entity->score = val;
    }
}


void grid_set_damage(game_arg arg, int x, int y, int damage)
{
    get_game_state(vs);
    vs_grid_damage[x][y] = vs_grid_damage[x][y] | damage;
}

int damage_right(int d) { return (d & 0b1); }
int damage_left (int d) { return (d & 0b10); }
int damage_up   (int d) { return (d & 0b100); }
int damage_down (int d) { return (d & 0b1000); }
int damage_top  (int d) { return (d & 0b10000); }

bool vs_will_damage(game_arg arg, int x, int y)
{
    get_game_state(vs);
    return vs_inside_grid(x,y) ? (((vs_grid_damage[x][y] >> 5) & 0b11111) != 0) : false;
}

bool vs_can_damage(game_arg arg, int x, int y)
{
    get_game_state(vs);
    return vs_inside_grid(x,y) ? ((vs_grid_damage[x][y] & 0b11111) != 0) : false;
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
        }
    }
}

void vs_load(game_arg arg)
{
    get_game_state(vs);



    vs_players[0].direction = vs_entity_dir_up;
    vs_players[0].x = vs_nb_colonne_x /2;
    vs_players[0].y = vs_nb_ligne_y-1;

    vs_players[1].direction = vs_entity_dir_down;
    vs_players[1].x = vs_nb_colonne_x /2;
    vs_players[1].y = 0;

    repeat(x, vs_nb_colonne_x)
    {
        repeat(y, vs_nb_ligne_y)
        {
            vs_grid_damage[x][y] = vs_damage_none;
        }
    }

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
        game_ordi_configure(the_game, 8, VS_INPUT_MAX_RANGE, 1, VS_OUTPUT_MOVE_RANGE, 10);
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

void coordinate_move(int* x, int* y, vs_entity_dir dir)
{
    switch (dir)
    {
        case vs_entity_dir_right:*x = x[0]+1; break;
        case vs_entity_dir_left: *x = x[0]-1; break;
        case vs_entity_dir_up:   *y = y[0]-1; break; // :'(
        case vs_entity_dir_down: *y = y[0]+1; break; // :'(        
        default: break;
    }
}   

void vs_player_get_input(game_arg arg, int idx)
{
    get_game_state(vs);
    vs_set_default_input(arg);

    if(idx == 0) // player
    {
        game_get_input(c,the_game, current_entity);
    }
}

void player_move_dir(game_arg arg, int idx, vs_output dir)
{
    get_game_state(vs);
    int x = player.x;
    int y = player.y;
    coordinate_move(&x,&y, dir);
    if(vs_inside_grid(x,y))
    {
        player.x = x;
        player.y = y;
        player.direction = dir;
    }
}



void bow_attack(game_arg arg, int x, int y, int dx, int dy)
{
    get_game_state(vs);

    while(vs_inside_grid(x,y))
    {
        grid_set_damage(arg, x, y, damage_create(dx>0,dx<0,dy<0,dy>0,0));
        x += dx;
        y += dy;
    }
}

void remove_damage(game_arg arg)
{
    get_game_state(vs);

    repeat(y, vs_nb_ligne_y)
    {
        repeat(x, vs_nb_colonne_x)
        {
            vs_grid_damage[x][y] = damage_update(vs_grid_damage[x][y]);
        }
    }
}

void vs_update_player(game_arg arg, int idx)
{
    get_game_state(vs);

    if(player.state == vs_entity_state_dead) return;

    set_player_score(arg, idx, get_player_score(arg, idx) + 1);

    if(player.state == vs_entity_state_load_bow) 
    {
        player.var_0--;
        if(player.var_0 == vs_bow_loading_time-1)
        {
            int dx = 0;
            int dy = 0;
            coordinate_move(&dx, &dy, player.direction);
            bow_attack(arg, player.x+dx, player.y+dy, dx, dy);
        }else if(player.var_0 <= 0)
        {
            player.state = vs_entity_state_normal;
        }
        return;
    }

    if(player.state == vs_entity_state_attack_sword) 
    {
        int dx = 0;
        int dy = 0;
        coordinate_move(&dx, &dy, player.direction);
        grid_set_damage(arg, player.x+dx, player.y+dy, damage_create(0,0,0,0,1));
        player.state = vs_entity_state_normal;
        return;
    }

    vs_player_get_input(arg, idx);

    vs_output player_input = tab_first_value(entity_input);

    switch (player_input)
    {
        case VS_OUTPUT_DO_NOTHINGS: break;
        case VS_OUTPUT_MOVE_RIGHT:
        case VS_OUTPUT_MOVE_LEFT:
        case VS_OUTPUT_MOVE_UP:
        case VS_OUTPUT_MOVE_DOWN:
            player_move_dir(arg, idx, player_input);
            break;
        case VS_OUTPUT_MOVE_SWORD:
            player.state = vs_entity_state_attack_sword;
            break;
        case VS_OUTPUT_MOVE_BOW:
            player.var_0 = vs_bow_loading_time;
            player.state = vs_entity_state_load_bow;
            break;
            default:
        break;
    }
}

void vs_update(game_arg arg)
{
    get_game_state(vs);
    if(current_game_state != GAME_STATE_RUNNING) return;

    remove_damage(arg);


    repeat(idx, vs_nb_player)
    {
        vs_update_player(arg, idx);
    }
    int nb_player_alive = vs_nb_player;
    repeat(idx, vs_nb_player)
    {
        if(player.state != vs_entity_state_dead)
        {
            if(vs_can_damage(arg, player.x, player.y))
            {
                player.state = vs_entity_state_dead;
            }
        }else
        {
            nb_player_alive--;
        }
    }

    if(nb_player_alive <= 1)
    {
        repeat(idx, vs_nb_player)
        {
            if(player.state != vs_entity_state_dead)
            {
                player.state = vs_entity_state_win; 
                set_player_score(arg, idx, get_player_score(arg, idx) + 1000000.f / nb_update);
            }
        }
        current_game_state = GAME_STATE_GAME_OVER;
    }
}

#define vs_lerp lerpf

void vs_draw_player(game_arg arg, int idx)
{
    get_game_state(vs);
    vs_entity* p = &(player);

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
    int frame = -1;
    switch (p->state)
    {
        case vs_entity_state_dead: fps = 3; nb_frame = 2; line = 5; direction_y_offset = 0; break;
        case vs_entity_state_win: fps = 3; nb_frame = 2; line = 5; direction_y_offset = 1; break;
        case vs_entity_state_load_bow:
        {
            fps = -1;
            nb_frame = 5;
            line = 4;
            if(player.var_0 < vs_bow_loading_time)
            {
                frame = 0;
            }
        }break;
        case vs_entity_state_attack_sword: fps = 1; nb_frame = 1; line = 0; break;
        case vs_entity_state_normal: fps = 7; nb_frame = 2; line = 0; break;
        default: break;
    }

    if(frame == -1)
    {
        frame = (fps > 0) ? ((int)((c->timer / frequence_s(fps)) % nb_frame)) : ((int)(draw_coef*nb_frame));
    }

    rect src = rectangle(32*frame+32*7*idx,32*(line*8+direction_y_offset),32,32);
    rectf dest = rectanglef(p->x-0.5, p->y-1,2,2);

    pen_texture(c, dstate->archere, src, dest);
}

void vs_draw_damage(game_arg arg, int x, int y)
{
    get_game_state(vs);

    int damage = vs_grid_damage[x][y];
    rect src = rectangle(0, 0, 16, 16);
    rectf dest = rectanglef(x, y,1,1);

    if(damage_right(damage))
    {
        src = rectangle(0, 16*0, 16, 16);
        pen_texture(c, dstate->damage, src, dest);
    }
    if(damage_left(damage))
    {
        src = rectangle(0, 16*1, 16, 16);
        pen_texture(c, dstate->damage, src, dest);
    }
    if(damage_up(damage))
    {
        src = rectangle(0, 16*2, 16, 16);
        pen_texture(c, dstate->damage, src, dest);
    }
    if(damage_down(damage))
    {
        src = rectangle(0, 16*3, 16, 16);
        pen_texture(c, dstate->damage, src, dest);
    }
    if(damage_top(damage))
    {
        src = rectangle(0, 16*4, 16, 16);
        pen_texture(c, dstate->damage, src, dest);
    }
}

void vs_draw(game_arg arg)
{
    get_game_state(vs);

    float coef = draw_coef;
    unused(coef);

    float offset = 1;
    rectf area = rectanglef(-offset,-offset, vs_nb_colonne_x+2*offset, vs_nb_ligne_y+2*offset);
    area = camera_push_focus_fullscreen(c, area);
    
    for(int x = floor(area.x); (float)x <= area.x+area.w; x++)
    {
        for(int y = floor(area.y);  (float)y <= area.y+area.h; y++)
        {
            rect fond_rect = texture_rect(dstate->grass);
            fond_rect.w /= 2;
            fond_rect.h /= 2;
            int parite = (x+y+10000) % 2;
            fond_rect.x = fond_rect.w *parite;
            fond_rect.y = fond_rect.h * (vs_inside_grid(x,y) ? 0 : 1);
            pen_texture(c,dstate->grass,fond_rect,rectanglef(x,y,1,1));
        }
    }

    repeat(y, vs_nb_ligne_y)
    {
        repeat(x, vs_nb_colonne_x)
        {
            repeat(i, vs_nb_player)
            {
                if(vs_players[i].y == y)
                {
                    vs_draw_player(arg, i);
                }

                if(vs_can_damage(arg, x, y))
                {
                    vs_draw_damage(arg, x, y);
                }
            }
        }
    }

    camera_pop(c);

    pen_formatted_text_at_center(c, window_width(c)/2, 0, FONT_SIZE_NORMAL, 0.5, 0, "p1 %.0f p2 %.0f", get_player_score(arg, 0), get_player_score(arg, 1));

    if(current_game_state == GAME_STATE_GAME_OVER){
         pen_text_at_center(c, "game over", window_width(c)/2, window_height(c), FONT_SIZE_NORMAL, 0.5, 1);
    }

}

char vs_rule_output_to_char(int output)
{
    return " ^v><BA"[output];
}
char vs_rule_input_to_char(int input)
{
    return "X.#!?EFFF"[input];
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
    if(input_special0(c))
    {
        output_single_value(VS_OUTPUT_MOVE_BOW); return;
    }
    if(input_special1(c))
    {
        output_single_value(VS_OUTPUT_MOVE_SWORD); return;
    }
}



void get_coord_relative_to_player(game_arg arg, int idx, int forward, int side, int* rx, int* ry)
{
    get_game_state(vs);
    int X = player.x;
    int Y = player.y;
    switch (player.direction)
    {
        case vs_entity_dir_up:
        X += side;
        Y += forward;
        break;

        case vs_entity_dir_down:
        X -= side;
        Y -= forward;
        break;

        case vs_entity_dir_right:
        X+=forward;
        Y-=side;
        break;

        case vs_entity_dir_left:
        X-=forward;
        Y+=side;
        break;
    
        default: break;
    }
    *rx = X;
    *ry = Y;
}

bool vs_rule_match(game_arg arg, entity* e, rule* r)
{
    get_game_state(vs);

    int idx = e->id;
    check(idx == 0);

/*
...
.X.
...
*/
    int input[8];
    int input_idx = 0;

    repeat(i, 8)
    {
        input[i] = VS_INPUT_SOL;
    }

    int dx = 0;
    int dy = 0;
    coordinate_move(&dx, &dy, player.direction);

    for(int x = -1; x <= 1; x++)
    {
        for(int y = -1; y <= 1; y++)
        {
            if(x == 0 && y == 0) continue;
            int rx = 0;
            int ry = 0;
            get_coord_relative_to_player(arg, idx, x, y, &rx, &ry);

            if(vs_inside_grid(rx, ry) == false)
            {
                input[input_idx++] = VS_INPUT_OUT_OF_ARENA;
            }else
            {
                int current_input = VS_INPUT_SOL;
                if(vs_can_damage(arg, rx, ry))
                {
                    current_input = VS_INPUT_DAMAGE;
                }else if(vs_will_damage(arg, rx, ry))
                {
                    current_input = VS_INPUT_FUTUR_DAMAGE;
                }else 
                {
                    repeat(i, vs_nb_player)
                    {
                        if(i == idx) continue;
                        if(vs_players[i].x == rx && vs_players[i].y == ry)
                        {
                            current_input = VS_INPUT_ENEMY_NORMAL;
                            break;
                        }
                    }
                }
                input[input_idx++] = current_input;
            }
        }
    }
    
    tab_as_array(r->input, rule_in);
    unused(rule_in_size);

    repeat(i, r->input->length)
    {
        if(rule_in[i] <= VS_INPUT_OSEF) continue;

        if(rule_in[i] != input[i])
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

void vs_printf(game_arg arg)
{
    unused(arg);
    printf("VerSUS game\n");
}