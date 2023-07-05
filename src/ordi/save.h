#ifndef SAVE_H
#define SAVE_H
#include "base.h"

file* game_get_save_file(game* g, char* mode);
void game_export_one_entity(game* g, file* f, entity* e);
entity* game_import_one_entity(game* g, file* f);
#endif