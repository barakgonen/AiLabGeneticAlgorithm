//
// Created by barak on 06/06/2020.
//

#ifndef AILABGENETICALGORITHM_NSGASTRUCT_H
#define AILABGENETICALGORITHM_NSGASTRUCT_H

#include "GeneticAlgorithmBaseStruct.h"
#include "vector"

struct Nsga2Struct : public GeneticAlgorithmBaseStruct {
    Nsga2Struct()
    : items{}
    {}
    std::vector<double> items;
};
#endif //AILABGENETICALGORITHM_NSGASTRUCT_H
