#include "base.h"

file* game_get_save_file(game* g, char* mode)
{
    char* name = (char*)calloc(128, sizeof(char));
    char* after = name;
    after = strcpy(after, "/save/");
    after = strcpy(after, g->type->name);
    after = strcpy(after, ".txt");
    printf("import/export entity from %s : ", name);
    file* f = fopen(name, mode);
    free(name);

    return f;
}

void game_export_one_entity(game* g, file* f, entity* e)
{
    unused(g);
    unused(f);
    unused(e);

    //rule* r = null;
    todo;
}
entity* game_import_one_entity(game* g, file* f)
{
    unused(g);
    unused(f);
    todo;
    return null;
}