#include "base.h"


#define offset_animation_bonus 3
#define arbalete_range 15
bool egg_can_damage(int id)
{
    return id == EGG_OBSTACLE_ARROW;
}

bool egg_inside_grid(game_arg arg, int ligne, int colonne)
{
    get_game_state(egg);
    return ligne >= 0 && ligne < egg_nb_ligne && colonne >= 0 && colonne < egg_grid->length;
}

// regular ge, the the origin of the grid
obstacle egg_grid_get_fixed(game_arg arg, int ligne, int colonne)
{
    get_game_state(egg);
    if(egg_inside_grid(arg, ligne, colonne))
    {
        return (obstacle)vec_get(vec_get(egg_grid, vec*, colonne), obstacle, ligne);
    }else
    {
        return 0;
    }
}

//relative to the player
obstacle egg_grid_get(game_arg arg, int ligne, int colonne)
{
    get_game_state(egg);
    return egg_grid_get_fixed(arg, ligne, colonne+mstate->player_x);
}


void egg_grid_set(game_arg arg, int ligne, int colonne, obstacle val)
{
    get_game_state(egg);
    check(egg_inside_grid(arg, ligne, colonne));
    vec_set(vec_get(egg_grid, vec*, colonne), obstacle, ligne, val);
}

void egg_grid_push_colonne(game_arg arg, vec* v)
{
    get_game_state(egg);
    vec_push(egg_grid, vec*, v);
}

void egg_init_grid(game_arg arg)
{
    get_game_state(egg);
    egg_grid = vec_empty(vec*);

    repeat(i, arbalete_range)
    {
        egg_pattern_add_empty_line(arg);
    }

    int j = 0;
    while(j < egg_nb_colonne)
    {
        j += egg_pattern_add(arg, -1);
    }
}

void egg_load(game_arg arg)
{
    get_game_state(egg);

    mstate->nb_tour = 0;
    mstate->player_y = egg_nb_ligne/2;
    mstate->player_x = 0;

    if(dstate != null)
    {
        dstate->player_y = mstate->player_y;
        if(dstate->arbalete_size == null)
        {
            dstate->arbalete_size = create_array(float, egg_nb_ligne);
        }
        repeat(i, egg_nb_ligne)
        {
            dstate->arbalete_size[i] = 1;
        }
    }

    if(need_reset)
    {

    }else
    {

        #ifdef EGG_RULE_BASED_ON_RANGE
            #ifdef EGG_RULE_USE_DENSITY
            game_ordi_configure(the_game, 2*egg_nb_ligne, EGG_INPUT_MAX_RANGE, 1, EGG_OUTPUT_MOVE_RANGE, 10);
            #else
            game_ordi_configure(the_game, egg_nb_ligne, EGG_INPUT_MAX_RANGE, 1, EGG_OUTPUT_MOVE_RANGE, 10);
            #endif
        #else
        game_ordi_configure(the_game, egg_nb_ligne*EGG_INPUT_MAX_RANGE, 2, 1, EGG_OUTPUT_MOVE_RANGE, 10);
        #endif
        dstate->fond = texture_create(c,"asset/fond.png");
        dstate->arbalete = texture_create(c,"asset/arbalete.png");
        dstate->sprite_archere_walk=sprite_sheet_create(c,"asset/archere_walk.png",32,32);
        dstate->sprite_archere_idle=sprite_sheet_create(c,"asset/archere_base.png",32,32);
        dstate->sprite_archere_mort=sprite_sheet_create(c,"asset/mort.png",32,32);
        dstate->sprite_fleche=sprite_sheet_create(c,"asset/fleche.png",16,16);
        dstate->sprite_robot_walk=sprite_sheet_create(c, "asset/robot_walk.png", 32,32);
        dstate->sprite_robot_mort=sprite_sheet_create(c, "asset/mort_robot.png", 32,32);
        dstate->sprite_portail_haut=sprite_sheet_create(c,"asset/portail.png",48,48);
        dstate->personnage_walk = animation_create(dstate->sprite_archere_walk,frequence_s(10));
        dstate->personnage_idle = animation_create(dstate->sprite_archere_idle,frequence_s(3));
        dstate->personnage_mort = animation_create(dstate->sprite_archere_mort,frequence_s(2));
        dstate->robot_walk = animation_create(dstate->sprite_robot_walk, frequence_s(8));
        dstate->robot_mort = animation_create(dstate->sprite_robot_mort, frequence_s(3));
        dstate->fleche = animation_create(dstate->sprite_fleche,frequence_s(10));
        dstate->portail_haut = animation_create(dstate->sprite_portail_haut,frequence_s(2));
       
    
        istate->nb_colonne = 1000;
        egg_init_grid(arg);
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
    sprite_sheet_free(dstate->sprite_archere_mort);
    sprite_sheet_free(dstate->sprite_portail_haut);
    
    sprite_sheet_free(dstate->sprite_robot_walk);
    sprite_sheet_free(dstate->sprite_robot_mort);
    animation_free(dstate->personnage_walk);
    animation_free(dstate->personnage_idle);
    animation_free(dstate->personnage_mort);
    animation_free(dstate->fleche);
    animation_free(dstate->portail_haut);
    
    animation_free(dstate->robot_walk);
    animation_free(dstate->robot_mort);

    free(dstate->arbalete_size);

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

bool egg_check_receive_damage(game_arg arg, int offset_y, int offset_x)
{
    get_game_state(egg);
    if(egg_can_damage(egg_grid_get(arg, ((mstate->player_y+offset_y)+egg_nb_ligne)%egg_nb_ligne, offset_x)))
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
    if(egg_check_receive_damage(arg, 0, offset_animation_bonus)) return;

    mstate->nb_tour++;

    if(egg_check_receive_damage(arg, 0, offset_animation_bonus)) return;

    current_entity->score += 1;
}

//#define egg_lerp lerpf
#define egg_lerp lerpf

void egg_draw(game_arg arg)
{

    get_game_state(egg);

    float coef = draw_coef;

    int nb_ligne = egg_nb_ligne;
    int nb_colonne = arbalete_range+1; //3*egg_nb_ligne;
    int colonne_arbalete = arbalete_range; //nb_colonne-1;

    rectf area = rectanglef(-1,-1, nb_colonne+2, nb_ligne+2);
    area = camera_push_focus_fullscreen(c, area);
    
    for(int x = floor(area.x); (float)x <= area.x+area.w; x++)
    {
        for(int y = floor(area.y);  (float)y <= area.y+area.h; y++)
        {
            // flèche
            rect fond_rect = texture_rect(dstate->fond);
            fond_rect.w /= 2;
            fond_rect.h /= 2;
            int parite = (x+y+10000) % 2;
            fond_rect.x = fond_rect.w *parite;
            fond_rect.y = fond_rect.h * (y >= 0 && y < nb_ligne ? 0 : 1);
            pen_texture(c,dstate->fond,fond_rect,rectanglef(x,y,1,1));
        }
    }

    repeat(y, nb_ligne)
    {
        for(int x = -1; x+coef*0.5 < colonne_arbalete+offset_animation_bonus; x++)
        {
            if(egg_grid_get(arg, y,x) == EGG_OBSTACLE_ARROW)
            {
                int arrow_old_x = x-offset_animation_bonus+1;
                int arrow_new_x = x-offset_animation_bonus;
                float lerp = egg_lerp(arrow_old_x, arrow_new_x, coef);

                pen_animation(c,dstate->fleche,rectanglef(lerp, y+0.1, 0.9, 0.9),c->timer+from_ms(50*y),0);
            }
        }

        {   // arbalète
            rect arbalete_fond_rect = rectangle(6*32,0,32,32);
            float taille = 1;// = 1+ abs(4*sin(pi*(second(c->timer)+from_s(y/(float)nb_ligne))))*0.25;
            if(egg_grid_get(arg, y, colonne_arbalete+offset_animation_bonus) == EGG_OBSTACLE_ARROW)
            {
                taille = 1.2;
            }
            dstate->arbalete_size[y] = moyenne_ponderee(dstate->arbalete_size[y], taille, dstate->arbalete_size[y] > taille ? 0.5 : 0.9);
            //dstate->arbalete_size[y] = 1;
            int recul = egg_grid_get(arg, y, colonne_arbalete+offset_animation_bonus-1) == EGG_OBSTACLE_ARROW ? 1 : 0;        
            pen_texture_at_center(c,dstate->arbalete,arbalete_fond_rect,colonne_arbalete+0.5 +1/8.0f*(0.2*(1-maxif(4*coef,1))*recul),y+0.5,dstate->arbalete_size[y]/18,dstate->arbalete_size[y]/18, 0.5, 0.5);
        }
    }

   
    rectf portail_haut_fond_rectf = rectanglef(-1.5,-2.7,4,4);
    rectf portail_bas_fond_rectf = rectanglef(-1.5,3.7,4,4);

    dstate->player_y = moyenne_ponderee(dstate->player_y, mstate->player_y, 0.85);
     
    pen_animation(c,dstate->portail_haut,portail_haut_fond_rectf,c->timer,0);
    pen_animation(c,dstate->portail_haut,portail_bas_fond_rectf,c->timer,1);

    bool perso_base = abs(mstate->player_y-gstate->player_y) < 1/32.0f;
    bool vers_le_haut = mstate->player_y-gstate->player_y < 0;
    rectf player_dest = rectanglef(-0.5, dstate->player_y-1, 2, 2);

    if(c->paused){

        pen_text_at(c,"Jouen Martin",2,6,0.5);
        pen_text_at(c,"Tamagnaud Thomas",7,6,0.5);
        pen_text_at(c,"Moosa Houzayfa",12,6,0.5);
    }
    
    if(current_game_state == GAME_STATE_GAME_OVER)
    {
        if (current_entity->type == ENTITY_TYPE_PLAYER)
        {
            pen_animation(c,dstate->personnage_mort,player_dest,c->timer,0);
        }
        else
        {
            pen_animation(c,dstate->robot_mort,player_dest,c->timer,0);
        }
    } 
    else if(perso_base)
    {
        if (current_entity->type == ENTITY_TYPE_PLAYER)
        {
            pen_animation(c,dstate->personnage_idle,player_dest,c->timer,2);
        }
        else
        {
            pen_animation(c,dstate->robot_walk,player_dest,c->timer,1);
        }
    }else {
        if (current_entity->type == ENTITY_TYPE_PLAYER)
        {
            pen_animation(c,dstate->personnage_walk,player_dest,c->timer,(vers_le_haut ? 4:0));
        }
        else
        {
            pen_animation(c,dstate->robot_walk,player_dest,c->timer,(vers_le_haut ? 2:0));
        }
    }

   // pen_color(c, color_green);
    //pen_rect(c, rectanglef(0, mstate->player_y, 1, 1));



    camera_pop(c);

    pen_formatted_text_at_center(c, 0, 0, FONT_SIZE_NORMAL, 0, 0, "%.0f", current_entity->score);
    pen_formatted_text_at_center(c, window_width(c)/2, 0, FONT_SIZE_NORMAL, 0.5, 0, "A ~ %.0f", best_score_player);
    pen_formatted_text_at_center(c, window_width(c), 0, FONT_SIZE_NORMAL, 1, 0, "Z ~ ordi %.0f", best_score_ordi);
    //pen_formatted_text_at_center(c, 0, FONT_SIZE_NORMAL, FONT_SIZE_NORMAL, 0, 0, "%.2f", coef);
    //pen_formatted_text_at_center(c, 0, 2*FONT_SIZE_NORMAL, FONT_SIZE_NORMAL, 0, 0, "%i", mstate->nb_tour);


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
    #ifdef EGG_RULE_BASED_ON_RANGE
        return "X0123456789"[input];
    #else
        return "X.!"[input];
    #endif
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

    action_ignore(c, action_right);
    action_ignore(c, action_left);

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

    int time_deformation[] = {0, 0, 1, 1, 0};

    #ifdef EGG_RULE_BASED_ON_RANGE
    repeat(y, egg_nb_ligne)
    {
        int yr;
        #ifdef EGG_RULE_USE_DENSITY
        yr = 2*y;
        #else
        yr = y;
        #endif

        if(rule_in[yr] == EGG_INPUT_OSEF) continue;

        // distance pour le prochain osbtacle
        int dx = EGG_INPUT_MAX_RANGE;

        #ifdef EGG_RULE_USE_DENSITY
        int density = 0;

        for(int x = EGG_INPUT_MAX_RANGE; x >= 0; x--)
        #else
        repeat(x, EGG_INPUT_MAX_RANGE+1) // -1 because of the Osef symbol
        #endif
        {
            if(egg_can_damage(egg_grid_get(arg, (y+mstate->player_y) % egg_nb_ligne, x+offset_animation_bonus+time_deformation[y])))
            {

                #ifdef EGG_RULE_USE_DENSITY
                density++;
                dx = x;
                #else
                dx = x+1;
                break;
                #endif
            }
        }
        //dx += 2; //d in [1, EGG_INPUT_MAX_RANGE]

        if(dx > rule_in[yr])
        {
            return false;
        }

        #ifdef EGG_RULE_USE_DENSITY
        if(rule_in[yr+1] == 0) continue; // Osef

        if((density+1) < rule_in[yr+1])
        {
            return false;
        }
        #endif

    }
    #else
    //egg_nb_ligne*EGG_INPUT_MAX_RANGE
    #define index(x,y) (y*EGG_INPUT_MAX_RANGE+x)

    repeat(y, egg_nb_ligne)
    {
        repeat(x, EGG_INPUT_MAX_RANGE)
        {
            int rval = rule_in[index(x,y)];
            if(rval == EGG_INPUT_OSEF) continue;

            if(rval != (egg_can_damage(egg_grid_get(arg, (y+mstate->player_y) % egg_nb_ligne, x+offset_animation_bonus+time_deformation[y]))))
            {
                return false;
            }
        }
    }
    #endif

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