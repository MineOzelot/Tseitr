//
// Created by mineozelot on 8/12/18.
//

#ifndef TSEITR_LEVEL_HPP
#define TSEITR_LEVEL_HPP

#include "Game.hpp"

#define LEVEL_ROWS 20
#define LEVEL_COLS 12
#define LEVEL_WIDTH  384
#define LEVEL_HEIGHT 640
#define BLOCK_WIDTH  (LEVEL_WIDTH / LEVEL_COLS)
#define BLOCK_HEIGHT (LEVEL_HEIGHT / LEVEL_ROWS)

class Level {
	int score = 0;
	int colors[LEVEL_ROWS][LEVEL_COLS];
public:
	Level();

	bool isRowFull(int row) const;
	void removeRow(int row);

	SDL_Color getColor(int c) const;

	void draw(Game *game, int x, int y) const;
	void drawBlock(Game *game, int x, int y, int c) const;

	int getScore() const {
		return score;
	}
};

#endif //TSEITR_LEVEL_HPP
