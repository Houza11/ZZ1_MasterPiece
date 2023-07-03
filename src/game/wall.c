#include "base.h"


void copy_pattern(game_arg arg, obstacle** p, int size)
{
    for (int i = 0; i < size; i++)
    {
        
    }
    
}

#define NB_PATTERN 2
void add_pattern(game_arg arg)
{
    //Liste des patterns
    obstacle a[][5] = {
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    }; int a_size = 5;
    obstacle b[][5] = {
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    }; int b_size = 5;

    int rng = rand()%NB_PATTERN;
    switch (rng)
    {
    case 0:
        copy_pattern(arg, a, a_size);
    break;
    case 1:

    break;
    }
}