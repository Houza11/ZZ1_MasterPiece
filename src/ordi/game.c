#include "../base.h"

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
    }
    return g;
}