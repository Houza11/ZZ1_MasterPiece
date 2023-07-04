#ifndef SAVE_H
#define SAVE_H
#include "base.h"

void game_export_one_entity(game* g, file* f, entity* e);
entity* game_import_one_entity(game* g, file* f);
#endif