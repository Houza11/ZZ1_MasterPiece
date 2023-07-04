#ifndef CONTEXT_CAMERA_H
#define CONTEXT_CAMERA_H
#include "base.h"

camera_state camera_state_create(float x, float y, float scale_x, float scale_y, bool allow_scrolling, bool allow_zooming);
camera_state camera_default();
camera_state camera_get(context* c);
void camera_set(context* c, camera_state s);
void camera_push(context* c, camera_state state);
void camera_push_set(context* c, camera_state state);
rectf camera_push_focus_fullscreen(context* c, rectf source);
rectf camera_push_focus(context* c, rectf source, rectf dest);
rectf camera_push_focus_centered(context* c, rectf source, rectf dest, float center_x_coef, float center_y_coef);
void camera_pop(context* c);

bool camera_load(context* c);
void camera_unload(context* c);

void camera_update(context* c);

void camera_allow_zooming(context* c, bool b);
void camera_allow_scrolling(context* c, bool b);
bool camera_event(context* c, event* ev);

float camera_x(context* c);
float camera_y(context* c);
float camera_scale_x(context* c);
float camera_scale_y(context* c);

void camera_set_x(context* c, float v);
void camera_set_y(context* c, float v);
float camera_set_scale_x(context* c, float v);
float camera_set_scale_y(context* c, float v);

bool camera_can_zoom(context* c);
bool camera_can_scroll(context* c);

float camera_cam_pos_2_pixel_pos_x(context* c, float x);
float camera_cam_pos_2_pixel_pos_y(context* c, float y);

float camera_pixel_pos_2_cam_pos_x(context* c, float pos);
float camera_pixel_pos_2_cam_pos_y(context* c, float pos);
#endif