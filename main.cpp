#include"Variables.h"
#include"Dog.h"
#include"LTexture.h"
#include"Stone.h"
#include"Timer.h"
#include"Bat.h"
#include "StoneManager.h"
#include "BatManager.h"
#include "DrugManager.h"

using namespace std;

int main( int argc, char* args[] )
{
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			highScore = LoadHighScore("highscore.txt");
			while (!quit)
			{
				if (currentScore > highScore) {
					highScore = currentScore;
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

					// Nếu đang ở menu
					if (isInMenu)
					{
						if (e.type == SDL_MOUSEBUTTONDOWN)
						{
							if (SDL_PointInRect(&mousePoint, &StartGameRect))
							{
								isInMenu = false;
								isInChooseMap = true; // Hoặc chuyển sang trạng thái game
							}
							else if (SDL_PointInRect(&mousePoint, &HelpGameRect))
							{
								isInMenu=false;
								isInHelp = true;
							}
							else if (SDL_PointInRect(&mousePoint, &ExitGameRect))
							{
								quit = true;
							}
						}
					}
					else if (isInChooseMap)
					{
						if (e.type == SDL_MOUSEBUTTONDOWN)
							{
								if (SDL_PointInRect(&mousePoint, &ChooseIceMap))
								{
									map = "Ice";
									isStartGame = true;
									isInChooseMap=false;
									timer.start();
								}
								else if (SDL_PointInRect(&mousePoint, &ChooseLavaMap))
								{
									map = "Lava";
									isStartGame = true;
									isInChooseMap=false;
									timer.start();
								}
								else if (SDL_PointInRect(&mousePoint, &ReturnButton))
								{
									isInMenu = true;
									isInChooseMap=false;
								}
							}
					}
					else if (isInHelp)
					{
						if (e.type == SDL_MOUSEBUTTONDOWN)
							{
								if (SDL_PointInRect(&mousePoint, &ReturnButton))
								{
									isInMenu = true;
									isInHelp=false;
								}
							}
					}
					if (isStartGame && isPause)
					{
						if (e.type == SDL_MOUSEBUTTONDOWN)
						{
							int mouseX, mouseY;
							SDL_GetMouseState(&mouseX, &mouseY);
							SDL_Point mousePoint = { mouseX, mouseY };

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
					// Nếu đang trong game
					else if (!isgameover)
					{
						if (e.type == SDL_KEYDOWN)
						{
							if (e.key.keysym.sym == SDLK_SPACE)
								dog.jump();

							if (e.key.keysym.sym == SDLK_f)
							{
								isFPressed = true;
								if (drugCount) drugCount--;
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
					else if (isgameover)
					{
						if (e.type == SDL_KEYDOWN)
						{
							if (e.key.keysym.sym == SDLK_SPACE)
							{
								// Reset trạng thái để chơi lại
								isgameover = false;
								isStartGame = true;
								isInMenu = false;
								isInChooseMap = false;
								isInHelp = false;
								drugCount=0;

								// Reset lại mọi thứ cần thiết ở đây
								currentScore = 0;
								dog.reset(); 
								stoneManager.reset(); 
								batManager.reset(); 
								drugManager.reset(); 
								timer.start(); 

							}
							else if (e.key.keysym.sym == SDLK_ESCAPE)
							{
								// Trở về menu
								isgameover = false;
								isInMenu = true;
								isStartGame = false;
								isInChooseMap = false;
								isInHelp = false;
								drugCount=0;
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

				}

				// ===== RENDER PHẦN RIÊNG BIỆT =====
				
				if (isInMenu)
				{
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderClear(gRenderer);
					gMenu.render(0, 0, NULL);

					// Hover effect
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

				else if (isInChooseMap)
				{
						SDL_RenderClear(gRenderer);
						
						if(SDL_PointInRect(&mousePoint, &ChooseIceMap))
						{
							gChooseIce.render(0,0);
						}
						else if (SDL_PointInRect(&mousePoint, &ChooseLavaMap))
						{
							gChooseLava.render(0,0);
						}
						else
						{
							gChoose1From2.render(0, 0); 
						}
						gReturnButton.render(15,15,NULL);
						SDL_RenderPresent(gRenderer);
				}
				else if (isInHelp)
				{
					SDL_RenderClear(gRenderer);
					gHelp.render(0,0,NULL);
					gReturnButton.render(0,0,NULL);
					SDL_RenderPresent(gRenderer);
				}
				else if (isStartGame)
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
					gSpriteSheetTextureDrug.render(SCREEN_WIDTH-75,0,NULL);
					
					if (isPause)
					{
						isHome = SDL_PointInRect(&mousePoint, &Home);
						isResume = SDL_PointInRect(&mousePoint, &Resume);
						isAgain = SDL_PointInRect(&mousePoint, &Again);
						
						if (isHome) HomeTexture.render(0,0,0);
						else if (isResume) ResumeTexture.render(0,0,0);
						else if (isAgain) AgainTexture.render(0,0,0);
						else Pause.render(0,0,NULL);
					}

					SDL_RenderPresent(gRenderer);
				}

			}


		}
	}
	saveHighScore("highScore.txt",score);
	close();
	return 0;

}

	


