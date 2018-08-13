//
// Created by mineozelot on 8/12/18.
//

#include "Game.hpp"
#include "GameScreen.hpp"

#define TEXT_PAUSED "Paused"
#define TEXT_SCORE "Score: "

void GameScreen::init(Game *game) {
	level = new Level(game);

	text_paused = game->renderText(game->getFont16(), TEXT_PAUSED, SDL_Color{0x10, 0x10, 0x10, 0xff}, text_paused_rect.w, text_paused_rect.h);
	text_paused_rect.x = 390;
	text_paused_rect.y = 4;

	text_score = game->renderText(game->getFont16(), TEXT_SCORE, SDL_Color{0x10, 0x10, 0x10, 0xff}, text_score_rect.w, text_score_rect.h);
	text_score_rect.x = 390;
	text_score_rect.y = 128;

	text_score_v = game->renderText(game->getFont16(), std::to_string(level->getScore()).c_str(), SDL_Color{0x10, 0x10, 0x10, 0xff}, text_score_v_rect.w, text_score_v_rect.h);
	text_score_v_rect.x = text_score_rect.x + text_score_rect.w + 8;
	text_score_v_rect.y = text_score_rect.y;
}

void GameScreen::handle(Game *game, const SDL_Event &event) {
	if(paused) return;
	level->handle(game, event);
}

void GameScreen::update(Game *game) {
	if(paused) return;
	level->update(game);
	if(score != level->getScore()) {
		SDL_DestroyTexture(text_score_v);
		text_score_v = game->renderText(game->getFont16(), std::to_string(level->getScore()).c_str(), SDL_Color{0x10, 0x10, 0x10, 0xff}, text_score_v_rect.w, text_score_v_rect.h);
	}
}

void GameScreen::render(Game *game) {
	SDL_SetRenderDrawColor(game->getRenderer(), 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(game->getRenderer());
	level->draw(game, 0, 0);

	if(paused) {
		SDL_RenderCopy(game->getRenderer(), text_paused, nullptr, &text_paused_rect);
	}

	SDL_RenderCopy(game->getRenderer(), text_score, nullptr, &text_score_rect);
	SDL_RenderCopy(game->getRenderer(), text_score_v, nullptr, &text_score_v_rect);

	SDL_RenderPresent(game->getRenderer());
}

void GameScreen::dispose() {
	SDL_DestroyTexture(text_paused);
	SDL_DestroyTexture(text_score);
	SDL_DestroyTexture(text_score_v);

	delete level;
}
