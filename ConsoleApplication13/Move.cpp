#include "Move.h"

Move::Move() {}
Move::Move(bool _crossMove, int _y, int _x) {
	crossMove = _crossMove;
	y = _y;
	x = _x;
}
Move::~Move() {}

bool Move::operator==(Move& move) {
	return (crossMove == move.crossMove && x == move.x && y == move.y);
}