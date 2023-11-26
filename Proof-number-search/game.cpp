#include "Game.h"

Game::Game() {
    this->height = 0;
    this->width = 0;
    this->fields = nullptr;
    this->numberOfPossibleMoves = 0;
}

Game::Game(short M, short N, short **fields) {
    this->height = N;
    this->width = M;

    this->fields = new short *[N];
    for (short i = 0; i < N; ++i) {
        this->fields[i] = new short [M];
        for (short j = 0; j < M; ++j) {
            this->fields[i][j] = fields[i][j];
        }
    }
    this->numberOfPossibleMoves = numberOfFreeFieldsOnBoard();
}

short Game::numberOfFreeFieldsOnBoard() const {
    short numberOfFreeFieldsOnBoard = 0;
    for (short y = 0; y < this->height; y++) {
        for (short x = 0; x < this->width; x++) {
            if (this->fields[y][x] == NONE)
                numberOfFreeFieldsOnBoard++;
        }
    }
    return numberOfFreeFieldsOnBoard;
}

short Game::numberOfPointsInRowHorizontal(const short &x, const short &y, const short &player) const {
    short points = 0;
    for (short i = x; i >= 0; i--) {
        if (fields[y][i] == player) points++;
        else break;
    }
    for (short i = x + 1; i < width; i++) {
        if (fields[y][i] == player) points++;
        else break;
    }
    return points;
}

short Game::numberOfPointsInRowVertical(const short &x, const short &y, const short &player) const {
    short points = 0;
    for (short i = y; i >= 0; i--) {
        if (fields[i][x] == player) points++;
        else break;
    }
    for (short i = y + 1; i < height; i++) {
        if (fields[i][x] == player) points++;
        else break;
    }
    return points;
}

short Game::numberOfPointsInRowDiagonalLeft(const short &x, const short &y, const short &player) const {
    short points = 0;
    short i = y, j = x;
    while (i >= 0 && j < width) {
        if (fields[i][j] == player) points++;
        else break;
        i--;
        j++;
    }
    i = y + 1;
    j = x - 1;
    while (i >= 0 && i < height && j < width && j >= 0) {
        if (fields[i][j] == player) points++;
        else break;
        i++;
        j--;
    }
    return points;
}

short Game::numberOfPointsInRowDiagonalRight(const short &x, const short &y, const short &player) const {
    short points = 0;
    short i = y, j = x;
    while (i >= 0 && j >= 0) {
        if (fields[i][j] == player) points++;
        else break;
        i--;
        j--;
    }
    i = y + 1;
    j = x + 1;
    while (i < height && j < width) {
        if (fields[i][j] == player) points++;
        else break;
        i++;
        j++;
    }
    return points;
}

void Game::putPawnOnField(short freeFieldIndex, const short &player) {
    short freeFieldsCount = 0;
    for (short y = 0; y < height; y++) {
        for (short x = 0; x < width; x++) {
            if (fields[y][x] == NONE) {
                if (freeFieldsCount == freeFieldIndex) {
                    lastMoveX = x;
                    lastMoveY = y;
                    fields[y][x] = player;
                    numberOfPossibleMoves--;
                    return;
                }
                freeFieldsCount++;
            }
        }
    }
}

Game &Game::operator=(const Game &other) {
    if (this == &other)
        return *this;

    this->height = other.height;
    this->width = other.width;
    this->numberOfPossibleMoves = other.numberOfPossibleMoves;

    this->fields = new short *[other.height];
    for (short i = 0; i < height; ++i) {
        this->fields[i] = new short [other.width];
        for (short j = 0; j < width; ++j)
            this->fields[i][j] = other.fields[i][j];
    }

    return *this;
}

Game::Game(const Game &other) {
    this->height = other.height;
    this->width = other.width;
    this->numberOfPossibleMoves = other.numberOfPossibleMoves;

    this->fields = new short *[height];
    for (short i = 0; i < height; ++i) {
        this->fields[i] = new short [width];

    }

    for (short i = 0; i < height; ++i) {
        for (short j = 0; j < width; ++j) {
            this->fields[i][j] = other.fields[i][j];
        }
    }
}

Game::~Game() {
    for (short i = 0; i < height; ++i) {
        delete[] fields[i];
    }
    delete[] fields;
}
