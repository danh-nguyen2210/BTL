#include"Dog.h"
#include"Ltexture.h"
#include"Variables.h"
#include"Timer.h"
Dog::Dog()
{
	DogPos.first=( SCREEN_WIDTH - 48 ) *1/4;
	DogPos.second=( SCREEN_HEIGHT + 5 ) *3/4;
	velocityY=0;
	isJumping=false;
    DogCollider={DogPos.first,DogPos.second,DOG_WIDTH,DOG_HEIGHT};
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
        if (DogPos.second >= ( SCREEN_HEIGHT + 15 ) *3/4) {
            DogPos.second = ( SCREEN_HEIGHT + 5 ) *3/4;
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

void Dog::renderDog()
{
    SDL_Rect* currentDogClip = &gSpriteClipsDog[ (dogframe / 6) % WALKING_ANIMATION_FRAMES ];
    gSpriteSheetTextureDog.render( DogPos.first, DogPos.second, currentDogClip );
    if(!isgameover&&!timer.isPaused()) ++dogframe;

    //Cycle animation
    if( dogframe / 6 >= WALKING_ANIMATION_FRAMES &&!isgameover&&!timer.isPaused())
    {
        dogframe = 0;
    }
}   
