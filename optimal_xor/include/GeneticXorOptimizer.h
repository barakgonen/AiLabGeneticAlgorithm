//
// Created by barak on 20/06/2020.
//

#ifndef AILABGENETICALGORITHM_GENETICXOROPTIMIZER_H
#define AILABGENETICALGORITHM_GENETICXOROPTIMIZER_H


#include "ExpressionTree.h"

class GeneticXorOptimizer {
public:
    GeneticXorOptimizer(const ExpressionTree& inputExpression);
    virtual ~GeneticXorOptimizer() = default;

    void optimizeExpression();
protected:
    const ExpressionTree& inputExpression;
};


#endif //AILABGENETICALGORITHM_GENETICXOROPTIMIZER_H
