#ifndef ENTITY_H
#define ENTITY_H
#include "base.h"

struct rule
{
    tab*  input;
    tab*  output;
    rectf draw_dest;
    int   nb_match;
};


rule* rule_create(game* g);
rule* rule_create_with_size(int size_input, int size_ouput);
void  rule_free(rule* r);
rule* rule_clone(rule* r);
void  rule_printf(game* g, rule* r);
void rule_printf_custom(rule* r, things_to_char_fn input, things_to_char_fn output);
void rule_randomize(game* g, rule* r);
struct behavior
{
    vec* /* rule* */ rules;

    // count the nb time a given symbol is useful at a given positon in a rule
    // input_and_symbol_match[input_size][input_range]
    int** input_and_symbol_match;
    float extra_score; // using how many bit matched

    //int nb_turn_survive;
};

behavior* behavior_empty();
int   behavior_nb_rule(behavior* b);
rule* behavior_get_rule(behavior* b, int idx);
void behavior_free(game* g, behavior* b);
behavior* behavior_clone(game* g, behavior* b);
int behavior_sum_colonne(game* g, behavior* b, int column_idx);

void behavior_set_rule(behavior* b, int idx, rule* r_will_be_copied);
void behavior_insert_rule(behavior* b, int idx, rule* r_will_be_copied);
void behavior_add_rule(behavior* b, rule* r_will_be_copied);
void behavior_remove_rule(behavior* b, int idx);
void behavior_printf(game* g, behavior* b);

#define ENTITY_TYPE_PLAYER 0
#define ENTITY_TYPE_ORDI   1

struct entity
{
    int id;
    entity_type type;
    behavior* behavior;
    float score;
};

entity* entity_create(game* g, entity_type type, behavior* b_will_be_cloned);
entity* entity_create_ordi_random(game* g, int default_nb_rule);
entity* entity_clone(game* g, entity* e);
void entity_init_random(game* g, entity* e);
void entity_behavior_set(game* g, entity* e, behavior* b_will_be_cloned);
void entity_free(game* g, entity* e);
behavior* entity_behavior(entity* e);
void entity_printf(game* g, entity* e);
#endif