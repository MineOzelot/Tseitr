//
// Created by mineozelot on 8/13/18.
//

#ifndef TSEITR_TETROMINO_HPP
#define TSEITR_TETROMINO_HPP

#include <utility>

class Tetromino {
	static const std::pair<int, int> tetrominoes[7][4];
	int type;
	int rotation = 0;
	std::pair<int, int> blocks[4];

	class Row *row;
	int pos_x, pos_y;
public:
	explicit Tetromino(int type);

	void setRow(class Row *row_) {
		row = row_;
	}

	class Row *getRow() const {
		return row;
	}

	void setX(int x) {
		pos_x = x;
	}

	int getX() const {
		return pos_x;
	}

	void setY(int y) {
		pos_y = y;
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
