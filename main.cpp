#include"Variables.h"
#include"Dog.h"
#include"LTexture.h"
#include"Stone.h"
#include"Timer.h"
#include"Bat.h"

using namespace std;

int main( int argc, char* args[] )
{
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			timer.start();
			while( !quit )
			{
				eventHandler();
                renderAll();
			}
		}
	}

	close();
	return 0;

}

	


