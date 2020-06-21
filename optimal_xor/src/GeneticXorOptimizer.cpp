//
// Created by barak on 20/06/2020.
//

#include <iostream>
#include "../include/GeneticXorOptimizer.h"

GeneticXorOptimizer::GeneticXorOptimizer(ExpressionTree &inputExpression)
: inputExpression{inputExpression}
, maxDepth{inputExpression.getMaxDepth()}
, populationSize{maxDepth * 5}
, numberOfCitizensInPopulationGroup{populationSize / 2}
, target{inputExpression.getEvaluatedResults()}
, operands{inputExpression.getAllOperands()}
{
}

void GeneticXorOptimizer::optimizeExpression() {
    init_population();

    for (int i = 0; i < 2000; i++){
        //
    }
    std::cout << "V" << std::endl;
}

void GeneticXorOptimizer::init_population(){
    std::cout << "need to initialize population in size of: " << populationSize << std::endl;
    std::cout << "According to the algorithm, we need to devide the population to parts: a total of maxDepth - 1 parts: " << maxDepth -1 << "parts in our case" << std::endl;
    for (int groupId = 0; groupId < maxDepth - 1; groupId++)
        populationGroups.push_back({});
    std::cout << "number of population groups: " << populationGroups.size() << std::endl;

    for (auto& populationGroup : populationGroups) {
        for (int citizenID = 0; citizenID < populationSize; citizenID++){
            if (citizenID % 2 == 0)
                growMethod();
            else
                fullMethod();
        }
    }
}

void GeneticXorOptimizer::growMethod(){
    bool functionOrTerminal = rand() & 1;
    std::cout << "GROW " << std::boolalpha << functionOrTerminal << std::endl;
    ExpressionTree tree{functionOrTerminal, operands, maxDepth};
    tree.printTruthTable();
    pop.push_back(std::move(tree));
}

void GeneticXorOptimizer::fullMethod(){
    std::cout << "FuLL" << std::endl;

}