//
// Created by mineozelot on 8/11/18.
//

#ifndef TSEITR_STARTSCREEN_HPP
#define TSEITR_STARTSCREEN_HPP

#include "Screen.hpp"
#include "Game.hpp"

class StartScreen: public Screen {
	SDL_Texture *text_start = nullptr;
	int text_start_width = 0, text_start_height = 0;
public:
	void init(Game *game) override;

	void update(Game *game) override;
	void render(Game *game) override;

	void pause() override {}
	void resume() override {}

	void dispose() override;
};

#endif //TSEITR_STARTSCREEN_HPP
