//
// Created by mineozelot on 8/11/18.
//

#ifndef TSEITR_STARTSCREEN_HPP
#define TSEITR_STARTSCREEN_HPP

#include "Screen.hpp"
#include "Game.hpp"
#include "Label.hpp"

class StartScreen: public Screen {
	Label *label_start = nullptr;
public:
	void init(Game *game) override;

	void handle(Game *game, const SDL_Event &event) override;

	void update(Game *game) override;
	void render(Game *game) override;

	void pause() override {}
	void resume() override {}

	void dispose() override;
};

#endif //TSEITR_STARTSCREEN_HPP
