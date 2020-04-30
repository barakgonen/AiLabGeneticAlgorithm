//
// Created by barak on 30/04/2020.
//

#include <iostream>
#include <time.h>
#include "../string_matching/include/GeneticStringMatcher.h"

int main(){
    GeneticStringMatcher matcher;
    std::cout << "Hello world!" << std::endl;
    srand(unsigned(time(NULL)));

    std::vector<GeneticAlgorithmStruct> pop_alpha, pop_beta;
    std::vector<GeneticAlgorithmStruct>* population, *buffer;

    matcher.init_population(pop_alpha, pop_beta);
    population = &pop_alpha;
    buffer = &pop_beta;

    for (int i=0; i<GA_MAXITER; i++) {
        matcher.calc_fitness(*population);		// calculate fitness
        matcher.sort_by_fitness(*population);	// sort them
        matcher.print_best(*population);		// print the best one

        if ((*population)[0].getFitnessValue() == 0)
            break;

        matcher.mate(*population, *buffer);		// mate the population together
        swap(population, buffer);		// swap buffers
    }

    return 0;
}