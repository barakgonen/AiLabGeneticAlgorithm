//
// Created by barak on 30/04/2020.
//

#include <iostream>
#include <cmath>
#include "../include/GeneticStringMatcher.h"
#include "../include/consts.h"

GeneticStringMatcher::GeneticStringMatcher(const std::string& heuristicType)
{
    // not initializing via MIL because we have to preform basic input validation
    if (heuristicType != bullAndCow && heuristicType != defaultHeuristic){
        std::cout << "You have inserted unsupported heuristic type, I decide you want to use default ;)" << std::endl;
        this->heuristicType = defaultHeuristic;
    } else
        this->heuristicType = heuristicType;
}

void GeneticStringMatcher::init_population(std::vector<GeneticAlgorithmStruct>& population,
                                                    std::vector<GeneticAlgorithmStruct>& buffer)
{
    int tsize = GA_TARGET.size();

    for (int i=0; i<GA_POPSIZE; i++) {
        GeneticAlgorithmStruct citizen{"", 0};

        for (int j=0; j<tsize; j++)
            citizen.appendToString(((rand() % 90) + 32));

        population.push_back(citizen);
    }

    buffer.resize(GA_POPSIZE);
}

void GeneticStringMatcher::calc_fitness(std::vector<GeneticAlgorithmStruct>& population)
{
    std::string target = GA_TARGET;
    int tsize = target.size();
    unsigned int fitness;

    // default / original heuristic
    if (heuristicType == defaultHeuristic){
        for (int i=0; i<GA_POPSIZE; i++) {
            fitness = 0;
            for (int j=0; j<tsize; j++) {
                fitness += abs(int(population[i].getString()[j] - target[j]));
            }
            population[i].setFitnessValue(fitness);
        }
    }
    else if (heuristicType == bullAndCow){
        for (int i = 0; i<GA_POPSIZE; i++) {
            fitness = tsize * 50;
            for (int j = 0; j<tsize; j++) {
                // if the letter on the right place we give 50 points
                if (population[i].getString()[j] == target[j])
                    fitness -= 50;
                else {
                    // if the letter in the string but not in the right place we give 10 points
                    for (int k = j + 1; k < tsize; k++) {
                        if (population[i].getString()[j] == target[k]) {
                            fitness -= 10;
                            break;
                        }
                    }
                }
            }
            population[i].setFitnessValue(fitness);
        }
    }
}

void GeneticStringMatcher::sort_by_fitness(std::vector<GeneticAlgorithmStruct>& population)
{
    std::sort(population.begin(),
              population.end(),
            [](const GeneticAlgorithmStruct& x, const GeneticAlgorithmStruct& y)
            { return (x.getFitnessValue() < y.getFitnessValue()); });
}

void GeneticStringMatcher::elitism(std::vector<GeneticAlgorithmStruct>& population,
                                   std::vector<GeneticAlgorithmStruct>& buffer,
                                   int esize){
    for (int i=0; i<esize; i++) {
        buffer[i].setString(population[i].getString());
        buffer[i].setFitnessValue(population[i].getFitnessValue());
    }
}

void GeneticStringMatcher::mutate(GeneticAlgorithmStruct& member){
    int tsize = GA_TARGET.size();
    int ipos = rand() % tsize;
    int delta = (rand() % 90) + 32;

    member.getString()[ipos] = ((member.getString()[ipos] + delta) % 122);
}

void GeneticStringMatcher::mate(std::vector<GeneticAlgorithmStruct>& population,
                                    std::vector<GeneticAlgorithmStruct>& buffer){
    int esize = GA_POPSIZE * GA_ELITRATE;
    int tsize = GA_TARGET.size(), spos, i1, i2;

    elitism(population, buffer, esize);

    // Mate the rest
    for (int i=esize; i<GA_POPSIZE; i++) {
        i1 = rand() % (GA_POPSIZE / 2);
        i2 = rand() % (GA_POPSIZE / 2);
        spos = rand() % tsize;

        buffer[i].setString(population[i1].getString().substr(0, spos) +
                        population[i2].getString().substr(spos, tsize - spos));

        if (rand() < GA_MUTATION)
            mutate(buffer[i]);
    }
}

void GeneticStringMatcher::print_best(std::vector<GeneticAlgorithmStruct>& gav)
{
    std::cout << "Best: " << gav[0].getString() << " (" << gav[0].getFitnessValue() << ")" << std::endl;
}

void GeneticStringMatcher::swap(std::vector<GeneticAlgorithmStruct>*& population,
                                        std::vector<GeneticAlgorithmStruct>*& buffer)
{
    std::vector<GeneticAlgorithmStruct> *temp = population;
    population = buffer;
    buffer = temp;
}

double GeneticStringMatcher::calculateFitnessAvg(std::vector<GeneticAlgorithmStruct>& gav){
    double avgRes = 0;
    for (auto val : gav){
        avgRes += val.getFitnessValue();
    }
    return avgRes / gav.size();
}

double GeneticStringMatcher::calculateStandardDeviation(std::vector<GeneticAlgorithmStruct>& gav,
                                                        double averagedFitnessValue)
{
    double standardDeviation = 0;
    for (auto val : gav){
        standardDeviation += pow(val.getFitnessValue() - averagedFitnessValue, 2);
    }
    return standardDeviation / gav.size();
}