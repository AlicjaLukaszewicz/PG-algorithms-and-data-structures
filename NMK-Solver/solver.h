#ifndef PROJECT_3_SOLVER_H
#define PROJECT_3_SOLVER_H
#include "Board.h"

class Solver {
    Board board;
    int inRow;

public:
    Solver(const Board& newBoard, int inRow);
    int minMax(const Board& gameState, int activePlayer);

    bool hasGameEnded() const;
    int hasSomeoneWonTheGame(const Board& gameBoard) const;
    int hasSomeoneWonTheGameExtended(const Board& gameBoard) const;

    void GenAllPosMov(int activePlayer) const;
    void GenAllPosMovCutIfGameOver(int activePlayer) const;
    void SolveGameState(int startingPlayer);
};


#endif //PROJECT_3_SOLVER_H
