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
    SDL_Log("Debut de l'export\n");
    if (!e) {SDL_Log("L'entite a sauvegarder est nulle.\n"); return;}
    if (e->type == ENTITY_TYPE_ORDI)
    {
        behavior* b = entity_behavior(e);
        fprintf(f, "~i%d~\n~o%d~\n~r%d~\n",
                g->type->condition_input_size,
                g->type->condition_output_size,
                b->rules->length);
        // printf("~i%d\n~o%d\n~r%d\n",
        //         g->type->condition_input_size,
        //         g->type->condition_output_size,
        //         b->rules->length);

        for (int i = 0; i < b->rules->length; i++)
        {
            rule* r = behavior_get_rule(b, i);
            for (int j = 0; j < g->type->condition_input_size; j++)
            {
                fprintf(f, "%d ",  tab_get(r->input, j));
                // printf("%d ", tab_get(r->input, j));
            }
            fprintf(f, "| ");
            // printf( "| ");
            
            for (int j = 0; j < g->type->condition_output_size; j++)
            {
                fprintf(f, "%d ", tab_get(r->output, j));
                // printf("%d ", tab_get(r->output, j));
            }

            fputc('\n', f);
            // printf("\n");
        }
        printf("export was successful\n");
    }
}

int scan_metadata(file* f)
{
    char line[20];
    char buffer[20];
    fgets(line, 19, f);
    if (line[0] == '~')
    {
        int i = 2;
        char c = line[i];
        int size = strlen(line);
        while(c != '~')
        {
            buffer[i-2] = c;
            i++;
            c = line[i];
            if (i >= size) {printf("Format de données incorrect\n"); return 0;}
        }
        buffer[i-2] = '\0';
        printf("buffer = |%s|\n", buffer);
        return atoi(buffer);
        
    }
    printf("Cette ligne ne contient pas de metadata !!!\n");
    return -1;
}

entity* game_import_one_entity(game* g, file* f)
{
    if (!f) {printf("Le fichier de l'entite a charger est nul\n"); return NULL;}
    printf("Debut de l'import\n");

    debug;
    int nb_input, nb_output, nb_rule;
    nb_input = scan_metadata(f);
    debug;
    nb_output = scan_metadata(f);
    debug;
    nb_rule = scan_metadata(f);
    debug;

    if(nb_input != g->type->condition_input_size || nb_output != g->type->condition_output_size)
    {
        printf("Le nombre d'i/o du fichier a cherher ne correspond pas\n");
        return null;
    }
    int line_size = nb_input * 2 + nb_output * 2 + 2 + 100;
    char* line = create_array(char, line_size);
    behavior* b = behavior_empty();
    debug;
    for (int i = 0; i < nb_rule; i++)
    {
        rule* r = rule_create_with_size(nb_input, nb_output);
    
        fgets(line, line_size, f);
        int j;
        for (j = 0; j < nb_input; j++)
        {
            char c = line[j*2];
            // printf("regle %d input %d val %c\n", i, j, c);
            tab_set(r->input, j, c- '0');
        }
        int k = 0;
        for (j=j+1; j < nb_output + nb_input + 1; j++)
        {
            char c = line[j*2];
            // printf("regle %d output %d val %c\n", i, k, c);
            tab_set(r->output, k, c- '0');
            k++;
        }
        vec_add(b->rules, rule*, r);
        debug;
    }
    debug;
    free(line); 
    entity* e = entity_create(ENTITY_TYPE_ORDI, b);
    behavior_free(b);
    printf("Fin de l'import\n");
    debug;
    return e;
}