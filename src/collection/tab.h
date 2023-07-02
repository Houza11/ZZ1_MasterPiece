#ifndef TAB_H
#define TAB_H
#include "base.h"

 /* of int*/
typedef vec tab;
#define tab_2_array_ptr(_tab, _name) int* _name = (int*)((_tab)->values); int _name ## _size = (int*)((_tab)->length);

int  tab_get(tab* t, int idx);
void tab_set(tab* t, int idx, int val);
int  tab_length(tab* t);
void tab_clear(tab* t, int val);

tab* tab_create_one_value(int val);
tab* tab_create(int size, int default_val);

#endif