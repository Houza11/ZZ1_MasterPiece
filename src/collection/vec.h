#ifndef VEC_H
#define VEC_H
#include "base.h"

typedef struct
{
    void* values;
    nuint sizeof_value;
    nuint max_capacity;
    int length;
} vec;

#define vec_index_valid_or_die(v, idx) check(vec_index_valid(v, idx));

// crash if outside of range
#define vec_get(v, type, idx) (((type*)v->values)[(vec_index_valid(v, (nuint)idx)) ? ((nuint)idx): ((nuint)-1)])
#define vec_set(v, type, idx, value) vec_get(v, type, idx) = value

#define vec_peek(v, type) (vec_get(v, type, v->length-1))
// pas sur que ça marche
//#define vec_pop(v, type)  (vec_get(v, type, --(v->length)))

#define reinterpret_cast(ptr_exp, type) (&ptr_exp)

#define vec_empty(type) (_vec_empty(sizeof(type)))
#define vec_with_capacity(type, capacity) (_vec_new_with_capacity(sizeof(type), capacity))

#define vec_push(v, type, element) vec_add(v, type, element)
#define vec_add(v, type, element)\
{\
    vec* __v = (v);\
    vec_resize_twice_if_needed(__v);\
    ((type*)__v->values)[__v->length++] = (element);\
}

#define vec_remove_end(v)\
{\
    vec* _v = (v);\
    check(_v->length >= 0);\
    _v->length--;\
    vec_shrink_if_needed(_v);\
}

//todo check index

#define vec_remove_at(v, idx)\
{\
    vec* _v = (v);\
    int _idx = (idx);\
    vec_index_valid_or_die(_v, _idx);\
    if(_idx+1 != _v->length)\
    {\
        vec_copy(_v, _v, (_idx+1)*_v->sizeof_value, (_v->length - _idx-1)*_v->sizeof_value, _idx*_v->sizeof_value);\
    }\
    _v->length--;\
    vec_shrink_if_needed(_v);\
}

#define vec_contains(v, type, value, bool_ptr_result) {vec_index_of(v,type,value, bool_ptr_result) != -1}
// would be cleaner with an expression statement, I'n not sure YJD will agree. -Mewily
#define vec_index_of(v, type, value, int_ptr_result)\
{\
    vec* _v = (v);\
    type _value = (value);\
    int _idx = -1;\
\
    repeat(_i, _v->length)\
    {\
        if(vec_get(_v, type, _i) == _value)\
        {\
            _idx = _i;\
            break;\
        }\
    }\
    *int_ptr_result = _idx;\
}

#define vec_insert(v, type, idx, value)\
{\
    vec* _v = (v);\
    int _idx = (idx);\
    type _value = (value);\
    vec_index_valid_or_die(_v, _idx);\
    vec_resize_twice_if_needed(_v);\
    vec_copy(_v, _v, _idx*_v->sizeof_value, (_v->length - _idx)*_v->sizeof_value, (_idx + 1)*_v->sizeof_value);\
    ((type*)_v->values)[_idx] = _value;\
    _v->length++;\
}

#define vec_plus(a, b, type, result_ptr)\
{\
    vec* _a = (a);\
    vec* _b = (b);\
    check(("vec_add() : Can't add a and b ", vec_identical_metadata(_a,_b)));\
    *result_ptr = _vec_new_with_capacity(_a->length);\
    repeat(_i, _a->length)\
    {\
        vec_set(*result_ptr, type, _i, vec_get(_a, type, _i) + vec_get(_b, type, _i));\
    }\
    _result;\
}

#define vec_fprintf_metadata(f,v)\
{\
    vec* _v = (v);\
    if(_v != null)\
    {\
        fprintf(f, #v" : vec of %i elements of %i bytes. (max capacity : %i) : ", _v->length, _v->sizeof_value, _v->max_capacity);\
    }else\
    {\
        fprintf(f, #v" : vec null");\
    }\
}

#define vec_printf_metadata(f,v) vec_fprintf_metadata(stdout, v)

#define vec_fprintf(f, v, type, format)\
{\
    vec* _v = (v);\
    vec_fprintf_metadata(f, v);\
    if(_v != null)\
    {\
        repeat(_i, _v->length)\
        {\
            fprintf(f, format, (type)vec_get(v, type, _i));\
        }\
    }\
    fprintf(f, "\n");\
}

#define vec_printf(v, type, format) /*LoL*/
//vec_fprintf(stdout, v, type, format)

vec* _vec_empty(nuint sizeof_type);
vec* _vec_new_with_capacity(nuint sizeof_type, nuint capacity);

void vec_free_lazy(vec* v);
void vec_set_capacity(vec* v, nuint capacity);
void vec_set_capacity_min(vec* v, nuint capacity);
void vec_resize_twice_if_needed(vec* v);
void vec_shrink_if_needed(vec* v);
vec* vec_clone(vec* v);
bool vec_index_valid(vec* v, nuint idx);
bool vec_equal(vec* a, vec* b);

bool vec_identical_metadata(vec* a, vec* b);

void vec_copy(vec* source, vec* destination, nuint sourceByteIdx, nuint sourceByteLength, nuint destinationByteIdx);
void vec_clear(vec* v);

#define vec_printf_int(v)   vec_printf(v, int, "%i, ");
#define vec_printf_float(v) vec_printf(v, float, "%f, ");
#define vec_printf_ptr(v)   vec_printf(v, void*, "%p, ");

#endif