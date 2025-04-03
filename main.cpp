#include"Variables.h"

using namespace std;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

bool checkCollision( SDL_Rect a, SDL_Rect b );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//Walking animation
const int WALKING_ANIMATION_FRAMES = 8;
SDL_Rect gSpriteClipsDog[ WALKING_ANIMATION_FRAMES ];
LTexture gSpriteSheetTextureDog;

LTexture gTextTexture;

const int STONE_ANIMATION_FRAMES = 18;
SDL_Rect gSpriteClipsIceStone [STONE_ANIMATION_FRAMES];
LTexture gSpriteSheetTextureIceStone;

SDL_Rect gSpriteClipsLavaStone [STONE_ANIMATION_FRAMES];
LTexture gSpriteSheetTextureLavaStone;

LTexture gTimeTextTexture;
LTexture gPausePromptTexture;
LTexture gStartPromptTexture;

//LTimer gTimer;
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
	
	return success;
}

void close()
{
	//Free loaded images
	gSpriteSheetTextureDog.free();
	gSpriteSheetTextureIceStone.free();
	gSpriteSheetTextureLavaStone.free();

	gTimeTextTexture.free();
	gStartPromptTexture.free();
	gPausePromptTexture.free();


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

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;
			bool isJump = true;
			bool isgameover = false;

			//Event handler
			SDL_Event e;

			Stone stone;

			Dog dog;

			SDL_Color textColor = { 0, 0, 0, 255 };

			LTimer timer;

			std::stringstream timeText;

			//Current animation frame
			int dogframe = 0;
			int stoneframe = 0;

			timer.start();

			//While application is running
			while( !quit )
			{
				
				//Handle events on queue
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
				
				
				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
				
				//Render current frame
				SDL_Rect* currentDogClip = &gSpriteClipsDog[ (dogframe / 10) % WALKING_ANIMATION_FRAMES ];
				SDL_Rect* currentStoneClip = &gSpriteClipsLavaStone[(stoneframe/2) % STONE_ANIMATION_FRAMES];
				if (!isgameover&&!timer.isPaused())
				{	
					dog.ApplyGravitationalForce();
					stone.UpdateStonePos();
					//Go to next frame
					++dogframe;

					//Cycle animation
					if( dogframe / 10 >= WALKING_ANIMATION_FRAMES )
					{
						dogframe = 0;
					}

					++stoneframe;

					//Cycle animation
					if( stoneframe/2 >= STONE_ANIMATION_FRAMES )
					{
						stoneframe = 0;
					}
				}
					gSpriteSheetTextureDog.render( dog.getDogPos().first, dog.getDogPos().second, currentDogClip );
					gSpriteSheetTextureLavaStone.render(stone.getStonePos().first, stone.getStonePos().second, currentStoneClip);
				
				timeText.str( "" );
				timeText << "Current Score : " << ( timer.getTicks() / 100.f ) ; 

				//Render text
				if( !gTimeTextTexture.loadFromRenderedText( timeText.str().c_str(), textColor ) )
				{
					printf( "Unable to render time texture!\n" );
				}
				//Render textures
				gTimeTextTexture.render( ( SCREEN_WIDTH - gTimeTextTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gTimeTextTexture.getHeight() ) / 4 );
				

				

				if(checkCollision(dog.getDogCollider(),stone.getStoneCollider()))
				{
					gTextTexture.render((SCREEN_WIDTH - gTextTexture.getWidth()) / 2,(SCREEN_HEIGHT - gTextTexture.getHeight()) / 2);
					isgameover = true;
					timer.pause();
				}

				//Update screen
				SDL_RenderPresent( gRenderer );

				
                
			}
		}
	}

	close();
	return 0;

}

	


