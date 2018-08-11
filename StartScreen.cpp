//
// Created by mineozelot on 8/11/18.
//

#include "StartScreen.hpp"
#include "GameScreen.hpp"

const char *TEXT_START = "Press any key to start";

void StartScreen::init(Game *game) {
	SDL_Surface *sur_text = TTF_RenderText_Blended(game->getFont24(), TEXT_START, {255, 255, 255});
	text_start = SDL_CreateTextureFromSurface(game->getRenderer(), sur_text);
	SDL_FreeSurface(sur_text);

	SDL_QueryTexture(text_start, nullptr, nullptr, &text_start_width, &text_start_height);
}

void StartScreen::update(Game *game) {
	SDL_Event event{};
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_QUIT:
				game->stop();
				break;
			case SDL_KEYDOWN:
				game->setScreen(std::make_shared<GameScreen>());
				break;
			default: break;
		}
	}
}

void StartScreen::render(Game *game) {
	SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 0xFF);
	SDL_RenderClear(game->getRenderer());
	SDL_Rect src = {0, 0, text_start_width, text_start_height};
	SDL_Rect dst = {WIN_WIDTH/2-text_start_width/2, WIN_HEIGHT/2-text_start_height/2, text_start_width, text_start_height};
	SDL_RenderCopy(game->getRenderer(), text_start, &src, &dst);
	SDL_RenderPresent(game->getRenderer());
}

void StartScreen::dispose() {
	SDL_DestroyTexture(text_start);
}
