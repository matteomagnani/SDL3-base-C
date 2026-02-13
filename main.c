#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#define LOGICAL_WIDTH 1920
#define LOGICAL_HEIGHT 1080

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} AppState;


// 1. Init SDL
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) return SDL_APP_FAILURE;

    AppState *as = SDL_calloc(1, sizeof(AppState));
    *appstate = as;

    as->window = SDL_CreateWindow("KitTheGame", 1280, 720, SDL_WINDOW_RESIZABLE);
    as->renderer = SDL_CreateRenderer(as->window, NULL);

    SDL_SetRenderLogicalPresentation(as->renderer, LOGICAL_WIDTH, LOGICAL_HEIGHT,
                                     SDL_LOGICAL_PRESENTATION_LETTERBOX);

    return SDL_APP_CONTINUE;
}

// 2. Handle events
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    AppState *as = appstate;
    if (event->type == SDL_EVENT_QUIT) return SDL_APP_SUCCESS;

    return SDL_APP_CONTINUE;
}

// 3. LOOP
SDL_AppResult SDL_AppIterate(void *appstate) {

    AppState *as = appstate;

    // Clear Screen (Dark background)
    SDL_SetRenderDrawColor(as->renderer, 90, 90, 90, 255);
    SDL_RenderClear(as->renderer);

    // SDL_Event event;
    // while (SDL_PollEvent(&event)) {
    //     SDL_Log("Event received: %d\n", event.type);
    // }

    return SDL_APP_CONTINUE;
}

// 4. Handle Quit
void SDL_AppQuit(void *appstate, SDL_AppResult result) {

    if (appstate) {
        AppState *as = appstate;

        if (as->renderer) SDL_DestroyRenderer(as->renderer);
        if (as->window) SDL_DestroyWindow(as->window);
        SDL_free(as);
    }
}
