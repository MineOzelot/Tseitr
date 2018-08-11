//
// Created by mineozelot on 8/12/18.
//

#include "Game.hpp"
#include "GameScreen.hpp"

void GameScreen::update(Game *game) {}

void GameScreen::render(Game *game) {
	SDL_RenderClear(game->getRenderer());

	SDL_RenderPresent(game->getRenderer());
}
