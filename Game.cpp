//
// Created by mineozelot on 8/11/18.
//

#include "Game.hpp"
#include "StartScreen.hpp"

#include <iostream>

#define FONT_FILE "font.ttf"

Game::Game() {
	win = SDL_CreateWindow(
			WIN_NAME,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WIN_WIDTH, WIN_HEIGHT,
			SDL_WINDOW_SHOWN
	);

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 0xFF);

	font16 = TTF_OpenFont(FONT_FILE, 16);
	if(!font16) {
		std::cerr << "Cannot open a file: " FONT_FILE ": " << TTF_GetError() << std::endl;
		exit(1);
	}
	font24 = TTF_OpenFont(FONT_FILE, 24);
	if(!font16) {
		std::cerr << "Cannot open a file: " FONT_FILE ": " << TTF_GetError() << std::endl;
		exit(1);
	}
}

void Game::start() {
	isRunning = true;

	setScreen(std::make_shared<StartScreen>());
	loop();
}

void Game::loop() {
	while(isRunning && screen) {
		screen->update(this);
		screen->render(this);
	}
	screen = nullptr;
}

void Game::setScreen(std::shared_ptr<Screen> screen_) {
	if(screen) screen->dispose();
	screen = std::move(screen_);
	if(screen) screen->init(this);
}

Game::~Game() {
	TTF_CloseFont(font16);
	TTF_CloseFont(font24);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
}
