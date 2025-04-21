#include "Variables.h"
#include "LTexture.h"
#include "Dog.h"
#include "Stone.h"
#include "Timer.h"
#include "StoneManager.h"
#include "Bat.h"
#include "BatManager.h"
#include "Drug.h"
#include "DrugManager.h"

// Initialize global variables
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
TTF_Font* gFontSmall = nullptr;
TTF_Font* gFontMedium = nullptr;
TTF_Font* gFontLarge = nullptr;

LTexture gSpriteSheetTextureDog;
LTexture gSpriteSheetTextureIceStone;
LTexture gSpriteSheetTextureLavaStone;
LTexture gSpriteSheetTextureIceBat;
LTexture gSpriteSheetTextureLavaBat;
LTexture gSpriteSheetTextureDrug;
LTexture gTextTexture;
LTexture gTimeTextTexture;
LTexture gPausePromptTexture;
LTexture gStartPromptTexture;
LTexture gDrugTextTexture;
LTexture gScoreText;
LTexture gHighScoreText;
LTexture Pause;
LTexture HomeTexture;
LTexture ResumeTexture;
LTexture AgainTexture;


LTexture gMenu;
LTexture gChoose1From2;
LTexture gChooseIce;
LTexture gChooseLava;
LTexture gStartGameText;
LTexture gExitGameText;
LTexture gHelpGameText;
LTexture gReturnButton;
LTexture gHelp;
LTexture Loser;




SDL_Rect gSpriteClipsDog[WALKING_ANIMATION_FRAMES];
SDL_Rect gSpriteClipsIceStone[STONE_ANIMATION_FRAMES];
SDL_Rect gSpriteClipsLavaStone[STONE_ANIMATION_FRAMES];
SDL_Rect gSpriteClipsIceBat[BAT_ANIMATION_FRAMES];
SDL_Rect gSpriteClipsLavaBat[BAT_ANIMATION_FRAMES];
SDL_Rect StartGameRect={525,253,169,33};
SDL_Rect HelpGameRect={575,323,67,31};
SDL_Rect ExitGameRect={575,400,64,27};
SDL_Rect ChooseIceMap ={70,170,480,200};
SDL_Rect ChooseLavaMap = {714,170,480,200};
SDL_Rect ReturnButton = {0,0,60,60};
SDL_Rect Home={315,110,202,278};
SDL_Rect Resume={528,110,202,278};
SDL_Rect Again={745,110,202,278};

Mix_Music *BGSound = NULL;
Mix_Chunk *Jump = NULL;
Mix_Chunk *Click = NULL;
Mix_Chunk *Die = NULL;
Mix_Chunk *UsingDrug = NULL;

Dog dog;
int dogframe = 0;
Stone stone;
int stoneframe = 0;
Bat bat;
int batframe = 0;
Drug drug;
SDL_Event e;
SDL_Color textColor = { 255, 255, 255, 255 };
LTimer timer;
std::stringstream timeText;
std::stringstream drugText;
std::stringstream StartGameText;
std::stringstream ExitGameText;
std::stringstream HelpGameText;
bool quit = false;
bool isJump = true;
bool isgameover = false;
bool isStartGame = false;
bool isInHelp = false;
bool isInMenu = true;
bool isInChooseMap = false;
bool isPause = false;
bool isHome = false;
bool isResume = false;
bool isAgain = false;
StoneManager stoneManager;
LTexture gBGLavaTexture;
LTexture gBGIceTexture;
BatManager batManager;
DrugManager drugManager;
int scrollingOffset = 0;
bool isFPressed = false;
int drugCount = 0;
SDL_Point mousePoint;
string map;
int highScore=0;    
int currentScore=0;
bool isMuted = false;

DayNightInfo dayNightInfo;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Dog Adventure", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				 //Initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
                 //Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	gFontSmall = TTF_OpenFont("Font/font.ttf",20);
    gFontMedium = TTF_OpenFont("Font/font.ttf",40);
    gFontLarge = TTF_OpenFont("Font/font.ttf",55);
	if( gFontSmall == NULL )
	{
		printf( "Failed to load small font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
    if( gFontMedium == NULL )
	{
		printf( "Failed to load medium font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
    if( gFontLarge == NULL )
	{
		printf( "Failed to load large font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 255, 255, 255, 255};
		if( !gTextTexture.loadFromRenderedText( "Game Over!", textColor, gFontSmall ) )
		{
			printf( "Failed to render text texture!\n" );
			success = false;
		}
	}
	//Load sprite sheet texture
	if( !gSpriteSheetTextureDog.loadFromFile( "Dog/Dog.png" ) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
        for (int i = 0; i<8;i++){
            gSpriteClipsDog[ i ].x = i*48;
            gSpriteClipsDog[ i ].y =   0;
            gSpriteClipsDog[ i ].w =  48;
            gSpriteClipsDog[ i ].h =  48;
        }
	}

	if( !gSpriteSheetTextureIceStone.loadFromFile( "Stone/IceStone.png" ) )
	{
		printf( "Failed to load rolling icestone animation texture!\n" );
		success = false;
	}
	else
	{
        for (int i = 0; i<18;i++){
            gSpriteClipsIceStone[ i ].x = i*48;
            gSpriteClipsIceStone[ i ].y =   0;
            gSpriteClipsIceStone[ i ].w =  48;
            gSpriteClipsIceStone[ i ].h =  48;
        }
	}

	if( !gSpriteSheetTextureLavaStone.loadFromFile( "Stone/LavaStone.png" ) )
	{
		printf( "Failed to load rolling lavastone animation texture!\n" );
		success = false;
	}
	else
	{
        for (int i = 0; i<18;i++){
            gSpriteClipsLavaStone[ i ].x = i*48;
            gSpriteClipsLavaStone[ i ].y =   0;
            gSpriteClipsLavaStone[ i ].w =  48;
            gSpriteClipsLavaStone[ i ].h =  48;
        }
	}
    if( !gSpriteSheetTextureIceBat.loadFromFile( "Bat/IceBat.png" ) )
	{
		printf( "Failed to load Ice Bat animation texture!\n" );
		success = false;
	}
	else
	{
        for (int i = 0; i<7;i++){
            gSpriteClipsIceBat[ i ].x = i*48;
            gSpriteClipsIceBat[ i ].y =   0;
            gSpriteClipsIceBat[ i ].w =  48;
            gSpriteClipsIceBat[ i ].h =  48;
        }
	}

	if( !gSpriteSheetTextureLavaBat.loadFromFile( "Bat/LavaBat.png" ) )
	{
		printf( "Failed to load rolling Lava Bat animation texture!\n" );
		success = false;
	}
	else
	{
        for (int i = 0; i<7;i++){
            gSpriteClipsLavaBat[ i ].x = i*48;
            gSpriteClipsLavaBat[ i ].y =   0;
            gSpriteClipsLavaBat[ i ].w =  48;
            gSpriteClipsLavaBat[ i ].h =  48;
        }
	}
	if (!gBGLavaTexture.loadFromFile("BG/BG_Lava.png"))
	{
		printf( "Failed to load Lava background texture!\n" );
		success = false;
	}
	if (!gBGIceTexture.loadFromFile("BG/BG_Ice.png"))
	{
		printf( "Failed to load Ice background texture!\n" );
		success = false;
	}
	if( !gSpriteSheetTextureDrug.loadFromFile( "Drug/Drug.png" ) )
	{
		printf( "Failed to load rolling Lava Bat animation texture!\n" );
		success = false;
	}
    if( !gSpriteSheetTextureDrug.loadFromFile( "Drug/Drug.png" ) )
	{
		printf( "Failed to load rolling Lava Bat animation texture!\n" );
		success = false;
	}
    if( !gMenu.loadFromFile( "BG/Menu.png" ) )
	{
		printf( "Failed to load Menu texture!\n" );
		success = false;
	}
    if( !gChoose1From2.loadFromFile( "BG/Choose1From2.png" ) )
	{
		printf( "Failed to load Choose Menu texture!\n" );
		success = false;
	}
    if( !gChooseIce.loadFromFile( "BG/ChooseIce.png" ) )
	{
		printf( "Failed to load Choose Ice Menu texture!\n" );
		success = false;
	}
    if( !gChooseLava.loadFromFile( "BG/ChooseLava.png" ) )
	{
		printf( "Failed to load Choose Lava Menu texture!\n" );
		success = false;
	}
    if( !gReturnButton.loadFromFile( "Button/Return.png" ) )
	{
		printf( "Failed to load Return Button texture!\n" );
		success = false;
	}
    if( !gHelp.loadFromFile( "BG/Help.png" ) )
	{
		printf( "Failed to load Help Menu texture!\n" );
		success = false;
	}
    if( !Loser.loadFromFile( "BG/Loser.png" ) )
	{
		printf( "Failed to load Loser texture!\n" );
		success = false;
	}
    if( !Pause.loadFromFile( "BG/Pause.png" ) )
	{
		printf( "Failed to load pause texture!\n" );
		success = false;
	}
    if( !HomeTexture.loadFromFile( "BG/Home.png" ) )
	{
		printf( "Failed to load home texture!\n" );
		success = false;
	}
    if( !ResumeTexture.loadFromFile( "BG/Resume.png" ) )
	{
		printf( "Failed to load Resume texture!\n" );
		success = false;
	}
    if( !AgainTexture.loadFromFile( "BG/Again.png" ) )
	{
		printf( "Failed to load again texture!\n" );
		success = false;
	}

    //Load music
    BGSound = Mix_LoadMUS( "Sound/bgsound.mp3" );
	if( BGSound == NULL )
	{
		printf( "Failed to load BG music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	Jump = Mix_LoadWAV( "Sound/jump.wav" );
	if( Jump == NULL )
	{
		printf( "Failed to load jump music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
    Click = Mix_LoadWAV( "Sound/click.wav" );
	if( Click == NULL )
	{
		printf( "Failed to load click music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
    Die = Mix_LoadWAV( "Sound/die.wav" );
	if( Die == NULL )
	{
		printf( "Failed to load die music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
    UsingDrug = Mix_LoadWAV( "Sound/drug.wav" );
	if( UsingDrug == NULL )
	{
		printf( "Failed to load drug music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

    return success;
}


void close()
{
	//Free loaded images
	gSpriteSheetTextureDog.free();
	gSpriteSheetTextureIceStone.free();
	gSpriteSheetTextureLavaStone.free();
    gSpriteSheetTextureIceBat.free();
	gSpriteSheetTextureLavaBat.free();
    gSpriteSheetTextureDrug.free();
    

    gMenu.free();
    gChoose1From2.free();
    gChooseIce.free();
    gChooseLava.free();
    gReturnButton.free();
    gHelp.free();
    Loser.free();
    Pause.free();
    HomeTexture.free();
    ResumeTexture.free();
    AgainTexture.free();

	gTimeTextTexture.free();
	gStartPromptTexture.free();
	gPausePromptTexture.free();

	gBGIceTexture.free();
	gBGLavaTexture.free();


	gTextTexture.free();
    gStartGameText.free();
    gHelpGameText.free();
    gExitGameText.free();

    Mix_FreeChunk( Jump );
	Mix_FreeChunk( Die );
	Mix_FreeChunk( UsingDrug );
	Mix_FreeChunk( Click );
	Jump = NULL;
	Die = NULL;
	UsingDrug = NULL;
	Click = NULL;
    Mix_FreeMusic( BGSound );
	BGSound = NULL;

	TTF_CloseFont( gFontSmall );
    TTF_CloseFont( gFontMedium);
    TTF_CloseFont (gFontLarge);
	gFontSmall = NULL;
    gFontMedium= NULL;
    gFontLarge = NULL;

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
    Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
	//If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

void checkDistanceOfBatsAndStones()
{
    auto& bats = batManager.getBats();
    auto stones = stoneManager.getStones();

    for (int i = 0; i < bats.size(); )
    {
        bool shouldDelete = false;
        int batX = bats[i].getBatPos().first;
        for (int j = 0; j < stones.size(); j++)
        {
            int stoneX = stones[j].getStonePos().first;
            if (batX - 70 < stoneX && batX + 70 > stoneX)
            {
                shouldDelete = true;
                break; 
            }
        }
        if (shouldDelete)
        {
            bats.erase(bats.begin() + i); // KHÔNG tăng i vì phần tử bị xóa
        }
        else
        {
            i++; // Chỉ tăng i nếu không xóa
        }
    }
}

void DayNightInfo::update(Uint32 timeNow)
{
    const Uint32 dayDuration = 10000;
    const Uint32 fadeDuration = 500;
    const Uint32 nightDuration = 10000;
    const Uint32 fullCycle = dayDuration + fadeDuration + nightDuration + fadeDuration;

    Uint32 cycleTime = timeNow % fullCycle;
    Uint32 currentCycleIndex = timeNow / fullCycle;

    enum Phase { DAY, FADING_TO_NIGHT, NIGHT, FADING_TO_DAY };
    Phase phase;
    float fadeProgress = 0.0f;

    if (cycleTime < dayDuration)
        phase = DAY;
    else if (cycleTime < dayDuration + fadeDuration) {
        phase = FADING_TO_NIGHT;
        fadeProgress = (float)(cycleTime - dayDuration) / fadeDuration;
    }
    else if (cycleTime < dayDuration + fadeDuration + nightDuration)
        phase = NIGHT;
    else {
        phase = FADING_TO_DAY;
        fadeProgress = (float)(cycleTime - (dayDuration + fadeDuration + nightDuration)) / fadeDuration;
    }

    // Alpha mờ dần
    if (phase == FADING_TO_NIGHT)
        overlayAlpha = (Uint8)(180.0f * fadeProgress);
    else if (phase == NIGHT)
        overlayAlpha = 180;
    else if (phase == FADING_TO_DAY)
        overlayAlpha = (Uint8)(180.0f * (1.0f - fadeProgress));
    else
        overlayAlpha = 0;
}

void renderNightOverlay()
{
    if (dayNightInfo.overlayAlpha > 0)
    {
        SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, dayNightInfo.overlayAlpha);
        SDL_Rect fullScreen = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_RenderFillRect(gRenderer, &fullScreen);
    }
}

void renderBackground(const string& map)
{
    if (map == "Ice")
    {
        gBGIceTexture.render(scrollingOffset, 0);
        gBGIceTexture.render(scrollingOffset + gBGIceTexture.getWidth(), 0);
    }
    else if (map == "Lava")
    {
        gBGLavaTexture.render(scrollingOffset, 0);
        gBGLavaTexture.render(scrollingOffset + gBGLavaTexture.getWidth(), 0);
    }
}

void updateGameLogic()
{
    if (!isgameover && !timer.isPaused())
    {
        dog.ApplyGravitationalForce();
        dog.HandleFlyLogic(isFPressed);  // <-- gọi hàm duy nhất này
        isFPressed = false; // reset sau khi xử lý
        stoneManager.updateStones();
        batManager.updateBats();
        drugManager.updateDrugs();

        --scrollingOffset;
        if (scrollingOffset < -gBGIceTexture.getWidth())
            scrollingOffset = 0;
        isFPressed = false;
    }
}

void renderGameObjects()
{
    checkDistanceOfBatsAndStones();
    stoneManager.renderStones(map);
    batManager.renderBats(map);
    drugManager.renderDrugs();
    dog.renderDog();
    dog.renderFlyTimeBar();
}

void renderDrug()

{
    drugText.str("");
    drugText  << "x" << drugCount;

    if (!gDrugTextTexture.loadFromRenderedText(drugText.str().c_str(), textColor,gFontSmall))
        printf("Unable to render drug text texture!\n");

    gDrugTextTexture.render(SCREEN_WIDTH-40,8); // Render góc trái trên cùng (tuỳ chỉnh vị trí)

    if (isgameover)
    {
       Loser.render(0,0,NULL);
    }
}
void renderScore()
{
    currentScore = (timer.getTicks() / 100);
    std::stringstream scoreText;
    scoreText << "Score: " << currentScore;
    gScoreText.loadFromRenderedText(scoreText.str().c_str(), textColor, gFontSmall);
    gScoreText.render(SCREEN_WIDTH/2-65, 15);

    std::stringstream hsText;
    hsText << "High Score: " << highScore;
    gHighScoreText.loadFromRenderedText(hsText.str().c_str(), textColor, gFontSmall);
    gHighScoreText.render(SCREEN_WIDTH/2-80, 0); 
}

void checkCollisions()
{
    if (isgameover) return;

    const SDL_Rect dogCollider = dog.getDogCollider();

    std::vector<Stone> stones = stoneManager.getStones();
    for (Stone stone : stones)
    {
        if (checkCollision(dogCollider, stone.getStoneCollider()))
        {
            Mix_PlayChannel(-1, Die, 0); 
            isgameover = true;
            timer.pause();
            return;
        }
    }

    std::vector<Bat> bats = batManager.getBats();
    for (Bat& bat : bats)
    {
        if (checkCollision(dogCollider, bat.getBatCollider()))
        {
            Mix_PlayChannel(-1, Die, 0); 
            isgameover = true;
            timer.pause();
            return;
        }
    }

    auto& drugs = drugManager.getDrugs();

    for (int i = 0; i < drugs.size(); )
    {
        if (checkCollision(dogCollider, drugs[i].getDrugCollider()))
        {
            drugCount++;
            drugs.erase(drugs.begin() + i); // Xóa và không tăng i
        }
        else
        {
            ++i; // Tăng nếu không xóa
        }
    }
}

int LoadHighScore(const string& filename) {
    std::ifstream file("highscore.txt");
    int score = 0;
    if (file.is_open()) {
        file >> score;
        file.close();
    }
    return score;
}

void saveHighScore(const string& filename, int score) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << score;
        file.close();
    } else {
        printf("Failed to save high score to %s!\n", filename.c_str());
    }
}
