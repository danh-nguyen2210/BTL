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
    if (isFlying)
    {
        // Nếu đang bay, thì hủy trạng thái bay
        isFlying = false;
        flyTimer.stop();
    }

    velocityY = JUMP_VEL; // Thiết lập vận tốc nhảy
    isJumping = true;     // Nếu bạn vẫn muốn giữ trạng thái nhảy
}


void Dog::HandleFlyLogic(bool isFPressedNow)
{
    // ===== XỬ LÝ SỰ KIỆN BẤM F =====
    if (isFPressedNow)
    {
        if (!isFlying && !hasFlown)
        {
            isFlying = true;
            velocityY = -4;
            flyTimer.start();
            hasFlown = true;
        }
        else if (hasFlown && !isFalling && flyTimer.getTicks() < 5000)
        {
            isFalling = true; // ép rơi xuống sớm nếu bấm lại trước 5s
        }
    }

    // ===== XỬ LÝ LOGIC BAY & RƠI =====
    if (isFlying)
    {
        DogPos.second += velocityY;

        if (DogPos.second <= 0)
        {
            DogPos.second = 0;
            velocityY = 0;
            isFlying = false;
        }
    }
    else
    {
        if (hasFlown && !isFalling && flyTimer.getTicks() >= 5000)
        {
            isFalling = true; // tự rơi sau 5s
        }

        if (isFalling)
        {
            int targetY = (SCREEN_HEIGHT + 5) * 3 / 4;

            if (DogPos.second < targetY)
            {
                DogPos.second += 4;
                if (DogPos.second > targetY)
                    DogPos.second = targetY;
            }
            else
            {
                isFalling = false;
                hasFlown = false;
                flyTimer.stop();
            }
        }
    }

    DogCollider = { DogPos.first, DogPos.second, DOG_WIDTH, DOG_HEIGHT };
}


void Dog::ApplyGravitationalForce()
{
	if (isJumping) 
    {
        velocityY += GRAVITY; // Tăng vận tốc rơi xuống
        DogPos.second += velocityY;

        // Khi chạm đất, đặt lại trạng thái
        if (DogPos.second >= ( SCREEN_HEIGHT + 15 ) *3/4)
        {
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

void Dog::renderFlyTimeBar()
{
    if (!hasFlown || flyTimer.getTicks() >= MAX_FLY_DURATION) return;

    Uint32 elapsed = flyTimer.getTicks();
    float percentage = 1.0f - (float)elapsed / MAX_FLY_DURATION;
    if (percentage < 0.0f) percentage = 0.0f;

    const int barWidth = 200;
    const int barHeight = 20;
    const int x = SCREEN_WIDTH-285;
    const int y = 5;

    int filledWidth = static_cast<int>(barWidth * percentage);
    if (filledWidth < 0) filledWidth = 0;

    // === Nhấp nháy nếu còn dưới 1 giây ===
    bool blink = false;
    if (MAX_FLY_DURATION - elapsed <= 1000)
    {
        Uint32 blinkTime = SDL_GetTicks() / 150; // nhấp nháy mỗi 150ms
        blink = (blinkTime % 2 == 0);
    }

    // === Vẽ nền xám ===
    SDL_SetRenderDrawColor(gRenderer, 100, 100, 100, 255);
    SDL_Rect background = { x, y, barWidth, barHeight };
    SDL_RenderFillRect(gRenderer, &background);

    // === Vẽ thanh tím nếu chưa đến lúc nhấp nháy ẩn ===
    if (filledWidth > 0 && (!blink || MAX_FLY_DURATION - elapsed > 1000))
    {
        SDL_SetRenderDrawColor(gRenderer, 75, 0, 130, 255);
        SDL_Rect bar = { x, y, filledWidth, barHeight };
        SDL_RenderFillRect(gRenderer, &bar);
    }
}

void Dog::reset()
{
    DogPos.first=( SCREEN_WIDTH - 48 ) *1/4;
	DogPos.second=( SCREEN_HEIGHT + 5 ) *3/4;
	velocityY=0;
	isJumping=false;
    DogCollider={DogPos.first,DogPos.second,DOG_WIDTH,DOG_HEIGHT};
}

