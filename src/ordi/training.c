#include "base.h"

#define gtype  (g->type)
// internal mutable state
#undef  mstate
#define mstate (g->internal_mutable_state)
#define arg game_arg_create(c, g)
#define current_entity (g->internal_mutable_state->current_entity)
#define entity_per_gen (gtype->nb_behavior)

void game_choose_next_generation(context* c, game* g)
{
    unused(c);
    unused(g);
}

void game_replace_best_ordi(context* c, game* g)
{
    unused(c);
    unused(g);
}

void game_train_entity(context* c, game* g)
{
    unused(c);
    unused(g);
}

void game_init_training_if_needed(context* c, game* g)
{
    if(mstate->generation != null) return;

    /*
    mstate->generation = vec_empty(entity*);
    repeat(i, entity_per_gen)
    {
        //entity_create(ENTITY_TYPE_ORDI, )
        //entity_init_random()
    }
    */
}

// train the generation, and choose the best
void game_train_best_ordi(context* c, game* g)
{
    printf("training ordi : generation %i\n", mstate->nb_generation);
    /*
    game_init_training_if_needed();


    if(mstate->generation->length < gtype->nb_behavior)
    {
        //behavior* b
    }*/


    //todo;
    unused(c);
    unused(g);
}