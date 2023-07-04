#ifndef GAME_OBSTACLE
#define GAME_OBSTACLE
#include "base.h"

int pattern_add(game_arg arg, int id_pattern);
void pattern_add_empty_line(game_arg arg);
void pattern_free(obstacle** p, int size);
#endif