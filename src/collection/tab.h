#ifndef TAB_H
#define TAB_H
#include "base.h"

#define tab_type uint8

 /* of tab_type */
typedef vec tab;
#define tab_as_array(_tab, _name) tab_type* _name = (tab_type*)((_tab)->values); int _name ## _size = (int)((_tab)->length);

int  tab_get(tab* t, int idx);
void tab_set(tab* t, int idx, int val);
int  tab_length(tab* t);
void tab_clear(tab* t, int val);
int  tab_first_value(tab* t);

tab* tab_create_one_value(int val);
tab* tab_create(int size, int default_val);
void tab_free(tab* t);

tab* tab_clone(tab* t);
void tab_printf(tab* t);

#endif