#include"Dog.h"

Dog::Dog()
{
	DogPos.first=( SCREEN_WIDTH - 48 ) *1/4;
	DogPos.second=( SCREEN_HEIGHT - 48 ) *3/4;
	velocityY=0;
	isJumping=false;
}

void Dog::jump()
{
	if (!isJumping) {
        isJumping = true;
        velocityY = JUMP_VEL; // Thiết lập vận tốc nhảy
    }
}

void Dog::ApplyGravitationalForce()
{
	if (isJumping) {
        velocityY += GRAVITY; // Tăng vận tốc rơi xuống
        DogPos.second += velocityY;

        // Khi chạm đất, đặt lại trạng thái
        if (DogPos.second >= (SCREEN_HEIGHT - DOG_HEIGHT) * 3 / 4) {
            DogPos.second = (SCREEN_HEIGHT - DOG_HEIGHT) * 3 / 4;
            velocityY = 0;
            isJumping = false;
        }
    }
    DogCollider={DogPos.first,DogPos.second,DOG_WIDTH,DOG_HEIGHT};
}


std::pair<int,int> Dog :: getDogPos()
{
	return DogPos;
}

void Dog::setDogPos(int NewDogPosY)
{
	DogPos.second=NewDogPosY;
}

SDL_Rect Dog::getDogCollider()
{
    return DogCollider;
}