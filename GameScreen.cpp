//
// Created by mineozelot on 8/12/18.
//

#include "Game.hpp"
#include "GameScreen.hpp"

#define TEXT_PAUSED "Paused"

void GameScreen::init(Game *game) {
	level = new Level();
	level->generateTest(game);

	SDL_Surface *sur_paused = TTF_RenderText_Blended(game->getFont16(), TEXT_PAUSED, SDL_Color{0xff, 0xff, 0xff, 0xff});
	text_paused = SDL_CreateTextureFromSurface(game->getRenderer(), sur_paused);
	SDL_FreeSurface(sur_paused);
	SDL_QueryTexture(text_paused, nullptr, nullptr, &text_paused_rect.w, &text_paused_rect.h);
	text_paused_rect.x = 390;
	text_paused_rect.y = 4;
}

void GameScreen::handle(Game *game, const SDL_Event &event) {

}

void GameScreen::update(Game *game) {}

void GameScreen::render(Game *game) {
	SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 0xFF);
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
