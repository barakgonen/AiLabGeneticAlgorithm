//
// Created by barak on 05/05/2020.
//

#ifndef AILABGENETICALGORITHM_NQUEENSGENETICALGOSTRUCT_H
#define AILABGENETICALGORITHM_NQUEENSGENETICALGOSTRUCT_H

#include "../../genetic_solver/include/GeneticAlgorithmBaseStruct.h"

struct nQueensGeneticAlgoStruct : public GeneticAlgorithmBaseStruct {
    nQueensGeneticAlgoStruct()
    : GeneticAlgorithmBaseStruct{}
    , nQueensBoard{}
    {};

    nQueensGeneticAlgoStruct(const int boardSize)
    : GeneticAlgorithmBaseStruct{}
    , nQueensBoard{boardSize}
    {};

    NqBoard nQueensBoard;
};
#endif //AILABGENETICALGORITHM_NQUEENSGENETICALGOSTRUCT_H
