//
// Created by barak on 30/04/2020.
//

#ifndef AILABGENETICALGORITHM_NQUEENSGENETICSOLVER_H
#define AILABGENETICALGORITHM_NQUEENSGENETICSOLVER_H


#include "nQueensGenericSolver.h"

class nQueensGeneticSolver : public nQueensGenericSolver{
public:
    nQueensGeneticSolver(const NqBoard& board);

    void solvePuzzle() override;
};


#endif //AILABGENETICALGORITHM_NQUEENSGENETICSOLVER_H
