//
// Created by mineozelot on 8/11/18.
//

#ifndef TSEITR_GAME_HPP
#define TSEITR_GAME_HPP

#include <memory>
#include <random>
#include <SDL_ttf.h>
#include <SDL.h>
#include "Screen.hpp"

#define WIN_NAME   "Tseitr"
#define WIN_WIDTH  800
#define WIN_HEIGHT 640

class Game {
	std::shared_ptr<Screen> screen = nullptr;

	SDL_Window *win = nullptr;
	SDL_Renderer *ren = nullptr;
	TTF_Font *font16 = nullptr;
	TTF_Font *font24 = nullptr;

	bool isRunning = false;

	std::default_random_engine eng;
public:
	Game();

	void start();
	void stop() { isRunning = false; }

	void pause() { if(screen) screen->pause(); }
	void resume() { if(screen) screen->resume(); }

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

	SDL_Texture *renderText(TTF_Font *font, const char *text, SDL_Color color, int &w, int &h) const;

	void setScreen(std::shared_ptr<Screen> screen);
	std::shared_ptr<Screen> getScreen() const {
		return screen;
	}

	int randomInt(int min = 0, int max = 100);

	~Game();
private:
	void loop();
	void input();
};

#endif //TSEITR_GAME_HPP
