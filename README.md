# Algorithms and Data Structures Implementations

This repository contains projects developed during the second semester of my Computer Science course, with a primary focus on the subject of "Algorithms and Data Structures." All implementations are written in the C programming language.

## Project 1: Partition

A partition of `n` is a representation of this number as a sum of positive integers: `n = n1 + n2 + ... + nr` such that `n1 ≥ n2 ≥ ... ≥ nr`. The numbers `n1, n2, ..., nr` are called parts.

The partition `19 = 5 + 3 + 3 + 2 + 2 + 2 + 2` can be written as `53224`, while `19 = 5 + 2 + 2 + 2 + 2 + 2 + 2 + 2` can be written as `527`. Hence the upper indices are `124` and `107`, thus `5 + 3 + 3 + 2 + 2 + 2 + 2` is larger than `5 + 2 + 2 + 2 + 2 + 2 + 2 + 2`, since `124` is larger than `107`.

### Problem

Starting from the smallest partition, write all partitions of the integer `n`, where the parts are prime numbers and the largest part is equal to `k`. `n` can be stored in a byte.

### Input

In the first line: a number of the rest lines
Then, separated by spaces: `n` and `k`

### Output

Partitions separated by `+`. If there is no partition, then write nothing.

## Project 2: Cachelist

This project focuses on implementing a simple double-linked list. The list is designed to efficiently manage memory, considering the organization of cache memory in computers.

## Operations:

1. `i x y`: Initialize an iterator to position `y`. `y` can be [BEG]inning, [END], or a number.

2. `+ x`: Move an iterator forward.

3. `- x`: Move an iterator backward.

4. `.A x y`: Add the number `y` before the position `x`. `x` can be [BEG]inning, [END], or a number of iterator.

5. `A. x y`: Add the number `y` after the position `x`. `x` can be [BEG]inning, [END], or a number of iterator.

6. `R x`: Remove an element at position `x`. `x` can be [BEG]inning, [END], or a number of iterator.

7. `P p`: Print the number at the position `p`. `p` can be [ALL] (print from head to tail) or a number of iterator.

## Project 3: NMK Solver

This project involves two parts. The first part focuses on implementing a generalized Tic-Tac-Toe game engine known as the NMK game (https://en.wikipedia.org/wiki/M,n,k-game). The second part involves implementing a program that solves these games using the min-max algorithm (https://en.wikipedia.org/wiki/Minimax).

### Part 1: NMK Game Engine

The NMK game engine takes three parameters, `N`, `M`, and `K`, where (`N x M`) is the size of the board, and `K` is the number of contiguous fields needed to win. The engine implements a deterministic move generator, adding player pieces (e.g., crosses or circles) starting from the top-left corner, continuing in rows, and then columns.

### Part 2: Solver Algorithm

The solver algorithm aims to solve a given state of the NMK game using the min-max algorithm. The deterministic nature of these games ensures that the solution is always conclusive, either a win, loss, or tie, assuming both players play optimally.

#### Algorithm Optimizations:

1. Stop searching for minimum values if a result of -1 is obtained, or maximum values if a result of 1 is obtained.
2. Detect and mark situations where a player has a winning move in the next turn, unless the opponent created a threat earlier. This helps in pruning the search tree.

### Commands

The program should support the following commands:

1. `GEN_ALL_POS_MOV N M K ActivePlayer`: Generate all possible moves along with their count.
   
2. `GEN_ALL_POS_MOV_CUT_IF_GAME_OVER N M K ActivePlayer`: Generate all possible moves, and if one is winning or ending, generate only the first one.

3. `SOLVE_GAME_STATE N M K ActivePlayer`: Solve the game state and provide the result - FIRST_PLAYER_WINS, SECOND_PLAYER_WINS, or BOTH_PLAYERS_TIE.


## Project 4: Proof Number Search

This project focuses on solving the generalized Tic-Tac-Toe game (similar to the NMK Solver task) using the Proof Number Search (PNS) algorithm.

