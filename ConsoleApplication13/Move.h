#pragma once
#include "Globals.hpp"
#include "Board.h"

class Board;

struct Move {
	bool crossMove;
	int y, x;

	Move();
	Move(bool _crossMove, int _y, int _x);
	~Move();
	bool operator==(Move& move);
};

