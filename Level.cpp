//
// Created by mineozelot on 8/12/18.
//

#include "Level.hpp"

#define TEXT_NEXT "Next:"

#define SCORE_PER_ROW 40
#define SCORE_SPEED_MULT 0.02F

Level::Level(Game *game) {
	for(auto &row : colors) {
		for(int &j : row) {
			j = 0;
		}
	}
	current = new Tetromino(game->randomInt(0, 6));
	current->setPosition(TETROMINO_START_POS_X, TETROMINO_START_POS_Y);
	next = new Tetromino(game->randomInt(0, 6));

	text_next = game->renderText(game->getFont16(), TEXT_NEXT, SDL_Color{0x10, 0x10, 0x10, 0xff}, text_next_rect.w, text_next_rect.h);
	text_next_rect.x = 14 * BLOCK_WIDTH;
	text_next_rect.y = 10;
}

bool Level::isRowFull(int row) const {
	for(int c : colors[row]) {
		if(c == 0) return false;
	}
	return true;
}

void Level::removeRow(int row) {
	for(int i = row; i < LEVEL_ROWS; i++) {
		for(int j = 0; j < LEVEL_COLS; j++) {
			colors[i][j] = colors[i + 1][j];
		}
	}
	for(int j = 0; j < LEVEL_COLS; j++) {
		colors[LEVEL_ROWS - 1][j] = 0;
	}
}

SDL_Color Level::getColor(int c) const {
	switch(c) {
		case 1: return SDL_Color{0xfa, 0x10, 0x10, 0xff}; //RED
		case 2: return SDL_Color{0x2e, 0xa5, 0xfc, 0xff}; //BLUE
		case 3: return SDL_Color{0xfe, 0x66, 0x00, 0xff}; //ORANGE
		case 4: return SDL_Color{0x96, 0x99, 0x9a, 0xff}; //GRAY
		case 5: return SDL_Color{0x36, 0xc6, 0x4c, 0xff}; //GREEN
		case 6: return SDL_Color{0xcc, 0x54, 0xc3, 0xff}; //MAGENTA
		case 7: return SDL_Color{0xfd, 0xfd, 0x00, 0xff}; //YELLOW
		default: return SDL_Color{0x00, 0x00, 0x00, 0xff};
	}
}

void Level::update(Game *game) {
	int tick = static_cast<int>(LEVEL_TICK - score * SCORE_SPEED_MULT);
	if(canPass(0, -1)) {
		int t = 60;
		if(!fall) t = tick;
		if(SDL_GetTicks() - last >= t) {
			current->setPosition(current->getX(), current->getY() - 1);
			last = SDL_GetTicks();
		}
	} else {
		if(SDL_GetTicks() - last >= tick) {
			int max_y = 0, min_y = 0;
			for(int i = 0; i < 4; i++) {
				auto b = current->getBlock(i);
				colors[current->getY() + b.second][current->getX() + b.first] = current->getType() + 1;
				max_y = (max_y < b.second) ? b.second : max_y;
				min_y = (min_y > b.second) ? b.second : min_y;
			}
			for(int i = max_y; i >= min_y; i--) {
				if(isRowFull(i + current->getY())) {
					removeRow(i + current->getY());
					score += SCORE_PER_ROW;
				}
			}
			delete current;
			current = next;
			current->setPosition(TETROMINO_START_POS_X, TETROMINO_START_POS_Y);
			next = new Tetromino(game->randomInt(0, 6));
		}
	}
}

void Level::draw(Game *game, int x, int y) const {
	SDL_SetRenderDrawColor(game->getRenderer(), 0xfa, 0xfa, 0xfa, 0xff);
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
				int ty = (i + 1) * BLOCK_HEIGHT + y;

				drawBlock(game, tx, ty, c);
			}
		}
	}

	drawTetramino(game, current->getX() * BLOCK_HEIGHT, (current->getY() + 1) * BLOCK_HEIGHT, current);
	drawTetramino(game, 14 * BLOCK_HEIGHT, 19 * BLOCK_HEIGHT, next);

	SDL_RenderCopy(game->getRenderer(), text_next, nullptr, &text_next_rect);
}

void Level::drawBlock(Game *game, int x, int y, int c) const {
	y = LEVEL_HEIGHT - y;
	SDL_Color col = getColor(c);
	SDL_SetRenderDrawColor(game->getRenderer(), col.r, col.g, col.b, col.a);
	SDL_Rect rect = {x + 1, y + 1, BLOCK_WIDTH - 2, BLOCK_HEIGHT - 2};
	SDL_RenderFillRect(game->getRenderer(), &rect);
	SDL_SetRenderDrawColor(game->getRenderer(),
	                       static_cast<Uint8>(col.r * 0.9F),
	                       static_cast<Uint8>(col.g * 0.9F),
	                       static_cast<Uint8>(col.b * 0.9F), 0xf
	);
	SDL_RenderDrawRect(game->getRenderer(), &rect);
}

void Level::drawTetramino(Game *game, int x, int y, const Tetromino *tetromino) const {
	for(int i = 0; i < 4; i++) {
		auto block = tetromino->getBlock(i);
		drawBlock(game, x + block.first * BLOCK_WIDTH, y + block.second * BLOCK_HEIGHT, tetromino->getType() + 1);
	}
}

bool Level::canPass(int xOffset, int yOffset) const {
	for(int i = 0; i < 4; i++) {
		int x = current->getX() + current->getBlock(i).first + xOffset;
		if(x < 0 || x > LEVEL_COLS-1) return false;
		int y = current->getY() + current->getBlock(i).second + yOffset;
		if(y < 0) return false;
		if(colors[y][x] != 0) return false;
	}
	return true;
}

void Level::moveLeft() {
	if(canPass(-1)) current->setPosition(current->getX() - 1, current->getY());
}

void Level::moveRight() {
	if(canPass(1)) current->setPosition(current->getX() + 1, current->getY());
}

void Level::rotate() {
	current->rotate();
	if(!canPass()) current->unrotate();
}

void Level::handle(Game *game, const SDL_Event &event) {
	switch(event.type) {
		case SDL_KEYDOWN:
			if(event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
				moveLeft();
			} else if(event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
				moveRight();
			} else if(event.key.keysym.scancode == SDL_SCANCODE_UP) {
				rotate();
			} else if(event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
				fall = true;
			}
			break;
		case SDL_KEYUP:
			if(event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
				fall = false;
			}
		default: break;
	}
}

Level::~Level() {
	SDL_DestroyTexture(text_next);
}
