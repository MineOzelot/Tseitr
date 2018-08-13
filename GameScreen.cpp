//
// Created by mineozelot on 8/12/18.
//

#include "Game.hpp"
#include "GameScreen.hpp"

#define TEXT_PAUSED "Paused"

void GameScreen::init(Game *game) {
	level = new Level(game);

	text_paused = game->renderText(game->getFont16(), TEXT_PAUSED, SDL_Color{0x10, 0x10, 0x10, 0xff}, text_paused_rect.w, text_paused_rect.h);
	text_paused_rect.x = 390;
	text_paused_rect.y = 4;
}

void GameScreen::handle(Game *game, const SDL_Event &event) {
	if(paused) return;
	switch(event.type) {
		case SDL_KEYDOWN:
			if(event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
				level->moveLeft();
			} else if(event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
				level->moveRight();
			} else if(event.key.keysym.scancode == SDL_SCANCODE_UP) {
				level->rotate();
			} else if(event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
				level->fall();
			}
			break;
		default: break;
	}
}

void GameScreen::update(Game *game) {
	if(paused) return;
	level->update(game);
}

void GameScreen::render(Game *game) {
	SDL_SetRenderDrawColor(game->getRenderer(), 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(game->getRenderer());
	level->draw(game, 0, 0);

	if(paused) {
		SDL_RenderCopy(game->getRenderer(), text_paused, nullptr, &text_paused_rect);
	}

	SDL_RenderPresent(game->getRenderer());
}

void GameScreen::dispose() {
	SDL_DestroyTexture(text_paused);

	delete level;
}
