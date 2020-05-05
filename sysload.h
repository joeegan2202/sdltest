#ifndef SYSLOAD_H
#define SYSLOAD_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>

enum KeyPressSurface {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL
};

const int SCREEN_HEIGHT = 760;
const int SCREEN_WIDTH = 1024;

extern SDL_Window *gWindow;
extern SDL_Surface *gScreenSurface;
extern SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
extern SDL_Surface *gCurrentSurface;
extern SDL_Renderer *gRenderer;

bool init();
void close();
SDL_Texture *loadTexture(std::string path);
SDL_Surface *loadSurface(std::string path);

#endif