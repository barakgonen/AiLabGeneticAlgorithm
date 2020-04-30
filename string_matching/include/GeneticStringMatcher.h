//
// Created by barak on 30/04/2020.
//

#ifndef AILABGENETICALGORITHM_GENETICSTRINGMATCHER_H
#define AILABGENETICALGORITHM_GENETICSTRINGMATCHER_H

#include <vector>
#include <algorithm>
#include "GeneticAlgorithmStruct.h"

#define GA_POPSIZE		2048		// ga population size
#define GA_MAXITER		16384		// maximum iterations
#define GA_ELITRATE		0.10f		// elitism rate
#define GA_MUTATIONRATE	0.25f		// mutation rate
#define GA_MUTATION		RAND_MAX * GA_MUTATIONRATE
#define GA_TARGET		std::string("Hello world!")


class GeneticStringMatcher {
public:
    GeneticStringMatcher();
    void init_population(std::vector<GeneticAlgorithmStruct>& population, std::vector<GeneticAlgorithmStruct>& buffer);
    void calc_fitness(std::vector<GeneticAlgorithmStruct>& population);

    void sort_by_fitness(std::vector<GeneticAlgorithmStruct>& population);
    void elitism(std::vector<GeneticAlgorithmStruct>& population, std::vector<GeneticAlgorithmStruct>& buffer, int esize);
    void mutate(GeneticAlgorithmStruct& member);
    void mate(std::vector<GeneticAlgorithmStruct>& population, std::vector<GeneticAlgorithmStruct>& buffer);
    void print_best(std::vector<GeneticAlgorithmStruct>& gav);
    void swap(std::vector<GeneticAlgorithmStruct>*& population, std::vector<GeneticAlgorithmStruct>*& buffer);

private:
    std::vector<GeneticAlgorithmStruct> ga_vector;
};

#endif //AILABGENETICALGORITHM_GENETICSTRINGMATCHER_H