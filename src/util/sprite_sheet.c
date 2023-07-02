#include "base.h"

sprite_sheet* sprite_sheet_create(context* c, char* path, int w, int h)
{
    sprite_sheet* ss = create(sprite_sheet);
    ss->t = texture_create(c, path);
    int nb_frame = texture_width(ss->t)/w;

    ss->frame_count = nb_frame;
    ss->frame_width = w;
    ss->frame_height = h;

    ss->frames = create_array(rect, nb_frame);
    repeat(i, nb_frame)
    {
        ss->frames[i] = rectangle(i*w, 0, w, h);
    }
    return ss;
}


void sprite_sheet_free(sprite_sheet* s)
{
    free(s->frames);
    texture_free(s->t);
    free(s);
}