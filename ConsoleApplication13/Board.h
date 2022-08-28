#pragma once

#include <iostream>
#include <vector>
#include "Move.h"
#include "Globals.hpp"

using namespace std;

class Move;

class Board {
private:
	int board[SIZE][SIZE];
public:
	Board();
	~Board();
	void setFigure(int figure, int y, int x);
	double checkRow();
	vector<Move> freeCells();
	void makeMove(Move& move);
	int makeRandomMove();
	void printBoard();
	bool testOfLegalMove(Move& move);
	bool isTerminate();

	bool crossMove = true;
};
