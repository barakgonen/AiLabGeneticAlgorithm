//
// Created by barak on 20/06/2020.
//

#include <iostream>
#include <algorithm>
#include "../include/GeneticXorOptimizer.h"

#include <limits.h>

GeneticXorOptimizer::GeneticXorOptimizer(ExpressionTree &inputExpression)
: AbstractGeneticSolver<CalculatedExpression>(SelectionMethod::Tournament, CrossoverMethod::Pmx, 5000, 5, 0.1, 10)
, inputExpression{inputExpression}
, maxDepth{inputExpression.getMaxDepth()}
, numberOfCitizensInPopulationGroup{populationSize / 2}
, target{inputExpression.getEvaluatedResults()}
, operands{inputExpression.getAllOperands()}
, numberOfTrues{std::count(target.begin(), target.end(), true)}
, numberOfFalses{std::count(target.begin(), target.end(), false)}
{
    std::cout << "Original expression is: " << std::endl;
    inputExpression.printTruthTable();
}

void GeneticXorOptimizer::optimizeExpression() {
    clock_t t, totalTicks = 0;
    srand(unsigned(time(NULL)));
    auto startTimeStamp = std::chrono::high_resolution_clock::now();
    init_population();
    int indexInPopulateion;
    int minimalLogicalGates = INT_MAX;
    int numberOfChecks = 0;
    int bestCounter = 0;

    t = clock();

    for (indexInPopulateion = 0; indexInPopulateion < population.size(); indexInPopulateion++) {
        calculate_fitness();
        sort_population_by_fitnes();
        print_best();                       // print the best one
        double averageFitnessValue = get_average_fitness();
        double standardDeviation = get_standard_deviation(averageFitnessValue);

        if (population.front().getCalculatedResult() == target)
        {
            const auto& citizen = population.front();
            const auto numberOfLogicalGates = citizen.getNumberOfLogicalGates();
            if (minimalLogicalGates > numberOfLogicalGates){
                minimalLogicalGates = numberOfLogicalGates;
                bestCounter = 0;
            }
            else{
                bestCounter++;
            }
        } else{
            numberOfChecks++;
        }
        if (population.front().fitnessVal == 0 || bestCounter == 5) {
            break;
        }

        specis = mate(); // mate the population together
        swap();        // swap buffers
        t = clock();
    }
    auto endTimeStamp = std::chrono::high_resolution_clock::now();
    auto numberOfMillis =  std::chrono::duration_cast<std::chrono::milliseconds>(endTimeStamp - startTimeStamp).count();
    std::cout << "End of execution:" << std::endl;
    std::cout << "number of checks is: " << numberOfChecks << ", pop size: " << population.size() << std::endl;
    std::cout << "BEST IS: " << std::endl;
    const auto& representation = population.front();
    representation.printTruthTable();
    std::cout << "Number of logical gates: " << representation.getNumberOfLogicalGates() << std::endl;
    std::cout << "Total time is: " << numberOfMillis << " millis" << std::endl;
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
    ExpressionTree tree{operands, InitializationMethod::Grow, 0, maxDepth};
//    population.push_back(std::make_unique<CalculatedExpression>(tree));
    population.push_back(tree);
    buffer.push_back(tree);
}

void GeneticXorOptimizer::fullMethod() {
    ExpressionTree tree{operands, maxDepth};
//    population.push_back(std::make_unique<CalculatedExpression>(tree));
    population.push_back(tree);
    buffer.push_back(tree);
}

void GeneticXorOptimizer::calculate_fitness() {
    // our target is to be with value of 0!
    // for each case we for in-matching we have fees!
    // starting of very greedy look, number of variables, if it's not the same, moving on
    for (auto& citizen : population) {
//        citizen.printTruthTable();
        double fitnessVal = 0;
        if (citizen.getNumberOfOperands() != inputExpression.getNumberOfOperands())
            fitnessVal = INT_MAX;
        else {
//            // for each mistake, reducing 5 points
            const auto citizenCalculatedResult = citizen.getCalculatedResult();
            for (int index = 0; index < citizenCalculatedResult.size(); index++){
                if (citizenCalculatedResult.at(index) != target.at(index))
                    fitnessVal += 5;
            }
//            // means all answers correct!
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
            }
        }

        citizen.fitnessVal = fitnessVal;
    }
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

}

void GeneticXorOptimizer::mutate(CalculatedExpression &member) {

}

int GeneticXorOptimizer::calculateDistanceBetweenTwoCitizens(const CalculatedExpression &citizenOne,
                                                             const CalculatedExpression &citizenTwo) {
    return 0;
}

void GeneticXorOptimizer::handle_specific_elitism(const int index) {

}
