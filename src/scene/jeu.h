#ifndef SCENE_JEU_H
#define SCENE_JEU_H
#include "base.h"

void scene_jeu_load  (argument arg);
void scene_jeu_unload(argument arg);

void scene_jeu_update(argument arg);
void scene_jeu_draw  (argument arg);

bool scene_jeu_event (argument arg);
void scene_jeu_printf(argument arg);

#endif