#include <iostream>
#include "Solver.h"
#include "Game.h"

#define MAX_COMMAND_LENGTH 17

bool compareStrings(const char *input, const char *command) {
    int length = 0;
    while (command[length] != '\0') length++;

    for (int i = 0; i < length; ++i) {
        if (input[i] != command[i])
            return false;
    }
    if (input[length] != '\0') return false;
    return true;
}

void deleteChildren(Node* node) {
    for (int i = 0; i < node->childrenCount; ++i) {
        if (node->children[i]->childrenCount != 0) {
            deleteChildren(node->children[i]);
        }
        delete node->children[i];
    }
    delete[] node->children;
}

void deleteTree(Node* root) {
    deleteChildren(root);
    delete root;
}

void restoreNode(Node* node) {
    node->childrenCount=0;
    node->proof=1;
    node->disproof=1;
    node->value=UNKNOWN;
    node->expanded= false;
    node->type = AND_NODE;
}

int main() {
    char command[MAX_COMMAND_LENGTH];
    char solveGameState[] = {"SOLVE_GAME_STATE"};

    short N, M, K, player;
    bool hasFirstWon;
    bool hasSecondWon;

    while (true) {
        scanf("%16s", command);
        if (feof(stdin) != 0)
            break;

        scanf("%hd %hd %hd %hd", &N, &M, &K, &player);
        short **fields;

        fields = new short *[N];
        for (int i = 0; i < N; ++i) {
            fields[i] = new short [M];
        }

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                scanf("%hd", &(fields[i][j]));
            }
        }

        Game newGame = Game(M, N, fields);

        if (compareStrings(command, solveGameState)) {
            Solver solver = Solver(newGame, K);
            Node* node = new Node(newGame);
            node->player = player;

            if (player == PLAYER_X) { // first move -> player X
                node->type = OR_NODE;
                solver.setCheckedPlayer(PLAYER_X);
                hasFirstWon = solver.PNS(node);
                if (!hasFirstWon) {
                    deleteChildren(node);
                    restoreNode(node);

                    solver.setCheckedPlayer(PLAYER_0);
                    hasSecondWon = solver.PNS(node);
                } else hasSecondWon = false;
            } else { // first move -> player 0
                node->type = OR_NODE;
                solver.setCheckedPlayer(PLAYER_0);
                hasSecondWon = solver.PNS(node);
                if (!hasSecondWon) {
                    deleteChildren(node);
                    restoreNode(node);

                    solver.setCheckedPlayer(PLAYER_X);
                    hasFirstWon = solver.PNS(node);
                } else hasFirstWon = false;
            }

            if (hasFirstWon && !hasSecondWon) printf("FIRST_PLAYER_WINS\n");
            else if (!hasFirstWon && hasSecondWon) printf("SECOND_PLAYER_WINS\n");
            else printf("BOTH_PLAYERS_TIE\n");

            deleteTree(node);
        }

        for (int i = 0; i < N; ++i) {
            delete[] fields[i];
        }
        delete[] fields;
    }
    return 0;
}
