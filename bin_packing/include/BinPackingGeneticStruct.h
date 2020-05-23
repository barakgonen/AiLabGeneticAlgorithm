//
// Created by barak on 22/05/2020.
//

#ifndef AILABGENETICALGORITHM_BINPACKINGGENETICSTRUCT_H
#define AILABGENETICALGORITHM_BINPACKINGGENETICSTRUCT_H

#include "vector"
#include "../../genetic_solver/include/GeneticAlgorithmBaseStruct.h"

// Fitness value is the number of bins used, we have to minimize it
struct BinPackingGeneticStruct : public GeneticAlgorithmBaseStruct {
    std::vector<int> items; // specific permutation of n items
};


#endif //AILABGENETICALGORITHM_BINPACKINGGENETICSTRUCT_H
