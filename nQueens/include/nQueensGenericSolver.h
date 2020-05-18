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
    std::pair<int, int> solvePuzzle() override;

protected:
    virtual int runSolver() = 0;
    virtual void printPuzzle() override;
    const std::string solverType;
    NqBoard board;
};

#endif //AILABGENETICALGORITHM_NQUEENSGENERICSOLVER_H
