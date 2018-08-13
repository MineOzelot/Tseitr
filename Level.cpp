//
// Created by mineozelot on 8/12/18.
//

#include <cstdlib>
#include "Level.hpp"

Level::Level() {
	for(auto &row : colors) {
		for(int &j : row) {
			j = 0;
		}
	}
}

void Level::generateTest(Game *game) {
//TEST
	for(int i = 0; i < 6; i++) {
		for(int &j : colors[i]) {
			j = game->randomInt(1, 7);
		}
	}
}

bool Level::isRowFull(int row) const {
	for(int c : colors[row]) {
		if(c == 0) return false;
	}
	return true;
}

void Level::removeRow(int row) {
	for(int i = row; i > 0; i--) {
		for(int j = 0; j < LEVEL_COLS; j++) {
			colors[i][j] = colors[i-1][j];
		}
	}
}

SDL_Color Level::getColor(int c) const {
	switch(c) {
		case 1: return SDL_Color{0xfa, 0x10, 0x10}; //RED
		case 2: return SDL_Color{0x2e, 0xa5, 0xfc}; //BLUE
		case 3: return SDL_Color{0xfe, 0x66, 0x00}; //ORANGE
		case 4: return SDL_Color{0x96, 0x99, 0x9a}; //GRAY
		case 5: return SDL_Color{0x36, 0xc6, 0x4c}; //GREEN
		case 6: return SDL_Color{0xcc, 0x54, 0xc3}; //MAGENTA
		case 7: return SDL_Color{0xfd, 0xfd, 0x00}; //YELLOW
		default: return SDL_Color{0x00, 0x00, 0x00};
	}
}

void Level::draw(Game *game, int x, int y) const {
	SDL_SetRenderDrawColor(game->getRenderer(), 0xfd, 0xfd, 0xfd, 0xff);
	SDL_Rect rect = {x, y, LEVEL_WIDTH, LEVEL_HEIGHT};
	SDL_RenderFillRect(game->getRenderer(), &rect);

	SDL_SetRenderDrawColor(game->getRenderer(), 0xed, 0xed, 0xed, 0xff);
	for(int i = 1; i < LEVEL_COLS; i += 2) {
		rect = {x + i * BLOCK_WIDTH, y, BLOCK_WIDTH, LEVEL_HEIGHT};
		SDL_RenderFillRect(game->getRenderer(), &rect);
	}

	for(int i = 0; i < LEVEL_ROWS; i++) {
		for(int j = 0; j < LEVEL_COLS; j++) {
			int c = colors[i][j];
			if(c != 0) {
				int tx = j * BLOCK_WIDTH + x;
				int ty = LEVEL_HEIGHT - i * BLOCK_HEIGHT + y;

				drawBlock(game, tx, ty, c);
			}
		}
	}
}

void Level::drawBlock(Game *game, int x, int y, int c) const {
	SDL_Color col = getColor(c);
	SDL_SetRenderDrawColor(game->getRenderer(), col.r, col.g, col.b, 0xff);
	SDL_Rect rect = {x + 1, y + 1, BLOCK_WIDTH - 2, BLOCK_HEIGHT - 2};
	SDL_RenderFillRect(game->getRenderer(), &rect);
	SDL_SetRenderDrawColor(game->getRenderer(),
	                       static_cast<Uint8>(col.r * 0.9F),
	                       static_cast<Uint8>(col.g * 0.9F),
	                       static_cast<Uint8>(col.b * 0.9F), 0xf
	);
	SDL_RenderDrawRect(game->getRenderer(), &rect);
}
