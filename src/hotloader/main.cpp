#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/sendfile.h>

#include <raylib.h>

#include "utils.h"
#include "backtrace.h"
#include "types.h"
#include "dll.h"

//#include "raylib_utils.h"

//
int main(int argc, char *argv[])
{
    const char *program = argv[0];

    if (argc < 2) {
        printf("Usage: %s <module.so>\n", program); 
        TRACE_ERROR_NO_FNC("no input module provided.\n");
    }

    const char *dll_filepath = argv[1];

    // register signal handler
    struct sigaction sa;
    sa.sa_sigaction = signal_handler;
    sa.sa_flags = SA_RESTART | SA_SIGINFO;
    if (sigaction(SIGSEGV, &sa, (struct sigaction *)NULL) != 0)
        fprintf(stderr, "ERROR: could not set signal handler for %d (%s)", SIGSEGV, strsignal(SIGSEGV));

    // load DLL
    DLLWrapper dll = DLLWrapper(dll_filepath);
    dll.addSymbol("dll_init");
    dll.addSymbol("dll_render_callback");
    dll.addSymbol("dll_shutdown");
    dll.reload();

    // raylib init
    SetTraceLogLevel(4);
    InitWindow(_width, _height, "raylib hotloader (module.so)");
    TRACE_INFO("raylib loaded.\n");
    //SetWindowState(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED);
    SetWindowState(FLAG_WINDOW_TOPMOST | FLAG_WINDOW_UNDECORATED);
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
    renderer_state_t state;
    state.font = LoadFont("./assets/JetBrainsMono-Medium.ttf");
    state.font_size = 20.0f;
    state.display_handle = GetCurrentMonitor();
    state.dim = { (float)GetMonitorWidth(state.display_handle) / 2, 
                  (float)GetMonitorHeight(state.display_handle) / 2 };
    state.pos = { state.dim.x, 0 };

    SetWindowSize((int)state.dim.x, (int)state.dim.y);
    SetWindowPosition((int)state.pos.x, (int)state.pos.y);
    dll.call<dll_init_ptr>("dll_init", &state);    


    // main event loop
    uint64_t frameCount = 0;
    while (!WindowShouldClose())
    {
        // auto reload DLL (if needed)
        if (dll.reload() == true) {
    		printf("\033[H\033[J"); // clearing terminal on reload
            TRACE_INFO("DLL '%s' reloaded.\n", dll.filename());
            dll.call<dll_init_ptr>("dll_init", &state);
        }
        
        // exit
        if (IsKeyPressed(KEY_W) && (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)))
            break;

        // toggle fullscreen
        if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)))
        {
            if (IsWindowFullscreen())
            {
                SetWindowSize((int)state.dim.x, (int)state.dim.y);
                SetWindowPosition((int)state.pos.x, (int)state.pos.y);
            }
            else
                SetWindowSize(GetMonitorWidth(state.display_handle), GetMonitorHeight(state.display_handle));
            
            ToggleFullscreen();
        }

        // call into DLL render function using set pointer
        dll.call<dll_render_ptr>("dll_render_callback", GetFrameTime());
        frameCount++;
    }

    //
    CloseWindow();
    TRACE_INFO("closed raylib window.\n");

    return 0;
}



