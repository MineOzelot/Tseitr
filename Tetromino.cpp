//
// Created by mineozelot on 8/13/18.
//

#include "Tetromino.hpp"

const std::pair<int, int> Tetromino::tetrominoes[7][4] {
		{ {-1, 0}, {0,  0}, {1,  0}, {2,  0} }, //I
		{ {-1, 0}, {0,  0}, {1,  0}, {1,  1} }, //J
		{ {-1, 1}, {-1, 0}, {0,  0}, {1,  0} }, //L
		{ {0,  0}, {1,  0}, {1,  1}, {0,  1} }, //O
		{ {-1, 1}, {0,  1}, {0,  0}, {1,  0} }, //S
		{ {-1, 0}, {0,  0}, {0,  1}, {1,  0} }, //T
		{ {-1, 0}, {0,  0}, {0,  1}, {1,  1} }, //Z
};

Tetromino::Tetromino(int type_): type(type_) {
	for(int i = 0; i < 4; i++) {
		blocks[i] = tetrominoes[type][i];
	}
}
