#ifndef ENTITY_H
#define ENTITY_H
#include "base.h"

struct rule
{
    tab*  input;
    tab*  output;
    rectf draw_dest;
};


rule* rule_create(game* g);
rule* rule_create_with_size(int size_input, int size_ouput);
void  rule_free(rule* r);
rule* rule_clone(rule* r);
void  rule_printf(rule* r);
void rule_printf_custom(rule* r, things_to_char_fn input, things_to_char_fn output);

struct behavior
{
    vec* /* rule* */ rules;
};

behavior* behavior_empty();
int   behavior_nb_rule(behavior* b);
rule* behavior_get_rule(behavior* b, int idx);
void  behavior_free(behavior* b);
behavior* behavior_clone(behavior* b);


void behavior_set_rule(behavior* b, int idx, rule* r_will_be_copied);
void behavior_insert_rule(behavior* b, int idx, rule* r_will_be_copied);
void behavior_add_rule(behavior* b, rule* r_will_be_copied);
void behavior_remove_rule(behavior* b, int idx);
void behavior_printf(behavior* b);

#define ENTITY_TYPE_PLAYER 0
#define ENTITY_TYPE_ORDI   1

struct entity
{
    int id;
    entity_type type;
    behavior* _behavior;
    float score;
};

entity* entity_create(entity_type type, behavior* b_will_be_cloned);
entity* entity_create_ordi_random(game* g);
entity* entity_clone(entity* e);
void entity_init_random(game* g, entity* e);
void entity_behavior_set(entity* e, behavior* b_will_be_cloned);
void entity_free(entity* e);
behavior* entity_behavior(entity* e);
void entity_printf(entity* e);
#endif