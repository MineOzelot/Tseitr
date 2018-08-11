//
// Created by mineozelot on 8/11/18.
//

#ifndef TSEITR_GAME_HPP
#define TSEITR_GAME_HPP

#include <memory>
#include <SDL_ttf.h>
#include "SDL.h"
#include "Screen.hpp"

#define WIN_NAME   "Tseitr"
#define WIN_WIDTH  800
#define WIN_HEIGHT 600

class Game {
	std::shared_ptr<Screen> screen = nullptr;

	SDL_Window *win = nullptr;
	SDL_Renderer *ren = nullptr;
	TTF_Font *font16 = nullptr;
	TTF_Font *font24 = nullptr;

	bool isRunning = false;
public:
	Game();

	void start();
	void stop() { isRunning = false; }

	SDL_Window *getWindow() const {
		return win;
	}
	SDL_Renderer *getRenderer() const {
		return ren;
	}
	TTF_Font *getFont16() const {
		return font16;
	}
	TTF_Font *getFont24() const {
		return font24;
	}

	void setScreen(std::shared_ptr<Screen> screen);
	std::shared_ptr<Screen> getScreen() const {
		return screen;
	}

	~Game();
private:
	void loop();
};

#endif //TSEITR_GAME_HPP
