#ifndef TEXTURE_H
#define TEXTURE_H
#include "base.h"

int texture_width(texture* t);
int texture_height(texture* t);

texture* texture_create(context* c, char *path);
void texture_free(texture* t);

rect texture_rect(texture* t);
rectf texture_rectf(texture* t);


#endif