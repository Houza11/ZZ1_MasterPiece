#include "base.h"

vec* _vec_empty(nuint sizeof_type)
{
    vec* v = create(vec);
    v->length = 0;
    v->max_capacity = 0;
    v->values = null;
    v->sizeof_value = sizeof_type;
    return v;
}

vec* _vec_new_with_capacity(nuint sizeof_type, nuint capacity)
{
    vec* v = create(vec);
    v->length = capacity;
    v->max_capacity = capacity;
    v->values = malloc(sizeof_type*capacity);
    v->sizeof_value = sizeof_type;
    return v;
}

void vec_free_lazy(vec* v)
{
    if(v == null) return;
    free(v->values);
    free(v);
}

void vec_set_capacity(vec* v, nuint capacity)
{
    v->values = (void*)realloc(v->values, capacity * v->sizeof_value);
    v->max_capacity = capacity;
}

void vec_set_capacity_min(vec* v, nuint capacity)
{
    if (capacity > v->max_capacity)
    {
        vec_set_capacity(v, capacity);
    }
}

void vec_resize_twice_if_needed(vec* v)
{
    if ((nuint)(v->length + 1) > v->max_capacity)
    {
        vec_set_capacity(v, v->max_capacity < 2 ? 2 : v->max_capacity * 2);
    }
}

void vec_shrink_if_needed(vec* v)
{
    if ((nuint)(v->length+4) <= v->max_capacity / 2)
    {
        vec_set_capacity(v, v->max_capacity / 2);
    }
}

vec* vec_clone(vec* v)
{
    if(v == null) { return null; }

    vec* result = create(vec);
    result->length = v->length;
    result->max_capacity = v->max_capacity;
    result->sizeof_value = v->sizeof_value;

    size_t nbByteToCopy = result->max_capacity*result->sizeof_value;
    result->values = malloc(nbByteToCopy);
    memcpy(result->values, v->values, nbByteToCopy);
    return result;
}

void vec_copy(vec* source, vec* destination, nuint sourceByteIdx, nuint sourceByteLength, nuint destinationByteIdx)
{
    if(destinationByteIdx+sourceByteLength > destination->max_capacity)
    {
        vec_set_capacity_min(destination, (destinationByteIdx+sourceByteLength)/destination->sizeof_value);
    }

    if((nuint)destination + (nuint)(destinationByteIdx) > (nuint)source + (nuint)sourceByteIdx)
    {
        for (nint i = sourceByteLength-1; i >= 0; i--)
        {
            ((byte*)destination->values)[destinationByteIdx + i] = ((char*)(source->values))[sourceByteIdx + i];
        }
    }else
    {
        for (nint i = 0; i < (nint)sourceByteLength; i++)
        {
            ((byte*)destination->values)[destinationByteIdx + i] = ((char*)(source->values))[sourceByteIdx + i];
        }
    }
}

bool vec_index_valid(vec* v, nuint idx) { return idx < (nuint)v->length; }

bool vec_equal(vec* a, vec* b)
{
    if(a->length != b->length || a->sizeof_value != b->sizeof_value) { return false; }

    if(a->values == b->values)
    {
        return true; // même adresse mémoire
    }

    return memcmp(a->values,b->values, a->length*a->sizeof_value) == 0;
}

bool vec_identical_metadata(vec* a, vec* b)
{
    return a->length == b->length && a->sizeof_value == b->sizeof_value;
}

void vec_clear(vec* v)
{
    v->length=0;
}