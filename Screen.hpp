//
// Created by mineozelot on 8/11/18.
//

#ifndef TSEITR_SCREEN_HPP
#define TSEITR_SCREEN_HPP

#include <SDL_events.h>

class Game;

class Screen {
public:
	virtual void init(Game *game) = 0;

	virtual void handle(Game *game, const SDL_Event &event) = 0;
	virtual void update(Game *game) = 0;
	virtual void render(Game *game) = 0;

	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void dispose() = 0;
};

#endif //TSEITR_SCREEN_HPP
