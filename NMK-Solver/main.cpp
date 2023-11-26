#include <iostream>
#include "Solver.h"
#include "Board.h"

#define MAX_COMMAND_LENGTH 33
using namespace std;

bool compare(char* input, char* command) {
    int length = 0;
    while (command[length] != '\0') length++;

    for (int i = 0; i < length; ++i) {
        if (input[i] != command[i])
            return false;
    }
    if (input[length] != '\0') return false;
    return true;
}

int main() {
    char command[MAX_COMMAND_LENGTH];
    char solveGameState[] = {"SOLVE_GAME_STATE"};
    char genAllPosMov[] = {"GEN_ALL_POS_MOV"};
    char genAllPosMovCutIfOver[] = {"GEN_ALL_POS_MOV_CUT_IF_GAME_OVER"};

    int N, M, K, player;

    while (true) {
        scanf("%32s", command);
        if (feof(stdin) != 0)
            break;

        scanf("%d %d %d %d", &N, &M, &K, &player);
        int **fields;

        fields = new int *[N];
        for (int i = 0; i < N; ++i) {
            fields[i] = new int[M];
        }
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                scanf("%d", &(fields[i][j]));
            }
        }
        Board newGame = Board(M, N, fields);
        Solver solver = Solver(newGame, K);

        if (compare(command, genAllPosMov)) {
            solver.GenAllPosMov(player);
        } else if (compare(command, genAllPosMovCutIfOver)) {
            solver.GenAllPosMovCutIfGameOver(player);
        } else if (compare(command, solveGameState)) {
            solver.SolveGameState(player);
        }

        for (int i = 0; i < N; ++i) {
            delete [] fields[i];
        }
        delete [] fields;
    }
    return 0;
}
