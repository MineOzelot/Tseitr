//
// Created by mineozelot on 8/12/18.
//

#ifndef TSEITR_LEVEL_HPP
#define TSEITR_LEVEL_HPP

#include "Game.hpp"
#include "Tetromino.hpp"

#define LEVEL_ROWS 20
#define LEVEL_COLS 12
#define LEVEL_WIDTH  384
#define LEVEL_HEIGHT 640
#define LEVEL_TICK 1000
#define BLOCK_WIDTH  (LEVEL_WIDTH / LEVEL_COLS)
#define BLOCK_HEIGHT (LEVEL_HEIGHT / LEVEL_ROWS)
#define TETROMINO_START_POS_X 5
#define TETROMINO_START_POS_Y 20

class Row {
	int colors[LEVEL_COLS]{0};
	Row *up = nullptr;
	Row *down = nullptr;
public:
	Row() = default;

	Row *getUp() const {
		return up;
	}

	Row *getDown() const {
		return down;
	}

	void setUp(Row *row) {
		up = row;
	}

	void setDown(Row *row) {
		down = row;
	}

	bool isFull() const;

	int operator[](size_t i) const {
		return colors[i];
	}

	int &operator[](size_t i) {
		return colors[i];
	}

	void clear() {
		up = down = nullptr;
		for(int &c : colors) c = 0;
	}

	~Row() = default;
};

class Level {
	int score = 0;

	Row *top;
	Row *back;
	int rows = LEVEL_ROWS;

	Tetromino *current = nullptr;
	Tetromino *next = nullptr;

	SDL_Texture *text_next = nullptr;
	SDL_Rect text_next_rect{};

	Uint32 last = 0;
	bool fall = false;
public:
	explicit Level(Game *game);

	void removeRow(Row *row);

	SDL_Color getColor(int c) const;

	void update(Game *game);

	void draw(Game *game, int x, int y) const;
	void drawBlock(Game *game, int x, int y, int c) const;
	void drawTetramino(Game *game, int x, int y, const Tetromino *tetromino) const;

	bool canPass(int xOffset = 0, int yOffset = 0) const;

	void handle(Game *game, const SDL_Event &event);

	void moveLeft();
	void moveRight();
	void rotate();

	Row *resolve(Row *row, int y);

	void nextTetromino(int type);

	int getScore() const {
		return score;
	}

	~Level();
};

#endif //TSEITR_LEVEL_HPP
