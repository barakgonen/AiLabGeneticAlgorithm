//
// Created by barak on 30/04/2020.
//

#ifndef AILABGENETICALGORITHM_GENETICSTRINGMATCHINGALGSTRUCT_H
#define AILABGENETICALGORITHM_GENETICSTRINGMATCHINGALGSTRUCT_H

#include <string>
#include "../../genetic_solver/include/GeneticAlgorithmBaseStruct.h"

struct GeneticStringMatchingAlgStruct : public GeneticAlgorithmBaseStruct{
    GeneticStringMatchingAlgStruct()
    : GeneticAlgorithmBaseStruct()
//    , items{""}
    {}
    // Default empty ctor
    std::vector<char> items;
};

#endif //AILABGENETICALGORITHM_GENETICSTRINGMATCHINGALGSTRUCT_H