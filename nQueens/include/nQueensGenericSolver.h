//
// Created by barak on 04/05/2020.
//

#ifndef AILABGENETICALGORITHM_NQUEENSGENERICSOLVER_H
#define AILABGENETICALGORITHM_NQUEENSGENERICSOLVER_H

#include "InQueensSolver.h"
#include "nQueensBoard.h"
#include "string"

class nQueensGenericSolver : public InQueensSolver {
public:
    nQueensGenericSolver(const NqBoard& board, std::string solverType);
    void solvePuzzle() override;

protected:
    virtual int runSolver() = 0;
    void printPuzzle() override;
    const std::string solverType;
    NqBoard board;
};

#endif //AILABGENETICALGORITHM_NQUEENSGENERICSOLVER_H
