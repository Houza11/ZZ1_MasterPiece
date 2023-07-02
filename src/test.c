#include "base.h"

void testVec(){

    //vec* v = vec_empty(int);
    //vec_push(v, color, rgb(1,2,3));
    /*
    vec_push(v, int, 1);
    vec_push(v, int, 2);
    vec_printf_int(v);
    int val = vec_get(v, int, 0);*/
    //v->
    //vec_free_lazy(v);
}

void test_graph()
{
    //graph* g = graph_complet(6,1);
    //graph_printf(g);
    //graph_free(g);
}

void test_debug()
{
    test_graph();
        //SDL_Rect r = rectangle(0,10,2)
    //angle a = from_degree(180);
    //float degree = as_degree(a);
    //float rad = as_radian(a);
    //float cosinus = cos(a);
}

#if 0
void draw_triangle(context* c)
{
    //pen_triangle_colored(c, 10, 10, color_red, 10, 90, color_blue, 40, 60, color_green);
    //int delta = 200;
    //pen_triangle_colored(c, 10, 10, color_red, 10, 10+delta, color_blue, 10+delta/2, delta*2/3, color_black);
    

    float x = c->screen_width/4;
    float y = c->screen_height/2;
    float step = c->screen_height/8;

    
    pen_goto(c, x-step, y+step);
    pen_color(c, color_white);

    pen_down(c);
        pen_goto(c, x+step, y+step);
        pen_color(c, color_red);

        pen_goto(c, x+step, y-step);
        pen_color(c, color_black);

        pen_goto(c, x-step, y-step);
        pen_color(c, color_blue);

        pen_goto(c, x-step, y+step);
        pen_color(c, color_white);
    pen_up(c);

    pen_goto(c, 0, 0);
}
#endif

void draw_test(context*c )
{
    
        pen_mode(c, PEN_MODE_FILLED);
        //pen_color(c, color_white);
        pen_color(c, rgb(100, 30, 150));
        pen_clear(c);


        //float len = length(c->mouse_x, c->mouse_y, c->window_width/2, c->window_height/2);
        float lenX = abs(c->mouse_x-(float)c->window_width/2);
        float lenY = abs(c->mouse_y-(float)c->window_height/2);

        pen_color(c, rgb(255*c->mouse_x/(float)c->window_width, 255*c->mouse_y/(float)c->window_height, 127));
        pen_oval(c, c->window_width/4, c->window_height/2, lenX, lenY);

        pen_mode(c, PEN_MODE_HOLLOW);
        pen_color(c, hsv(360*lenX/(c->window_width/2), 1 , 1));
        pen_oval(c, c->window_width*3/4, c->window_height/2, lenY, lenX);



        pen_color(c, color_white);
        pen_line(c, c->window_width/2, c->window_height/2, c->mouse_x, c->mouse_y);

        //draw_triangle(c);
}