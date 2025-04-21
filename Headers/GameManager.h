#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SDL.h>

void handleMenuEvents(SDL_Point mousePoint);
void handleChooseMapEvents(SDL_Point mousePoint);
void handleHelpEvents(SDL_Point mousePoint);
void handlePauseEvents(SDL_Point mousePoint);
void handleGameEvents();
void handleBGMusic();
void handleGameOverEvents();
void renderMenu(SDL_Point mousePoint);
void renderChooseMap(SDL_Point mousePoint);
void renderHelp();
void renderGame();

#endif