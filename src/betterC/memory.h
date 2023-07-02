#ifndef MEMORY_H
#define MEMORY_H

#define calloc(nbBytes) ((calloc)(1,nbBytes))

#define create(type) (type*)malloc(sizeof(type))
#define create_array(type, nb) (type*)malloc(nb*sizeof(type))

/*
#define malloc(nbBytes) (malloc)(nbBytes)
#define calloc(nbBytes) (calloc)(nbBytes)
#define realloc(ptr, nbBytes) (realloc)(ptr, nbBytes)
*/
#endif