#include "GameManager.h"
#include "Variables.h"
#include "Dog.h"
#include "LTexture.h"
#include "Stone.h"
#include "Timer.h"
#include "Bat.h"
#include "StoneManager.h"
#include "BatManager.h"
#include "DrugManager.h"

// Các hàm xử lý sự kiện
void handleMenuEvents(SDL_Point mousePoint)
{
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        if (!isMuted) Mix_PlayChannel(-1, Click, 0);
        if (SDL_PointInRect(&mousePoint, &StartGameRect))
        {
            isInMenu = false;
            isInChooseMap = true;
        }
        else if (SDL_PointInRect(&mousePoint, &HelpGameRect))
        {
            isInMenu = false;
            isInHelp = true;
        }
        else if (SDL_PointInRect(&mousePoint, &ExitGameRect))
        {
            quit = true;
        }
    }
}

void handleChooseMapEvents(SDL_Point mousePoint)
{
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        if (!isMuted) Mix_PlayChannel(-1, Click, 0);
        if (SDL_PointInRect(&mousePoint, &ChooseIceMap))
        {
            map = "Ice";
            isStartGame = true;
            isInChooseMap = false;
            timer.start();
        }
        else if (SDL_PointInRect(&mousePoint, &ChooseLavaMap))
        {
            map = "Lava";
            isStartGame = true;
            isInChooseMap = false;
            timer.start();
        }
        else if (SDL_PointInRect(&mousePoint, &ReturnButton))
        {
            isInMenu = true;
            isInChooseMap = false;
        }
    }
}

void handleHelpEvents(SDL_Point mousePoint)
{
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        if (!isMuted) Mix_PlayChannel(-1, Click, 0);
        if (SDL_PointInRect(&mousePoint, &ReturnButton))
        {
            isInMenu = true;
            isInHelp = false;
        }
    }
}

void handlePauseEvents(SDL_Point mousePoint)
{
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        if (!isMuted) Mix_PlayChannel(-1, Click, 0);
        if (SDL_PointInRect(&mousePoint, &Home))
        {
            isHome = true;
            isPause = false;
            isgameover = false;
            isInMenu = true;
            isStartGame = false;
            isInChooseMap = false;
            isInHelp = false;

            drugCount = 0;
            currentScore = 0;

            dog.reset();
            stoneManager.reset();
            batManager.reset();
            drugManager.reset();

            timer.stop();
        }
        else if (SDL_PointInRect(&mousePoint, &Resume))
        {
            isResume = true;
            isPause = false;
            timer.unpause();
        }
        else if (SDL_PointInRect(&mousePoint, &Again))
        {
            isAgain = true;
            isPause = false;
            isgameover = false;
            isInMenu = false;
            isStartGame = true;
            isInChooseMap = false;
            isInHelp = false;

            drugCount = 0;
            currentScore = 0;

            dog.reset();
            stoneManager.reset();
            batManager.reset();
            drugManager.reset();

            timer.start();
        }
    }
}

void handleGameEvents()
{
    if (e.type == SDL_KEYDOWN)
    {
        if (e.key.keysym.sym == SDLK_SPACE)
        {
            dog.jump();
            if (!isMuted) Mix_PlayChannel(-1, Jump, 0);
        }

        if (e.key.keysym.sym == SDLK_f)
        {
            if (drugCount >= 1) {
                if (!dog.isDogFlying() && !isMuted)
                {
                    Mix_PlayChannel(-1, UsingDrug, 0);
                }
                isFPressed = true;
                drugCount--;
            }
            else if (drugCount == 0 && dog.isDogFlying())
            {
                isFPressed = true;
            }
        }

        if (e.key.keysym.sym == SDLK_p)
        {
            isPause = !isPause;
            if (isPause)
                timer.pause();
            else
                timer.unpause();
        }
    }
}

void handleBGMusic()
{
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_m)
    {
        isMuted = !isMuted;
        if (isMuted)
        {
            Mix_PauseMusic();
            Mix_Volume(-1, 0); // Tắt âm thanh tất cả các kênh
        }
        else
        {
            Mix_ResumeMusic();
            Mix_Volume(-1, MIX_MAX_VOLUME); // Bật âm thanh tất cả các kênh
        }
    }
}


void handleGameOverEvents()
{
    if (e.type == SDL_KEYDOWN)
    {
        if (e.key.keysym.sym == SDLK_SPACE)
        {
            isgameover = false;
            isStartGame = true;
            isInMenu = false;
            isInChooseMap = false;
            isInHelp = false;
            drugCount = 0;
            currentScore = 0;
            dog.reset();
            stoneManager.reset();
            batManager.reset();
            drugManager.reset();
            timer.start();
        }
        else if (e.key.keysym.sym == SDLK_ESCAPE)
        {
            isgameover = false;
            isInMenu = true;
            isStartGame = false;
            isInChooseMap = false;
            isInHelp = false;
            drugCount = 0;
            currentScore = 0;
            dog.reset();
            stoneManager.reset();
            batManager.reset();
            drugManager.reset();
            timer.start();
            timer.stop();
        }
    }
}

// Các hàm render
void renderMenu(SDL_Point mousePoint)
{
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
    gMenu.render(0, 0, NULL);

    StartGameText.str("");
    StartGameText << "Start Game";
    gStartGameText.loadFromRenderedText(
        StartGameText.str().c_str(),
        textColor,
        SDL_PointInRect(&mousePoint, &StartGameRect) ? gFontLarge : gFontMedium
    );

    HelpGameText.str("");
    HelpGameText << "Help";
    gHelpGameText.loadFromRenderedText(
        HelpGameText.str().c_str(),
        textColor,
        SDL_PointInRect(&mousePoint, &HelpGameRect) ? gFontLarge : gFontMedium
    );

    ExitGameText.str("");
    ExitGameText << "Exit";
    gExitGameText.loadFromRenderedText(
        ExitGameText.str().c_str(),
        textColor,
        SDL_PointInRect(&mousePoint, &ExitGameRect) ? gFontLarge : gFontMedium
    );

    gStartGameText.render(525, 250, NULL);
    gHelpGameText.render(575, 320, NULL);
    gExitGameText.render(575, 390, NULL);

    SDL_RenderPresent(gRenderer);
}

void renderChooseMap(SDL_Point mousePoint)
{
    SDL_RenderClear(gRenderer);
    
    if (SDL_PointInRect(&mousePoint, &ChooseIceMap))
    {
        gChooseIce.render(0, 0);
    }
    else if (SDL_PointInRect(&mousePoint, &ChooseLavaMap))
    {
        gChooseLava.render(0, 0);
    }
    else
    {
        gChoose1From2.render(0, 0);
    }
    gReturnButton.render(15, 15, NULL);
    SDL_RenderPresent(gRenderer);
}

void renderHelp()
{
    SDL_RenderClear(gRenderer);
    gHelp.render(0, 0, NULL);
    gReturnButton.render(0, 0, NULL);
    SDL_RenderPresent(gRenderer);
}

void renderGame()
{
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
    dayNightInfo.update(timer.getTicks());
    renderBackground(map);
    renderNightOverlay();
    updateGameLogic();
    renderGameObjects();
    renderDrug();
    renderScore();
    checkCollisions();
    gSpriteSheetTextureDrug.render(SCREEN_WIDTH - 75, 0, NULL);
    
    if (isPause)
    {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        SDL_Point mousePoint = { mouseX, mouseY };

        isHome = SDL_PointInRect(&mousePoint, &Home);
        isResume = SDL_PointInRect(&mousePoint, &Resume);
        isAgain = SDL_PointInRect(&mousePoint, &Again);
        
        if (isHome) HomeTexture.render(0, 0, 0);
        else if (isResume) ResumeTexture.render(0, 0, 0);
        else if (isAgain) AgainTexture.render(0, 0, 0);
        else Pause.render(0, 0, NULL);
    }

    SDL_RenderPresent(gRenderer);
}