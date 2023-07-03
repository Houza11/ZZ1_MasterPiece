#ifndef GAME_OBSTACLE
#define GAME_OBSTACLE
#include "base.h"

typedef struct pattern
{
    int duration;
    obstacle** data;
} pattern;

int pattern_add(game_arg arg, int id_pattern);

#endif