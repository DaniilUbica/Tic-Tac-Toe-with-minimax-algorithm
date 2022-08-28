#include "Game.h"

Game::Game() {
    menu();
}
Game::~Game() {}

double Game::minimax(Board& board, int depth) {
    if (board.isTerminate()) {
        return board.checkRow();
    }

    double max = -INFINITY;
    vector<Move> availableMoves = board.freeCells();

    Board savedBoard = board;
    Move currentMove;

    for (int i = 0; i < availableMoves.size(); i++) {
        board.makeMove(availableMoves[i]);
        double tmp = -minimax(board, depth + 1);
        board = savedBoard;

        if (tmp > max) {
            max = tmp;
            currentMove = availableMoves[i];
        }
    }

    if (depth == 0) {
        if (availableMoves.size() > 0) {
            board.makeMove(currentMove);
        }
    }

    return max;
}

int Game::startGameWithPc() {
    int cellToMove;
    int cellToMovePc;
    int movesCounter = 0;
    int player;
    bool randomMoveMade = true;

    cout << "Choose your figure ('X' - 1, 'O' - 0): ";
    cin >> player;
    if (player == 0) {
        player = -1;
        randomMoveMade = false;
    }

    if (player == 1) {
        board.printBoard();
    }

    while (movesCounter <= SIZE * SIZE) {
        if (player == 1) {
            cout << "Enter the number of cell to move (1-" << SIZE * SIZE << "): ";
            cin >> cellToMove;
            cellToMove--;
            Move move = Move(board.crossMove, cellToMove / SIZE, cellToMove % SIZE);
            while (!board.testOfLegalMove(move)) {
                cout << "Enter the number of cell to move (1-" << SIZE * SIZE << "): ";
                cin >> cellToMove;
                cellToMove--;
                move = Move(board.crossMove, cellToMove / SIZE, cellToMove % SIZE);
            }
            board.makeMove(move);
            movesCounter++;
            player = -player;
        }
        else {
            if (!randomMoveMade) {
                cellToMovePc = board.makeRandomMove();
                Move move = Move(board.crossMove, cellToMovePc / SIZE, cellToMovePc % SIZE);
                while (!board.testOfLegalMove(move)) {
                    move = Move(board.crossMove, cellToMovePc / SIZE, cellToMovePc % SIZE);
                }
                board.makeMove(move);
                movesCounter++;
                randomMoveMade = true;
                player = -player;
                board.printBoard();
            }
            else {
                minimax(board, 0);
                movesCounter++;
                board.printBoard();
                player = -player;
            }
        }
        if (board.checkRow() * player > 0) {
            cout << "You win!\n";
            return 0;
        }
        else if (board.checkRow() * player < 0) {
            cout << "PC win!\n";
            return 0;
        }
    }

    cout << "Draw!\n";
    return 0;
}

int Game::startGameWithPlayer() {
    int cellToMove;
    int movesCounter = 0;
    int player = 1;

    while (movesCounter <= SIZE * SIZE) {
        if (player == 1) {
            board.printBoard();
            cout << "Enter the number of cell to move (1-" << SIZE * SIZE << "): ";
            cin >> cellToMove;
            cellToMove--;
            Move move = Move(board.crossMove, cellToMove / SIZE, cellToMove % SIZE);
            while (!board.testOfLegalMove(move)) {
                cout << "Enter the number of cell to move (1-" << SIZE * SIZE << "): ";
                cin >> cellToMove;
                cellToMove--;
                move = Move(board.crossMove, cellToMove / SIZE, cellToMove % SIZE);
            }
            board.makeMove(move);
            movesCounter++;
            player = -player;
        }
        else {
            board.printBoard();
            cout << "Enter the number of cell to move (1-" << SIZE * SIZE << "): ";
            cin >> cellToMove;
            cellToMove--;
            Move move = Move(board.crossMove, cellToMove / SIZE, cellToMove % SIZE);
            while (!board.testOfLegalMove(move)) {
                cout << "Enter the number of cell to move (1-" << SIZE * SIZE << "): ";
                cin >> cellToMove;
                cellToMove--;
                move = Move(board.crossMove, cellToMove / SIZE, cellToMove % SIZE);
            }
            board.makeMove(move);
            movesCounter++;
            player = -player;
        }
        if (board.checkRow() * player > 0) {
            board.printBoard();
            cout << "'X' is a winner!\n";
            return 0;
        }
        else if (board.checkRow() * player < 0) {
            board.printBoard();
            cout << "'O' is a winner!\n";
            return 0;
        }
    }
    board.printBoard();
    cout << "Draw!\n";
    return 0;
}

int Game::startDemoGame() {
    int cellToMove = board.makeRandomMove();
    int movesCounter = 0;
    int player = 1;
    bool randomMoveMade = false;

    while (movesCounter <= SIZE * SIZE) {
        if (player == 1) {
            if (!randomMoveMade) {
                Move move = Move(board.crossMove, cellToMove / SIZE, cellToMove % SIZE);
                while (!board.testOfLegalMove(move)) {
                    move = Move(board.crossMove, cellToMove / SIZE, cellToMove % SIZE);
                }
                board.makeMove(move);
                movesCounter++;
                player = -player;
                board.printBoard();
                randomMoveMade = true;
            }
            else {
                minimax(board, 0);
                movesCounter++;
                board.printBoard();
                player = -player;
            }
        }
        else {
            minimax(board, 0);
            movesCounter++;
            board.printBoard();
            player = -player;
        }
        if (board.checkRow() * player > 0) {
            cout << "'X' win!\n";
            return 0;
        }
        else if (board.checkRow() * player < 0) {
            cout << "'O' win!\n";
            return 0;
        }
    }

    cout << "Draw!\n";
    return 0;
}

void Game::menu() {
    int choose;
    cout << "Choose the game mode: \n";
    cout << "Player VS Player - 1 \n";
    cout << "Player VS Computer - 2 \n";
    cout << "Demo game(computer VS computer) - 3 \n";
    cin >> choose;
    switch (choose) {
    case 1:
        startGameWithPlayer();
    case 2:
        startGameWithPc();
    case 3:
        startDemoGame();
    }
}