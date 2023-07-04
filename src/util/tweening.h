#ifndef TWEENING_H
#define TWEENING_H
#include "base.h"

float lerpf(float ancienne_val, float nouvelle_val, float coef);
float tweening_linear(float ancienne_val, float nouvelle_val, float coef);
float tweening_sqrt(float ancienne_val, float nouvelle_val, float coef);
float moyenne_ponderee(float val1, float val2, float coef_val_1);
#endif