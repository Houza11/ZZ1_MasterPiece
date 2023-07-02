#include "base.h"

game* game_create_arg(
    context* c,
    size_t sizeof_immutable_state,
    size_t sizeof_mutable_state,
    size_t sizeof_draw_state,
    game_fn update,
    game_fn draw,
    game_draw_rule_fn draw_rule,
    game_clone_fn clone_mutable,
    game_fn unload_mutable,
    game_fn load,
    game_fn unload,
    game_get_input_fn player_input,
    game_rule_match_fn rule_match,
    int condition_input_size,
    int condition_input_max_range,
    int condition_output_size,
    int condition_output_max_range,
    int nb_behavior)
{
    check(nb_behavior >= 1);
    check(condition_input_size >= 1);
    check(condition_input_max_range >= 1);
    check(condition_output_size >= 1);
    check(condition_output_max_range >= 1);

    game* g = create(game);

    
    {
        g->type = create(game_type);
        g->internal_mutable_state = create(game_mutable);
        g->mutable_state   = create_array(byte, sizeof_mutable_state);
        g->immutable_state = create_array(byte, sizeof_immutable_state);
        g->draw_state      = create_array(byte, sizeof_draw_state);
    }

    game_type* t = g->type;
    game_mutable* m = g->internal_mutable_state;

    {
        m->draw_dest = window_rectf(c);
        m->nb_turn = 0;
        m->state = GAME_STATE_RUNNING;
        m->current_ordi = null;
        m->current_ordi_output = tab_create(condition_output_size, 0);
    }

    {
        t->load = load;
        t->unload = unload;

        t->update = update;
        t->draw   = draw;
        t->draw_rule = draw_rule;

        t->clone_mutable = clone_mutable;
        t->unload_mutable = unload_mutable;

        t->player_input = player_input;
        t->rule_match = rule_match;

        t->condition_input_size = condition_input_size;
        t->condition_input_max_range = condition_input_max_range;
        t->condition_output_size = condition_output_size;
        t->condition_output_max_range = condition_output_max_range;

        t->maximize_score = true;
        t->best_entity = null;
        t->nb_behavior = nb_behavior;
        t->is_loaded = false;
    }
    return g;
}

game_arg game_arg_create(context* c, game* g)
{
    game_arg arg;
    arg.c = c;
    arg.g = g;
    return arg;
}

//#define g (arg.g)
#define gtype (g->type)
#define arg game_arg_create(c, g)

void game_update(context* c, game* g)
{
    check(gtype->is_loaded == true);
    gtype->update(arg);
}

void game_load(context* c, game* g)
{
    check(gtype->is_loaded == false);
    gtype->is_loaded = true;
    gtype->load(arg);
}

void game_internal_mutable_free(game_mutable* mut)
{
    entity_free(mut->current_ordi);
    tab_free(mut->current_ordi_output);
}


void game_type_unload(context* c, game* g)
{
    unused(c);
    if(gtype->best_entity != null)
    {
        entity_free(gtype->best_entity);
    }
    free(gtype);
    g->type = null;
}


void game_unload(context* c, game* g)
{
    check(gtype->is_loaded == true);
    gtype->is_loaded = false;
    gtype->unload_mutable(arg);
    gtype->unload(arg);

    game_type_unload(c, g);
    
    game_internal_mutable_free(g->internal_mutable_state);
    
    free(g);
    //todo;
}

void game_draw(context* c, game* g)
{
    check(gtype->is_loaded == true);
    gtype->draw(arg);
}

void game_draw_rule(context* c, game* g, rule* r)
{
    check(gtype->is_loaded == true);
    gtype->draw_rule(arg, r);
}

game_mutable* game_internal_mutable_clone(game_mutable* mut)
{
    game_mutable* copy = create(game_mutable);
    copy->nb_turn = mut->nb_turn;
    copy->draw_dest = mut->draw_dest;
    copy->current_ordi_output = tab_clone(copy->current_ordi_output);
    copy->current_ordi = entity_clone(mut->current_ordi);
    copy->nb_turn = mut->nb_turn;
    copy->state = mut->state;
    return copy;
}



game* game_clone(context* c, game* g)
{
    check(gtype->is_loaded == true);
    game* copy = create(game);
    copy->type = gtype;
    copy->immutable_state = g->immutable_state;
    copy->draw_state = null; // don't care
    copy->internal_mutable_state = game_internal_mutable_clone(g->internal_mutable_state);
    copy->mutable_state = gtype->clone_mutable(arg);
    return copy;
}

void game_get_player_input(context* c, game* g, entity* e)
{
    check(gtype->is_loaded == true);
    gtype->player_input(arg, e);
}

bool game_rule_match(context* c, game* g, entity* e, rule* r)
{
    check(gtype->is_loaded == true);
    return gtype->rule_match(arg, e, r);
}