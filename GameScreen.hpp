//
// Created by mineozelot on 8/12/18.
//

#ifndef TSEITR_GAMESCREEN_HPP
#define TSEITR_GAMESCREEN_HPP

#include <iostream>
#include "Screen.hpp"
#include "Level.hpp"

class GameScreen: public Screen {
	Level *level = nullptr;
	bool paused = false;

	Label *label_paused = nullptr;
public:
	void init(Game *game) override;

	void handle(Game *game, const SDL_Event &event) override;
	void update(Game *game) override;
	void render(Game *game) override;

	void pause() override {
		paused = true;
	}
	void resume() override {
		paused = false;
	}

	void dispose() override;
};

#endif //TSEITR_GAMESCREEN_HPP
