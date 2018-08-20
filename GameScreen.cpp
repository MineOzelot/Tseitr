//
// Created by mineozelot on 8/12/18.
//

#include "Game.hpp"
#include "GameScreen.hpp"

#define TEXT_PAUSED "Paused"

void GameScreen::init(Game *game) {
	level = new Level(game);

	label_paused = new Label(game->getRenderer(), TEXT_PAUSED, 4, 4, game->getFont16());
}

void GameScreen::handle(Game *game, const SDL_Event &event) {
	if(paused) return;
	level->handle(game, event);
}

void GameScreen::update(Game *game) {
	if(paused) return;
	level->update(game);
}

void GameScreen::render(Game *game) {
	SDL_SetRenderDrawColor(game->getRenderer(), 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(game->getRenderer());
	level->draw(game);

	if(paused) {
		label_paused->draw(game->getRenderer());
	}

	SDL_RenderPresent(game->getRenderer());
}

void GameScreen::dispose() {
	delete label_paused;

	delete level;
}
