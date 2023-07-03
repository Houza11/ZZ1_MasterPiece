#include "base.h"


void copy_pattern(game_arg arg, obstacle p[][EGG_NB_LIGNE], int size)
{
    printf("%p\n", p);
    for (int i = 0; i < size; i++)
    {
        
        vec* line = vec_empty(obstacle);
        for (int j = 0; j < EGG_NB_LIGNE; j++)
        {
            printf("%i ", p[i][j]);
            debug;
            //vec_push(line, obstacle, p[i][j]);
        }
            debug;
printf("\n");
        
        grid_push_colonne(arg, line);
    }
    
}

#define NB_PATTERN 2
int pattern_add(game_arg arg, int id_pattern)
{
    //Liste des patterns
    obstacle a[][EGG_NB_LIGNE] = {
        {0,0,1,0,0},
        {0,0,5,0,0},
        {0,0,7,0,0},
        {0,3,0,0,4}
    }; int a_size = 4;
    #define tab_size(t) (sizeof(t)/sizeof(t[0]))
    printf("%d\n", a[0][2]);
    printf("%d\n", tab_size(a));
    obstacle b[][EGG_NB_LIGNE] = {
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    }; int b_size = 5;

    if (id_pattern < 0) { id_pattern = rand()%NB_PATTERN; }
    switch (id_pattern)
    {
    case 0:
        copy_pattern(arg, a, a_size);
        return a_size;
    case 1:
        copy_pattern(arg, b, b_size);
        return b_size;
    default: return 0;
    }
    
}