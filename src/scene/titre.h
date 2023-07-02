#ifndef SCENE_TITRE_H
#define SCENE_TITRE_H
#include "base.h"

void scene_titre_load  (argument arg);
void scene_titre_unload(argument arg);

void scene_titre_update(argument arg);
void scene_titre_draw  (argument arg);

bool scene_titre_event (argument arg);
void scene_titre_printf(argument arg);

#endif