#include "base.h"



void copy_pattern(game_arg arg, obstacle p[][EGG_NB_LIGNE], int size)
{
    for (int i = 0; i < size; i++)
    {
        vec* line = vec_empty(obstacle);
        for (int j = 0; j < EGG_NB_LIGNE; j++)
        {
            int a = p[i][j];
            if (a < 0) { a = 0;}
            vec_push(line, obstacle, a);
        }
        grid_push_colonne(arg, line);
    }
    
}


#define NB_PATTERN 5
#define pattern(number, pattern_name) case number: copy_pattern(arg, pattern_name, tab_size(pattern_name)); return tab_size(pattern_name);
#define tab_size(t) (sizeof(t)/sizeof(t[0]))
#define pattern_create(name) obstacle name[][EGG_NB_LIGNE]

int pattern_add(game_arg arg, int id_pattern)
{
    //Liste des patterns
    pattern_create(a) = {
        { 0, 0, 0, 0, 0}
    };
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
    };

    if (id_pattern < 0) { id_pattern = rand()%NB_PATTERN; }
    switch (id_pattern)
    {
        pattern(0, a);
        pattern(1, b);
        pattern(2, c);
        pattern(3, d);
        pattern(4, e);
        default: return 0;
    }
}

obstacle** pattern_shift_match_exits(obstacle** p, obstacle* exits, int pattern_ID)
{
    int size = tab_size(p);
    
    //clone p
    obstacle** shifted_pattern = create_array(obstacle*, size);
    for (int i = 0; i < size; i++)
    {
        shifted_pattern[i] = create_array(obstacle, EGG_NB_LIGNE);
    }
    

    //cherche une entrée et une sortie aléatoire
    int mark_entry = -1;
    int mark_exit  = -1;
    // for (int i = 0; i < EGG_NB_LIGNE; i++)
    // {
    //     if (p[0][i] == -1)
    //     {
    //         mark_entry = mark_entry == -1 ? 
    //                      i                :
    //                      (mark_entry = rand()%EGG_NB_LIGNE == 1 ? //Proba 1/5
    //                                    mark_entry               :
    //                                    i);
    //     }

    //     if (exits[i] == -2)
    //     {
    //         mark_exit = mark_exit == -1 ? 
    //                     i               :
    //                     (mark_exit = rand()%EGG_NB_LIGNE == 1 ? //Proba 1/5
    //                                   mark_exit               :
    //                                   i);
    //     }
    // }
    for (int i = 0; i < 30; i++)
    {
        mark_entry = rand()%EGG_NB_LIGNE;
        if (p[0][mark_entry] == EGG_OBSTACLE_ENTRY) { break; }
    }
    if (p[0][mark_entry] != EGG_OBSTACLE_ENTRY) {SDL_Log("Impossible de trouver une entrée pour le pattern %d\n", pattern_ID);return NULL;}
    
    for (int i = 0; i < 30; i++)
    {
        mark_exit = rand()%EGG_NB_LIGNE;
        if (exits[mark_exit] == EGG_OBSTACLE_EXIT) { break; }
    }
    if (exits[mark_entry] != EGG_OBSTACLE_EXIT) {SDL_Log("Impossible de trouver une sortie pour le pattern %d\n", pattern_ID);return NULL;}




    int shift = mark_entry - mark_exit;
    if (shift)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < EGG_NB_LIGNE; j++)
            {
                shifted_pattern[i][j] = p[i][ (j+shift + EGG_NB_LIGNE)%EGG_NB_LIGNE ];
            }
        }
    }
    return shifted_pattern;
    
    
}