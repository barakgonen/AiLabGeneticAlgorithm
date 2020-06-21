//
// Created by barak on 20/06/2020.
//

#ifndef AILABGENETICALGORITHM_CALCULATEDEXPRESSION_H
#define AILABGENETICALGORITHM_CALCULATEDEXPRESSION_H

#include <GeneticAlgorithmBaseStruct.h>
#include "ExpressionTree.h"
#include "../../string_matching/include/GeneticStringMatchingAlgStruct.h"

// This class represents expression in "cheaper" way, a few bits only
class CalculatedExpression : public GeneticAlgorithmBaseStruct{
public:
    CalculatedExpression(ExpressionTree&& calculatedTree)
    : GeneticAlgorithmBaseStruct{}
    , calculatedResult{calculatedTree.getEvaluatedResults()}
    {}

    std::vector<bool> getCalculatedResult() const{
        return calculatedResult;
    }

protected:
    std::vector<bool> calculatedResult;
};
#endif //AILABGENETICALGORITHM_CALCULATEDEXPRESSION_H
