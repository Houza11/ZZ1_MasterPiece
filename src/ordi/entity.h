#ifndef ENTITY_H
#define ENTITY_H
#include "base.h"

struct rule
{
    tab*  input;
    rectf draw_dest;
};

rule* rule_create(int size);
void  rule_free(rule* r);
rule* rule_clone(rule* r);
void rule_printf(rule* r);

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
entity* entity_clone(entity* e);
void entity_behavior_set(entity* e, behavior* b_will_be_cloned);
void entity_free(entity* e);
behavior* entity_behavior(entity* e);
void entity_printf(entity* e);
#endif