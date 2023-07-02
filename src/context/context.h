#ifndef THE_CONTEXT_LOADER_H
#define THE_CONTEXT_LOADER_H
#include "base.h"

#define gs global_state
#define global_state (c->_global_state)

context* context_create(char* window_name, int width, int height, Uint32 flags);
void context_update(context* c);
void context_draw (context* c);
void contexte_free(context* c);

void context_should_exit_application(context* c, bool should_exit);
scene* context_get_current_scene(context* c);

#endif