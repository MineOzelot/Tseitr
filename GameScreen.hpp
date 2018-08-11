//
// Created by mineozelot on 8/12/18.
//

#ifndef TSEITR_GAMESCREEN_HPP
#define TSEITR_GAMESCREEN_HPP

#include "Screen.hpp"

class GameScreen: public Screen {
public:
	void init(Game *game) override {}

	void update(Game *game) override;
	void render(Game *game) override;

	void pause() override {}
	void resume() override {}

	void dispose() override {}
};

#endif //TSEITR_GAMESCREEN_HPP
