#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 760;

bool init();

bool loadMedia();

void close();

SDL_Surface *loadSurface(std::string path);

SDL_Window *gWindow = NULL;

SDL_Surface *gScreenSurface = NULL;

SDL_Surface *gTestImage = NULL;

int main(int argc, char *args[]) {
  if (init()) {
    SDL_FillRect(gScreenSurface, NULL,
                 SDL_MapRGB(gScreenSurface->format, 0xFF, 0xFF, 0xFF));
    gTestImage = loadSurface("image.jpg");

    SDL_BlitSurface(gTestImage, NULL, gScreenSurface, NULL);

    SDL_UpdateWindowSurface(gWindow);

    bool quit = false;

    SDL_Event e;
    while (!quit) {
      while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
          quit = true;
        }
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
  SDL_FreeSurface(gTestImage);
  gTestImage = NULL;
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
