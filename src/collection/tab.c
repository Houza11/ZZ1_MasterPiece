#include "base.h"

int  tab_get(tab* t, int idx) { return vec_get(t, tab_type, idx);}
void tab_set(tab* t, int idx, int val) { vec_set(t, tab_type, idx, val); }
int  tab_length(tab* t) { return t->length; }
void tab_clear(tab* t, int val) { repeat(i, tab_length(t)) { tab_set(t, i, val); } }
int  tab_first_value(tab* t) { return tab_get(t, 0);}


tab* tab_create_one_value(int val)
{
    return tab_create(1, val);
}
tab* tab_create(int size, int default_val)
{
    check(size >= 0);
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
    return vec_clone(t);
}

void tab_printf(tab* t)
{
    printf("[");
    if(tab_length(t) == 0) { printf("]"); return;}
    int i = 0;
    goto debut;
    while(i < tab_length(t))
    {
        printf(", ");
        debut:
        printf("%i", tab_get(t, i));
        i++;
    }
    printf("]");
}

void tab_printf_custom(tab* t, things_to_char_fn get_char)
{
    printf("[");
    if(tab_length(t) == 0) { printf("]"); return;}
    repeat(i, tab_length(t))
    {
        printf("%c", get_char(tab_get(t, i)));

    }
    printf("]");
}