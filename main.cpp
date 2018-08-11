#include <iostream>
#include <SDL_ttf.h>
#include "Game.hpp"

int main() {
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
		std::cerr << "Unable to init SDL: " << SDL_GetError() << std::endl;
		return 1;
	}
	std::atexit(SDL_Quit);
	if(TTF_Init() != 0) {
		std::cerr << "Unable to init SDL_tff: " << TTF_GetError() << std::endl;
		return 1;
	}
	std::atexit(TTF_Quit);

	Game game;
	game.start();

	return 0;
}