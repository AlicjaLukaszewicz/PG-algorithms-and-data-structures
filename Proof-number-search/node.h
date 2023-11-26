#ifndef MAIN_CPP_NODE_H
#define MAIN_CPP_NODE_H

#include "Game.h"

#define MY_INFINITY 35000

enum Type {
    OR_NODE = 0,
    AND_NODE = 1
};

enum Value {
    UNKNOWN = 0,
    PROVEN = 1,
    DISPROVEN = 2
};

class Node {
public:
    Game gameState;
    Node **children;
    short childrenCount;
    Node *parent;
    int proof;
    int disproof;
    Value value;
    Type type;
    bool expanded;
    short player;

    Node() : gameState(Game()) {
        children = nullptr;
        childrenCount = 0;
        parent = nullptr;
        proof = 1;
        disproof = 1;
        expanded = false;

        value = UNKNOWN;
        type = AND_NODE;
        player = NONE;
    }

    explicit Node(const Game &game) : gameState(game) {
        children = nullptr;
        childrenCount = 0;
        parent = nullptr;
        proof = 1;
        disproof = 1;
        expanded = false;

        value = UNKNOWN;
        type = AND_NODE;
        player = NONE;
    }

    Node(const Game &game, Type type, short opponent, Node *parent) : gameState(game) {
        this->children = nullptr;
        this->childrenCount = 0;
        this->parent = parent;
        this->player = opponent;
        this->type = type;
        proof = 1;
        disproof = 1;
        expanded = false;
    }
};


#endif //MAIN_CPP_NODE_H
