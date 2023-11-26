#ifndef PROJECT_3_BOARD_H
#define PROJECT_3_BOARD_H

#define NONE 0
#define PLAYER_X 1
#define PLAYER_O 2

class Board {
public:
    int** fields;
    int N; //N - height
    int M; //M - width
    int newX = -1;
    int newY = -1;
    int numberOfPossibleMoves;

    Board();
    Board(Board const& other);
    Board(int M, int N, int** fields);

    int getNumberOfPossibleMoves() const;

    int pointsHorizontal(const int& x,const int& y, const int& activePlayer) const;
    int pointsVertical(const int& x,const int& y, const int& activePlayer) const;
    int pointsDiagonalLeft(const int& x,const int& y, const int& activePlayer) const;
    int pointsDiagonalRight(const int& x,const int& y, const int& activePlayer) const;

    void printBoard() const;
    void makeAMoveOnField(int index, int player);

    Board& operator=(const Board& other);

    ~Board();
};


#endif //PROJECT_3_BOARD_H
