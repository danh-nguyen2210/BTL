#include"Stone.h"
extern LTexture gStoneTexture;

Stone::Stone()
{
	StonePos.first=SCREEN_WIDTH;
	StonePos.second=(SCREEN_HEIGHT - 48)*3/4;
}

void Stone::UpdateStonePos()
{
	StonePos.first-=STONE_VEL;
	if (StonePos.first==0){
		StonePos.first=SCREEN_WIDTH;
	}
	StoneCollider={StonePos.first,StonePos.second,STONE_WIDTH,STONE_HEIGHT};
}
void Stone::renderStone()
{
	gStoneTexture.render(StonePos.first,StonePos.second);
}
SDL_Rect Stone::getStoneCollider()
{
	return StoneCollider;
}