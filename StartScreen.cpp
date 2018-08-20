//
// Created by mineozelot on 8/11/18.
//

#include "StartScreen.hpp"
#include "GameScreen.hpp"

const char *TEXT_START = "Press any key to start";

void StartScreen::init(Game *game) {
	label_start = new Label(game->getRenderer(), TEXT_START, 0, 0, game->getFont16(), Game::COLOR_WHITE);
	label_start->setX(WIN_WIDTH / 2 - label_start->getWidth() / 2);
	label_start->setY(WIN_HEIGHT / 2 - label_start->getHeight() / 2);
}

void StartScreen::handle(Game *game, const SDL_Event &event) {
	switch(event.type) {
		case SDL_KEYDOWN:
			game->setScreen(std::make_shared<GameScreen>());
			break;
		default: break;
	}
}

void StartScreen::update(Game *game) {}

void StartScreen::render(Game *game) {
	SDL_SetRenderDrawColor(game->getRenderer(), 0x00, 0x00, 0x00, 0xff);
	SDL_RenderClear(game->getRenderer());

	label_start->draw(game->getRenderer());

	SDL_RenderPresent(game->getRenderer());
}

void StartScreen::dispose() {
	delete label_start;
}
