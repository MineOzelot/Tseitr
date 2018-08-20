//
// Created by mineozelot on 8/12/18.
//

#ifndef TSEITR_LEVEL_HPP
#define TSEITR_LEVEL_HPP

#include "Game.hpp"
#include "Tetromino.hpp"
#include "Label.hpp"

#define LEVEL_ROWS 20
#define LEVEL_COLS 12
#define LEVEL_WIDTH  384
#define LEVEL_HEIGHT 640
#define LEVEL_TICK 1000
#define BLOCK_WIDTH  (LEVEL_WIDTH / LEVEL_COLS)
#define BLOCK_HEIGHT (LEVEL_HEIGHT / LEVEL_ROWS)
#define TETROMINO_START_POS_X 5

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

	int get(int i) const {
		return colors[i];
	}

	void set(int i, int c) {
		colors[i] = c;
	}

	void clear() {
		up = down = nullptr;
		for(int &c : colors) c = 0;
	}

	~Row() = default;
};

class Level {
	int score = 100;
	int lines = 0;
	int tetrominoes = 0;

	Row *top;
	Row *back;
	Row *gameover_row = nullptr;
	bool gameover_row_up = false;
	int rows = LEVEL_ROWS;

	Tetromino *current = nullptr;
	Tetromino *next = nullptr;

	Label *label_next = nullptr;
	Label *label_gameover = nullptr;
	Label *label_score = nullptr;
	Label *label_score_value = nullptr;
	Label *label_lines = nullptr;
	Label *label_lines_value = nullptr;
	Label *label_tetrominoes = nullptr;
	Label *label_tetrominoes_value = nullptr;

	Uint32 last = 0;
	bool fall = false;
	bool gameover = false;
public:
	explicit Level(Game *game);

	Row *removeRow(Row *row);

	SDL_Color getColor(int c) const;

	void update(Game *game);

	void draw(Game *game);
	void drawBlock(Game *game, int x, int y, int c) const;
	void drawMiniblock(Game *game, int x, int y, int c) const;
	void drawTetromino(Game *game, int x, int y, const Tetromino *tetromino) const;

	bool canPass(int xOffset = 0, int yOffset = 0) const;

	void handle(Game *game, const SDL_Event &event);

	void moveLeft();
	void moveRight();
	void rotate();

	Row *resolve(Row *row, int y);

	void nextTetromino(int type);

	void addScore(int add) {
		score += add;
		label_score_value->setText(std::to_string(score));
	}
	void addLines(int add) {
		lines += add;
		label_lines_value->setText(std::to_string(lines));
	}
	void addTetrominoes(int add) {
		tetrominoes += add;
		label_tetrominoes_value->setText(std::to_string(tetrominoes));
	}

	~Level();
};

#endif //TSEITR_LEVEL_HPP
