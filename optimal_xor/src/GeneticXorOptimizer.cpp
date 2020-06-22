//
// Created by barak on 20/06/2020.
//

#include <iostream>
#include <algorithm>
#include "../include/GeneticXorOptimizer.h"

GeneticXorOptimizer::GeneticXorOptimizer(ExpressionTree &inputExpression)
: inputExpression{inputExpression}
, maxDepth{inputExpression.getMaxDepth()}
, populationSize{30000} // assume it full binary tree with DEPTH = n, calculate number of leafs + number of inner nodes!
, numberOfCitizensInPopulationGroup{populationSize / 2}
, target{inputExpression.getEvaluatedResults()}
, operands{inputExpression.getAllOperands()}
, numberOfTrues{std::count(target.begin(), target.end(), true)}
, numberOfFalses{std::count(target.begin(), target.end(), false)}
{
}

void GeneticXorOptimizer::optimizeExpression() {
    init_population();
    int indexInPopulateion;
    std::pair<int, int> indexAndLogicalGates = std::make_pair(0, 13);

    int numberOfChecks = 0;
    for (indexInPopulateion = 0; indexInPopulateion < pop.size(); indexInPopulateion++) {
        calculate_fitness();
        sort_pop();
        const auto citizen = pop.at(indexInPopulateion);
        if (citizen.getCalculatedResult() == target)
        {
            if (indexAndLogicalGates.second > citizen.getNumberOfLogicalGates()){
                indexAndLogicalGates.second = citizen.getNumberOfLogicalGates();
                indexAndLogicalGates.first = indexInPopulateion;
                std::cout << "BEST IS: " << std::endl;
                int num = citizen.getNumberOfLogicalGates();
                citizen.printTruthTable();
                std::cout << "num of logical gates: " << num << std::endl;
            }
//            break;
        }
        else
            numberOfChecks++;
        // mate
        // mutate
    }
    std::cout << "number of checks is: " << numberOfChecks << ", pop size: " << pop.size() << std::endl;
    const auto& representation = pop.at(indexAndLogicalGates.first);
    representation.printTruthTable();
    std::cout << "Number of logical gates: " << representation.getNumberOfLogicalGates() << std::endl;
}

void GeneticXorOptimizer::init_population() {
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

void GeneticXorOptimizer::growMethod() {
    int treesMaxDepth = rand() % maxDepth + 1;
    bool functionOrTerminal = rand() & 1;
    ExpressionTree tree{functionOrTerminal, operands, maxDepth};
//    tree.printTruthTable();
    pop.push_back(std::move(tree));
}

void GeneticXorOptimizer::fullMethod() {
//    std::cout << "FULL " /*<< std::boolalpha << functionOrTerminal*/ << std::endl;
    ExpressionTree tree{operands, maxDepth};
//    tree.printTruthTable();
    pop.push_back(std::move(tree));

}

void GeneticXorOptimizer::calculate_fitness() {
    // Iterating for each citizen
    for (auto& citizen : pop) {
        double fitnessVal = 0;
        const auto& citizenCalculatedResult = citizen.getCalculatedResult();
        for (int index = 0; index < citizenCalculatedResult.size(); index++){
            if (citizenCalculatedResult.at(index) == target.at(index))
                fitnessVal += 2;
            else
                fitnessVal -= 1;
        }
        if (fitnessVal > 0){
            // Trying - there are more correct than incorrect add another dimension - number of true & false
            int currNumberOfTrue = std::count(citizenCalculatedResult.begin(), citizenCalculatedResult.end(), true);
            int currNumberOfFalse = std::count(citizenCalculatedResult.begin(), citizenCalculatedResult.end(), false);
            if (currNumberOfFalse == numberOfFalses && currNumberOfTrue == numberOfTrues)
                fitnessVal += 3;
        }

    }
}

void GeneticXorOptimizer::sort_pop() {
//    std::sort(pop.begin(),
//            pop.end(),
//            [](const CalculatedExpression& x, const CalculatedExpression& y){ return x.fitnessVal < y.fitnessVal;});
}
