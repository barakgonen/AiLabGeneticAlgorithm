//
// Created by barak on 03/05/2020.
//

#ifndef AILABGENETICALGORITHM_INQUEENSSOLVER_H
#define AILABGENETICALGORITHM_INQUEENSSOLVER_H

#include "nQueensSolutionData.h"

class InQueensSolver{
public:
    virtual nQueensSolutionData solvePuzzle() = 0;
    virtual void printPuzzle() = 0;
    virtual void fillAditionalSolutionData(nQueensSolutionData&){};
};

#endif //AILABGENETICALGORITHM_INQUEENSSOLVER_H
