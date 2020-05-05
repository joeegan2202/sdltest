#include "sysload.h"
#include <iostream>

SDL_Texture *gTexture = NULL;

int main(int argc, char *args[]) {
  SDL_Rect scale;
  scale.x = SCREEN_WIDTH / 3;
  scale.y = SCREEN_HEIGHT / 3;
  scale.w = SCREEN_WIDTH / 3;
  scale.h = SCREEN_HEIGHT / 3;

  if (init()) {
    gTexture = loadTexture("image.jpg");

    bool quit = false;

    SDL_Event e;
    while (!quit) {
      while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
          quit = true;
        }
      }

      SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

      SDL_RenderClear(gRenderer);

      SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);

      SDL_Rect draw = {0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};

      SDL_RenderCopy(gRenderer, gTexture, NULL, &scale);
      SDL_RenderFillRect(gRenderer, &draw);

      SDL_RenderPresent(gRenderer);
    }
  }

  close();

  return 0;
}
