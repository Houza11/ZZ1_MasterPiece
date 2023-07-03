#include "base.h"


void copy_pattern(game_arg arg, obstacle p[][EGG_NB_LIGNE], int size)
{
    for (int i = 0; i < size; i++)
    {
        vec* line = vec_empty(obstacle);
        for (int j = 0; j < EGG_NB_LIGNE; j++)
        {
            vec_push(line, obstacle, p[i][j]);
        }
        grid_push_colonne(arg, line);
    }
    
}


#define NB_PATTERN 2
#define pattern(number, pattern_name) case number: copy_pattern(arg, pattern_name, tab_size(pattern_name)); return tab_size(pattern_name);
#define tab_size(t) (sizeof(t)/sizeof(t[0]))
#define pattern_create(name) obstacle name[][EGG_NB_LIGNE]

int pattern_add(game_arg arg, int id_pattern)
{
    //Liste des patterns
    pattern_create(a) = {
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };
    pattern_create(b) = {
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,1,1},
        {0,0,1,1,1},
        {0,1,0,1,1}
    };

    if (id_pattern < 0) { id_pattern = rand()%NB_PATTERN; }
    switch (id_pattern)
    {
        pattern(0, a);
        pattern(1, b);
        default: return 0;
    }
}