//
// Created by mineozelot on 8/12/18.
//

#include "Game.hpp"
#include "GameScreen.hpp"

void GameScreen::init(Game *game) {
	level = new Level();
}

void GameScreen::update(Game *game) {}

void GameScreen::render(Game *game) {
	SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 0xFF);
	SDL_RenderClear(game->getRenderer());
	level->draw(game, 0, 0);
	SDL_RenderPresent(game->getRenderer());
}

void GameScreen::dispose() {
	delete level;
}
