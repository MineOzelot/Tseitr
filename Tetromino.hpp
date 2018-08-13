//
// Created by mineozelot on 8/13/18.
//

#ifndef TSEITR_TETROMINO_HPP
#define TSEITR_TETROMINO_HPP

#include <utility>

class Tetromino {
	static const std::pair<int, int> tetrominoes[7][4];
	int type;
	std::pair<int, int> blocks[4];

	int pos_x, pos_y;
public:
	explicit Tetromino(int type);

	void setPosition(int x, int y) {
		pos_x = x; pos_y = y;
	}

	int getX() const {
		return pos_x;
	}

	int getY() const {
		return pos_y;
	}

	int getType() const {
		return type;
	}

	std::pair<int, int> getBlock(int b) const {
		return blocks[b];
	};

	void rotate();
	void unrotate();
};

#endif //TSEITR_TETROMINO_HPP
