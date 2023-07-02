#include "base.h"

// en ms. SDL_Tick
typedef Uint32 time;

typedef SDL_Texture texture;
typedef SDL_Vertex vertex;

typedef SDL_FRect rectf;
typedef SDL_Rect rect;

typedef SDL_Event event;

declare_struct(the_global_state);

declare_struct(rule);
declare_struct(game);
declare_struct(game_arg);
declare_struct(game_type);
declare_struct(game_mutable);

typedef int game_state;
typedef int entity_type;

declare_struct(rule);
declare_struct(behavior);
declare_struct(entity);

declare_struct(camera_state);