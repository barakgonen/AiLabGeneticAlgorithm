//
// Created by barak on 09/05/2020.
//

#ifndef AILABGENETICALGORITHM_NQUEENSMINIMALCONFLICTSSOLVER_H
#define AILABGENETICALGORITHM_NQUEENSMINIMALCONFLICTSSOLVER_H


#include "nQueensGenericSolver.h"

class nQueensMinimalConflictsSolver : public nQueensGenericSolver{
public:
    nQueensMinimalConflictsSolver(const NqBoard& board);
    void solvePuzzle() override;

private:
    int calculateConflictsForSpecificQueen(int queenRow);
};


#endif //AILABGENETICALGORITHM_NQUEENSMINIMALCONFLICTSSOLVER_H
