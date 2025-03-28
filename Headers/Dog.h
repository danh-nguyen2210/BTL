#ifndef DOG_H
#define DOG_H

#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Variables.h"

class Dog
{
	public :

		static const int DOG_WIDTH = 40;
		static const int DOG_HEIGHT = 48;
		static const int JUMP_VEL = -15.0f;
		static const int GRAVITY = 1.0f;

		Dog();

		void jump();
		void ApplyGravitationalForce();


		std::pair<int,int> getDogPos();
		void setDogPos(int NewDogPosY);
		SDL_Rect getDogCollider();

	private :

		std::pair<int,int> DogPos;
		float velocityY;
		bool isJumping;
		SDL_Rect DogCollider;
};

#endif