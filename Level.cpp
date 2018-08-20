//
// Created by mineozelot on 8/12/18.
//

#include <iostream>
#include <unordered_set>
#include "Level.hpp"

#define TEXT_NEXT "Next:"
#define TEXT_GAMEOVER "Game Over"
#define TEXT_SCORE "Score:"
#define TEXT_LINES "Lines:"
#define TEXT_TETROMINOES "Tetrominoes:"

#define SCORE_PER_ROW 40
#define SCORE_SPEED_MULT 0.05F
#define MINIMAP_BLOCK_SIZE 5
#define MINIMAP_ROWS (LEVEL_HEIGHT / MINIMAP_BLOCK_SIZE)

#define TETROMINO_COST 10

bool Row::isFull() const {
	for(int c : colors) {
		if(c == 0) return false;
	}
	return true;
}

Level::Level(Game *game) {
	back = top = new Row();
	for(int i = 1; i < LEVEL_ROWS; i++) {
		Row *row = new Row();
		row->setDown(top);
		top->setUp(row);
		top = row;
	}

	label_next = new Label(game->getRenderer(), TEXT_NEXT, 14 * BLOCK_WIDTH, 10, game->getFont16());
	label_gameover = new Label(game->getRenderer(), TEXT_GAMEOVER, 400, 108, game->getFont16());

	label_score = new Label(game->getRenderer(), TEXT_SCORE, 400, 128, game->getFont16());
	label_score_value = new Label(game->getRenderer(), std::to_string(score), label_score->getMaxX() + 8, label_score->getMinY(), game->getFont16());

	label_lines = new Label(game->getRenderer(), TEXT_LINES, 400, label_score->getMaxY(), game->getFont16());
	label_lines_value = new Label(game->getRenderer(), std::to_string(lines), label_lines->getMaxX() + 8, label_lines->getMinY(), game->getFont16());

	label_tetrominoes = new Label(game->getRenderer(), TEXT_TETROMINOES, 400, label_lines->getMaxY(), game->getFont16());
	label_tetrominoes_value = new Label(game->getRenderer(), std::to_string(tetrominoes), label_tetrominoes->getMaxX() + 8, label_tetrominoes->getMinY(), game->getFont16());

	next = new Tetromino(game->randomInt(0, 6));
	nextTetromino(game->randomInt(0, 6));
}

Row *Level::removeRow(Row *row) {
	Row *ret;
	if(row->getUp()) (ret = row->getUp())->setDown(row->getDown());
	else ret = top = row->getDown();
	if(row->getDown()) row->getDown()->setUp(row->getUp());
	else back = row->getUp();
	if(rows <= LEVEL_ROWS) {
		row->clear();
		row->setDown(top);
		top->setUp(row);
		top = row;
	} else {
		rows--;
		delete row;
	}
	return ret;
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
	if(!gameover) {
		int tick = static_cast<int>(LEVEL_TICK - score * SCORE_SPEED_MULT);
		if(canPass(0, -1)) {
			int t = 60;
			if(!fall) t = tick;
			if(SDL_GetTicks() - last >= t) {
				current->setRow(current->getRow()->getDown());
				current->setY(current->getY() - 1);
				last = SDL_GetTicks();
			}
		} else {
			if(SDL_GetTicks() - last >= tick) {
				std::unordered_set<Row *> changed;
				for(int i = 0; i < 4; i++) {
					auto b = current->getBlock(i);
					Row *row = resolve(current->getRow(), b.second);
					row->set(current->getX() + b.first, current->getType() + 1);
					changed.insert(row);
				}
				for(Row *row : changed) {
					if(row->isFull()) {
						row = removeRow(row);
						addScore(SCORE_PER_ROW);
						addLines(1);
					}
					resolve(row, 4);
				}
				addTetrominoes(1);
				nextTetromino(game->randomInt(0, 6));
				last = SDL_GetTicks();
			}
		}
	}
	label_score_value->update(game->getRenderer());
	label_lines_value->update(game->getRenderer());
	label_tetrominoes_value->update(game->getRenderer());
}

void Level::draw(Game *game) {
	SDL_SetRenderDrawColor(game->getRenderer(), 0xfa, 0xfa, 0xfa, 0xff);
	SDL_Rect rect = {0, 0, LEVEL_WIDTH, LEVEL_HEIGHT};
	SDL_RenderFillRect(game->getRenderer(), &rect);

	SDL_SetRenderDrawColor(game->getRenderer(), 0xed, 0xed, 0xed, 0xff);
	for(int i = 1; i < LEVEL_COLS; i += 2) {
		rect = {i * BLOCK_WIDTH, 0, BLOCK_WIDTH, LEVEL_HEIGHT};
		SDL_RenderFillRect(game->getRenderer(), &rect);
	}

	Row *render_row = nullptr;
	if(gameover) {
		if(!gameover_row) {
			gameover_row = top;
		} else {
			if(SDL_GetTicks() - last >= 1000) {
				if(!gameover_row_up && gameover_row->getDown()) gameover_row = gameover_row->getDown();
				else gameover_row_up = true;
				if(gameover_row_up && gameover_row->getUp()) gameover_row = gameover_row->getUp();
				else gameover_row_up = false;
				last = SDL_GetTicks();
			}
		}

		render_row = gameover_row;
	} else {
		render_row = current->getRow();
	}

	Row *row = render_row;
	for(int i = 0; i < 4; i++) {
		if(row->getUp()) row = row->getUp();
		else break;
	}
	for(int i = 0; i < (LEVEL_ROWS - 1); i++) {
		if(row->getDown()) row = row->getDown();
		else break;
	}
	for(int i = 0; i < LEVEL_ROWS; i++) {
		for(int j = 0; j < LEVEL_COLS; j++) {
			int c = row->get(j);
			if(c != 0) {
				int tx = j * BLOCK_WIDTH;
				int ty = (i + 1) * BLOCK_HEIGHT;

				drawBlock(game, tx, ty, c);
			}
			if(current && current->getRow() == row) {
				drawTetromino(game, current->getX() * BLOCK_HEIGHT, (i + 1) * BLOCK_WIDTH, current);
			}
		}
		row = row->getUp();
	}

	row = render_row;
	for(int i = 0; i < 10; i++) {
		if(row->getUp()) row = row->getUp();
		else break;
	}
	for(int i = 0; i < (MINIMAP_ROWS - 1); i++) {
		if(row->getDown()) row = row->getDown();
		else break;
	}
	for(int i = 0; row; i++) {
		for(int j = 0; j < LEVEL_COLS; j++) {
			int c = row->get(j);
			if(c != 0) {
				drawMiniblock(game, j, i, c);
			}
		}
		if(current && current->getRow() == row) {
			for(int k = 0; k < 4; k++) {
				auto block = current->getBlock(k);
				drawMiniblock(game, current->getX() + block.first, i + block.second, current->getType() + 1);
			}
		}
		row = row->getUp();
	}

	SDL_SetRenderDrawColor(game->getRenderer(), 0x10, 0x10, 0x10, 0xff);
	SDL_RenderDrawLine(
			game->getRenderer(),
			WIN_WIDTH - LEVEL_COLS * MINIMAP_BLOCK_SIZE - 1, 0,
			WIN_WIDTH - LEVEL_COLS * MINIMAP_BLOCK_SIZE - 1, WIN_HEIGHT
	);

	drawTetromino(game, 14 * BLOCK_WIDTH, 19 * BLOCK_HEIGHT, next);

	label_next->draw(game->getRenderer());
	if(gameover) {
		label_gameover->draw(game->getRenderer());
	}
	label_score->draw(game->getRenderer());
	label_score_value->draw(game->getRenderer());
	label_lines->draw(game->getRenderer());
	label_lines_value->draw(game->getRenderer());
	label_tetrominoes->draw(game->getRenderer());
	label_tetrominoes_value->draw(game->getRenderer());
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
	                       static_cast<Uint8>(col.b * 0.9F), 0xff
	);
	SDL_RenderDrawRect(game->getRenderer(), &rect);
}

void Level::drawMiniblock(Game *game, int x, int y, int c) const {
	SDL_Color col = getColor(c);
	SDL_SetRenderDrawColor(game->getRenderer(), col.r, col.g, col.b, col.a);
	SDL_Rect rect = {
			WIN_WIDTH - LEVEL_COLS * MINIMAP_BLOCK_SIZE + x * MINIMAP_BLOCK_SIZE,
			WIN_HEIGHT - (y + 1) * MINIMAP_BLOCK_SIZE,
			MINIMAP_BLOCK_SIZE, MINIMAP_BLOCK_SIZE
	};
	SDL_RenderFillRect(game->getRenderer(), &rect);
}

void Level::drawTetromino(Game *game, int x, int y, const Tetromino *tetromino) const {
	for(int i = 0; i < 4; i++) {
		auto block = tetromino->getBlock(i);
		drawBlock(game, x + block.first * BLOCK_WIDTH, y + block.second * BLOCK_HEIGHT, tetromino->getType() + 1);
	}
}

bool Level::canPass(int xOffset, int yOffset) const {
	for(int i = 0; i < 4; i++) {
		int x = current->getX() + current->getBlock(i).first + xOffset;
		if(x < 0 || x > LEVEL_COLS-1) return false;
		int y = current->getBlock(i).second + yOffset;
		Row *row = current->getRow();
		if(y < 0) {
			while(y != 0) {
				if(!row->getDown()) return false;
				row = row->getDown();
				y++;
			}
		} else if(y > 0) {
			while(y != 0) {
				if(!row->getUp()) break;
				row = row->getUp();
				y--;
			}
		}
		if(row->get(x) != 0) return false;
	}
	return true;
}

void Level::moveLeft() {
	if(canPass(-1)) current->setX(current->getX() - 1);
}

void Level::moveRight() {
	if(canPass(1)) current->setX(current->getX() + 1);
}

void Level::rotate() {
	current->rotate();
	if(!canPass()) current->unrotate();
}

void Level::handle(Game *game, const SDL_Event &event) {
	if(!gameover) {
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
			default:
				break;
		}
	}
}

Row *Level::resolve(Row *row, int y) {
	if(y > 0) {
		while(y != 0) {
			if(!row->getUp()) {
				Row *nrow = new Row();
				nrow->setDown(row);
				row->setUp(nrow);
				top = nrow;
				rows++;
			}
			row = row->getUp();
			y--;
		}
	} else if(y < 0) {
		while(y != 0) {
			row = row->getDown();
			y++;
		}
	}
	return row;
}

void Level::nextTetromino(int type) {
	delete current;
	if(score < TETROMINO_COST) {
		current = nullptr;
		gameover = true;
		return;
	}
	addScore(-TETROMINO_COST);
	current = next;
	current->setRow(top);
	current->setX(TETROMINO_START_POS_X);
	current->setY(rows-1);
	next = new Tetromino(type);
}

Level::~Level() {
	delete label_next;
	delete label_gameover;
	delete label_score;
	delete label_score_value;
	delete label_lines;
	delete label_lines_value;
	delete label_tetrominoes;
	delete label_tetrominoes_value;

	Row *cur = top;
	while(cur) {
		Row *next = cur->getDown();
		delete cur;
		cur = next;
	}
}
