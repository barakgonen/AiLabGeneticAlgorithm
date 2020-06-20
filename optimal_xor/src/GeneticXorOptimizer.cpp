//
// Created by barak on 20/06/2020.
//

#include <iostream>
#include "../include/GeneticXorOptimizer.h"

GeneticXorOptimizer::GeneticXorOptimizer(const ExpressionTree &inputExpression)
: inputExpression{inputExpression}
, maxDepth{inputExpression.getMaxDepth()}
, populationSize{maxDepth * 5}
, numberOfCitizensInPopulationGroup{populationSize / 2}
{
}

void GeneticXorOptimizer::optimizeExpression() {
    init_population();
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
    if (functionOrTerminal)
    {
        // Generating a tree with function in root
        ExpressionTree tree{functionOrTerminal, inputExpression.getAllOperands(), maxDepth};
        tree.printTruthTable();
    } else{
        // Generating a tree with operand in root{tree such as that must have just a NODE it won't be a TREE
    }

}

void GeneticXorOptimizer::fullMethod(){
    std::cout << "FuLL" << std::endl;

}