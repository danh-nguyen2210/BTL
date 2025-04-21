#include "Variables.h"
#include "Dog.h"
#include "LTexture.h"
#include "Stone.h"
#include "Timer.h"
#include "Bat.h"
#include "StoneManager.h"
#include "BatManager.h"
#include "DrugManager.h"
#include "GameManager.h"
#include <iostream>

using namespace std;



int main(int argc, char* args[])
{
    if (!init())
    {
        cout << "Failed to initialize !" << endl;
    }
    else
    {
        if (!loadMedia())
        {
            cout << "Falied to load media !" << endl;
        }
        else
        {
            highScore = LoadHighScore("highscore.txt");
            if (!isMuted)
            {
                Mix_PlayMusic(BGSound, -1); 
            }
            
            while (!quit)
            {
                if (currentScore > highScore) {
                    highScore = currentScore;
                    saveHighScore("highscore.txt", highScore);
                }
                
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                SDL_Point mousePoint = { mouseX, mouseY };

                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }

					handleBGMusic();

                    if (isInMenu)
                    {
                        handleMenuEvents(mousePoint);
                    }
                    else if (isInChooseMap)
                    {
                        handleChooseMapEvents(mousePoint);
                    }
                    else if (isInHelp)
                    {
                        handleHelpEvents(mousePoint);
                    }
                    else if (isStartGame && isPause)
                    {
                        handlePauseEvents(mousePoint);
                    }
                    else if (!isgameover)
                    {
                        handleGameEvents();
                    }
                    else if (isgameover)
                    {
                        handleGameOverEvents();
                    }
                }

                // Render các phần riêng biệt
                if (isInMenu)
                {
                    renderMenu(mousePoint);
                }
                else if (isInChooseMap)
                {
                    renderChooseMap(mousePoint);
                }
                else if (isInHelp)
                {
                    renderHelp();
                }
                else if (isStartGame)
                {
                    renderGame();
                }
            }
        }
    }
    saveHighScore("highscore.txt", highScore);
    close();
    return 0;
}

