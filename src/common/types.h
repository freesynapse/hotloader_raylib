#ifndef __TYPES_H
#define __TYPES_H

#include "raylib.h"

// raylib defualt screen res
#define _width  1600
#define _height  900

// for passing state to the dynamic library
typedef struct
{
    Font font;
    float font_size;

    // window parameters
    int display_handle;
    Vector2 dim;
    Vector2 pos;

} renderer_state_t;

// func ptr typedef for dll function ptrs
typedef void (*dll_render_ptr)(float dt);
typedef void(*dll_init_ptr)(renderer_state_t *state);


#endif // __TYPES_H
