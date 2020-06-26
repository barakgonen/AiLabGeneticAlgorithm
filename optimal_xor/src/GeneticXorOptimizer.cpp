//
// Created by barak on 20/06/2020.
//

#include <iostream>
#include <algorithm>
#include "../include/GeneticXorOptimizer.h"

#include <limits.h>
#include <assert.h>

static int counter = 0;
GeneticXorOptimizer::GeneticXorOptimizer(ExpressionTree &inputExpression)
: AbstractGeneticSolver<CalculatedExpression>(SelectionMethod::Tournament, CrossoverMethod::Pmx, 6, 5, 0.1, 10, 6,6,350)
, inputExpression{inputExpression}
, maxDepth{inputExpression.getMaxDepth()}
, numberOfCitizensInPopulationGroup{populationSize / 2}
, target{inputExpression.getEvaluatedResults()}
, operands{inputExpression.getAllOperands()}
, numberOfTrues{std::count(target.begin(), target.end(), true)}
, numberOfFalses{std::count(target.begin(), target.end(), false)}
{
}

int GeneticXorOptimizer::optimizeExpression() {
    std::cout << "Starting to optimize the following expression: " << inputExpression.getOriginalExpr() << std::endl;
    clock_t t, totalTicks = 0;
    init_population();
    srand(unsigned(time(NULL)));
    auto startTimeStamp = std::chrono::high_resolution_clock::now();

    int minimalLogicalGates = INT_MAX;
    int c = 0;
    bool hasFound = false;

    while (!hasFound){
        calc_fitness();
        sort_population_by_fitnes();
        print_best();

        const auto& best = population.front();
        if (best.getCalculatedResult() == target) {
            if (best.fitnessVal < minimalLogicalGates) {
                minimalLogicalGates = best.fitnessVal;
                c = 0;
            } else{
                if(best.fitnessVal == minimalLogicalGates){
                    if (c == 100){
                        hasFound = true;
                        break;
                    } else
                        c++;
                }
            }
        }
//        else{
            int index = 0;
            for (auto& citizen : population){
                bool mutationOrCrossover = std::experimental::randint(0, 1);
                if (mutationOrCrossover){
                    // mutation
                    mutate(citizen);
                } else{
                    // crossover
                    int firstIndex = index;/*std::experimental::randint(0, (int)(population.size() - 1));*/
                    int secondIndex = std::experimental::randint(0, (int)(population.size() - 1));
                    while (secondIndex == firstIndex)
                        secondIndex = std::experimental::randint(0, (int)(population.size() - 1));
                    non_uniform_crossover(firstIndex, secondIndex);
                }
                index++;
            }
//        }
//        bool mutationOrCrossover = std::experimental::randint(0, 1);
//        if (mutationOrCrossover){
//            // mutation
//            mutate(population.at(std::experimental::randint(0, (int)(population.size() - 1))));
//        } else{
//            // crossover
//            int firstIndex = std::experimental::randint(0, (int)(population.size() - 1));
//            int secondIndex = std::experimental::randint(0, (int)(population.size() - 1));
//            while (secondIndex == firstIndex)
//                secondIndex = std::experimental::randint(0, (int)(population.size() - 1));
//            non_uniform_crossover(firstIndex, secondIndex);
//        }
    }

    auto endTimeStamp = std::chrono::high_resolution_clock::now();
    auto numberOfMillis =  std::chrono::duration_cast<std::chrono::milliseconds>(endTimeStamp - startTimeStamp).count();
    std::cout << "End of execution:" << std::endl;
//    std::cout << "number of checks is: " << numberOfChecks << ", pop size: " << population.size() << std::endl;
    std::cout << "BEST IS: " << std::endl;
    const auto& representation = population.front();
    representation.printTruthTable();
//    std::cout << "Number of logical gates: " << representation.getNumberOfLogicalGates() << std::endl;
    std::cout << "Total time is: " << numberOfMillis << " millis" << std::endl;
    return representation.getNumberOfLogicalGates();
}

void GeneticXorOptimizer::init_population() {
    for (int i = 0; i < populationSize; i++)
        if (i % 2 == 0)
            growMethod();
        else
            fullMethod();
}

void GeneticXorOptimizer::growMethod() {
    ExpressionTree tree{operands, InitializationMethod::Grow, 0, maxDepth};
    while(std::find(population.begin(), population.end(), tree) != population.end())
        tree = ExpressionTree{operands, InitializationMethod::Grow, 0, maxDepth};
    population.push_back(tree);
}

void GeneticXorOptimizer::fullMethod() {
    ExpressionTree tree{operands, InitializationMethod::Full, 0, maxDepth};
    while(std::find(population.begin(), population.end(), tree) != population.end())
        tree = ExpressionTree{operands, InitializationMethod::Full, 0, maxDepth};
    population.push_back(tree);
}

std::string GeneticXorOptimizer::getBestGene() const {
    return std::string();
}

void GeneticXorOptimizer::resetCitizenProps(CalculatedExpression &citizen) {

}

void GeneticXorOptimizer::setCitizenProps(CalculatedExpression &citizen) {

}

int GeneticXorOptimizer::start_solve() {
    return 0;
}

void GeneticXorOptimizer::print_results() {

}

void GeneticXorOptimizer::calc_fitness() {
// our target is to be with value of 0!
    // for each case we for in-matching we have fees!
    // starting of very greedy look, number of variables, if it's not the same, moving on
    for (auto& citizen : population) {
        double fitnessVal = 0;
        // For bloating support, if number of operands is different, means it's larger -> bigger tree generated, or
        // smaller, means truth table will never be equal --> tautology
        if (citizen.getNumberOfOperands() != inputExpression.getNumberOfOperands())
            fitnessVal = INT_MAX;
        else {
            // for each mistake, reducing 5 points
            const auto citizenCalculatedResult = citizen.getCalculatedResult();
            for (int index = 0; index < citizenCalculatedResult.size(); index++){
                if (citizenCalculatedResult.at(index) != target.at(index))
                    fitnessVal += 50;
            }
            // means all answers correct!
            if (fitnessVal == 0){
                // Trying - there are more correct than incorrect add another dimension - number of true & false
                int currNumberOfTrue = std::count(citizenCalculatedResult.begin(), citizenCalculatedResult.end(), true);
                int currNumberOfFalse = std::count(citizenCalculatedResult.begin(), citizenCalculatedResult.end(), false);
                if (currNumberOfFalse == numberOfFalses && currNumberOfTrue == numberOfTrues){
                    fitnessVal = 1;
                    fitnessVal *= citizen.getNumberOfLogicalGates();
                }
                else{
                    // penalty, if we missed it.. it should not get here
                    fitnessVal += 10;
                }
//                // Another check is height check
//                if (citizen.getExpressionTree().getTreeHeight() > inputExpression.getTreeHeight())
//                    fitnessVal *= 2;
            }
        }

        citizen.fitnessVal = fitnessVal;
    }
}



int GeneticXorOptimizer::calculateDistanceBetweenTwoCitizens(const CalculatedExpression &citizenOne,
                                                             const CalculatedExpression &citizenTwo) {
    return 0;
}

void GeneticXorOptimizer::handle_specific_elitism(const int index) {

}

void GeneticXorOptimizer::mutate(CalculatedExpression &member) {
    // Mutation is modifing existing tree, thus we will generate new randomly chosen subtree with same terminals
    // and add it to the tree
    counter++;
    std::cout << "COUNTER = " << counter << std::endl;
    auto expr = member.getExpressionTree();
    auto randomInitializationMethod = (InitializationMethod)std::experimental::randint(0, 1);
    const auto maxDepth = std::experimental::randint(0, expr.getMaxDepth());
    auto generatedNewSubtree = ExpressionTree(expr.getAllOperands(), randomInitializationMethod, 0, maxDepth);
    if (!expr.isOK()) {
        std::cout << "BLA" << std::endl;
    }
    expr.treeCrossover(generatedNewSubtree, maxDepth);
    if (!expr.isOK()) {
        std::cout << "BLA" << std::endl;
    }
    population.push_back(expr);
}

void GeneticXorOptimizer::non_uniform_crossover(const int i1, const int i2) {
    counter++;
    std::cout << "COUNTER = " << counter << std::endl;
    // Getting both randomly chosen trees from general population
    auto& firstExpr = population.at(i1).getExpressionTree();
    auto& secondExpr = population.at(i2).getExpressionTree();

    // Finding the minimal height for not increasing tree size
    int minHeight = std::min(firstExpr.getTreeHeight(), secondExpr.getTreeHeight());

    if (!firstExpr.isOK() || !secondExpr.isOK())
        std::cout << "BLA" << std::endl;
    // Calling for crossover in randomly chosen depth, the directions inside the tree also randomized
    firstExpr.treeCrossover(secondExpr, std::experimental::randint(0, minHeight));
    if (!firstExpr.isOK() || !secondExpr.isOK())
        std::cout << "BLA" << std::endl;
    assert(firstExpr.isOK() && "firstExpr is not OK!");
    assert(secondExpr.isOK() && "secondExpr is not OK!");
}

void GeneticXorOptimizer::generateNextGeneration() {

}

double GeneticXorOptimizer::getValueToPrint(const CalculatedExpression &citizen) {
    return citizen.getNumberOfLogicalGates();
}
