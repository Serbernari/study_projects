#pragma once
#include <utility>
#include <array>

struct cell
{
	bool is_correct; //true if is cell can be played in checkers
	bool is_buisy;  //true if there is a man in that cell
	bool is_king; //true if this man is a king
	bool is_white; //true if this man is a white
	std::pair<unsigned short, unsigned short> pos; //coordinates of the cell

};

struct board
{
	std::array<std::array<cell, 8>,8> field;
};

bool possibilityToMove(board* MyBoard); //true if there is possible way for whites to make a step
