//
// Created by barak on 27/06/2020.
//

#include "../include/ParallelizedStringMatching.h"
//
// Created by barak on 30/04/2020.
//

#include <iostream>
#include <chrono>
#include "../include/StringMatchingGeneticSolver.h"

ParallelizedStringMatching::ParallelizedStringMatching(const std::string &inputString,
                                                         const HeuristicsEnum heuristicType,
                                                         const SelectionMethod selectionMethod,
                                                         const CrossoverMethod crossoverMethod,
                                                         const int numberOfProccessors)
: AbstractParallelizedGeneticSolver<GeneticStringMatchingAlgStruct>{selectionMethod, crossoverMethod, static_cast<int>(inputString.size()), 5, 0.1, numberOfProccessors, 4, 3, 2}
, heuristicMethod{heuristicType}
, inputString{inputString}
{
    // Initializing each cell
    for (auto &res : rawOutputArr)
        res.id = -1;
    std::cout << "Heuristic: " << heuristicMethod << std::endl;
    std::cout << "input string is: " << inputString << std::endl;
}

void ParallelizedStringMatching::init_population() {
    for (int i = 0; i < populationSize; i++) {
        GeneticStringMatchingAlgStruct citizen;
        resetCitizenProps(citizen);
        setCitizenProps(citizen);

        population.push_back(citizen);
        GeneticStringMatchingAlgStruct citizenn;
        resetCitizenProps(citizenn);
        buffer.push_back(citizenn);
    }
}

int ParallelizedStringMatching::start_solve() {
    clock_t t, totalTicks = 0;
    srand(unsigned(time(NULL)));
    auto startTimeStamp = std::chrono::high_resolution_clock::now();
    init_population();
    t = clock();
    for (int i = 0; i < GA_MAXITER; i++) {
        calc_fitness();                     // calculate fitnessVal
        sort_population_by_fitnes();        // sort them
        print_best();                       // print the best one

        double averageFitnessValue = get_average_fitness();
        double standardDeviation = get_standard_deviation(averageFitnessValue);

        rawOutputArr[i].id = i;
        rawOutputArr[i].standardDeviation = standardDeviation;
        rawOutputArr[i].averageFitnessValue = averageFitnessValue;
        rawOutputArr[i].elapsedTimeSeconds = ((float) (clock() - t)) / CLOCKS_PER_SEC;
        rawOutputArr[i].clockTicks = clock() - t;

        if (population[0].fitnessVal == 0) {
            break;
        }

        if (i > 1 && isAtLocalOptima(standardDeviation, i)) {
            isInLocalOptima = true;
            threshold = 12;
        }
        else
            isInLocalOptima = false;

        specis = mate(); // mate the population together
        if (specis > maxSpecis - 2)
            threshold += 1;
        else if (specis < maxSpecis + 2)
            threshold -= 1;

//        swap();        // swap buffers

        t = clock();
    }

    auto endTimeStamp = std::chrono::high_resolution_clock::now();
    print_results();
    return std::chrono::duration_cast<std::chrono::milliseconds>(endTimeStamp - startTimeStamp).count();
}

void ParallelizedStringMatching::calc_fitness() {
    unsigned int fitness;

    switch (heuristicMethod) {
        case DefaultHeuristic:
            for (int i = 0; i < populationSize; i++) {
                fitness = 0;
                for (int j = 0; j < numberOfItems; j++) {
                    fitness += abs(int(population[i].items[j] - inputString.at(j)));
                }
                population[i].fitnessVal = fitness;
            }
            break;
        case BullsAndCows:
            for (int i = 0; i < populationSize; i++) {
                fitness = numberOfItems * 50;
                for (int j = 0; j < numberOfItems; j++) {
                    // if the letter on the right place we give 50 points
                    if (population[i].items[j] == inputString[j])
                        fitness -= 50;
                    else {
                        // if the letter in the string but not in the right place we give 10 points
                        for (int k = j + 1; k < numberOfItems; k++) {
                            if (population[i].items[j] == inputString[k]) {
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

void ParallelizedStringMatching::mutate(GeneticStringMatchingAlgStruct &member) {
    int ipos = rand() % numberOfItems;
    char delta = (rand() % 90) + 32;
    member.items[ipos] = (char)((member.items[ipos] + delta) % 122);
}

void ParallelizedStringMatching::print_results() {
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

std::vector<IterationRawOutput> ParallelizedStringMatching::getRawOutput() const {
    std::vector<IterationRawOutput> rawOutput;
    for (int i = 0; i < GA_MAXITER && rawOutputArr[i].id != -1; i++)
        rawOutput.push_back(rawOutputArr[i]);

    return rawOutput;
}

void ParallelizedStringMatching::handle_specific_elitism(const int index){
    buffer[index].items = population[index].items;
}

void ParallelizedStringMatching::set_data_in_buffer_vec_for_single_point_selection(const int indexInBuffer,
                                                                                    const int startIndex,
                                                                                    const int endIndex,
                                                                                    int spos,
                                                                                    int tsize) {
//    auto& bufferedItems = buffer.at(indexInBuffer).items;
//    bufferedItems.clear();
//    const auto& populationStartIndexItems = population.at(startIndex).items;
//    const auto& populationEndIndexItems = population.at(endIndex).items;
//    for (int i = 0; i < spos; i++)
//        bufferedItems.push_back(populationStartIndexItems.at(i));
//    for (int i = spos; i < tsize; i++)
//        bufferedItems.push_back(populationEndIndexItems.at(i));
}

void ParallelizedStringMatching::set_data_in_buffer_vec_for_two_points_selection(const int indexInBuffer,
                                                                                  const int startIndex,
                                                                                  const int endIndex, int spos,
                                                                                  int spos2, int tsize) {
    auto& bufferedItems = buffer.at(indexInBuffer).items;
    bufferedItems.clear();
    const auto& populationStartIndexItems = population.at(startIndex).items;
    const auto& populationEndIndexItems = population.at(endIndex).items;
    int index = 0;
    for (int i = index; i < spos; i++, index++)
        bufferedItems.push_back(populationStartIndexItems.at(i));
    for (int i = index; i < tsize - spos ; i++, index++)
        bufferedItems.push_back(populationEndIndexItems.at(i));
    for (int i = index; i < populationStartIndexItems.size(); i++, index++)
        bufferedItems.push_back(populationStartIndexItems.at(i));
}

void ParallelizedStringMatching::uniform_crossover(const int indexInBuffer, const int i1, const int i2, const int spos, int tsize) {
    int temp;
    std::string temp2;
    for (int j = 0; j < tsize; j++) {
        temp = (rand() % 2) ? i1 : i2;
        temp2+= population[temp].items[j];
    }
    buffer.at(indexInBuffer).items.clear();
    for (const auto& c : temp2)
        buffer.at(indexInBuffer).items.push_back(c);
}
std::string ParallelizedStringMatching::getBestGene() const {
    return std::string{population[0].items.begin(), population[0].items.end()};
}

int ParallelizedStringMatching::calculateDistanceBetweenTwoCitizens(const GeneticStringMatchingAlgStruct &citizenOne,
                                                                     const GeneticStringMatchingAlgStruct &citizenTwo) {
    return levenshtein(citizenOne.items, citizenTwo.items);
}

void ParallelizedStringMatching::resetCitizenProps(GeneticStringMatchingAlgStruct &citizen) {
    citizen.resetMembers();
    citizen.items.clear();
    for (int i = 0; i < numberOfItems; i++)
        citizen.items.push_back(' ');
}

void ParallelizedStringMatching::setCitizenProps(GeneticStringMatchingAlgStruct &citizen) {
    for (int j = 0; j < numberOfItems; j++)
        citizen.items.at(j) = (char)(65 + rand() % 57);
}