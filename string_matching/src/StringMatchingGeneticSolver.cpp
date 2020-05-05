//
// Created by barak on 30/04/2020.
//

#include <iostream>
#include <chrono>
#include "../include/StringMatchingGeneticSolver.h"

StringMatchingGeneticSolver::StringMatchingGeneticSolver(const std::string &inputString,
                                                         const HeuristicsEnum heuristicType,
                                                         const SelectionMethod selectionMethod,
                                                         const CrossoverMethod crossoverMethod)
: AbstractGeneticSolver<GeneticStringMatchingAlgStruct>{selectionMethod, crossoverMethod}
, inputString{inputString}
, heuristicMethod{heuristicType} {
    // Initializing each cell
    for (auto &res : rawOutputArr)
        res.id = -1;
    std::cout << "Heuristic: " << heuristicMethod << std::endl;
    std::cout << "input string is: " << inputString << std::endl;
}

void StringMatchingGeneticSolver::init_population() {
    int tsize = inputString.size();

    for (int i = 0; i < GA_POPSIZE; i++) {
        GeneticStringMatchingAlgStruct citizen;

        for (int j = 0; j < tsize; j++)
            citizen.str += (rand() % 90) + 32;

        population.push_back(citizen);
    }

    buffer.resize(GA_POPSIZE);
}

int StringMatchingGeneticSolver::start_solve() {
    clock_t t, totalTicks = 0;
    srand(unsigned(time(NULL)));
    auto startTimeStamp = std::chrono::high_resolution_clock::now();
    init_population();
    t = clock();
    for (int i = 0; i < GA_MAXITER; i++) {
        calc_fitness();                     // calculate fitness
        sort_population_by_fitnes();        // sort them
        print_best();                       // print the best one

        double averageFitnessValue = get_average_fitness();
        double standardDeviation = get_standard_aviation(averageFitnessValue);

        rawOutputArr[i].id = i;
        rawOutputArr[i].standardDeviation = standardDeviation;
        rawOutputArr[i].averageFitnessValue = averageFitnessValue;
        rawOutputArr[i].elapsedTimeSeconds = ((float) (clock() - t)) / CLOCKS_PER_SEC;
        rawOutputArr[i].clockTicks = clock() - t;

        if (population[0].fitnessVal == 0) {
            break;
        }

        this->mate();        // mate the population together
        this->swap();        // swap buffers

        t = clock();
    }

    auto endTimeStamp = std::chrono::high_resolution_clock::now();
    print_results();
    return std::chrono::duration_cast<std::chrono::milliseconds>(endTimeStamp - startTimeStamp).count();
}

void StringMatchingGeneticSolver::calc_fitness() {
    std::string target = inputString;
    int tsize = target.size();
    unsigned int fitness;

    switch (heuristicMethod) {
        case DefaultHeuristic:
            for (int i = 0; i < GA_POPSIZE; i++) {
                fitness = 0;
                for (int j = 0; j < tsize; j++) {
                    fitness += abs(int(population[i].str[j] - target[j]));
                }
                population[i].fitnessVal = fitness;
            }
            break;
        case BullsAndCows:
            for (int i = 0; i < GA_POPSIZE; i++) {
                fitness = tsize * 50;
                for (int j = 0; j < tsize; j++) {
                    // if the letter on the right place we give 50 points
                    if (population[i].str[j] == target[j])
                        fitness -= 50;
                    else {
                        // if the letter in the string but not in the right place we give 10 points
                        for (int k = j + 1; k < tsize; k++) {
                            if (population[i].str[j] == target[k]) {
                                fitness -= 10;
                                break;
                            }
                        }
                    }
                }
                population[i].fitnessVal = fitness;
            }
            break;
    }
}

void StringMatchingGeneticSolver::mutate(GeneticStringMatchingAlgStruct &member) {
    int tsize = inputString.size();
    int ipos = rand() % tsize;
    int delta = (rand() % 90) + 32;

    member.str[ipos] = ((member.str[ipos] + delta) % 122);
}

int StringMatchingGeneticSolver::get_input_size() {
    return inputString.size();
};

void StringMatchingGeneticSolver::print_results() {
    int totalIterations = 0;
    for (int i = 0; i < GA_MAXITER && rawOutputArr[i].id != -1; i++) {
        std::cout << "Averaged Fitness Value: " << rawOutputArr[i].averageFitnessValue
                  << ", Standard Deviation val: " << rawOutputArr[i].standardDeviation
                  << ", ticks: " << rawOutputArr[i].clockTicks
                  << ", calculation time: " << rawOutputArr[i].elapsedTimeSeconds << " seconds" << std::endl;
        totalIterations++;
    }
    std::cout << "Total iterations: " << totalIterations << std::endl;
}

std::vector<double> StringMatchingGeneticSolver::get_weights_vector(double avg) {
    std::vector<double> weights;
    double bla = population.at(0).fitnessVal;
    for (int j = 0; j < GA_POPSIZE; j++) {
        if (j != 0)
            // we add previous weight for later use in rws function
            weights.push_back(population.at(j).fitnessVal / (avg * GA_POPSIZE) + weights[j - 1]);
        else
            weights.push_back(population.at(j).fitnessVal / (avg * GA_POPSIZE));
    }
    return weights;
}

std::vector<IterationRawOutput> StringMatchingGeneticSolver::getRawOutput() const {
    std::vector<IterationRawOutput> rawOutput;
    for (int i = 0; i < GA_MAXITER && rawOutputArr[i].id != -1; i++)
        rawOutput.push_back(rawOutputArr[i]);

    return rawOutput;
}
