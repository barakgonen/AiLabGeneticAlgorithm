//
// Created by barak on 20/06/2020.
//

#include <iostream>
#include <algorithm>
#include "../include/GeneticXorOptimizer.h"

#include <limits.h>
#include <assert.h>

GeneticXorOptimizer::GeneticXorOptimizer(ExpressionTree &inputExpression, const int numberOfProccessors)
: AbstractGeneticSolver<CalculatedExpression>(SelectionMethod::Tournament, CrossoverMethod::Pmx, 6, 5, 0.1, numberOfProccessors, 6,6,350)
, inputExpression{inputExpression}
, maxDepth{inputExpression.getMaxDepth()}
, numberOfCitizensInPopulationGroup{populationSize / 2}
, target{inputExpression.getEvaluatedResults()}
, operands{inputExpression.getAllOperands()}
, numberOfTrues{static_cast<int>(std::count(target.begin(), target.end(), true))}
, numberOfFalses{static_cast<int>(std::count(target.begin(), target.end(), false))}
{
}

CalculatedExpression GeneticXorOptimizer::optimizeExpression() {
    std::cout << "Starting to optimize the following expression: " << inputExpression.getOriginalExpr() << std::endl;
    init_population();

    // run scenerio on initialized population
    auto singleThreadedTotalRuntime = runScenerio();

    // printing results for users
    print_results();
    // if user wants multi-threaded run also
    if (numberOfProccessors != 1) {
        prepareMultiThreadedEnv();
        auto muliThreadedTotalRuntime = runScenerio();

        // printing results for users
        print_results();

        std::string winner = "";
        if (muliThreadedTotalRuntime < singleThreadedTotalRuntime)
            winner = "parallel";
        else
            winner = "single";
        std::cout << "The winner is: "
                  << ((muliThreadedTotalRuntime < singleThreadedTotalRuntime) ? "Parralel" : "Single")
                  << " Parralel: " << muliThreadedTotalRuntime << ", single: " << singleThreadedTotalRuntime << std::endl;
    }

    const auto& representation = population.front();
    representation.printTruthTable();
    std::cout << "Total time is: " << singleThreadedTotalRuntime << " millis" << std::endl;
    return representation;
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
    tmpPopulation.push_back(tree);
}

void GeneticXorOptimizer::fullMethod() {
    ExpressionTree tree{operands, InitializationMethod::Full, 0, maxDepth};
    while(std::find(population.begin(), population.end(), tree) != population.end())
        tree = ExpressionTree{operands, InitializationMethod::Full, 0, maxDepth};
    population.push_back(tree);
    tmpPopulation.push_back(tree);
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

int GeneticXorOptimizer::calculateDistanceBetweenTwoCitizens(const CalculatedExpression &citizenOne,
                                                             const CalculatedExpression &citizenTwo) {
    return 0;
}

void GeneticXorOptimizer::handle_specific_elitism(const int index) {

}

void GeneticXorOptimizer::mutate(CalculatedExpression &member) {
    // Mutation is modifying existing tree, thus we will generate new randomly chosen subtree with same terminals
    // and add it to the tree
    auto expr = member.getExpressionTree();
    auto randomInitializationMethod = (InitializationMethod)(rand() % 1);
    const auto maxDepth = rand() % expr.getMaxDepth();
    auto generatedNewSubtree = ExpressionTree(expr.getAllOperands(), randomInitializationMethod, 0, maxDepth);

    expr.treeCrossover(generatedNewSubtree, maxDepth);
    assert(expr.isTreeBuiltSuccessfully() && "expr is not OK!");
}

void GeneticXorOptimizer::non_uniform_crossover(const int i1, const int i2) {
    // Getting both randomly chosen trees from general population
    auto& firstExpr = population.at(i1).getExpressionTree();
    auto& secondExpr = population.at(i2).getExpressionTree();

    // Finding the minimal height for not increasing tree size
    int minHeight = std::min(firstExpr.getTreeHeight(), secondExpr.getTreeHeight());

    // Calling for crossover in randomly chosen depth, the directions inside the tree also randomized
    firstExpr.treeCrossover(secondExpr, rand() % minHeight);

    assert(firstExpr.isTreeBuiltSuccessfully() && "firstExpr is not OK!");
    assert(secondExpr.isTreeBuiltSuccessfully() && "secondExpr is not OK!");
}

double GeneticXorOptimizer::getValueToPrint(const CalculatedExpression &citizen) {
    return citizen.getNumberOfLogicalGates();
}

void GeneticXorOptimizer::runGeneticAlgo() {
    clock_t t, totalTicks = 0;
    srand(unsigned(time(NULL)));
    auto startTimeStamp = std::chrono::high_resolution_clock::now();

    int minimalLogicalGates = INT_MAX;
    int c = 0;
    bool hasFound = false;

    while (!hasFound) {
        calc_fitness();
        sort_population_by_fitnes();
        print_best();

        const auto &best = population.front();
        if (best.getCalculatedResult() == target) {
            if (best.fitnessVal < minimalLogicalGates) {
                minimalLogicalGates = best.fitnessVal;
                c = 0;
            } else {
                if (best.fitnessVal == minimalLogicalGates) {
                    if (c == 10) {
                        hasFound = true;
                        break;
                    } else
                        c++;
                }
            }
        } else {
            int index = 0;
            for (auto &citizen : population) {
                bool mutationOrCrossover = rand() % 1;
                if (mutationOrCrossover) {
                    // mutation
                    mutate(citizen);
                } else {
                    // crossover
                    int firstIndex = index;
                    int secondIndex = rand() % (int) (population.size() - 1);
                    while (secondIndex == firstIndex)
                        secondIndex = rand() % (int) (population.size() - 1);
                    non_uniform_crossover(firstIndex, secondIndex);
                }
                index++;
            }
        }
    }

    auto endTimeStamp = std::chrono::high_resolution_clock::now();
    auto numberOfMillis =  std::chrono::duration_cast<std::chrono::milliseconds>(endTimeStamp - startTimeStamp).count();
    std::cout << "End of execution:" << std::endl;
    std::cout << "BEST IS: " << std::endl;
}

void GeneticXorOptimizer::setFitnessInRange(const unsigned int startIndex, const unsigned int endIndex) {
// our target is to be with value of 0!
    // for each case we for in-matching we have fees!
    // starting of very greedy look, number of variables, if it's not the same, moving on
    for (int i = startIndex; i < endIndex; i++){
        auto& citizen = population.at(i);

        citizen.setNotTargetGene();
        double fitnessVal = 0;
        // For bloating support, if number of operands is different, means it's larger -> bigger tree generated, or
        // smaller, means truth table will never be equal --> tautology
        if (citizen.getNumberOfOperands() != inputExpression.getNumberOfOperands())
            fitnessVal = INT_MAX;
        else {
            // for each mistake, increasing by 50 points
            const auto citizenCalculatedResult = citizen.getCalculatedResult();
            for (int index = 0; index < citizenCalculatedResult.size(); index++){
                if (citizenCalculatedResult.at(index) != target.at(index))
                    fitnessVal += 50;
            }
            // means all answers correct!
            if (fitnessVal == 0){
                // Trying - there are more correct than incorrect add another dimension - number of true & false
                fitnessVal = 1;
                fitnessVal *= citizen.getNumberOfLogicalGates();
                citizen.setItsTargetGene();
            }
            else{
                // penalty, if we missed it.. it should not get here
                fitnessVal += 10;
            }
        }

        citizen.fitnessVal = fitnessVal;
    }
}
