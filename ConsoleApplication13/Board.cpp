#include "Board.h"
#include <random>
#include "time.h"

using namespace std;

Board::Board() {
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            board[y][x] = EMPTY;
        }
    }
}

Board::~Board() {}

void Board::setFigure(int figure, int y, int x) {
    board[y][x] = figure;
}

double Board::checkRow() {
    int mul = 1;

    if (!crossMove) {
        mul = -1;
    }
    
    for (int y = 0; y < SIZE; y++) {
        int count = 0;
        for (int x = 0; x < SIZE; x++) {
            if (board[y][x] == EMPTY)  break; 
            if (board[y][x] == board[y][0]) ++count; 
        }

        if (count >= SIZE) {
            if (board[y][0] == CROSS) return 1 * mul; 
            else  return -1 * mul; 
        }
    }

    for (int x = 0; x < SIZE; x++) {
        int count = 0;
        for (int y = 0; y < SIZE; y++) {
            if (board[y][x] == EMPTY) break; 
            if (board[y][x] == board[0][x]) { ++count; }
        }

        if (count >= SIZE) {
            if (board[0][x] == CROSS) return 1 * mul;
            else return -1 * mul;
        }
    }

    int count = 0;
    for (int i = 0, j = 0; i < SIZE || j < SIZE; i++, j++) {
        if (board[i][j] == EMPTY) {
            break;
        }

        if (board[i][j] == board[0][0]) {
            ++count;
        }
    }

    if (count >= SIZE) {
        if (board[0][0] == CROSS) { return 1 * mul; }
        else return -1 * mul;
    }

    count = 0;
    for (int i = 0, j = SIZE - 1; i < SIZE || j >= 0; i++, j--) {
        if (board[i][j] == EMPTY) {
            break;
        }

        if (board[i][j] == board[0][SIZE - 1]) {
            ++count;
        }
    }

    if (count >= SIZE) {
        if (board[0][SIZE - 1] == CROSS) { return 1 * mul; }
        else return -1 * mul;
    }

    return 0;
}

vector<Move> Board::freeCells() {
    vector<Move> freeCells;

    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            if (board[y][x] == EMPTY) {
                freeCells.push_back(Move(crossMove, y, x));
            }
        }
    }

    return freeCells;
}

void Board::makeMove(Move& move) {
    if (move.crossMove) {
        setFigure(CROSS, move.y, move.x);
    }
    else {
        setFigure(ZERO, move.y, move.x);
    }

    crossMove = !crossMove;
}

int Board::makeRandomMove() {
    srand(time(NULL));
    int randomMove = rand() % 9;
    return randomMove;
}

void Board::printBoard() {
    cout << endl;
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            if (board[y][x] == CROSS) {
                cout << "X ";
            }
            else if (board[y][x] == ZERO) {
                cout << "O ";
            }
            else {
                cout << "= ";
            }
        }

        cout << "\n";
    }
}

bool Board::testOfLegalMove(Move& move) {
    vector<Move> moves = freeCells();

    for (int i = 0; i < moves.size(); i++) {
        if (moves[i] == move) { 
            return true; 
        }
    }

    return false;
}

bool Board::isTerminate() {
    if (checkRow() != 0) {
        return true;
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == EMPTY) { 
                return false; 
            }
        }
    }

    return true;
}
