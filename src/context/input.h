#ifndef INPUT_H
#define INPUT_H
#include "base.h"

#define pull_up_masked(newState, oldState, mask)      ( (  (newState)  & (mask) )  && (!((oldState) & (mask))) )
#define pull_down_masked(newState, oldState, mask)    ( (!((newState)  & (mask)))  && (  (oldState) & (mask) ) )
#define pull_changed_masked(newState, oldState, mask) ( (  (newState)  & (mask) )  != (  (oldState) & (mask) ) )

#define pull_up(newState, oldState)      (  (newState)  && (!(oldState)))
#define pull_down(newState, oldState)    ((!(newState)) &&   (oldState) )
#define pull_changed(newState, oldState) (( (newState)) !=   (oldState) )

#define is_key_pull_up(context, sdl_scan_code) todo
#define is_key_pull_down(context, sdl_scan_code) todo
#define is_key_pull_changed(context, sdl_scan_code) todo

// en partant du principe que la variable c contient le context
#define is_key_pull_up_with_context(sdl_scan_code) is_key_pull_up(c, sdl_scan_code)
#define is_key_pull_down_with_context(sdl_scan_code) is_key_pull_down(c, sdl_scan_code)
#define is_key_pull_changed_with_context(sdl_scan_code) is_key_pull_changed(c, sdl_scan_code)

#define is_key_pressed(newState)
#define is_key_pressed(newState)

int input_mouse_x(context* c);
int input_mouse_y(context* c);
int input_mouse_old_x(context* c);
int input_mouse_old_y(context* c);
int input_mouse_delta_x(context* c);
int input_mouse_delta_y(context* c);
int32 input_mouse_flag(context* c);
const Uint8* input_kb_state(context* c);

bool input_load(context* c);
void input_unload(context* c);
void input_update(context* c);
bool input_event(context* c, event* ev);

#endif