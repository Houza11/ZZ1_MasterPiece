#ifndef ANIMSPRITE_H
#define ANIMSPRITE_H
#include "base.h"

typedef struct{
    sprite_sheet* sprite_sheet;
    time frame_duration; //temps d'une image en millisecondes
    int first_frame;
    int last_frame;
    int nb_frame;
    bool loop;
} anim;
typedef anim animation;

#define create_animation animation_create 
anim* animation_create(sprite_sheet* sprite_sheet, time frame_duration);

#define free_animation animation_free 
void animation_free(animation* a);

int animation_width(animation* a);
int animation_height(animation* a);

rect* animation_get_frame(animation* a, time t);


#endif