#include "base.h"
//#include "threads.h"

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
    entity* copy = entity_clone(g, e_will_be_copied);
    vec_set(gen, entity*, idx, copy);
    entity_free(g, old);
}

#define rng_pourcent(pourcentage) ((rand() % RAND_MAX) <= ((pourcentage/100.0f)*RAND_MAX))
#define rng_one (((float)(rand() % RAND_MAX))/RAND_MAX)
#define rng_p (rng_one * 100.0f)


bool replace_best_entity_if_needed(context* c, game* g, entity* e)
{
    //return false;
    unused(c);
    if(e->type != ENTITY_TYPE_ORDI) return false;

    /*
    if(
        (e != best_entity) && 
        ((best_entity == null) ||
        ((e->score > best_entity->score) || 
          (e->score >= best_entity->score && e->behavior->rules->length <= (best_entity->behavior->rules->length+2) && rng_pourcent(30) && (mstate->nb_generation % 10 == 0)
          )))
        )
    */
    //if((e != best_entity) && ((best_entity == null) || ((e->score > best_entity->score) || (e->score >= best_entity->score && ((rand()%100)<=64)))))
    //if((e != best_entity) && ((best_entity == null) || ((e->score > best_entity->score) || (e->score >= best_entity->score && ((rand()%100)<=64) && (e->behavior->rules->length < 2+best_entity->behavior->rules->length)))))
    
    
    if(
        (e != best_entity) && 
        ((best_entity == null) ||
        ((e->score > best_entity->score) || 
         (e->score >= best_entity->score && e->behavior->rules->length <= (best_entity->behavior->rules->length+2) && rng_pourcent(30)) || // && (mstate->nb_generation % 10 == 0)) ||
         (e->score >= best_entity->score && e->behavior->extra_score > best_entity->behavior->extra_score)
        ))
       )
    {
        if(best_entity != null)
        {
            float old_score = best_entity->score;
            entity_free(g, best_entity);
            gen_delta_score += e->score - old_score;
        }
        best_entity = entity_clone(g, e);
        
        entity_behavior_set(g, cur_entity, entity_behavior(e));
        //float score = cur_entity->score;
        //entity_free(cur_entity);
        //cur_entity = entity_clone(best_entity);
        //cur_entity->score = score;

        return true;
    }
    return false;
}

void game_glouton(context* c, game* g, vec* next_gen, entity* best, int nb_modif)
{
    unused(nb_modif);
    unused(c);
    behavior* b = best->behavior;

    /*
    nb_modif %= 3;
    nb_modif--;

    if(nb_modif < 0)
    {
        return;
    }*/

    //if(nb_modif == 0)
    {
        repeat(r_idx, behavior_nb_rule(b))
        {   
            rule* r = behavior_get_rule(b, r_idx);

            // input
            repeat(i, r->input->length)
            {   
                repeat(k, gtype->condition_input_max_range)
                {
                    entity* e = entity_clone(g, best);
                    rule* r_replace = behavior_get_rule(e->behavior, r_idx);
                    tab_set(r_replace->input, i, k);
                    vec_add(next_gen, entity*, e);
                }
            }

            // ouput
            repeat(i, r->output->length)
            {   
                repeat(k, gtype->condition_output_max_range)
                {
                    entity* e = entity_clone(g, best);
                    rule* r_replace = behavior_get_rule(e->behavior, r_idx);
                    tab_set(r_replace->output, i, k);
                    vec_add(next_gen, entity*, e);
                } 
            }
        }
        return;
    }


    //entity* e = game_glouton(c, g, next_gen, best,)
}




void rule_is_useless(context* c, game* g, behavior* b, rule* r)
{
    unused(c);
    /*
    if(rng_pourcent(10))
    {
        rule_randomize(g, r);
        return;
    }*/

    repeat(colonne_idx, gtype->condition_input_size)
    {
        int sum_colonne = behavior_sum_colonne(g, b, colonne_idx);
        if(sum_colonne == 0)
        {
            tab_set(r->input, colonne_idx, rand()% gtype->condition_input_max_range);
        }else
        {
            int symb = tab_get(r->input, colonne_idx);
            if(b->input_and_symbol_match[colonne_idx][symb] == 0)
            {
                int symb_replace;
                do
                {
                    symb_replace = rand()% gtype->condition_input_max_range;
                } while (b->input_and_symbol_match[colonne_idx][symb_replace] == 0);
                tab_set(r->input, colonne_idx, symb_replace);
            }
            /*
            float rng_number = rand()%RAND_MAX/(float)RAND_MAX;
            float sum_normalise = 0;

            int line_idx = 0;
            repeat(line_idx, gtype->condition_input_max_range)
            {
                 b->input_and_symbol_match[colonne_idx]
            }*/
        }

    }

    repeat(colonne_idx, gtype->condition_output_size)
    {
        if(rng_pourcent(5))
        {
            int output_symb = rand()% (gtype->condition_output_max_range);
            tab_set(r->output, colonne_idx, output_symb);
        }
    }

}

void add_rule(context* c, game* g, entity* e, behavior* b)
{
    unused(c);
    unused(e);

    rule* r = rule_create(g);
    rule_randomize(g, r);
    behavior_add_rule(b, r);
    rule_free(r);
}

void mutation_input(context* c, game* g, entity* e, behavior* b)
{
    unused(c);
    unused(e);
    unused(g);

    int r_idx = rand()%behavior_nb_rule(b);
    rule* r = behavior_get_rule(b, r_idx);

    int j = rand() % gtype->condition_input_size;
    tab_set(r->input, j, rand()%gtype->condition_input_max_range);
}

void mutation_output(context* c, game* g, entity* e, behavior* b)
{
    unused(c);
    unused(e);
    unused(g);
    int r_idx = rand()%behavior_nb_rule(b);
    rule* r = behavior_get_rule(b, r_idx);

    int j = rand() % gtype->condition_output_size;
    tab_set(r->output, j, rand() % gtype->condition_output_max_range);
}

void mutation(context* c, game* g, entity* e, behavior* b)
{
    unused(c);
    unused(e);
    unused(g);

    if(rng_pourcent(1) || rng_pourcent(gtype->condition_output_size)/(gtype->condition_input_size+gtype->condition_input_size))
    {
        mutation_output(c,g,e,b);
    }else
    {
        mutation_input(c,g,e,b);
    }
}

void rule_remove(context* c, game* g, entity* e, behavior* b)
{
    unused(c);
    unused(g);
    unused(e);

    if(behavior_nb_rule(b) <= 1) return;
    int j = rand()%b->rules->length;
    behavior_remove_rule(b, j);
}

void rule_swap(context* c, game* g, entity* e, behavior* b)
{
    unused(c);
    unused(g);
    unused(e);

    if(behavior_nb_rule(b) <= 1) return;
    int j = rand() % behavior_nb_rule(b);
    int k;
    do
    {
        k = rand() % behavior_nb_rule(b);
    }while(j == k);

    rule* rj = behavior_get_rule(b, j);
    rule* rk = behavior_get_rule(b, k);
    vec_set(b->rules, rule*, j, rk);
    vec_set(b->rules, rule*, k, rj);
}

void clone_rule(context* c, game* g, entity* e, behavior* b)
{
    unused(c);
    unused(g);
    unused(e);

    int j = rand()%b->rules->length;
    int idx = rand()%(b->rules->length+1);
    rule* r_clone = rule_clone(behavior_get_rule(b, j));
    vec_insert(b->rules, rule*, idx, r_clone);
}


#define apply_rng(luck, fn_call)\
if(rng <= luck)\
{\
    fn_call(c,g,e,b);\
    return;\
}\
rng -= luck;\

void one_changement_on_rule(context* c, game* g, entity* e, behavior* b)
{
    unused(c);

#define proba_rule_add    35
#define proba_rule_clone  10
#define proba_rule_swap   20
#define proba_rule_remove 10

    float proba_sum = proba_rule_add  + proba_rule_clone
                    + proba_rule_swap + proba_rule_remove;

    if(behavior_nb_rule(b) == 1)
    {
        proba_sum -= (proba_rule_swap+proba_rule_remove);
    }

    float rng = rng_one * proba_sum;

    apply_rng(proba_rule_add,    add_rule);
    apply_rng(proba_rule_clone,  clone_rule);
    apply_rng(proba_rule_remove, rule_remove);
    apply_rng(proba_rule_swap,   rule_swap);
}

/*
void one_changement(context* c, game* g, entity* e, behavior* b)
{
    float rng = rng_one;

#define proba_mutation 0.92f

    apply_rng(proba_mutation, mutation);

    return;
    // already quitted if apply_rng is true
    one_changement_on_rule(c,g,e,b);
}*/

void change_rule_if_useless(context* c, game* g, entity* e, behavior* b, int* r_idx_ptr)
{
    unused(c);
    unused(e);

    int r_idx = r_idx_ptr[0];

    rule* r = behavior_get_rule(b, r_idx);
    
    // la règles n'est jamais appliqué
    int r_nb_match = r->nb_match;
    if(r_nb_match == 0)
    {
        if(rng_pourcent(30) || behavior_nb_rule(b) <= 1)
        {
            rule_is_useless(c, g, b, r);
        }else
        {
            vec_remove_at(b->rules, r_idx);
            rule_free(r);
            r_idx_ptr[0]--;
        }
    }
}

int count_rule_useless(behavior* b)
{
    int total_rule_useless = 0;
    repeat(r_idx, behavior_nb_rule(b))
    {
        if(behavior_get_rule(b, r_idx)->nb_match == 0)
        {
            total_rule_useless++;
        }
    }
    return total_rule_useless;
}

void game_choose_next_generation(context* c, game* g)
{
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

    vec* next_gen = vec_empty(entity*);
    {
        // keep the best
        repeat(i, 30)
        {
            entity* e = entity_clone(g, best_entity);
            vec_add(next_gen, entity*, e);
        }
        // random from the last gen
        repeat(i, 30)
        {
            int j = rand()%gen->length;
            entity* e = entity_clone(g, gen_get(j));
            vec_add(next_gen, entity*, e);
        }

        // pure random
        repeat(i, 20)
        {
            int nb_rule;
            

            nb_rule = rand()%(best_entity->behavior->rules->length)+1+rand()%2;
            entity* rng = entity_create_ordi_random(g, nb_rule);
            vec_add(next_gen, entity*, rng);
        }
    }
    
    repeat(i, next_gen->length)
    {
        entity* e = vec_get(next_gen, entity*, i);
        behavior* b = e->behavior;

        int total_rule_useless = count_rule_useless(b);
        float active_rule_coef = 1-total_rule_useless / (float)behavior_nb_rule(b);
        // 1 : all rule can be active at some point
        // 0 : all rule are inactive

        repeat(r_idx, behavior_nb_rule(b))
        {
            change_rule_if_useless(c, g, e, b, &r_idx);
        }

        if(active_rule_coef <= 0.1) 
        {
            continue;
        }


        int nb_mut;
        if(rng_pourcent(90))
        {
            nb_mut = gtype->condition_input_size;
            nb_mut = (rand() % nb_mut)+1;
            nb_mut = (rand() % nb_mut);
        }else
        {
            nb_mut = rand()%(4+2*total_rule_useless);
        }

        repeat(i, nb_mut)
        {
            mutation(c,g,e,b);
        }

        nb_mut = 0;
        if(rng_pourcent(60))
        {
            int nb_mut = rand()%4;
            repeat(i, nb_mut)
            {
                one_changement_on_rule(c,g,e,b);
            }
        }


    }

    if(mstate->nb_generation % 70 == 0)
    {
        game_glouton(c, g, next_gen, best_entity, (mstate->nb_generation / 20));
    }
    
    repeat(i, gen_length)
    {
        entity_free(g, gen_get(i));
    }
    vec_free_lazy(gen);
    gen = next_gen;

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
        if (!g->internal_mutable_state->best_ordi) {entity_free(g, g->internal_mutable_state->best_ordi);}
        g->internal_mutable_state->best_ordi = entity_clone(g, e);
    }else
    {
        printf("import failed, entity null\n");
    }
    fclose(f);
    debug;
}

void load_best_entity(context* c, game* g)
{
    if(gen != null) return;

    gen = vec_empty(entity*);

    import_best_entity(c,g);
}

void game_init_training_if_needed(context* c, game* g)
{
    unused(c);
    
    check(entity_per_gen >= 2);

    // call game_ordi_configure before init training
    check(mstate->input != null);

    if(gen != null) return;

    load_best_entity(c,g);

    repeat(i, entity_per_gen)
    {
        vec_add(gen, entity*, entity_create_ordi_random(g, 1));
    }

    //if(mstate->input == null)
    //a

    gen_idx_training = 0;
    gen_current_idx_nb_update = 0;
    // hardcoder
    gen_max_update_per_entity = 256;
    gen_delta_score = 4;
    gtype->total_entities_generated = 0;
}


void game_unload_copy(context* c, game* g)
{
    unused(c);

    gtype->unload_mutable(arg);
    free(g->mutable_state);
    //current_entity = null;
    game_internal_mutable_free(g, g->internal_mutable_state);
    free(g);
}

void update_current_entity(context* c, game* g)
{
    unused(c);

    //current_entity = entity_clone(gen_current_entity);
    //current_entity->score = 0;
    game* copy = game_clone(c, g);


    copy->internal_mutable_state->current_entity = gen_current_entity;
    behavior* b = (gen_current_entity)->behavior;
    b->extra_score = 0;
    int nb_rule = b->rules->length;

    if(b->input_and_symbol_match == null)
    {
        b->input_and_symbol_match = create_array(int*, gtype->condition_input_size);
        repeat(i, gtype->condition_input_size)
        {
            b->input_and_symbol_match[i] = create_array(int, gtype->condition_input_max_range);
        }
    }

    repeat(i, gtype->condition_input_size)
    {
        repeat(j, gtype->condition_input_max_range)
        {
            b->input_and_symbol_match[i][j] = 0;
        }
    }
    repeat(i, nb_rule)
    {
        rule* r = behavior_get_rule(b, i);
        r->nb_match = 0;
    }
    game_reset(c, copy);

    gen_current_idx_nb_update = 0;
    while(gen_current_idx_nb_update < gen_max_update_per_entity && copy->internal_mutable_state->state == GAME_STATE_RUNNING)
    {
        tab_clear(copy->internal_mutable_state->input, 0);
        gtype->ordi_input_init(game_arg_create(c, g));
        game_update_fixed(c, copy);
        gen_current_idx_nb_update++;
    }


    int sum_active = 0;
    repeat(i, gtype->condition_input_size)
    {
        repeat(j, gtype->condition_input_max_range)
        {
            sum_active+=b->input_and_symbol_match[i][j];
        }
    }
    b->extra_score = sum_active;

    copy->internal_mutable_state->current_entity = null;
    game_unload_copy(c, copy);
    gen_idx_training++;
    gtype->total_entities_generated++;
}


// train the generation, and choose the best
void game_train_best_ordi(context* c, game* g)
{
    //return;
    game_init_training_if_needed(c, g);

    int nb_action = 0;

    while(current_tick() <= (c->update_tick_end- (time)from_ms(update_ms_budget*0.6)))
    {
        if(gen_current_entity == null)
        {
            if(nb_action == 0) 
            {
                game_choose_next_generation(c, g);
            }
            break;
            /*
            if(current_tick() <= (c->update_tick_end- (time)from_ms(update_ms_budget*0.2)))
            {
                
            }*/
        }else
        {
            update_current_entity(c, g);
        }
        nb_action++;
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
        printf("generation %i (%i/%i entities evaluated = %.0f %%), total %i entities\n", mstate->nb_generation, gen_idx_training, gen_length, gen_idx_training/(float)gen_length*100, gtype->total_entities_generated);
        //printf("generation %i (%i/%i entities evaluated = %.0f %%), total %i entities\n", mstate->nb_generation, gen_idx_training, entity_per_gen, gen_idx_training/(float)entity_per_gen, mstate->nb_generation*entity_per_gen+gen_idx_training);

    }
    printf("best entity :\n");
    entity_printf(g, best_entity);
    printf("\n");
}