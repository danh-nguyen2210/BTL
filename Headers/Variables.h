#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class LTexture;
class Dog;
class Stone;
class LTimer;
class StoneManager;
class Animation;
class Bat;
class BatManager;

constexpr int SCREEN_WIDTH = 1272;
constexpr int SCREEN_HEIGHT = 450;
const int WALKING_ANIMATION_FRAMES = 8;
const int STONE_ANIMATION_FRAMES = 18;
const int BAT_ANIMATION_FRAMES = 7;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern TTF_Font* gFont;
extern LTexture gSpriteSheetTextureDog;
extern LTexture gSpriteSheetTextureIceStone;
extern LTexture gSpriteSheetTextureLavaStone;
extern LTexture gSpriteSheetTextureIceBat;
extern LTexture gSpriteSheetTextureLavaBat;
extern LTexture gTextTexture;
extern LTexture gTimeTextTexture;
extern LTexture gPausePromptTexture;
extern LTexture gStartPromptTexture;
extern SDL_Rect gSpriteClipsDog[WALKING_ANIMATION_FRAMES];
extern SDL_Rect gSpriteClipsIceStone[STONE_ANIMATION_FRAMES];
extern SDL_Rect gSpriteClipsLavaStone[STONE_ANIMATION_FRAMES];
extern SDL_Rect gSpriteClipsIceBat[BAT_ANIMATION_FRAMES];
extern SDL_Rect gSpriteClipsLavaBat[BAT_ANIMATION_FRAMES];
extern Dog dog;
extern int dogframe;
extern Stone stone;
extern int stoneframe;
extern Bat bat;
extern int batframe;
extern SDL_Event e;
extern SDL_Color textColor;
extern LTimer timer;
extern std::stringstream timeText;
extern bool quit;
extern bool isJump;
extern bool isgameover;
extern StoneManager stoneManager;
extern BatManager batManager;
extern LTexture gBGLavaTexture;
extern LTexture gBGIceTexture;
extern int scrollingOffset;
extern string map;
extern vector<Stone> stones;
extern vector<Bat> bats;

bool init();
bool loadMedia();
void close();
bool checkCollision(SDL_Rect a, SDL_Rect b);
void eventHandler();
void renderAll();
