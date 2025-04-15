#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>


using namespace std;

class LTexture;
class Dog;
class Stone;
class LTimer;
class StoneManager;
class Animation;
class Bat;
class BatManager;
class Drug;
class DrugManager;
struct DayNightInfo {
    Uint8 overlayAlpha;
    Uint32 lastCycleIndex = 0; 
    string map = "Ice";
    bool justStartedNewCycle = false; 

    void update(Uint32 timeNow);
};



constexpr int SCREEN_WIDTH = 1272;
constexpr int SCREEN_HEIGHT = 450;
const int WALKING_ANIMATION_FRAMES = 8;
const int STONE_ANIMATION_FRAMES = 18;
const int BAT_ANIMATION_FRAMES = 7;
const int DRUG_ANIMATION_FRAMES = 6;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern TTF_Font* gFontSmall;
extern TTF_Font* gFontMedium;
extern TTF_Font* gFontLarge;
extern LTexture gSpriteSheetTextureDog;
extern LTexture gSpriteSheetTextureIceStone;
extern LTexture gSpriteSheetTextureLavaStone;
extern LTexture gSpriteSheetTextureIceBat;
extern LTexture gSpriteSheetTextureLavaBat;
extern LTexture gSpriteSheetTextureDrug;
extern LTexture gTextTexture;
extern LTexture gTimeTextTexture;
extern LTexture gPausePromptTexture;
extern LTexture gStartPromptTexture;
extern LTexture gMenu;
extern LTexture gChoose1From2;
extern LTexture gChooseIce;
extern LTexture gChooseLava;
extern LTexture gStartGameText;
extern LTexture gExitGameText;
extern LTexture gHelpGameText;
extern LTexture gReturnButton;
extern LTexture gHelp;
extern LTexture Loser;
extern LTexture gScoreText;
extern LTexture gHighScoreText;
extern LTexture Pause;
extern LTexture HomeTexture;
extern LTexture ResumeTexture;
extern LTexture AgainTexture;

extern SDL_Rect gSpriteClipsDog[WALKING_ANIMATION_FRAMES];
extern SDL_Rect gSpriteClipsIceStone[STONE_ANIMATION_FRAMES];
extern SDL_Rect gSpriteClipsLavaStone[STONE_ANIMATION_FRAMES];
extern SDL_Rect gSpriteClipsIceBat[BAT_ANIMATION_FRAMES];
extern SDL_Rect gSpriteClipsLavaBat[BAT_ANIMATION_FRAMES];

extern SDL_Rect StartGameRect;
extern SDL_Rect HelpGameRect;
extern SDL_Rect ExitGameRect;
extern SDL_Rect ChooseIceMap;
extern SDL_Rect ChooseLavaMap;
extern SDL_Rect ReturnButton;
extern SDL_Rect Home;
extern SDL_Rect Resume;
extern SDL_Rect Again;


extern Dog dog;
extern int dogframe;
extern Stone stone;
extern int stoneframe;
extern Bat bat;
extern int batframe;
extern Drug drug;
extern SDL_Event e;
extern SDL_Color textColor;
extern LTimer timer;
extern std::stringstream timeText;
extern std::stringstream StartGameText;
extern std::stringstream ExitGameText;
extern std::stringstream HelpGameText;
extern bool quit;
extern bool isJump;
extern bool isgameover;
extern StoneManager stoneManager;
extern BatManager batManager;
extern DrugManager drugManager;
extern LTexture gBGLavaTexture;
extern LTexture gBGIceTexture;
extern int scrollingOffset;
extern vector<Stone> stones;
extern vector<Bat> bats;
extern vector<Drug> drugs;
extern bool isFPressed;
extern DayNightInfo dayNightInfo;
extern bool isInChooseMap;
extern SDL_Point mousePoint;
extern int drugCount;
extern bool isInMenu;
extern bool isInHelp;
extern bool isStartGame;
extern string map;
extern int score;
extern int highScore;
extern int currentScore;
extern bool isPause;
extern bool isHome;
extern bool isResume;
extern bool isAgain;




bool init();
bool loadMedia();
void close();
bool checkCollision(SDL_Rect a, SDL_Rect b);
void checkDistanceOfBatsAndStones();
void renderNightOverlay();
void renderBackground(const string& map);
void updateGameLogic();
void renderGameObjects();
void renderDrug();
void renderScore();
void checkCollisions();



void eventHandler();
void renderAll();

int LoadHighScore(const string& filename);
void saveHighScore(const string& filename,int &score);

