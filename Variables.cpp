#include "Variables.h"
#include "LTexture.h"
#include "Dog.h"
#include "Stone.h"
#include "Timer.h"
#include "StoneManager.h"
#include "Bat.h"
#include "BatManager.h"

// Initialize global variables
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
TTF_Font* gFont = nullptr;
LTexture gSpriteSheetTextureDog;
LTexture gSpriteSheetTextureIceStone;
LTexture gSpriteSheetTextureLavaStone;
LTexture gSpriteSheetTextureIceBat;
LTexture gSpriteSheetTextureLavaBat;
LTexture gTextTexture;
LTexture gTimeTextTexture;
LTexture gPausePromptTexture;
LTexture gStartPromptTexture;
SDL_Rect gSpriteClipsDog[WALKING_ANIMATION_FRAMES];
SDL_Rect gSpriteClipsIceStone[STONE_ANIMATION_FRAMES];
SDL_Rect gSpriteClipsLavaStone[STONE_ANIMATION_FRAMES];
SDL_Rect gSpriteClipsIceBat[BAT_ANIMATION_FRAMES];
SDL_Rect gSpriteClipsLavaBat[BAT_ANIMATION_FRAMES];
Dog dog;
int dogframe = 0;
Stone stone;
int stoneframe = 0;
Bat bat;
int batframe = 0;
SDL_Event e;
SDL_Color textColor = { 0, 0, 0, 255 };
LTimer timer;
std::stringstream timeText;
bool quit = false;
bool isJump = true;
bool isgameover = false;
StoneManager stoneManager;
LTexture gBGLavaTexture;
LTexture gBGIceTexture;
BatManager batManager;
int scrollingOffset = 0;
string map;

struct DayNightInfo {
    Uint8 overlayAlpha;
    Uint32 lastCycleIndex = 0; 
    string map = "Ice";
    bool justStartedNewCycle = false; 

    void update(Uint32 timeNow);
};

DayNightInfo dayNightInfo;
void checkDistanceOfBatsAndStones();

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
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
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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

	gFont = TTF_OpenFont("Font/font.ttf",20);
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 0, 0, 0, 255 };
		if( !gTextTexture.loadFromRenderedText( "Game Over!", textColor ) )
		{
			printf( "Failed to render text texture!\n" );
			success = false;
		}
		if( !gStartPromptTexture.loadFromRenderedText( "Press S to Start or Stop the Timer", textColor ) )
		{
			printf( "Unable to render start/stop prompt texture!\n" );
			success = false;
		}
		
		//Load pause prompt texture
		if( !gPausePromptTexture.loadFromRenderedText( "Press P to Pause or Unpause the Timer", textColor ) )
		{
			printf( "Unable to render pause/unpause prompt texture!\n" );
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
        for (int i = 0; i<18;i++){
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
        for (int i = 0; i<18;i++){
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

	gTimeTextTexture.free();
	gStartPromptTexture.free();
	gPausePromptTexture.free();

	gBGIceTexture.free();
	gBGLavaTexture.free();


	gTextTexture.free();
	TTF_CloseFont( gFont );
	gFont = NULL;

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void eventHandler()
{
    while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            
            if (e.type == SDL_KEYDOWN&&!isgameover)
            {
                if (e.key.keysym.sym == SDLK_SPACE)
                {
                    dog.jump();
                }
                //Pause/unpause
                if( e.key.keysym.sym == SDLK_p )
                {
                    if( timer.isPaused() )
                    {
                        timer.unpause();
                    }
                    else
                    {
                        timer.pause();
                    }
                }
                
            }
        }
}

void updateGameLogic()
{
    if (!isgameover && !timer.isPaused())
    {
        dog.ApplyGravitationalForce();
        stoneManager.updateStones();
        batManager.updateBats();

        --scrollingOffset;
        if (scrollingOffset < -gBGIceTexture.getWidth())
            scrollingOffset = 0;
    }
}

void DayNightInfo::update(Uint32 timeNow)
{
    const Uint32 dayDuration = 1000;
    const Uint32 fadeDuration = 500;
    const Uint32 nightDuration = 1000;
    const Uint32 fullCycle = dayDuration + fadeDuration + nightDuration + fadeDuration;

    Uint32 cycleTime = timeNow % fullCycle;
    Uint32 currentCycleIndex = timeNow / fullCycle;

    // Đổi map nếu bắt đầu cycle mới
    if (currentCycleIndex != lastCycleIndex) {
        justStartedNewCycle = true;
        lastCycleIndex = currentCycleIndex;

        // Chuyển đổi map
        map = (map == "Ice") ? "Lava" : "Ice";
    } else {
        justStartedNewCycle = false;
    }

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

void renderGameObjects()
{
    checkDistanceOfBatsAndStones();
    dog.renderDog();
    stoneManager.renderStones();
    batManager.renderBats();
}

void renderScore()
{
    timeText.str("");
    timeText << "Current Score : " << (timer.getTicks() / 100.f);

    if (!gTimeTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor))
        printf("Unable to render time texture!\n");

    gTimeTextTexture.render(
        (SCREEN_WIDTH - gTimeTextTexture.getWidth()) / 2,
        (SCREEN_HEIGHT - gTimeTextTexture.getHeight()) / 4
    );
    if (isgameover)
    {
        gTextTexture.render((SCREEN_WIDTH - gTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gTextTexture.getHeight()) / 2 );
    }
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

void checkCollisions()
{
    if (isgameover) return;

    const SDL_Rect dogCollider = dog.getDogCollider();

    std::vector<Stone> stones = stoneManager.getStones();
    for (Stone stone : stones)
    {
        if (checkCollision(dogCollider, stone.getStoneCollider()))
        {
            
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
            isgameover = true;
            timer.pause();
            return;
        }
    }
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






void renderAll()
{
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    dayNightInfo.update(timer.getTicks());

    renderBackground(dayNightInfo.map);
    renderNightOverlay();

    updateGameLogic();

    renderGameObjects();
    renderScore();
    checkCollisions();

    SDL_RenderPresent(gRenderer);
}
