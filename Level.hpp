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
#define BLOCK_WIDTH  (LEVEL_WIDTH / LEVEL_COLS)
#define BLOCK_HEIGHT (LEVEL_HEIGHT / LEVEL_ROWS)
#define TETROMINO_START_POS_X 5
#define TETROMINO_START_POS_Y 0

class Level {
	int score = 0;
	int colors[LEVEL_ROWS][LEVEL_COLS];

	Tetromino *current = nullptr;
	Tetromino *next = nullptr;

	SDL_Texture *text_next = nullptr;
	SDL_Rect text_next_rect{};
public:
	explicit Level(Game *game);

	bool isRowFull(int row) const;
	void removeRow(int row);

	SDL_Color getColor(int c) const;

	void draw(Game *game, int x, int y) const;
	void drawBlock(Game *game, int x, int y, int c) const;
	void drawTetramino(Game *game, int x, int y, const Tetromino *tetromino) const;

	int getScore() const {
		return score;
	}

	~Level();
};

#endif //TSEITR_LEVEL_HPP
