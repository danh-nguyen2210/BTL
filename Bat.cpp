#include"Bat.h"
#include"Variables.h"
#include"LTexture.h"
#include"Timer.h"


Bat::Bat(int startX) : BatPos(startX, ((SCREEN_HEIGHT - 100) *3/4))
{
    BatCollider = {BatPos.first, BatPos.second, BAT_WIDTH, BAT_HEIGHT};
}

void Bat::UpdateBatPos(float speed)
{
	BatPos.first-=speed;
	BatCollider = {BatPos.first, BatPos.second, BAT_WIDTH, BAT_HEIGHT};
}

std::pair<int,int> Bat :: getBatPos()
{
	return BatPos;
}

void Bat::renderBat(const string& map)
{
	SDL_Rect* currentBatClip = &gSpriteClipsLavaBat[(batFrame/6) % BAT_ANIMATION_FRAMES];
	if (map=="Lava"){
		gSpriteSheetTextureLavaBat.render(BatPos.first, BatPos.second, currentBatClip);
	}
	else
	{
		gSpriteSheetTextureIceBat.render(BatPos.first, BatPos.second, currentBatClip);
	}
	
	if(!isgameover&&!timer.isPaused()) ++batFrame;

	//Cycle animation
	if( batFrame/6 >= BAT_ANIMATION_FRAMES)
	{
		batFrame = 0;
	}
}

SDL_Rect Bat::getBatCollider()
{
	return BatCollider;
}

