#include "base.h"

int  tab_get(tab* t, int idx) { return vec_get(t, tab_type, idx);}
void tab_set(tab* t, int idx, int val) { vec_set(t, tab_type, idx, val); }
int  tab_length(tab* t) { return t->length; }
void tab_clear(tab* t, int val) { repeat(i, tab_length(t)) { tab_set(t, i, val); } }

tab* tab_create_one_value(int val)
{
    return tab_create(1, val);
}
tab* tab_create(int size, int default_val)
{
    tab* t = vec_empty(tab_type);
    repeat(i, size)
    {
        vec_push(t, tab_type, default_val);
    }
    return t;
}

void tab_free(tab* t)
{
    vec_free_lazy(t);
}

tab* tab_clone(tab* t)
{
    tab* copy = vec_empty(tab_type);
    repeat(i, tab_length(t))
    {
        tab_set(copy, i, tab_get(t, i));
    }
    return copy;
}

void tab_printf(tab* t)
{
    printf("[");
    if(tab_length(t) == 0) { printf("]\n"); return;}
    int i = 0;
    goto debut;
    while(i < tab_length(t))
    {
        printf(", ");
        i++;
        debut:
        printf("%i", tab_get(t, i));
    }
    printf("]\n");
}