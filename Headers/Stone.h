#ifndef STONE_H
#define STONE_H

#include"Variables.h"


using namespace std;

class Stone
{
	public : 
		static const int STONE_WIDTH = 40;
		static const int STONE_HEIGHT = 48;
		static const int STONE_VEL = 6;

		Stone();
		void UpdateStonePos();
		std::pair<int,int> getStonePos();
		void renderStone();
		SDL_Rect getStoneCollider();
		
		
	private :
		std::pair<int,int> StonePos;
		SDL_Rect StoneCollider;

};

#endif