//
// Created by barak on 20/06/2020.
//

#ifndef AILABGENETICALGORITHM_GENETICXOROPTIMIZER_H
#define AILABGENETICALGORITHM_GENETICXOROPTIMIZER_H

#include <set>
#include "ExpressionTree.h"
#include "CalculatedExpression.h"

class GeneticXorOptimizer {
public:
    GeneticXorOptimizer(ExpressionTree& inputExpression);
    virtual ~GeneticXorOptimizer() = default;

    void optimizeExpression();
protected:
    void growMethod();
    void fullMethod();
    void init_population();
    const ExpressionTree& inputExpression;
    const int maxDepth;
    const int populationSize;
    const int numberOfCitizensInPopulationGroup;
    const std::vector<bool> target;
    const std::set<char> operands;
    std::vector<std::vector<int>> populationGroups;
    std::vector<CalculatedExpression> pop;
};


#endif //AILABGENETICALGORITHM_GENETICXOROPTIMIZER_H
