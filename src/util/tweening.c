#include "base.h"

float lerpf(float ancienne_val, float nouvelle_val, float coef)
{
    return nouvelle_val*coef+ancienne_val*(1-coef);
}
float tweening_linear(float ancienne_val, float nouvelle_val, float coef)
{
    return lerpf(ancienne_val, nouvelle_val, coef);
}
float tweening_sqrt(float ancienne_val, float nouvelle_val, float coef)
{
    float delta = nouvelle_val-ancienne_val;
    return ancienne_val+delta*sqrt(coef);
}
float moyenne_ponderee(float val1, float val2, float coef_val_1)
{
    return lerpf(val2, val1, coef_val_1);
}