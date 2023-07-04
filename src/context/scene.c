#include "base.h"
scene* scene_create_arg(char name[scene_name_max_length], scene_fn load, scene_fn unload, scene_fn update, scene_fn draw, scene_fn_event event, scene_fn printf, int32 flags)
{
    scene* sce = create(scene);
    scene_info* i = &sce->info;

    i->active = true;

    i->flags = flags;

    repeat(k, scene_name_max_length)
    {
        i->name[k] = name[k];
    }
    i->name[scene_name_max_length-1] = '\0'; // just to be sure

    i->load = load;
    i->unload = unload;
    i->update = update;
    i->draw = draw;
    i->event = event;
    i->printf = printf;

    i->is_loaded = false;

    sce->state = null;

    return sce;
}

#define get_argument argument_create(c, sce, null)
#define get_argument_with_event argument_create(c, sce, ev)

argument argument_create(context* arg_context, scene* arg_scene, event* arg_event)
{
    argument arg;
    arg.arg_context = arg_context;
    arg.arg_scene = arg_scene;
    arg.arg_event = arg_event;
    return arg;
}

void scene_unload(context* c, scene* sce)
{
    if(sce == null) return;

    if(sce->info.active) { scene_set_inactive(c, sce); }

    sce->info.unload(get_argument);
    free(sce->state);
    free(sce);
}

void scene_update(context* c, scene* sce)
{
    if(sce == null) return;
    sce->info.time = c->timer - sce->info.time_when_active;
    sce->info.update(get_argument);
}

void scene_draw(context* c, scene* sce)
{
    if(sce == null) return;
    /*
    color co = pen_get_color(c);

    pen_clear(c);
    pen_color(c, co);*/

    sce->info.draw(get_argument);
}

void scene_printf(context* c, scene* sce)
{
    if(sce == null) return;

    printf("global state printf :\n");
    global_state_printf(c);
    printf("scene %s printf:\n", sce->info.name);
    sce->info.printf(get_argument);

    printf("\n");
}

bool scene_event(context* c, scene* sce, event* ev)
{
    if(sce == null) return false;
    return sce->info.event(get_argument_with_event);
}

void scene_set_active(context* c, scene* sce)
{
    if(sce == null) { return;}
    if(sce->info.is_loaded == false)
    {
        /*
        if(((scene*)c->scene))
        {
            sce->info.background_color = ((scene*)c->scene)->info.background_color;
        }*/
        sce->info.is_loaded = true;
        sce->info.load(get_argument);
    }
    printf("scene %s active\n", sce->info.name);
    sce->info.active = true;
}

void scene_set_inactive(context* c, scene* sce)
{
    unused(c);
    if(sce == null) { return;}
    sce->info.active = false;
}

void scene_switch(context* c, scene* sce)
{
    scene_unload(c, c->scene);
    c->scene = sce;
    if(sce)
    {
        scene_set_active(c, sce);
        sce->info.time_when_active = c->timer;
    }
}

bool scene_context_load(context* c)
{
    c->scene = null;
    return true;
}
void scene_context_unload(context* c)
{
    scene_unload(c, (scene*)(c->scene));
}