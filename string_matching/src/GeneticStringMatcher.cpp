//
// Created by barak on 30/04/2020.
//

#include <iostream>
#include <cmath>
#include <limits.h>
#include "../include/GeneticStringMatcher.h"
#include "../include/consts.h"

GeneticStringMatcher::GeneticStringMatcher(const std::string &inputString,
                                           const HeuristicsEnum heuristicType,
                                           const SelectionMethod selectionMethod,
                                           const CrossoverMethod crossoverMethod)
        : inputString{inputString}, heuristicMethod{heuristicType}, selectionMethod{selectionMethod},
          crossoverMethod{crossoverMethod} {
}

void GeneticStringMatcher::init_population(std::vector<GeneticAlgorithmStruct> &population,
                                           std::vector<GeneticAlgorithmStruct> &buffer) {
    int tsize = inputString.size();

    for (int i = 0; i < GA_POPSIZE; i++) {
        GeneticAlgorithmStruct citizen{"", 0, 0};

        for (int j = 0; j < tsize; j++)
            citizen.str += (rand() % 90) + 32;

        population.push_back(citizen);
    }

    buffer.resize(GA_POPSIZE);
}

void GeneticStringMatcher::calc_fitness(std::vector<GeneticAlgorithmStruct> &population) {
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

void GeneticStringMatcher::sort_by_fitness(std::vector<GeneticAlgorithmStruct> &population) {
    std::sort(population.begin(),
              population.end(),
              [](const GeneticAlgorithmStruct &x, const GeneticAlgorithmStruct &y) {
                  return (x.fitnessVal < y.fitnessVal);
              });
}

void GeneticStringMatcher::elitism(std::vector<GeneticAlgorithmStruct> &population,
                                   std::vector<GeneticAlgorithmStruct> &buffer,
                                   int esize) {
    for (int i = 0; i < esize; i++) {
        buffer[i].str = population[i].str;
        buffer[i].fitnessVal = population[i].fitnessVal;
    }
}

void GeneticStringMatcher::mutate(GeneticAlgorithmStruct &member) {
    int tsize = inputString.size();
    int ipos = rand() % tsize;
    int delta = (rand() % 90) + 32;

    member.str[ipos] = ((member.str[ipos] + delta) % 122);
}

void GeneticStringMatcher::mate(std::vector<GeneticAlgorithmStruct> &population,
                                std::vector<GeneticAlgorithmStruct> &buffer, const std::vector<double> &weights) {
    int esize = GA_POPSIZE * GA_ELITRATE;
    int tsize = inputString.size(), spos, spos2, i1, i2;
    elitism(population, buffer, esize);

    // Mate the rest
    for (int i = esize; i < GA_POPSIZE; i++) {
        switch (selectionMethod) {
            case SelectionMethod::Aging: {


                std::vector<int> temp;
                for (int i = esize; i < GA_POPSIZE / 2; i++) {
                    if (population[i].ageVal < 10) {
                        temp.push_back(i);
                    }
                }
                random_shuffle(temp.begin(), temp.end());
                int esize = (int) (GA_POPSIZE * GA_ELITRATE);

                for (int i = 0; i < esize; i++) {
                    population[i].ageVal = population[i].ageVal + 1;
                }
                i1 = rand() % temp.size();
                i2 = rand() % temp.size();
            }
                break;
            case SelectionMethod::Rws: {
                i1 = getRws(weights);
                i2 = getRws(weights);
                break;
            }
            case SelectionMethod::Tournament: {
                // choose k genes
                int best, secondBest;
                best = INT_MAX, secondBest = INT_MAX, i1 = 0, i2 = 0;
                for (int i = 0; i < K; i++) {
                    // random gene
                    int temp = rand() % GA_POPSIZE;
                    // if better gene found we save it
                    if (population[temp].fitnessVal < best) {
                        i2 = i1;
                        i1 = temp;
                        best = population[i1].fitnessVal;
                        if (i != 0)
                            secondBest = population[i2].fitnessVal;
                    }
                        // if gene better than the second best found
                    else if (population[temp].fitnessVal < secondBest) {
                        i2 = temp;
                        secondBest = population[i2].fitnessVal;
                    }
                }
                break;
            }
                // Select 2 random parents from top half
            case SelectionMethod::Random:
                i1 = rand() % (GA_POPSIZE / 2);
                i2 = rand() % (GA_POPSIZE / 2);
                spos = rand() % tsize;

                buffer[i].str = population[i1].str.substr(0, spos) +
                                population[i2].str.substr(spos, tsize - spos);
                break;
        }
        switch (crossoverMethod) {
            // this is the selection method given in the beginning
            case CrossoverMethod::SinglePoint:
                spos = rand() % tsize;
                buffer[i].str = population[i1].str.substr(0, spos) +
                                population[i2].str.substr(spos, tsize - spos);
                buffer[i].ageVal = 0;
                if (rand() < GA_MUTATION) mutate(buffer[i]);
                break;
            case CrossoverMethod::TwoPoints:
                // choose two positions
                spos = rand() % tsize;
                spos2 = rand() % tsize;
                // spos will hold the smaller index
                if (spos > spos2) {
                    int temp = spos2;
                    spos2 = spos;
                    spos = temp;
                }
                // two point crossover
                buffer[i].str = population[i1].str.substr(0, spos) +
                                population[i2].str.substr(spos, spos2 - spos) +
                                population[i1].str.substr(spos2, tsize - spos2);
                break;
            case CrossoverMethod::UniformCrossover:
                int temp = inputString.size();
                std::string temp2;
                for (int j = 0; j < tsize; j++) {
                    temp = (rand() % 2) ? i1 : i2;
                    temp2 += population[temp].str[j];
                }
                buffer[i].str = temp2;
                break;
        }

        if (rand() < GA_MUTATION)
            mutate(buffer[i]);

        if (selectionMethod == SelectionMethod::Rws) {
            // need to preform scailling
            for (int i = 0; i < GA_POPSIZE; i++) {
                double fitness = population[i].fitnessVal;
                if (fitness != 0)
                    population[i].fitnessVal = sqrt(population[i].fitnessVal);
            }
        }
    }
}

int GeneticStringMatcher::getRws(const std::vector<double> &weights) {
    // get a random value in the range
    double value = (rand() / (double) (RAND_MAX + 1)) * weights.at(GA_POPSIZE - 1);
    // locate the random value based on the weights
    for (int i = 0; i < GA_POPSIZE; i++) {
        value -= weights.at(i);
        if (value <= 0) {
            return i;
        }
    }
    return 0;
}

void GeneticStringMatcher::print_best(std::vector<GeneticAlgorithmStruct> &gav) {
    std::cout << "Best: " << gav[0].str << " (" << gav[0].fitnessVal << ")" << std::endl;
}

void GeneticStringMatcher::swap(std::vector<GeneticAlgorithmStruct> &population,
                                std::vector<GeneticAlgorithmStruct> &buffer) {
    std::swap(population, buffer);
}

double GeneticStringMatcher::calculateFitnessAvg(std::vector<GeneticAlgorithmStruct> &gav) {
    double avgRes = 0;
    for (auto val : gav)
        avgRes += val.fitnessVal;
    return avgRes / gav.size();
}

double GeneticStringMatcher::calculateStandardDeviation(std::vector<GeneticAlgorithmStruct> &gav,
                                                        double averagedFitnessValue) {
    double standardDeviation = 0;
    for (auto val : gav)
        standardDeviation += pow(val.fitnessVal - averagedFitnessValue, 2);
    return standardDeviation / gav.size();
}