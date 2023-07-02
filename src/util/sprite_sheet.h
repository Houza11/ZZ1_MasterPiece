#ifndef SPRITESHEET_H
#define SPRITESHEET_H
#include "base.h"

typedef struct {
    texture* t;

    rect* frames;
    int frame_count;

    //taille d'une frame (constante)
    int frame_width;
    int frame_height;

    //taille de la texture totale
    //int texture_width;
    //int texture_height;
} sprite_sheet;


sprite_sheet* sprite_sheet_create(context* c, char* path, int w, int h);
void sprite_sheet_free(sprite_sheet* s);

#endif