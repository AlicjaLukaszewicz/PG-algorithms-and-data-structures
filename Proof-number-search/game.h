#ifndef PROJECT_3_BOARD_H
#define PROJECT_3_BOARD_H

#define NO_NEW_MOVE -1
#define NONE 0
#define PLAYER_X 1
#define PLAYER_0 2

class Game {
public:
    short** fields;
    short height;
    short width;
    short lastMoveX = NO_NEW_MOVE;
    short lastMoveY = NO_NEW_MOVE;
    int numberOfPossibleMoves;

    Game();
    Game(short M, short N, short ** fields);
    Game(const Game& other);

    short numberOfFreeFieldsOnBoard() const;

    short numberOfPointsInRowHorizontal(const short& x, const short& y, const short& player) const;
    short numberOfPointsInRowVertical(const short& x, const short& y, const short& player) const;
    short numberOfPointsInRowDiagonalLeft(const short& x, const short& y, const short& player) const;
    short numberOfPointsInRowDiagonalRight(const short& x, const short& y, const short& player) const;

    void putPawnOnField(short freeFieldIndex, const short& player);

    Game& operator=(const Game& other);

    ~Game();
};


#endif //PROJECT_3_BOARD_H
