#include "base.h"

int texture_width(texture* t)
{
    if(t == null){ return 0;}
    SDL_Point size;
    SDL_QueryTexture(t, NULL, NULL, &size.x, &size.y);
    return size.x;
}

int texture_height(texture* t)
{
    if(t == null){ return 0;}
    SDL_Point size;
    SDL_QueryTexture(t, NULL, NULL, &size.x, &size.y);
    return size.y;
}

rect texture_rect(texture* t)
{
    if(t == null){ return rectangle(0,0,0,0);}
    SDL_Point size;
    SDL_QueryTexture(t, NULL, NULL, &size.x, &size.y);
    return rectangle(0,0, size.x, size.y);;
}

rectf texture_rectf(texture* t)
{
    if(t == null){ return rectanglef(0,0,0,0);}
    SDL_Point size;
    SDL_QueryTexture(t, NULL, NULL, &size.x, &size.y);
    return rectanglef(0,0, size.x, size.y);;
}


texture* texture_create(context* c, char *path)
{
    SDL_Surface *my_image = NULL;           // Variable de passage
    texture*     my_texture = NULL;         // La texture
    my_image = IMG_Load(path);              // Chargement de l'image dans la surface
                                            // image=SDL_LoadBMP(file_image_name); fonction standard de la SDL, 
                                            // uniquement possible si l'image est au format bmp */
    if (my_image == NULL) { printf("Impossible de charger l'image %s\n", path); return null; }
   
    my_texture = SDL_CreateTextureFromSurface(c->renderer, my_image); // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);   
                                         // la SDL_Surface ne sert que comme élément transitoire 
    if (my_texture == NULL)
    { 
        printf("Echec de la transformation de la surface %s en texture : %s\n", path, SDL_GetError());
        return null;
    }

    printf("texture %s chargée\n", path);

    return my_texture;
}

void texture_free(texture* t)
{
    SDL_DestroyTexture(t);
}
