#include"Stone.h"
#include"Variables.h"
#include"LTexture.h"
#include"Timer.h"


Stone::Stone(int startX) : StonePos(startX, (SCREEN_HEIGHT + 15)*3/4) {
    StoneCollider = {StonePos.first, StonePos.second, STONE_WIDTH, STONE_HEIGHT};
}

void Stone::UpdateStonePos()
{
	StonePos.first-=STONE_VEL;
	StoneCollider={StonePos.first,StonePos.second,STONE_WIDTH,STONE_HEIGHT};
}
std::pair<int,int> Stone :: getStonePos()
{
	return StonePos;
}
void Stone::renderStone()
{
	SDL_Rect* currentStoneClip = &gSpriteClipsLavaStone[(stoneFrame/2) % STONE_ANIMATION_FRAMES];
	gSpriteSheetTextureLavaStone.render(StonePos.first, StonePos.second, currentStoneClip);
	if(!isgameover&&!timer.isPaused()) ++stoneFrame;

	if( stoneFrame/2 >= STONE_ANIMATION_FRAMES)
	{
		stoneFrame = 0;
	}
}
SDL_Rect Stone::getStoneCollider()
{
	return StoneCollider;
}
