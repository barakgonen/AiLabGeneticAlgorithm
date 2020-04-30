//
// Created by barak on 30/04/2020.
//

#ifndef AILABGENETICALGORITHM_GENETICSTRINGMATCHER_H
#define AILABGENETICALGORITHM_GENETICSTRINGMATCHER_H

#include <vector>
#include <algorithm>
#include "GeneticAlgorithmStruct.h"



class GeneticStringMatcher {
public:
    GeneticStringMatcher(const std::string& heuristicType);
    void init_population(std::vector<GeneticAlgorithmStruct>& population, std::vector<GeneticAlgorithmStruct>& buffer);
    void calc_fitness(std::vector<GeneticAlgorithmStruct>& population);

    void sort_by_fitness(std::vector<GeneticAlgorithmStruct>& population);
    void elitism(std::vector<GeneticAlgorithmStruct>& population, std::vector<GeneticAlgorithmStruct>& buffer, int esize);
    void mutate(GeneticAlgorithmStruct& member);
    void mate(std::vector<GeneticAlgorithmStruct>& population, std::vector<GeneticAlgorithmStruct>& buffer);
    void print_best(std::vector<GeneticAlgorithmStruct>& gav);
    void swap(std::vector<GeneticAlgorithmStruct>*& population, std::vector<GeneticAlgorithmStruct>*& buffer);
    double calculateFitnessAvg(std::vector<GeneticAlgorithmStruct>& gav);
    double calculateStandardDeviation(std::vector<GeneticAlgorithmStruct>& gav, double averagedFitnessValue);

private:
    std::string heuristicType;
};

#endif //AILABGENETICALGORITHM_GENETICSTRINGMATCHER_H