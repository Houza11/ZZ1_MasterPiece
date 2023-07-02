#ifndef CONTEXT_SCENE_H
#define CONTEXT_SCENE_H
#include "base.h"

#define scene_name_max_length 64

struct scene_struct;
typedef struct scene_struct scene;

typedef struct 
{
   context* arg_context;
   scene*   arg_scene;
   event*   arg_event;
}argument;

typedef void (*scene_fn)(argument);
typedef bool (*scene_fn_event)(argument);

argument argument_create(context* arg_context, scene* arg_scene, event* arg_event);
typedef struct
{
   int32 flags;
   time time;              // since the beginning of the scene
   time time_when_active;  // based on context.time

   bool active;
   bool is_loaded;
   char name[scene_name_max_length];

   scene_fn load;
   scene_fn unload;

   scene_fn update;
   scene_fn draw;

   // return a bool consumed
   scene_fn_event event;

   scene_fn printf;

} scene_info;

struct scene_struct
{
   scene_info info;
   void* state;
};

scene* scene_create_arg(char name[scene_name_max_length], scene_fn load, scene_fn unload, scene_fn update, scene_fn draw, scene_fn_event event, scene_fn printf, int32 flags);

void scene_unload(context* c, scene* sce);
void scene_update(context* c, scene* sce);
void scene_draw  (context* c, scene* sce);
bool scene_event (context* c, scene* sce, event* ev); // return a bool consumed
void scene_printf(context* c, scene* sce);

#define scene_create(name) scene_create_arg(#name "\0",  \
   scene_ ## name ## _load,  \
   scene_ ## name ## _unload,\
   scene_ ## name ## _update,\
   scene_ ## name ## _draw,  \
   scene_ ## name ## _event, \
   scene_ ## name ## _printf,\
   0\
)

void scene_switch(context* c, scene* sce);

void scene_set_active(context* c, scene* sce);
void scene_set_inactive(context* c, scene* sce);

#define scene_set(context, name) scene_switch(context, scene_create(name))

bool scene_context_load(context* c);
void scene_context_unload(context* c);

#endif