#include "base.h"
#define tab_size(t) (sizeof(t)/sizeof(t[0]))

void egg_pattern_free(obstacle** p, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(p[i]);
    }
    free(p);
}

void egg_copy_pattern(game_arg arg, obstacle p[][egg_nb_ligne], int size)
{
    for (int i = 0; i < size; i++)
    {
        vec* line = vec_empty(obstacle);
        for (int j = 0; j < egg_nb_ligne; j++)
        {
            int a = p[i][j];
            // if (a < 0) { a = 0;}
            vec_push(line, obstacle, a);
        }
        egg_grid_push_colonne(arg, line);
    }
    
}


#define NB_PATTERN 19
#define pattern(number, pattern_name) case number: pattern_shift_match_exits(arg, pattern_name, number, tab_size(pattern_name)); return tab_size(pattern_name);
#define pattern_create(name) obstacle name[][egg_nb_ligne]

void egg_pattern_add_empty_line(game_arg arg)
{
    pattern_create(a) = {
        {-2,-2,-2,-2,-2}
    };

    egg_copy_pattern(arg, a, tab_size(a));
}


int pattern_shift_match_exits(game_arg arg, obstacle p[][egg_nb_ligne], int pattern_ID, int size)
{
    get_game_state(egg);

    obstacle exits[egg_nb_ligne];
    for (int i = 0; i < egg_nb_ligne; i++)
    {
        exits[i] = egg_grid_get(arg, i, egg_grid->length -1);
    }
    
    
    //clone p
    obstacle** shifted_pattern = create_array(obstacle*, size);
    for (int i = 0; i < size; i++)
    {
        shifted_pattern[i] = create_array(obstacle, egg_nb_ligne);
    }
    

    //cherche une entrée et une sortie aléatoire
    int mark_entry = -1;
    int mark_exit  = -1;
    
    for (int i = 0; i < 30; i++)
    {
        mark_entry = rand()%egg_nb_ligne;
        if (p[0][mark_entry] == EGG_OBSTACLE_ENTRY) { break; }
    }
    if (p[0][mark_entry] != EGG_OBSTACLE_ENTRY) {SDL_Log("Impossible de trouver une entrée pour le pattern %d\n", pattern_ID); return 0;}
    
    for (int i = 0; i < 30; i++)
    {
        mark_exit = rand()%egg_nb_ligne;
        if (exits[mark_exit] == EGG_OBSTACLE_EXIT) { break; }
    }
    if (exits[mark_exit] != EGG_OBSTACLE_EXIT) {SDL_Log("Impossible de trouver une sortie pour le pattern %d\n", pattern_ID); debug; return 0;}




    int shift = mark_entry - mark_exit;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < egg_nb_ligne; j++)
        {
            shifted_pattern[i][j] = p[i][ (j+shift + egg_nb_ligne)%egg_nb_ligne ];
        }
    }
    for (int i = 0; i < size; i++)
    {
        vec* line = vec_empty(obstacle);
        for (int j = 0; j < egg_nb_ligne; j++)
        {
            int a = shifted_pattern[i][j];
            vec_push(line, obstacle, a);
        }
        egg_grid_push_colonne(arg, line);
    }
    egg_pattern_free(shifted_pattern, size);
    return 0;
}

void pattern_free(obstacle** p, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(p[i]);
    }
    free(p);
}

int egg_pattern_add(game_arg arg, int id_pattern)
{
    //Liste des patterns
    pattern_create(a) = {
        {-1,-1,-1,-1,-1},
        { 1, 0, 1, 0, 0},
        { 0, 1, 0, 1, 0},
        { 0, 1, 0, 0, 0},
        { 1, 0, 0, 0, 0},
        {-2,-2,-2,-2,-2}
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
        { 1, 1, 1, 0, 0},
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

    pattern_create(f) = {
        {-1,-1,-1,-1,-1},
        { 0, 0, 0, 0, 0},
        { 0, 1, 0, 0, 0},
        { 1, 1, 0, 1, 0},
        { 1, 1, 0, 1, 0},
        { 0, 1, 1, 1, 0},
        {-2,-2, 0,-2,-2}
    };
    pattern_create(g) = {
        {-1,-1,-1,-1,-1},
        { 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0},
        { 1, 0, 1, 0, 1},
        { 0, 1, 0, 1, 0},
        { 0, 1, 1, 1, 0},
        {-2,-2, 0,-2,-2}
    };
    pattern_create(h) = {
        {-1,-1,-1,-1,-1},
        { 0, 0, 0, 0, 0},
        { 1, 0, 1, 0, 0},
        { 1, 0, 1, 0, 1},
        { 1, 0, 1, 1, 0},
        { 1, 1, 1, 0, 1},
        { 1, 1,-2,-2,-2}
    };
    
    pattern_create(i) = {
        {-1, 1,-1, 1,-1},
        { 1, 0, 1, 0, 1},
        { 0, 1, 0, 1, 0},
        {-2,-2,-2,-2,-2}
    };
    pattern_create(j) = {
        {-1,-1,-1,-1,-1},
        { 0, 1, 1, 1, 1},
        { 0, 0, 0, 0, 0},
        { 0, 1, 0, 1, 0},
        { 1, 1, 0, 1, 1},
        { 1,-2,-2,-2, 0}
    };
    pattern_create(k) = {
        {-1,-1,-1,-1,-1},
        { 0, 0, 0, 0, 0},
        { 1, 0, 1, 0, 0},
        { 1, 0, 1, 0, 1},
        { 1, 0, 1, 1, 0},
        { 0, 1, 1, 1, 1},
        {-2,-2, 0, 1, 1}
    };
    pattern_create(l) = {
        { 1,-1,-1,-1, 1},
        { 1, 1, 0, 1, 1},
        { 1, 1, 0, 1, 1},
        { 1, 1, 0, 1, 1},
        { 1,-2,-2,-2, 1}
    };
    pattern_create(m) = {
        { 1,-1,-1,-1, 1},
        { 1, 1, 0, 1, 1},
        { 1, 1, 0, 1, 1},
        { 1, 0, 1, 0, 1},
        { 0, 1, 1, 0, 1},
        { 1, 1, 0, 1, 0},
        { 0, 1, 0, 1, 1},
        { 1, 0, 0, 1, 1},
        { 1, 1, 0, 1, 1},
        { 1,-2,-2,-2, 1}
    };
    pattern_create(n) = {
        {-1,-1,-1,-1,-1},
        { 0, 1, 0, 0, 1},
        { 1, 1, 0, 1, 0},
        {-2,-2,-2,-2,-2}
    };
    
    pattern_create(o) = {
        { 1, 1, 1, 1,-1},
        { 1, 1, 1, 0, 1},
        { 1, 1, 0, 1, 1},
        { 1, 0, 1, 1, 1},
        {-2, 1, 1, 1, 1}
    };
    
    pattern_create(p) = {
        { 0, 0, 1, 1,-1},
        { 0, 1, 1, 0, 1},
        { 1, 1, 0, 1, 1},
        { 1, 0, 1, 1, 0},
        {-2, 1, 1, 0, 0}
    };
    pattern_create(q) = {
        {-1, 1, 1, 0, 0},
        { 1, 0, 1, 1, 0},
        { 1, 1, 0, 1, 1},
        { 0, 1, 1, 0, 1},
        { 0, 0, 1, 1,-2}
    };
    pattern_create(r) = {
        { 0,-1,-1,-1, 0},
        { 0, 1, 0, 1, 1},
        { 0, 1, 0, 0, 1},
        { 0, 1, 0, 0, 1},
        { 1, 1, 1,-2, 1}
    };
    pattern_create(z) = {
        {-1,-1,-1,-1,-1},
        { 0, 0, 0, 0, 0},
        {-2,-2,-2,-2,-2}
    };
    if (id_pattern < 0) 
    { 
        id_pattern = rand() % NB_PATTERN;
    }
    switch (id_pattern)
    {
        
        pattern(0, a);
        pattern(1, b);
        pattern(2, c);
        pattern(3, d);
        pattern(4, e);
        pattern(5, f);
        pattern(6, g);
        pattern(7, h);
        pattern(8, i);
        pattern(9, j);
        pattern(10,k);
        pattern(11,l);
        pattern(12,m);
        pattern(13,n);
        pattern(14,o);
        pattern(15,p);
        pattern(16,q);
        pattern(17,r);
        pattern(18,z);
        default: return 0;
    }
}