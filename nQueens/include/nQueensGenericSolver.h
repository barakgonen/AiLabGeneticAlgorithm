//
// Created by barak on 04/05/2020.
//

#ifndef AILABGENETICALGORITHM_NQUEENSGENERICSOLVER_H
#define AILABGENETICALGORITHM_NQUEENSGENERICSOLVER_H

#include "InQueensSolver.h"
#include "nQueensBoard.h"

class nQueensGenericSolver : public InQueensSolver{
public:
    nQueensGenericSolver(const NqBoard& board);
    void printPuzzle() override;
protected:
    NqBoard board;
};

#endif //AILABGENETICALGORITHM_NQUEENSGENERICSOLVER_H
