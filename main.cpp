/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
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
SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];
LTexture gSpriteSheetTexture;
LTexture gTextTexture;
LTexture gStoneTexture;

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

	gFont = TTF_OpenFont("Font/font.ttf",50);
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 0, 0, 0 };
		if( !gTextTexture.loadFromRenderedText( "Game Over!", textColor ) )
		{
			printf( "Failed to render text texture!\n" );
			success = false;
		}
	}

	if(!gStoneTexture.loadFromFile("Stone/Stone.png"))
	{
		printf("Failed to load Stone Texture \n");
		success = false;
	}

	//Load sprite sheet texture
	if( !gSpriteSheetTexture.loadFromFile( "Dog/Dog.png" ) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
        for (int i = 0; i<8;i++){
            gSpriteClips[ i ].x = i*48;
            gSpriteClips[ i ].y =   0;
            gSpriteClips[ i ].w =  48;
            gSpriteClips[ i ].h =  48;
        }
	}
	
	return success;
}

void close()
{
	//Free loaded images
	gSpriteSheetTexture.free();
	gStoneTexture.free();

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

			//Event handler
			SDL_Event e;

			Stone stone;

			Dog dog;

			//Current animation frame
			int frame = 0;

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
					if (e.type == SDL_KEYDOWN)
					{
						if (e.key.keysym.sym == SDLK_SPACE)
						{
							dog.jump();
							
							
						}
						
					}
				}
				dog.ApplyGravitationalForce();
				
				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
				
				//Render current frame
				SDL_Rect* currentClip = &gSpriteClips[ frame / 8 ];
				gSpriteSheetTexture.render( dog.getDogPos().first, dog.getDogPos().second, currentClip );

				stone.UpdateStonePos();
				stone.renderStone();

				//Update screen
				SDL_RenderPresent( gRenderer );

				if(checkCollision(dog.getDogCollider(),stone.getStoneCollider()))
				{
					SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
					SDL_RenderClear(gRenderer);
					gTextTexture.render((SCREEN_WIDTH - gTextTexture.getWidth()) / 2,(SCREEN_HEIGHT - gTextTexture.getHeight()) / 2);
					gSpriteSheetTexture.render( dog.getDogPos().first, dog.getDogPos().second, currentClip );
					stone.renderStone();
					SDL_RenderPresent(gRenderer);
					SDL_Delay(20000);
					quit = true;
				}

				//Go to next frame
				++frame;

				//Cycle animation
				if( frame / 8 >= WALKING_ANIMATION_FRAMES )
				{
					frame = 0;
				}
                
			}
		}
	}

	close();
	return 0;

}

	


