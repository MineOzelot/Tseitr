//
// Created by mineozelot on 8/11/18.
//

#include "Game.hpp"
#include "StartScreen.hpp"

#include <iostream>

#define FONT_FILE "font.ttf"

Game::Game(): eng(std::random_device()()) {

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
		input();
		screen->update(this);
		screen->render(this);
	}
	screen = nullptr;
}

void Game::input() {
	SDL_Event event{};
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_QUIT:
				stop();
				break;
			case SDL_WINDOWEVENT:
				if(event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) pause();
				if(event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) resume();
				break;
			default: break;
		}
		if(screen) screen->handle(this, event);
	}
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

int Game::randomInt(int min, int max) {
	std::uniform_int_distribution<int> distr(min, max);
	return distr(eng);
}
