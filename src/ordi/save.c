#include "base.h"
#define SAVE_PATH "save/eggsave.sus"

file* game_get_save_file(game* g, char* mode)
{
    char name[512];
    sprintf(name, "./save/%s_in_%i_%i_out_%i_%i.txt", g->type->name, g->type->condition_input_size, g->type->condition_input_max_range, g->type->condition_output_size, g->type->condition_output_max_range);
    printf("import/export entity from %s : ", name);
    file* f = fopen(name, mode);
    perror("");
    return f;
}

// int int_nb_digit(int x)
// {
//     char buffer[8];
//     sprintf(buffer, "%d", x);
//     return strlen(buffer);
// }

void game_export_one_entity(game* g, file* f, entity* e)
{
    if (!e) {SDL_Log("L'entite a sauvegarder est nulle.\n"); return;}
    if (e->type == ENTITY_TYPE_PLAYER)
    {
        behavior* b = entity_behavior(e);
        fprintf(f, "~i%d\n~o%d\n~r%d\n",
                g->type->condition_input_size,
                g->type->condition_output_size,
                b->rules->length);


        for (int i = 0; i < b->rules->length; i++)
        {
            rule r = vec_get(b->rules, rule, i);
            for (int j = 0; j < g->type->condition_input_size; j++)
            {
                fprintf(f, "%d ", tab_get(r.input, j));
            }
            fprintf(f, "| ");
            
            for (int j = 0; j < g->type->condition_output_size; j++)
            {
                fprintf(f, "%d ", tab_get(r.output, j));
            }

            fputc('\n', f);
        }
    }
}

int scan_metadata(file* f)
{
    char line[128];
    char buffer[128];
    fgets(line, 19, f);
    if (line[0] == '~')
    {
        int size = strlen(line) - 1;
        for (int i = 2; i < size; i++)
        {
            buffer[i] = line[i];
        }
        return atoi(buffer);
    }
    printf("Cette ligne ne contient pas de metadata !!!\n");
    return -1;
}

entity* game_import_one_entity(game* g, file* f)
{
    if (!f) {printf("Le fichier de l'entite a charger est nul\n"); return NULL;}
    int nb_input, nb_output, nb_rule;
    nb_input = scan_metadata(f);
    nb_output = scan_metadata(f);
    nb_rule = scan_metadata(f);

    if(nb_input != g->type->condition_input_size || nb_output != g->type->condition_output_size)
    {
        return null;
    }

    int line_size = nb_input * 2 + nb_output * 2 + 2 + 1;
    char* line = create_array(char, line_size);
    behavior* b = behavior_empty();
    for (int i = 0; i < nb_rule; i++)
    {
        rule* r = rule_create_with_size(nb_input, nb_output);
        fgets(line, line_size, f);
        int j;
        for (j = 0; j < nb_input; j++)
        {
            char c = line[j*2];
            vec_add( r->input, int, c - '0');
        }

        for (j=j+2; j < nb_output + nb_input + 2; j++)
        {
            char c = line[j*2];
            vec_add( r->output, int, c - '0');
        }
        vec_add(b->rules, rule*, r);
    }

    free(line);
    fclose(f);   
    entity* e = entity_create(ENTITY_TYPE_ORDI, b);
    behavior_free(b);
    return e;
}