## Raylib hotloader

A framework for hotloading a shared library module for faster project iteration. On recompilation of the module, it is automatically reloaded. Loaded module functions are

```
void dll_init(renderer_state_t *state);
void dll_render_frame(float dt);
void dll_shutdown();
```

A Raylib window is opened by the hotloader (once), and each frame dll_render_frame(dt) is called. Raylib's stateless nature lends itself well to this method of hotloading.

### Build and execution
```
> make            # builds the hotloader
> make module     # builds example module
> ./hotloader src/module/module.so
```

