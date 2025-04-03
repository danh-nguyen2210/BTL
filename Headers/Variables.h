#ifndef VARIABLES_H
#define VARIABLES_H

#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <string>
#include <sstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Dog.h"
#include "LTexture.h"
#include "Stone.h"
#include "Timer.h"

constexpr int SCREEN_WIDTH = 816;
constexpr int SCREEN_HEIGHT = 480;

extern SDL_Renderer* gRenderer;
extern TTF_Font* gFont;

#endif
