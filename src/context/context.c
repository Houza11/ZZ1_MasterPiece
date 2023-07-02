#include "base.h"

// void check_font_charged(TTF_Font* f)
// {
//     if (!f)
//     {
//         SDL_Log("Impossible d'ouvrir la police : %s\n", TTF_GetError());
//     }
// }

context* context_create(char* window_name, int width, int height, Uint32 flags)
{
    context* c = create(context);

    // todo better handling if failed (to unload previosuly loaded module)
    if(window_load(c, window_name, width, height, flags) == false) { return null; }
    if(camera_load(c) == false ) { return null; }
    if(pen_load(c) == false ) { return null; }
    if(scene_context_load(c) == false ) { return null; }
    if(input_load(c) == false ) { return null; }
    
    global_state_load(c);

    c->timer = 0;
    c->nb_update = 0;
    c->should_exit = false;
    twice(context_update(c););
    
    // //Charge la font sous différentes tailles 
    // c->font_small           = TTF_OpenFont(FONT_PATH, 20); check_font_charged(c->font_small);
    // c->font_medium          = TTF_OpenFont(FONT_PATH, 30); check_font_charged(c->font_medium);
    // c->font_big             = TTF_OpenFont(FONT_PATH, 50); check_font_charged(c->font_big);
    // c->font_fullscreen      = TTF_OpenFont(FONT_PATH, 70); check_font_charged(c->font_fullscreen);

    return c;
}


void contexte_free(context* c)
{
    // TTF_CloseFont(c->font_small);
    // TTF_CloseFont(c->font_medium);
    // TTF_CloseFont(c->font_big);
    // TTF_CloseFont(c->font_fullscreen);
    global_state_unload(c);
    scene_context_unload(c);
    pen_unload(c);
    camera_unload(c);
    window_unload(c);
    input_unload(c);
}

void context_update(context* c)
{
    window_update(c); // Oh shit, it's gonna take a loooong time...

    //printf("window %i %i, mouse %i %i\n", c->window_width, c->window_height, c->mouse_x, c->mouse_y);
    // todo faire/dépalcer le fichier input dans context ?

    c->timer = from_ms(SDL_GetTicks());
    c->nb_update++;

    SDL_Event ev;
    while(SDL_PollEvent(&ev))
    {
        if(ev.type == SDL_QUIT)
        {
            c->should_exit = true;
            continue;
        }

        if(input_event(c, &ev))  { continue; }
        if(global_state_event(c, &ev)) { continue; }
        
        switch (ev.type)
        {
            case SDL_KEYDOWN:
            case SDL_KEYUP:
            {
                switch (ev.key.keysym.sym)
                {
                    case SDLK_ESCAPE: c->should_exit = true; continue;
                    default: break;
                }
            } break;
            default: break;
        }
        if(scene_event(c, (scene*)(c->scene), &ev)) { continue; }
        if(camera_event(c, &ev)) { continue; }
    }

    input_update(c);
    camera_update(c);
    scene_update(c, (scene*)(c->scene));
    global_state_update(c);
}

void context_draw(context* c)
{
    c->pen_nb_rectangle = 0;
    scene_draw(c, (scene*)(c->scene));
    SDL_RenderPresent(c->renderer);
}

void context_should_exit_application(context* c, bool should_exit) { c->should_exit = should_exit; }
scene* context_get_current_scene(context* c) { return (scene*)c->scene; }
