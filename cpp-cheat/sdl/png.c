/* https://stackoverflow.com/questions/4153055/how-to-load-jpg-png-textures-in-an-sdl-opengl-app-under-osx/41686559#41686559
 * https://gamedev.stackexchange.com/questions/59078/sdl-function-for-loading-pngs/135894#135894
 */

#include "common.h"

int main(void) {
    SDL_Event event;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;
    SDL_Window *window = NULL;

    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(
        COMMON_WINDOW_WIDTH, COMMON_WINDOW_WIDTH,
        0, &window, &renderer
    );
    IMG_Init(IMG_INIT_PNG);
    texture = IMG_LoadTexture(renderer, "flower.png");
    common_fps_init();
    while (1) {
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        common_fps_update_and_print();
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }
    SDL_DestroyTexture(texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
