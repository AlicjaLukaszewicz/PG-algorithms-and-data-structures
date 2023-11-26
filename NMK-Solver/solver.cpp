#include "Solver.h"
#include <iostream>

#define minimum(a, b) (((a)<(b))?(a):(b))
#define maximum(a, b) (((a)>(b))?(a):(b))

Solver::Solver(const Board &newBoard, int inRow) : board(newBoard) {
    this->inRow = inRow;
}

bool Solver::hasGameEnded() const {
    for (int i = 0; i < board.N; ++i) {
        for (int j = 0; j < board.M; ++j) {
            if (board.fields[i][j] == NONE) return false;
        }
    }
    return true;
}

int Solver::hasSomeoneWonTheGame(const Board &gameBoard) const {
    for (int i = 0; i < gameBoard.N; i++) {
        for (int j = 0; j < gameBoard.M; j++) {
            if (gameBoard.fields[i][j] != NONE) {
                if (gameBoard.pointsHorizontal(j, i, gameBoard.fields[i][j]) >= inRow)
                    return gameBoard.fields[i][j];
                if (gameBoard.pointsVertical(j, i, gameBoard.fields[i][j]) >= inRow)
                    return gameBoard.fields[i][j];
                if (gameBoard.pointsDiagonalLeft(j, i, gameBoard.fields[i][j]) >= inRow)
                    return gameBoard.fields[i][j];
                if (gameBoard.pointsDiagonalRight(j, i, gameBoard.fields[i][j]) >= inRow)
                    return gameBoard.fields[i][j];
            }
        }
    }
    return NONE;
}

int Solver::hasSomeoneWonTheGameExtended(const Board &gameBoard) const {
    int posY = gameBoard.newY, posX = gameBoard.newX;
    if (gameBoard.fields[posY][posX] != NONE) {
        if (gameBoard.pointsHorizontal(posX, posY, gameBoard.fields[posY][posX]) >= inRow ||
            gameBoard.pointsVertical(posX, posY, gameBoard.fields[posY][posX]) >= inRow ||
            gameBoard.pointsDiagonalLeft(posX, posY, gameBoard.fields[posY][posX]) >= inRow ||
            gameBoard.pointsDiagonalRight(posX, posY, gameBoard.fields[posY][posX]) >= inRow )
                return gameBoard.fields[posY][posX];
    }
    return NONE;
}

void Solver::GenAllPosMov(int activePlayer) const {
    //Check if game ended - if it did return 0
    if (hasGameEnded() || hasSomeoneWonTheGame(board) != NONE)
        printf("%d \n", 0);
    else {
        //Return number of possible moves
        int possibleMoves = board.getNumberOfPossibleMoves();
        printf("%d \n", possibleMoves);

        //Generate possible moves and print them
        auto *scenarios = new Board[possibleMoves];
        for (int i = 0; i < possibleMoves; ++i) {
            scenarios[i] = board;
            scenarios[i].makeAMoveOnField(i, activePlayer);
            scenarios[i].printBoard();
        }
        delete[] scenarios;
    }
}

void Solver::GenAllPosMovCutIfGameOver(int activePlayer) const {
    //Check number of possible moves
    int possibleMoves = board.getNumberOfPossibleMoves();

    //If there are no possible moves or game won - return 0
    if (hasGameEnded() || hasSomeoneWonTheGame(board) != NONE)
        printf("%d\n", 0);
    else {
        auto *scenarios = new Board[possibleMoves];

        for (int i = 0; i < possibleMoves; ++i) {
            int moves = 0;
            scenarios[i] = board;
            scenarios[i].makeAMoveOnField(i, activePlayer);

            moves = board.getNumberOfPossibleMoves();
            //Only active player makes moves, so it's only possible that he won
            //or there was a tie - no possible moves
            if (hasSomeoneWonTheGame(scenarios[i]) == activePlayer || moves == 0) {
                printf("%d\n", 1);
                scenarios[i].printBoard();
                delete[] scenarios;
                return;
            }
        }
        printf("%d\n", possibleMoves);
        for (int i = 0; i < possibleMoves; ++i) {
            scenarios[i].printBoard();
        }
        delete[] scenarios;
    }
}

int Solver::minMax(const Board &gameState, int activePlayer) {
    //need a score that we want to accomplish -1 or 1 -> that is const
    int best;

    if (activePlayer == 1) best = -1;
    else best = 1;

    int numberOfFreeFields = gameState.numberOfPossibleMoves;

    if (gameState.newX == -1 && gameState.newY == -1) {
        int player = hasSomeoneWonTheGame(gameState);
        if (player == PLAYER_X) return 1;
        else if (hasSomeoneWonTheGame(gameState) == PLAYER_O) return -1;
    } /*
    else {
        int player = hasSomeoneWonTheGameExtended(gameState);
        if (player == PLAYER_X) return 1;
        else if (player == PLAYER_O) return -1;
    }
    */
    if (numberOfFreeFields == 0) return 0;

    //Generate possible moves for active player
    Board *possibleMoves = new Board[numberOfFreeFields];

    for (int i = 0; i < numberOfFreeFields; ++i) {
        possibleMoves[i] = gameState;
        possibleMoves[i].makeAMoveOnField(i, activePlayer);

        int player = hasSomeoneWonTheGameExtended(possibleMoves[i]);
        if (player == PLAYER_X) return 1;
        else if (player == PLAYER_O) return -1;
    }

    if (activePlayer == PLAYER_X) {
        for (int i = 0; i < numberOfFreeFields; ++i) {
            if (best == 1) break;
            best = maximum(best, minMax(possibleMoves[i], PLAYER_O));
        }
        delete[] possibleMoves;
        return best;
    } else {
        for (int i = 0; i < numberOfFreeFields; ++i) {
            if (best == -1) break;
            best = minimum(best, minMax(possibleMoves[i], PLAYER_X));
        }
        delete[] possibleMoves;
        return best;
    }
}


void Solver::SolveGameState(int startingPlayer) {
    int score = minMax(board, startingPlayer);
    if (score == -1) {
        printf("SECOND_PLAYER_WINS\n");
    } else if (score == 1) {
        printf("FIRST_PLAYER_WINS\n");
    } else {
        printf("BOTH_PLAYERS_TIE\n");
    }
}


