#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <stdio.h>
#include <string>

enum KeyPressSurface {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL
};

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 760;

bool init();

bool loadMedia();

void close();

SDL_Surface *loadSurface(std::string path);

SDL_Window *gWindow = NULL;

SDL_Surface *gScreenSurface = NULL;

SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

SDL_Surface *gCurrentSurface = NULL;

int main(int argc, char *args[]) {
  if (init()) {
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] =
        SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
    SDL_FillRect(gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT], NULL,
                 SDL_MapRGB(gScreenSurface->format, 0x00, 0x00, 0x00));
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] =
        SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
    SDL_FillRect(gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN], NULL,
                 SDL_MapRGB(gScreenSurface->format, 0xFF, 0x00, 0x00));
    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] =
        SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
    SDL_FillRect(gKeyPressSurfaces[KEY_PRESS_SURFACE_UP], NULL,
                 SDL_MapRGB(gScreenSurface->format, 0x00, 0xFF, 0x00));
    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] =
        SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
    SDL_FillRect(gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT], NULL,
                 SDL_MapRGB(gScreenSurface->format, 0x00, 0x00, 0xFF));
    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] =
        SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
    SDL_FillRect(gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT], NULL,
                 SDL_MapRGB(gScreenSurface->format, 0xFF, 0x00, 0xFF));
    // gTestImage = loadSurface("image.jpg");

    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
    SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
    // SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);

    SDL_UpdateWindowSurface(gWindow);

    bool quit = false;

    SDL_Event e;
    while (!quit) {
      while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
          quit = true;
        } else if (e.type == SDL_KEYDOWN) {
          switch (e.key.keysym.sym) {
          case SDLK_UP:
            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
            break;
          case SDLK_LEFT:
            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
            break;
          case SDLK_RIGHT:
            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
            break;
          case SDLK_DOWN:
            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
            break;
          default:
            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
            break;
          }
        } else if (e.type == SDL_KEYUP) {
          gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
        }

        std::cout << gCurrentSurface << std::endl;
        SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);

        SDL_UpdateWindowSurface(gWindow);
      }
    }
  }

  close();

  return 0;
}

bool init() {
  bool success = true;

  if (success) {
    std::cout << "Test Stuff\n";
  }

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = false;
  } else {
    // Create window
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      success = false;
    } else {
      // Initialize PNG loading
      int imgFlags = IMG_INIT_PNG;
      if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n",
               IMG_GetError());
        success = false;
      } else {
        // Get window surface
        gScreenSurface = SDL_GetWindowSurface(gWindow);
      }
    }
  }

  return success;
}

void close() {
  SDL_FreeSurface(gCurrentSurface);
  gCurrentSurface = NULL;
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  SDL_Quit();
}

SDL_Surface *loadSurface(std::string path) {
  // The final optimized image
  SDL_Surface *optimizedSurface = NULL;

  // Load image at specified path
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == NULL) {
    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(),
           IMG_GetError());
  } else {
    // Convert surface to screen format
    optimizedSurface =
        SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
    if (optimizedSurface == NULL) {
      printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(),
             SDL_GetError());
    }

    // Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);
  }

  return optimizedSurface;
}
