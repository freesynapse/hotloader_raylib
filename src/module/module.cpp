
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <raylib.h>
#include <raymath.h>

#include "module.h"

#include "log.h"
#include "raylib_utils.h"


#ifdef __cplusplus
extern "C" {
#endif

// called once on dll reload
void dll_init(renderer_state_t *state)
{
    // copy state and parameters from hotloader
    _copy_state(state);
    //SetExitKey(KEY_ESCAPE);

    // create a pixel buffer
    CreatePixelBuffer(w, h);
    memset(PIXELS, 0, PIXELS_SIZE);
    CreatePixelTexture(w, h);

    //
    TRACE_INFO("module.so initialized.\n");
}

// called once every frame, from ../loader_src/main.cpp
void dll_render_callback(float dt)
{
    BeginDrawing();

    ClearBackground(_bg_color);

    // update and render pixel array
    /*
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            int idx = j * w + i;
            PIXELS[idx] = px_t(255, 100, 0, 255);
        }
    }
    UpdatePixelTexture(PIXELS);
    DrawPixelTexture();
    */


    //
    DrawTextEx(state->font, _timer_text(dt), _v2_text_pos, state->font_size, 0.0f, WHITE);
    EndDrawing();
    _alive_time += dt;

}

// called on module shutdown
void dll_shutdown()
{
    ReleasePixelTexture();

}


#ifdef __cplusplus
}
#endif


