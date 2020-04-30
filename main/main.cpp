//
// Created by barak on 30/04/2020.
//

#include <iostream>
#include <time.h>
#include "../string_matching/include/GeneticStringMatcher.h"
#include "chrono"
#include "../string_matching/include/consts.h"

using namespace std;

int main(){
    vector<GeneticAlgorithmStruct> pop_alpha, pop_beta;
    vector<GeneticAlgorithmStruct>* population, *buffer;
    string heuristicType;

    cout << "Choose heuristic method: " << defaultHeuristic << " / " << bullAndCow << endl;
    getline(cin, heuristicType);

    GeneticStringMatcher matcher{heuristicType};

    matcher.init_population(pop_alpha, pop_beta);
    population = &pop_alpha;
    buffer = &pop_beta;

    auto startTimeStamp = std::chrono::high_resolution_clock::now();

    for (int i=0; i<GA_MAXITER; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        matcher.calc_fitness(*population);		// calculate fitness
        matcher.sort_by_fitness(*population);	// sort them
        matcher.print_best(*population);		// print the best one

        if ((*population)[0].getFitnessValue() == 0)
            break;
        matcher.mate(*population, *buffer);		// mate the population together
        swap(population, buffer);		// swap buffers
        double averageFitnessValue = matcher.calculateFitnessAvg(*population);
        double standardDeviation = matcher.calculateStandardDeviation(*population, averageFitnessValue);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Averaged Fitness Value: " << averageFitnessValue << ", Standard Deviation val: " << standardDeviation << " calculation time: " << duration.count() << " millis" << std::endl;
    }

    auto endTimeStamp = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTimeStamp - startTimeStamp);

    std::cout << "Total runtime is: " << duration.count() << " millis" << std::endl;
    return 0;
}