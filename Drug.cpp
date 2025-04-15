#include"Drug.h"
#include"Variables.h"
#include"LTexture.h"
#include"Timer.h"


Drug::Drug(int startX) : DrugPos(startX, ((SCREEN_HEIGHT - 40) *3/4))
{
    DrugCollider = {DrugPos.first, DrugPos.second, DRUG_WIDTH, DRUG_HEIGHT};
}

void Drug::UpdateDrugPos()
{
	DrugPos.first-=DRUG_VEL;
	DrugCollider = {DrugPos.first, DrugPos.second, DRUG_WIDTH, DRUG_HEIGHT};
}

std::pair<int,int> Drug :: getDrugPos()
{
	return DrugPos;
}

void Drug::renderDrug()
{
	gSpriteSheetTextureDrug.render(DrugPos.first, DrugPos.second,NULL);
}

SDL_Rect Drug::getDrugCollider()
{
	return DrugCollider;
}

