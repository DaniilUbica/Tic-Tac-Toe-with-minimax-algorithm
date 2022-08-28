#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include "Board.h"
#include "Move.h"

using namespace std;

class Game {
private:
	Board board;
public:
	Game();
	~Game();
	double minimax(Board& board, int depth);
	vector<Move> movefreeCells;
	int startGameWithPc();
	int startGameWithPlayer();
	int startDemoGame();
	void menu();
};

