#include "base.h"



#define gtype  (g->type)
// internal mutable state
#undef  mstate
#define mstate (g->internal_mutable_state)
#define arg game_arg_create(c, g)
#define cur_entity (g->internal_mutable_state->current_entity)
#define entity_per_gen (gtype->nb_behavior)
#define best_entity (mstate->best_ordi)
#define gen (mstate->generation)
#define gen_length (gen->length)

#define gen_idx_training          (mstate->generation_idx_training)
#define gen_current_idx_nb_update (mstate->generation_current_idx_nb_update)
#define gen_max_update_per_entity     (mstate->generation_update_per_entity)
#define gen_current_entity (gen_idx_training < gen_length ? gen_get(gen_idx_training) : null)

#define gen_delta_score (mstate->gen_delta_score)


#define game_state (mstate->state)
#define gen_get(idx) gen_get_at(g, idx)


entity* gen_get_at(game* g, int idx)
{
    return vec_get(gen, entity*, idx);
}

void gen_set(game* g, int idx, entity* e_will_be_copied)
{
    entity* old = gen_get_at(g, idx);
    entity* copy = entity_clone(e_will_be_copied);
    vec_set(gen, entity*, idx, copy);
    entity_free(old);
}

bool replace_best_entity_if_needed(context* c, game* g, entity* e)
{
    //return false;
    unused(c);
    if(e->type != ENTITY_TYPE_ORDI) return false;

    if(((best_entity == null) || (e->score > best_entity->score)) && (e != best_entity))
    {

        if(best_entity != null)
        {
            float old_score = best_entity->score;
            entity_free(best_entity);
            gen_delta_score += e->score - old_score;
        }
        best_entity = entity_clone(e);
        
        entity_behavior_set(cur_entity, entity_behavior(e));
        
        //float score = cur_entity->score;
        //entity_free(cur_entity);
        //cur_entity = entity_clone(best_entity);
        //cur_entity->score = score;

        return true;
    }
    return false;
}

void game_choose_next_generation(context* c, game* g)
{
    gen_delta_score -= 1/200.0f;
    if(gen_delta_score < 0)
    {
        repeat(i, gen_length)
        {
            entity* e = gen_get(i);
            rule* r = rule_create(g);
            behavior_add_rule(entity_behavior(e), r);
            rule_free(r);
            //printf("%i\n", e->behavior->rules->length);
        }
        gen_delta_score = 100;
    }



    g->internal_mutable_state->nb_generation++;
    gen_idx_training = 0;
    gen_current_idx_nb_update = 0;
    //current_entity = null;
    //return;

    repeat(i, gen_length)
    {
        if(replace_best_entity_if_needed(c, g, gen_get(i)))
        {
            //entity_printf(g, gen_get(i));
        }
    }

    // full random
    repeat(i, gen_length)
    {
        entity_init_random(g, gen_get(i));
    }

    /*
    entity* first = gen_get(0);
    vec_remove_at(gen, 0);
    entity_free(first);*/
    //entity* first = gen_get(0);
    //entity_free(first);
    //vec_set(gen, entity*, 0, entity_clone(best_entity));

    //return;
    gen_set(g, 0, best_entity);
}



void import_best_entity(context* c, game* g)
{
    unused(c);
    file* f = game_get_save_file(g, "r");

    if(f == null) 
    { 
        printf("import failed, no file\n");
        return;
    }

    entity* e = game_import_one_entity(g, f);
    if(e != null)
    {
        printf("import succeed\n");
        vec_add(gen, entity*, e);
    }else
    {
        printf("import failed, entity null\n");
    }
    fclose(f);
}

void game_init_training_if_needed(context* c, game* g)
{
    unused(c);
    
    check(entity_per_gen >= 2);

    // call game_ordi_configure before init training
    check(mstate->input != null);

    if(gen != null) return;

    gen = vec_empty(entity*);

    import_best_entity(c,g);
    repeat(i, entity_per_gen)
    {
        vec_add(gen, entity*, entity_create_ordi_random(g));
    }

    //if(mstate->input == null)
    //a

    gen_idx_training = 0;
    gen_current_idx_nb_update = 0;
    // hardcoder
    gen_max_update_per_entity = 128;
    gen_delta_score = 4;
}


void game_unload_copy(context* c, game* g)
{
    unused(c);

    gtype->unload_mutable(arg);
    free(g->mutable_state);
    //current_entity = null;
    game_internal_mutable_free(g->internal_mutable_state);
    free(g);
}


void update_current_entity(context* c, game* g)
{
    unused(c);

    //current_entity = entity_clone(gen_current_entity);
    //current_entity->score = 0;
    game* copy = game_clone(c, g);

    copy->internal_mutable_state->current_entity = gen_current_entity;
    game_reset(c, copy);

    gen_current_idx_nb_update = 0;
    while(gen_current_idx_nb_update < gen_max_update_per_entity && copy->internal_mutable_state->state == GAME_STATE_RUNNING)
    {
        tab_clear(copy->internal_mutable_state->input, 0);
        game_update_fixed(c, copy);
        gen_current_idx_nb_update++;
    }
    copy->internal_mutable_state->current_entity = null;
    game_unload_copy(c, copy);
    gen_idx_training++;
}


// train the generation, and choose the best
void game_train_best_ordi(context* c, game* g)
{
    //return;
    game_init_training_if_needed(c, g);

    repeat(i, 100)
    {
        update_current_entity(c, g);
        if(gen_current_entity == null)
        {
            game_choose_next_generation(c, g);
        }
    }

    unused(c);
    unused(g);
}

void game_trainning_printf(context* c, game* g)
{
    unused(c);
    printf("\n");
    if(mstate->nb_generation == 0)
    {
        printf("generation 0\n");
    }else
    {
        printf("generation %i (%i/%i entities evaluated = %.0f %%), total %i entities\n", mstate->nb_generation, gen_idx_training, entity_per_gen, gen_idx_training/(float)entity_per_gen, mstate->nb_generation*entity_per_gen+gen_idx_training);

    }
    printf("best entity :\n");
    entity_printf(g, best_entity);
    printf("\n");
}