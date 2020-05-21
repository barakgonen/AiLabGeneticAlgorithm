//
// Created by barak on 18/05/2020.
//

#ifndef AILABGENETICALGORITHM_NQUEENSSOLUTIONDATA_H
#define AILABGENETICALGORITHM_NQUEENSSOLUTIONDATA_H

#include "../../genetic_solver/include/SelectionMethodEnum.h"
#include "../../genetic_solver/include/CrossoverMethod.h"
struct nQueensSolutionData{
    int timeToSolve;
    int numberOfSteps;
    int boardSize;
    SelectionMethod selectionMethod = SelectionMethod::None;
    CrossoverMethod crossoverMethod = CrossoverMethod::Empty;
};

#endif //AILABGENETICALGORITHM_NQUEENSSOLUTIONDATA_H
