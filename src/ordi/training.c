#ifndef TRAINING_H
#define TRAINING_H
#include "base.h"

#define gtype  (g->type)
// internal mutable state
#undef  mstate
#define mstate (g->internal_mutable_state)
#define arg game_arg_create(c, g)
#define current_entity (g->internal_mutable_state->current_entity)


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

// train the generation, and choose the best
void game_train_best_ordi(context* c, game* g)
{
    printf("training ordi : generation %i\n", mstate->nb_generation);

    if(mstate->generation == null)
    {
        //mstate->generation = vec_empty(entity* e);
    }


    //todo;
    unused(c);
    unused(g);
}
#endif