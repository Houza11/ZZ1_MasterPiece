#include "betterC.h"

#ifdef TRACK_MEMORY
int memory_nb_malloc_actif = 0;

void* memory_malloc(size_t nb_byte)
{
    if(nb_byte == 0) { return null;}
    void* ptr;
    do
    {
        ptr = (malloc)(nb_byte);
    }while(ptr == null);
    memory_nb_malloc_actif++;
    return ptr;
}

void* memory_calloc(size_t count, size_t size)
{
    size_t nb_byte = count*size;
    if(nb_byte == 0) { return null;}
    void* ptr;
    do
    {
        ptr = (calloc)(count, size);
    }while(ptr == null);
    memory_nb_malloc_actif++;
    return ptr;
}

void memory_free(void* ptr)
{
    if(ptr == null) return;
    memory_nb_malloc_actif--;
    (free)(ptr);
}

void* memory_realloc(void* ptr, size_t nb_byte)
{
    if(ptr == null) { return malloc(nb_byte); }
    if(nb_byte == 0) { free(ptr); }
    return (realloc)(ptr, nb_byte);
}
#endif

void memory_printf()
{
    #ifdef TRACK_MEMORY
    printf("memory : %i malloc actif\n\n", memory_nb_malloc_actif);
    #else
    printf("memory not tracked\n\n");
    #endif
}

int  memory_get_nb_alloc()
{
    #ifdef TRACK_MEMORY
    return memory_nb_malloc_actif;
    #else
    return -1;
    #endif
}