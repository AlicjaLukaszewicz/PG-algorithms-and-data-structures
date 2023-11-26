#include "Board.h"
#include <iostream>

//Constructors
Board::Board() {
    this->N = 0;
    this->M = 0;
    this->fields = nullptr;
    this->numberOfPossibleMoves = 0;
}
Board::Board(int M, int N, int** fields) {
    this->N = N;
    this->M = M;

    this->fields = new int *[N];
    for (int i = 0; i < N; ++i) {
        this->fields[i] = new int[M];
        for (int j = 0; j < M; ++j) {
            this->fields[i][j] = fields[i][j];
        }
    }
    this->numberOfPossibleMoves = getNumberOfPossibleMoves();
}
Board::Board(const Board &other) {
    this->N = other.N;
    this->M = other.M;
    this->numberOfPossibleMoves = other.numberOfPossibleMoves;

    this->fields = new int*[N];
    for (int i = 0; i < N; ++i) {
        this->fields[i] = new int[M];
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            this->fields[i][j] = other.fields[i][j];
        }
    }
}

//Methods
void Board::printBoard() const {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            printf("%d ", fields[i][j]);
        }
        printf("\n");
    }
}

int Board::getNumberOfPossibleMoves() const {
    int possibleMoves = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (fields[i][j] == 0)
                possibleMoves++;
        }
    }
    return possibleMoves;
}

int Board::pointsHorizontal(const int& x,const int& y, const int& activePlayer) const {
    //y - const. -> width
    int points = 0;
    //Check left side of x
    for (int i = x; i >= 0; i--) {
        if (fields[y][i] == activePlayer) points++;
        else break;
    }
    //Check right side of x
    for (int i = x+1; i < M; i++) {
        if (fields[y][i] == activePlayer) points++;
        else break;
    }
    return points;
}
int Board::pointsVertical(const int& x,const int& y, const int& activePlayer) const {
    //x - const. -> height
    int points = 0;
    //Check up of y
    for (int i = y; i >= 0; i--) {
        if (fields[i][x] == activePlayer) points++;
        else break;
    }
    //Check down of y
    for (int i = y+1; i < N; i++) {
        if (fields[i][x] == activePlayer) points++;
        else break;
    }
    return points;
}

int Board::pointsDiagonalLeft(const int& x,const int& y, const int& activePlayer) const {
    int points = 0;
    //Check "/" up side -> x increases, y decreases
    int i=y, j=x;
    while (i >= 0 && j < M) {
        if (fields[i][j] == activePlayer) points++;
        else break;
        i--; j++;
    }
    //Check "/" down side -> x decreases, y increases
    i=y+1; j=x-1;
    while (i >= 0 && i < N && j < M && j >= 0) {
        if (fields[i][j] == activePlayer) points++;
        else break;
        i++; j--;
    }
    return points;
}
int Board::pointsDiagonalRight(const int& x,const int& y, const int& activePlayer) const {
    int points = 0;
    //Check "\" up side -> x decreases, y decreases
    int i=y, j=x;
    while (i >= 0 && j >= 0) {
        if (fields[i][j] == activePlayer) points++;
        else break;
        i--; j--;
    }
    //Check "\" down side -> x increases, y increases
    i=y+1; j=x+1;
    while (i < N && j < M) {
        if (fields[i][j] == activePlayer) points++;
        else break;
        i++; j++;
    }
    return points;
}

void Board::makeAMoveOnField(int index, int player) {
    int freeFieldsCount = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (fields[i][j] == NONE) {
                if (freeFieldsCount == index) {
                    newX = j; newY = i;
                    fields[i][j] = player;
                    numberOfPossibleMoves--;
                    return;
                }
                freeFieldsCount++;
            }
        }
    }
}

Board &Board::operator=(const Board& other) {
    if (this == &other || &other == nullptr)
        return *this;

    this->N = other.N;
    this->M = other.M;
    this->numberOfPossibleMoves = other.numberOfPossibleMoves;

    this->fields = new int*[other.N];
    for (int i = 0; i < N; ++i) {
        this->fields[i] = new int[other.M];
        for (int j = 0; j < M; ++j)
            this->fields[i][j] = other.fields[i][j];
    }

    return  *this;
}

Board::~Board() {
    for (int i = 0; i < N; ++i) {
        delete [] fields[i];
    }
    delete [] fields;
}