#ifndef ENTITY_H
#define ENTITY_H
#include "../base.h"

struct rule
{
    tab*  input;
    rectf draw_dest;
};

struct behavior
{
    vec* /* rule */ rules;
};

#define ENTITY_TYPE_PLAYER 0
#define ENTITY_TYPE_ORDI   1

struct entity
{
    entity_type type;
    behavior behavior;
    float score;
};

#endif