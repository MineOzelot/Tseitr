//
// Created by mineozelot on 8/13/18.
//

#include "Tetromino.hpp"

const std::pair<int, int> Tetromino::tetrominoes[7][4] {
		{ {-1, 0}, {0,  0}, {1,  0}, {2,  0} }, //I
		{ {-1, 0}, {0,  0}, {1,  0}, {1, -1} }, //J
		{ {-1,-1}, {-1, 0}, {0,  0}, {1,  0} }, //L
		{ {0,  0}, {1,  0}, {1, -1}, {0, -1} }, //O
		{ {-1,-1}, {0, -1}, {0,  0}, {1,  0} }, //S
		{ {-1, 0}, {0,  0}, {0, -1}, {1,  0} }, //T
		{ {-1, 0}, {0,  0}, {0, -1}, {1, -1} }, //Z
};

const int rotateTypes[7] { 1, 2, 2, 0, 1, 2, 1 };

Tetromino::Tetromino(int type_): type(type_) {
	for(int i = 0; i < 4; i++) {
		blocks[i] = tetrominoes[type][i];
	}
}

void Tetromino::rotate() {
	if(rotateTypes[type] == 0) return;;
	if(rotateTypes[type] == 1 && rotation % 2 == 1) {
		unrotate();
	} else {
		for(auto &block : blocks) {
			std::swap(block.first, block.second);
			block.second = -block.second;
		}
		rotation++;
	}
}

void Tetromino::unrotate() {
	if(rotateTypes[type] == 0) return;;
	if(rotateTypes[type] == 1 && rotation % 2 == 0) {
		rotate();
	} else {
		for(auto &block : blocks) {
			std::swap(block.first, block.second);
			block.first = -block.first;
		}
		rotation--;
	}
}
