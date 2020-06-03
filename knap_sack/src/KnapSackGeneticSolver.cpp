//
// Created by barak on 12/05/2020.
//

#include <consts.h>
#include <functional>
#include <random>
#include "../include/KnapSackGeneticSolver.h"
#include "vector"
#include "iostream"
#include "../../string_matching/include/consts.h"

KnapSackGeneticSolver::KnapSackGeneticSolver(const int puzzleKey,
                                             const KnapSackStaticDataSetInitializer& staticDataSetInitializer,
                                             SelectionMethod selectionMethod, CrossoverMethod crossoverMethod)
: AbstractGeneticSolver<KnapSackGeneticStruct>(selectionMethod, crossoverMethod, static_cast<int>(weights.size()))
, capacity{staticDataSetInitializer.getCapacity(puzzleKey)}
, profits{staticDataSetInitializer.getProfits(puzzleKey)}
, weights{staticDataSetInitializer.getWeights(puzzleKey)}
{
}

void KnapSackGeneticSolver::init_population() {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1,1000);
    auto dice = std::bind ( distribution, generator );

    for (int i = 0; i < GA_POPSIZE; i++) {
        KnapSackGeneticStruct citizen;

        citizen.sigmaWeight = 0;
        for (int j = 0; j < numberOfItems; j++){
            auto end = citizen.items.end();
            citizen.items.insert(end, dice() % 2);
        }
        buffer.push_back(citizen);
        population.push_back(citizen);
    }
}

void KnapSackGeneticSolver::calc_fitness() {
    for (int i = 0; i < GA_POPSIZE; i++) {
        int sigmaFitness = 0;
        int sigmaWeight = 0;
        for (int j = 0; j < numberOfItems; j++) {
            sigmaFitness += profits.at(j) * population.at(i).items.at(j);
            sigmaWeight += weights.at(j) * population.at(i).items.at(j);
        }

        // Im sure it's god dam right, do not change it
        if (sigmaWeight <= capacity)
            population.at(i).fitnessVal = sigmaFitness;
        else
            population.at(i).fitnessVal = 0;
    }
}

void KnapSackGeneticSolver::handle_specific_elitism(const int index) {
    for (int j = 0; j < numberOfItems; j++)
        buffer.at(index).items.at(j) = population.at(index).items.at(j);
}

void KnapSackGeneticSolver::mutate(KnapSackGeneticStruct &member) {
    int i = rand() % numberOfItems;
    int j = rand() % 2;
    member.items.at(i) = j;
}

std::vector<int> KnapSackGeneticSolver::solve() {
    clock_t t;
    double avg;
    srand(unsigned(time(NULL)));
    int max = 0, num = 20;
    init_population();
    calc_fitness(); // calculate fitnessVal
    sort_population_by_fitnes(); // sort them

    for (int i = 0; i < GA_MAXITER; i++) {
        t = clock();
        calc_fitness(); // calculate fitnessVal
        sort_population_by_fitnes(); // sort them
        print_best(); // print the best one
        avg = get_average_fitness();
        std::cout << "fitnessVal avg: " << avg;
        double standardAviation = get_standard_deviation(avg);
        std::cout << " Standard deviation: " << standardAviation;

        if (population.back().fitnessVal == max)
            num--;

        if (max < population.back().fitnessVal) {
            max = population.back().fitnessVal;
            num = 20;
        }

        if (population.front().fitnessVal == 0 && num == 0) {
            t = clock() - t;
            std::cout << " CLOCK TICKS Time :" << t << " Elapsed time:" << ((float) t) / CLOCKS_PER_SEC << std::endl;

            break;
        }

        mate(); // mate the population together
        swap(); // swap buffers
        t = clock() - t;
        std::cout << " CLOCK TICKS Time :" << t << " Elapsed time:" << ((float) t) / CLOCKS_PER_SEC << std::endl;
    }
    return population.back().items;
}

std::string KnapSackGeneticSolver::getBestGene() const {
    std::string bestGene;
    for (int j = 0; j < numberOfItems; j++)
        bestGene.append(std::to_string(population.back().items.at(j)));
    return bestGene;
}

int KnapSackGeneticSolver::getBestGeneIndex() const
{
    return population.size()-1;
}

int KnapSackGeneticSolver::start_solve() {
    return 0;
}

void KnapSackGeneticSolver::print_results(){

}

void KnapSackGeneticSolver::set_data_in_buffer_vec_for_single_point_selection(const int indexInBuffer,
                                                                              const int startIndex,
                                                                              const int endIndex,
                                                                              int spos,
                                                                              int tsize) {
    for (int j = 0; j < spos; j++)
        buffer.at(indexInBuffer).items.at(j) = population.at(startIndex).items.at(j);
    for (int j = spos; j < numberOfItems; j++)
        buffer.at(indexInBuffer).items.at(j) = population.at(endIndex).items.at(j);
}

void KnapSackGeneticSolver::set_data_in_buffer_vec_for_two_points_selection(const int indexInBuffer,
                                                                            const int startIndex,
                                                                            const int endIndex,
                                                                            int spos,
                                                                            int spos2,
                                                                            int tsize) {
    for (int j = 0; j < spos; j++)
        buffer[indexInBuffer].items[j] = population[startIndex].items[j];

    for (int j = spos; j < spos2; j++)
        buffer[indexInBuffer].items[j] = population[startIndex].items[j];

    for (int j = spos2; j < numberOfItems; j++)
        buffer[indexInBuffer].items[j] = population[endIndex].items[j];

}