//
// Created by barak on 04/05/2020.
//

#include "../include/nQueensGenericSolver.h"

nQueensGenericSolver::nQueensGenericSolver(const NqBoard &board)
: board{board}
{
}

void nQueensGenericSolver::printPuzzle() {
    board.printBoard();
}