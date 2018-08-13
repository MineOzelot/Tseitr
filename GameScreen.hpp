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

	SDL_Texture *text_paused = nullptr;
	SDL_Rect text_paused_rect{};

	SDL_Texture *text_score = nullptr;
	SDL_Rect text_score_rect{};

	SDL_Texture *text_score_v = nullptr;
	SDL_Rect text_score_v_rect{};
	int score = 0;
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
