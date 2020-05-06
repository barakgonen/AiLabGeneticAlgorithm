//
// Created by barak on 05/05/2020.
//

#ifndef AILABGENETICALGORITHM_ABSTRACTGENETICSOLVER_H
#define AILABGENETICALGORITHM_ABSTRACTGENETICSOLVER_H

#include <algorithm>
#include <iostream>
#include <limits.h>
#include "IGeneticAlgorithmApi.h"
#include "consts.h"
#include "SelectionMethodEnum.h"
#include "CrossoverMethod.h"
#include "cmath"

// This abstract class defines generic behavior of any genetic solver, each specific
// solver (for specific problem such as string matching / nQueens) should inherit this function
// and implement specific logic, like heuristics for example

template<typename PopulationStruct>
class AbstractGeneticSolver : public IGeneticAlgorithmApi<PopulationStruct> {
public:
    AbstractGeneticSolver(const SelectionMethod selectionMethod,
                          const CrossoverMethod crossoverMethod)
    : selectionMethod{selectionMethod}
    , crossoverMethod{crossoverMethod}
    , population{std::vector<PopulationStruct>()}
    , buffer{std::vector<PopulationStruct>()} {
        std::cout << "Starting GeneticSolver with the following parameters:" << std::endl;
        std::cout << "selection: " << selectionMethod << std::endl;
        std::cout << "crossover: " << crossoverMethod << std::endl;
    }

    virtual ~AbstractGeneticSolver() = default;

    void sort_population_by_fitnes() override {
        std::sort(population.begin(),
                  population.end(),
                  [](const PopulationStruct &x, const PopulationStruct &y) {
                      return (x.fitnessVal < y.fitnessVal);
                  });
    }

    void elitism(const int esize) override {
        for (int i = 0; i < esize; i++) {
            buffer[i].fitnessVal = population[i].fitnessVal;
            handle_specific_elitism(i);
        }
    }

    void aging(int &i1, int &i2, int esize) override {
        std::vector<int> temp;
        for (int i = esize; i < GA_POPSIZE / 2; i++) {
            if (population[i].ageVal < 10) {
                temp.push_back(i);
            }
        }
        random_shuffle(temp.begin(), temp.end());
        int elsize = (int) (GA_POPSIZE * GA_ELITRATE);

        for (int i = 0; i < elsize; i++) {
            population[i].ageVal = population[i].ageVal + 1;
        }
        i1 = rand() % temp.size();
        i2 = rand() % temp.size();
    }

    int rws(const std::vector<double> &weights) override {
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

    void calc_rws(int &i1, int &i2) {
        const std::vector<double> weights = get_weights_vector(get_average_fitness());
        i1 = rws(weights);
        i2 = rws(weights);
    }

    void random_selection(int &i1, int &i2, int& spos, int tsize) {
        // Select 2 random parents from top half
        i1 = rand() % (GA_POPSIZE / 2);
        i2 = rand() % (GA_POPSIZE / 2);
        spos = rand() % tsize;
    }

    void mate() override {
        int esize = GA_POPSIZE * GA_ELITRATE;
        int tsize = this->get_input_size(), spos, spos2, i1, i2;

        elitism(esize);

        // Mate the rest
        for (int i = esize; i < GA_POPSIZE; i++) {
            switch (selectionMethod) {
                case SelectionMethod::Aging:
                    aging(i1, i2, esize);
                    break;
                case SelectionMethod::Rws:
                    calc_rws(i1, i2);
                    break;
                case SelectionMethod::Tournament:
                    tournament();
                    break;
                case SelectionMethod::Random:
                    random_selection(i1, i2, spos, tsize);
                    set_data_in_buffer_vec_for_single_point_selection(i, i1, i2, spos, tsize);

                    break;
            }
            switch (crossoverMethod) {
                // this is the selection method given in the beginning
                case CrossoverMethod::SinglePoint:
                    spos = rand() % tsize;
                    set_data_in_buffer_vec_for_single_point_selection(i, i1, i2, spos, tsize);
                    buffer[i].ageVal = 0;
                    if (rand() < GA_MUTATION)
                        this->mutate(buffer[i]);
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
                    set_data_in_buffer_vec_for_two_points_selection(i, i1, i2, spos, spos2, tsize);

                    break;
                case CrossoverMethod::UniformCrossover:
                    this->uniform_crossover(i, i1, i2, spos, tsize);
                    break;
            }

            if (rand() < GA_MUTATION)
                this->mutate(buffer[i]);

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

    virtual void tournament() override {
        // choose k genes
        int best = INT_MAX, secondBest = INT_MAX, i1 = 0, i2 = 0;
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
    }

    void print_best() override {
        std::cout << "Best: " << getBestGene() << " (" << population[0].fitnessVal << ")" << std::endl;
    }

    virtual std::string getBestGene() const = 0;

    void swap() override {
        std::swap(population, buffer);
    }

    double get_average_fitness() override {
        double avgRes = 0;
        for (auto val : population)
            avgRes += val.fitnessVal;
        return avgRes / population.size();
    }

    double get_standard_aviation(const double averagedFitnessValue) override {
        double standardDeviation = 0;
        for (auto val : population)
            standardDeviation += pow(val.fitnessVal - averagedFitnessValue, 2);
        return standardDeviation / population.size();
    }

    virtual std::vector<double> get_weights_vector(double avg) override {
        std::cout << "Returning default vector, if you see this print, you use base func instead of overriding it"
                  << std::endl;
        return std::vector<double>();
    }

protected:
    // this function is nesseccerry for specific structs we handle in this algorithm
    virtual void handle_specific_elitism(const int index) = 0;

    virtual void set_data_in_buffer_vec_for_single_point_selection(const int indexInBuffer, const int startIndex, const int endIndex, int spos, int tsize) = 0;
    virtual void set_data_in_buffer_vec_for_two_points_selection(const int indexInBuffer, const int startIndex, const int endIndex, int spos, int spos2, int tsize) = 0;

    SelectionMethod selectionMethod;
    CrossoverMethod crossoverMethod;
    std::vector<PopulationStruct> population;
    std::vector<PopulationStruct> buffer;
};


#endif //AILABGENETICALGORITHM_ABSTRACTGENETICSOLVER_H
