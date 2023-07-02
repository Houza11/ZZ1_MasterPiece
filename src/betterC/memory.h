#ifndef MEMORY_H
#define MEMORY_H

//#define calloc(nbBytes) ((calloc)(1,nbBytes))

#define create(type) (type*)malloc(sizeof(type))
#define create_array(type, nb) (type*)malloc(nb*sizeof(type))

#define TRACK_MEMORY

#ifdef TRACK_MEMORY
#define malloc(nbBytes) memory_malloc(nbBytes)
#define calloc(count, size) memory_calloc(count, size)
#define realloc(ptr, nbBytes) memory_realloc(ptr, nbBytes)
#define free(ptr) memory_free(ptr)

void* memory_malloc(size_t nb_byte);
void* memory_calloc(size_t count_, size_t size);
void* memory_realloc(void* ptr, size_t nb_byte);
void  memory_free(void* ptr);
#endif

void memory_printf();
int  memory_get_nb_alloc();
#endif