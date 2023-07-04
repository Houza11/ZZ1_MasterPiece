#include "base.h"
#define tab_size(t) (sizeof(t)/sizeof(t[0]))


void copy_pattern(game_arg arg, obstacle p[][egg_nb_ligne], int size)
{
    for (int i = 0; i < size; i++)
    {
        vec* line = vec_empty(obstacle);
        for (int j = 0; j < egg_nb_ligne; j++)
        {
            int a = p[i][j];
            if (a < 0) { a = 0;}
            vec_push(line, obstacle, a);
        }
        grid_push_colonne(arg, line);
    }
    
}


#define NB_PATTERN 6
#define pattern(number, pattern_name) case number: copy_pattern(arg, pattern_name, tab_size(pattern_name)); return tab_size(pattern_name);
#define tab_size(t) (sizeof(t)/sizeof(t[0]))
#define pattern_create(name) obstacle name[][egg_nb_ligne]

void pattern_add_empty_line(game_arg arg)
{
    pattern_create(a) = {
        { 0, 0, 0, 0, 0}
    };

    copy_pattern(arg, a, tab_size(a));
}

int pattern_add(game_arg arg, int id_pattern)
{
    //Liste des patterns
    pattern_create(a) = {
        { 0, 0, 0, 0, 0}
    };

    pattern_create(a0) = {
        { 1, 0, 0, 0, 0}
    };

    pattern_create(a1) = {
        { 0, 1, 0, 0, 0}
    };

    pattern_create(a2) = {
        { 0, 0, 1, 0, 0}
    };

    pattern_create(a3) = {
        { 0, 0, 0, 1, 0}
    };

    pattern_create(a4) = {
        { 0, 0, 0, 0, 1}
    };
    /*
    pattern_create(b) = {
        {-1, 1, 1, 1, 1},
        { 1, 0, 1, 1, 1},
        { 1, 1, 0, 1, 1},
        { 1, 1, 1, 0, 1},
        { 1, 1, 1, 1,-2}
    };
    pattern_create(c) = {
        { 1, 1,-1, 1, 1},
        { 0, 0, 0, 0, 0},
        { 1, 1, 1, 1, 0},
        { 0, 0, 0, 0, 0},
        { 1,-2, 1, 1, 1}
    };
    pattern_create(d) = {
        {-1,-1, 0, 0,-1},
        { 0, 1, 0, 0, 1},
        { 0, 1, 0, 0, 1},
        { 0, 1, 0, 0, 1},
        {-2, 1, 1, 1, 1}
    };
    pattern_create(e) = {
        {-1,-1,-1,-1,-1},
        { 0, 0, 1, 0, 0},
        { 0, 1, 0, 0, 0},
        { 0, 0, 0, 1, 0},
        {-2,-2,-2,-2,-2}
    };*/

    if (id_pattern < 0) { id_pattern = rand() % NB_PATTERN; }
    switch (id_pattern)
    {
        pattern(0, a);
        pattern(1, a0);
        pattern(2, a1);
        pattern(3, a2);
        pattern(4, a3);
        pattern(5, a4);
        //pattern(1, b);
        /*
        pattern(2, c);
        pattern(3, d);
        pattern(4, e);*/
        default: return 0;
    }
}