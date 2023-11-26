#ifndef PROJECT_3_SOLVER_H
#define PROJECT_3_SOLVER_H

#include "Game.h"
#include "Node.h"

int min(int a, int b) {
    if (a < b) return a;
    else return b;
}

short getOpponent(Node *node) {
    if (node->player == PLAYER_X) return PLAYER_0;
    else return PLAYER_X;
}

Type changeType(Node *node) {
    if (node->type == OR_NODE) return AND_NODE;
    else return OR_NODE;
}

class Solver {
    Game gameState;
    short inRow;
    short checkedPlayer;

public:
    Solver(const Game &newGame, short inRow) : gameState(newGame) {
        this->inRow = inRow;
    }

    void setCheckedPlayer(short player) {
        checkedPlayer = player;
    }

    short whoWonCheckWholeBoard(const Game &state) const {
        for (short y = 0; y < state.height; y++) {
            for (short x = 0; x < state.width; x++) {
                if (state.fields[y][x] != NONE) {
                    if (state.numberOfPointsInRowHorizontal(x, y, state.fields[y][x]) >= inRow)
                        return state.fields[y][x];
                    if (state.numberOfPointsInRowVertical(x, y, state.fields[y][x]) >= inRow)
                        return state.fields[y][x];
                    if (state.numberOfPointsInRowDiagonalLeft(x, y, state.fields[y][x]) >= inRow)
                        return state.fields[y][x];
                    if (state.numberOfPointsInRowDiagonalRight(x, y, state.fields[y][x]) >= inRow)
                        return state.fields[y][x];
                }
            }
        }
        return NONE;
    }

    short whoWonCheckLastMove(const Game &state) const {
        short y = state.lastMoveY, x = state.lastMoveX;
        if (state.fields[y][x] != NONE) {
            if (state.numberOfPointsInRowHorizontal(x, y, state.fields[y][x]) >= inRow ||
                state.numberOfPointsInRowVertical(x, y, state.fields[y][x]) >= inRow ||
                state.numberOfPointsInRowDiagonalLeft(x, y, state.fields[y][x]) >= inRow ||
                state.numberOfPointsInRowDiagonalRight(x, y, state.fields[y][x]) >= inRow)
                return state.fields[y][x];
        }
        return NONE;
    }

    short hasGameEnded(const Game &state) {
        short winner = whoWonCheckWholeBoard(state);
        if (winner == checkedPlayer)
            return 0;
        else if (winner != NONE || state.numberOfPossibleMoves == 0)
            return 1;
        else
            return 2;
    }

    bool PNS(Node *root) {
        short winner = hasGameEnded(root->gameState);
        if (winner == 0) return true;
        else if (winner == 1) return false;

        Node *current = root;
        Node *mostProving;
        while (root->proof != 0 && root->disproof != 0) {
            mostProving = selectMostProvingNode(current);
            expandNode(mostProving);
            current = updateAncestors(mostProving, root);
        }
        if (root->proof == 0)
            return true;
        else
            return false;
    }

    void setProofAndDisproofNumbers(Node *node) {
        if (node->expanded) {
            if (node->type == AND_NODE) {
                node->proof = 0;
                node->disproof = MY_INFINITY;
                for (int i = 0; i < node->childrenCount; ++i) {
                    if (node->proof != MY_INFINITY)
                        node->proof += node->children[i]->proof;
                    node->disproof = min(node->disproof, node->children[i]->disproof);
                }
            } else {
                node->proof = MY_INFINITY;
                node->disproof = 0;
                for (int i = 0; i < node->childrenCount; ++i) {
                    if (node->disproof != MY_INFINITY)
                        node->disproof += node->children[i]->disproof;
                    node->proof = min(node->proof, node->children[i]->proof);
                }
            }
        } else {
            if (node->value == DISPROVEN) {
                node->proof = MY_INFINITY;
                node->disproof = 0;
            } else if (node->value == PROVEN) {
                node->proof = 0;
                node->disproof = MY_INFINITY;
            } else {
                node->proof = 1;
                node->disproof = 1;
            }
        }
    }

    Node *selectMostProvingNode(Node *node) {
        while (node->expanded) {
            int value = MY_INFINITY;
            Node *best = nullptr;
            if (node->type == AND_NODE) {
                for (int i = 0; i < node->childrenCount; ++i) {
                    if (value > node->children[i]->disproof) {
                        best = node->children[i];
                        value = node->children[i]->disproof;
                    }
                }
            } else {
                for (int i = 0; i < node->childrenCount; ++i) {
                    if (value > node->children[i]->proof) {
                        best = node->children[i];
                        value = node->children[i]->proof;
                    }
                }
            }
            node = best;
        }
        return node;
    }

    void evaluate(Node *node) const {
        short winner;
        if (node->gameState.lastMoveX == -1) {
            winner = whoWonCheckWholeBoard(node->gameState);
        } else {
            winner = whoWonCheckLastMove(node->gameState);
        }

        if (winner == checkedPlayer) node->value = PROVEN;
        else if (winner == 0 && node->gameState.numberOfPossibleMoves != 0) node->value = UNKNOWN;
        else node->value = DISPROVEN;
    }

    void expandNode(Node *node) {
        node->expanded = true;

        short numberOfFreeFields = node->gameState.numberOfPossibleMoves;
        node->children = new Node *[numberOfFreeFields];
        node->childrenCount = numberOfFreeFields;

        for (short i = 0; i < numberOfFreeFields; ++i) {
            // Generating children
            node->children[i] = new Node(node->gameState, changeType(node), getOpponent(node), node);
            node->children[i]->gameState.putPawnOnField(i, node->player);

            // Updating children
            evaluate(node->children[i]);
            setProofAndDisproofNumbers(node->children[i]);
            if (node->type == AND_NODE) {
                if (node->children[i]->disproof == 0) {
                    // Creating the rest of nodes with default values
                    if (i+1 < numberOfFreeFields) {
                        for (short j = i+1; j < numberOfFreeFields; ++j) {
                            node->children[j] = new Node();
                        }
                    }
                    break;
                }
            } else {
                if (node->children[i]->proof == 0) {
                    // Creating the rest of nodes with default values
                    if (i+1 < numberOfFreeFields) {
                        for (short j = i+1; j < numberOfFreeFields; ++j) {
                            node->children[j] = new Node();
                        }
                    }
                    break;
                }
            }
        }
    }

    Node *updateAncestors(Node *node, Node *root) {
        while (node != root) {
            int oldProof = node->proof;
            int oldDisproof = node->disproof;
            setProofAndDisproofNumbers(node);
            if (node->proof == oldProof && node->disproof == oldDisproof)
                return node;
            node = node->parent;
        }
        setProofAndDisproofNumbers(root);
        return root;
    }
};

#endif
