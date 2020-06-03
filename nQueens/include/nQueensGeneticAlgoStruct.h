//
// Created by barak on 05/05/2020.
//

#ifndef AILABGENETICALGORITHM_NQUEENSGENETICALGOSTRUCT_H
#define AILABGENETICALGORITHM_NQUEENSGENETICALGOSTRUCT_H

#include "../../genetic_solver/include/GeneticAlgorithmBaseStruct.h"

struct nQueensGeneticStruct : public GeneticAlgorithmBaseStruct
{
    // in items[i]=j => the queen is in column i, row j
    std::vector<int> items;
};
#endif //AILABGENETICALGORITHM_NQUEENSGENETICALGOSTRUCT_H
