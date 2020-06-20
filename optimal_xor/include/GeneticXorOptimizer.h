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
    void growMethod();
    void fullMethod();
    void init_population();
    const ExpressionTree& inputExpression;
    const int maxDepth;
    const int populationSize;
    const int numberOfCitizensInPopulationGroup;
    std::vector<std::vector<int>> populationGroups;
};


#endif //AILABGENETICALGORITHM_GENETICXOROPTIMIZER_H
