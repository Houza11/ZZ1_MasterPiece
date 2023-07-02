#include "base.h"

int  tab_get(tab* t, int idx) { return vec_get(t, int, idx);}
void tab_set(tab* t, int idx, int val) { vec_set(t, int, idx, val); }
int  tab_length(tab* t) { return t->length; }
void tab_clear(tab* t, int val) { repeat(i, tab_length(t)) { tab_set(t, i, val); } }

tab* tab_create_one_value(int val)
{
    return tab_create(1, val);
}
tab* tab_create(int size, int default_val)
{
    tab* t = vec_empty(int);
    repeat(i, size)
    {
        vec_push(t, int, default_val);
    }
    return t;
}