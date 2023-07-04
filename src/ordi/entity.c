#include "base.h"


rule* rule_create(game* g)
{
    return rule_create_with_size(g->type->condition_input_size, g->type->condition_output_size);
}

rule* rule_create_with_size(int size_input, int size_ouput)
{
    rule* r = create(rule);
    r->input  = tab_create(size_input, 0);
    r->output = tab_create(size_ouput, 0);
    return r;
}

void rule_free(rule* r)
{
    tab_free(r->input);
    tab_free(r->output);
    free(r);
}

rule* rule_clone(rule* r)
{
    rule* copy = create(rule);
    copy->input  = tab_clone(r->input);
    copy->output = tab_clone(r->output);
    copy->draw_dest = r->draw_dest;
    return copy;
}

void rule_printf(game* g, rule* r)
{
    rule_printf_custom(r, g->type->input_to_char, g->type->output_to_char);
}

void rule_printf_custom(rule* r, things_to_char_fn input, things_to_char_fn output)
{
    tab_printf_custom(r->input,  input);
    printf(" => ");
    tab_printf_custom(r->output, output);
    printf("\n");
}




behavior* behavior_empty()
{
    behavior* b = create(behavior);
    b->rules = vec_empty(rule*);
    return b;
}

int behavior_nb_rule(behavior* b)
{
    return b->rules->length;
}

behavior* behavior_clone(behavior* b)
{
    behavior* copy = behavior_empty();
    repeat(i, behavior_nb_rule(b))
    {
        behavior_add_rule(copy, behavior_get_rule(b, i));
    }
    return copy;
}

rule* behavior_get_rule(behavior* b, int idx)
{
    check(idx >= 0 && idx < behavior_nb_rule(b));
    return vec_get(b->rules, rule*, idx);
}
void behavior_set_rule(behavior* b, int idx, rule* r_will_be_copied)
{
    check(idx >= 0 && idx < behavior_nb_rule(b));
    rule* r2free = behavior_get_rule(b, idx);
    rule_free(r2free);
    rule* r = rule_clone(r_will_be_copied);
    vec_set(b->rules, rule*, idx, r);
}

void behavior_free(behavior* b)
{
    repeat(i, behavior_nb_rule(b))
    {
        rule_free(behavior_get_rule(b, i));
    }
    vec_free_lazy(b->rules);
    b->rules = null;
    free(b);
}

void behavior_insert_rule(behavior* b, int idx, rule* r_will_be_copied)
{
    check(idx >= 0 && idx <= behavior_nb_rule(b));
    rule* r = rule_clone(r_will_be_copied);
    vec_insert(b->rules, rule*, idx, r);
}
void behavior_remove_rule(behavior* b, int idx)
{
    check(idx >= 0 && idx < behavior_nb_rule(b));
    rule* r = behavior_get_rule(b, idx);
    vec_remove_at(b->rules, idx);
    rule_free(r);
}

void behavior_add_rule(behavior* b, rule* r_will_be_copied)
{
    vec_add(b->rules, rule*, rule_clone(r_will_be_copied));
    //behavior_set_rule(b, behavior_nb_rule(b)-1, r_will_be_copied);
}
void behavior_printf(game* g, behavior* b)
{
    printf("behavior: {\n");
    repeat(i, behavior_nb_rule(b))
    {
        printf("   r%i  ", i);
        rule_printf(g, behavior_get_rule(b, i));
    }
    printf("}\n");
}


void entity_init_random(game* g, entity* e)
{
    repeat(i, behavior_nb_rule(entity_behavior(e)))
    {
        rule* r = behavior_get_rule(entity_behavior(e), i);
        repeat(j, tab_length(r->input))
        {
            tab_set(r->input, j, rand()% g->type->condition_input_max_range);
        }
        repeat(j, tab_length(r->output))
        {
            tab_set(r->output, j, rand()% g->type->condition_output_max_range);
        }
    }
    e->score = 0;
}

entity* entity_create_ordi_random(game* g)
{
    behavior* b = behavior_empty();
    rule* r_default = rule_create(g);

    repeat(i, 1)
    {
        behavior_add_rule(b, r_default);
    }

    entity* result = entity_create(ENTITY_TYPE_ORDI, b);
    behavior_free(b);
    rule_free(r_default);
    entity_init_random(g, result);
    return result;
}

entity* entity_create(entity_type type, behavior* b_will_be_cloned)
{
    entity* e = create(entity);
    e->id = 0;
    e->type = type;
    e->score = 0;
    e->_behavior = behavior_clone(b_will_be_cloned);
    return e;
}

behavior* entity_behavior(entity* e)
{
    return e->_behavior;
}

void entity_behavior_set(entity* e, behavior* b_will_be_cloned)
{
    behavior_free(e->_behavior);
    e->_behavior = behavior_clone(b_will_be_cloned);
}

void entity_free(entity* e)
{
    if(e == null) return;
    behavior_free(e->_behavior);
    free(e);
}

entity* entity_clone(entity* e)
{
    entity* copy = entity_create(e->type, e->_behavior);
    copy->score = e->score;
    copy->id = e->id;
    copy->_behavior = behavior_clone(e->_behavior);
    return copy;
}
void entity_printf(game* g, entity* e)
{
    if(e == null) 
    {
        printf("entity null\n");
        return;
    }
    printf("entity %s with score %.3f\n", e->type == ENTITY_TYPE_PLAYER ? "player" : "ordi", e->score);
    behavior_printf(g, entity_behavior(e));
}