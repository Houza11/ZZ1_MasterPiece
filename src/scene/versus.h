#ifndef SCENE_VERSUS_H
#define SCENE_VERSUS_H
#include "base.h"

void scene_versus_load  (argument arg);
void scene_versus_unload(argument arg);

void scene_versus_update(argument arg);
void scene_versus_draw  (argument arg);

bool scene_versus_event (argument arg);
void scene_versus_printf(argument arg);

#endif