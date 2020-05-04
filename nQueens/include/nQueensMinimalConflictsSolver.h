//
// Created by barak on 03/05/2020.
//

#ifndef AILABGENETICALGORITHM_NQUEENSMINIMALCONFLICTSSOLVER_H
#define AILABGENETICALGORITHM_NQUEENSMINIMALCONFLICTSSOLVER_H

#include "nQueensGenericSolver.h"

class nQueensMinimalConflictsSolver : public nQueensGenericSolver{
public:
    nQueensMinimalConflictsSolver(const NqBoard& board);
    void solvePuzzle() override;

private:
    void initialize();

    void MinConflicts();

    int HighestConflicts();
};

#endif //AILABGENETICALGORITHM_NQUEENSMINIMALCONFLICTSSOLVER_H
