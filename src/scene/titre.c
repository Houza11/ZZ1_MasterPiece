#include "base.h"

typedef struct 
{
   int dummy;
}state;

void scene_titre_load(argument arg)
{
    obtenir_scene_state;
}

void scene_titre_unload(argument arg) 
{ 
    obtenir_scene_state;
}

void scene_titre_update(argument arg) 
{ 
    obtenir_scene_state;
}

void scene_titre_draw(argument arg)
{
    obtenir_scene_state;
    pen_text_at_center(c, "title", window_width(c)/2, window_height(c)/2, FONT_SIZE_NORMAL, 0.5, 0.5);
}

bool scene_titre_event (argument arg) 
{ 
    obtenir_scene_state;
    return false;
}

void scene_titre_printf(argument arg)
{
    obtenir_scene_state;
    printf("Titre \n");
}