//
// Created by barak on 30/04/2020.
//

#ifndef AILABGENETICALGORITHM_GENETICSTRINGMATCHER_H
#define AILABGENETICALGORITHM_GENETICSTRINGMATCHER_H

#include <vector>
#include <algorithm>
#include "GeneticAlgorithmStruct.h"
#include "SelectionMethodEnum.h"
#include "CrossoverMethod.h"
#include "HeuristicsEnum.h"


class GeneticStringMatcher {
public:
    GeneticStringMatcher(const std::string& inputString,
                         const HeuristicsEnum heuristicType,
                         const SelectionMethod selectionMethod,
                         const CrossoverMethod crossoverMethod);
    virtual ~GeneticStringMatcher() = default;

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
    int calcRws(std::vector<GeneticAlgorithmStruct>& population);
    const std::string inputString;
    HeuristicsEnum heuristicMethod;
    SelectionMethod selectionMethod;
    CrossoverMethod crossoverMethod;
};

#endif //AILABGENETICALGORITHM_GENETICSTRINGMATCHER_H