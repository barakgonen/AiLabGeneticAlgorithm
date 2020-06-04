//
// Created by barak on 24/05/2020.
//

#ifndef AILABGENETICALGORITHM_KNAPSACKGENETICSTRUCT_H
#define AILABGENETICALGORITHM_KNAPSACKGENETICSTRUCT_H

#include <GeneticAlgorithmBaseStruct.h>
#include "vector"

struct KnapSackGeneticStruct : public GeneticAlgorithmBaseStruct {
    KnapSackGeneticStruct() = default;
    double sigmaWeight;
    std::vector<int> items;
};

#endif //AILABGENETICALGORITHM_KNAPSACKGENETICSTRUCT_H
