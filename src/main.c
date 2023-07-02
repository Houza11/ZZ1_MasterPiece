#include "base.h"
#include "test.h"


void sdl_load()
{
    srand(0);
    printf("Compilation de %s\n", current_time);
    SDL_version nb;
    SDL_VERSION(&nb);
    printf("Version de la SDL : %d.%d.%d\n", nb.major, nb.minor, nb.patch);

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Impossible d'initialiser la SDL\n");
        crash(SDL_GetError());
    }
}

void sdl_unload()
{
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *argv[])
{
    unused(argc); unused(argv);
    sdl_load();
    test_debug();


    context* c = context_create("Houzayfa M, Martin J, Thomas T. Version de " current_time, 960, 540, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    
    window_center_coef(c, 0.5, 0.5);


    //scene_set(c, jeu);
    scene_set(c, titre);


    while (!c->should_exit)
    {
        context_update(c);
        context_draw(c);
    }


    contexte_free(c);
    sdl_unload();

    memory_printf();

    return 0;
}