//
// Created by barak on 05/05/2020.
//

#ifndef AILABGENETICALGORITHM_ABSTRACTGENETICSOLVER_H
#define AILABGENETICALGORITHM_ABSTRACTGENETICSOLVER_H

static const int GENES_TO_LEAVE = 10;

#include <algorithm>
#include <iostream>
#include <limits.h>
#include "IGeneticAlgorithmApi.h"
#include "consts.h"
#include "SelectionMethodEnum.h"
#include "CrossoverMethod.h"
#include "cmath"
#include <thread>
#include <mutex>
#include <random>
#include <functional>
#include <set>

// This abstract class defines generic behavior of any genetic solver, each specific
// solver (for specific problem such as string matching / nQueens) should inherit this function
// and implement specific logic, like heuristics for example

template<typename PopulationStruct>
class AbstractGeneticSolver : public IGeneticAlgorithmApi<PopulationStruct> {
public:
    AbstractGeneticSolver(const SelectionMethod selectionMethod,
                          const CrossoverMethod crossoverMethod,
                          const int numberOfItems,  // problem size - string length, number of items, number of bins, items, etc..
                          const int maxAge = 5,
                          const int maxSpecis = 30,
                          const int specis = 0)
    : selectionMethod{selectionMethod}
    , crossoverMethod{crossoverMethod}
    , population{std::vector<PopulationStruct>()}
    , buffer{std::vector<PopulationStruct>()}
    , numberOfItems{numberOfItems}
//    , threshold{static_cast<int>(pow(numberOfItems, 2))}
    , threshold{numberOfItems}
    , maxAge{maxAge}
    , maxSpecis{maxSpecis}
    , specis{specis}
    , isInLocalOptima{false}{
//        std::cout << "Starting GeneticSolver with the following parameters:" << std::endl;
//        std::cout << "selection: " << selectionMethod << std::endl;
//        std::cout << "crossover: " << crossoverMethod << std::endl;
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
        int j = 0, i = 0;
        while (i < GA_POPSIZE && j < esize) {
            if (population[i].ageVal < maxAge) {
                buffer[j].items.clear();
                std::copy(population[i].items.begin(), population[i].items.end(), back_inserter(buffer[j].items));
                buffer[j].fitnessVal = population[i].fitnessVal;
                buffer[j].ageVal = population[i].ageVal + 1;
//                handle_specific_elitism(i);
//                for (int m = 0; m < numberOfItems; m++)
//                    buffer[j].item
//                    buffer[j].items[m] = population[i].items[m];
//
                if (isInLocalOptima && j > GENES_TO_LEAVE)
                    immigration(buffer[j]);
                j++;
            }
            i++;
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

    void random_selection(int &i1, int &i2, int tsize) {
        // Select 2 random parents from top half
        i1 = rand() % (GA_POPSIZE / 2);
        i2 = rand() % (GA_POPSIZE / 2);
    }

    virtual int mate() override {
        int esize = GA_POPSIZE * GA_ELITRATE;
        int spos, i1, i2;
        int count, distance, specis = 0;
        elitism(esize);

        // Mate the rest
        for (int i = esize; i < GA_POPSIZE; i++)  {
            count = 0;
            do {
                count++;
                switch (selectionMethod)
                {
                    case SelectionMethod::Aging:
                        aging(i1, i2, esize);
                        break;
                    case SelectionMethod::Rws:
                        calc_rws(i1, i2);
                        break;
                    case SelectionMethod::Random:
                        random_selection(i1, i2, numberOfItems);
                        break;
                    case SelectionMethod::Tournament:
                        i1 = tournament();
                        i2 = tournament();
                        break;
                    case SelectionMethod::None:
                        break;
                }
                distance = this->calculateDistanceBetweenTwoCitizens(population[i1], population[i2]);
                if (distance > threshold)
                    specis++;
            }
            while(distance > threshold && count < 1000);

            switch (crossoverMethod) {
//                // this is the selection method given in the beginning
                case CrossoverMethod::SinglePoint:
                    spos = rand() % numberOfItems;
                    set_data_in_buffer_vec_for_single_point_selection(i, i1, i2, spos, numberOfItems);
//                    buffer[i].ageVal = 0;
                    if (rand() < GA_MUTATION)
                        this->mutate(buffer.at(i));
                    break;
                case CrossoverMethod::TwoPoints:{
                    // choose two positions
                    spos = rand() % numberOfItems;
                    int spos2 = rand() % numberOfItems;
                    // spos will hold the smaller index
                    if (spos > spos2) {
                        int temp = spos2;
                        spos2 = spos;
                        spos = temp;
                    }
                    // two point crossover
                    set_data_in_buffer_vec_for_two_points_selection(i, i1, i2, spos, spos2, numberOfItems);
                    break;
                }
                case CrossoverMethod::UniformCrossover:
                    this->uniform_crossover(i, i1, i2, spos, numberOfItems);
                    break;
                case CrossoverMethod::Ox:
                    this->ox(i);
                    break;
                case CrossoverMethod::Pmx:
                    this->pmx(i);
                    break;
            }
//            std::set<int> gene;
//            // we take the even items from parent1, and odd items from parent2 and combine it
//            // std::set can not contain the same element twice, so we will get premutation
//            for (int j = 0; j < 2 * numberOfItems; j++) {
//                // if even copy parent 1 item
//                if (j % 2 == 0)
//                    gene.insert(buffer[i1].items[j / 2]);
//                    // if odd copy parent 2 item
//                else
//                    gene.insert(buffer[i2].items[(j - 1) / 2]);
//            }
//            std::set<int>::iterator it;
//            buffer[i].items.clear();
//            for (const auto val : gene)
//                buffer[i].items.push_back(val);

            if (rand() < GA_MUTATION){
                this->mutate(buffer.at(i));
            }
            if (isInLocalOptima)
                immigration(buffer[i]);
            if (selectionMethod == SelectionMethod::Rws) {
                // need to preform scailling
                for (int i = 0; i < GA_POPSIZE; i++) {
                    double fitness = population[i].fitnessVal;
                    if (fitness != 0)
                        population[i].fitnessVal = sqrt(population[i].fitnessVal);
                }
            }
        }
        return specis;
    }

    int tournament() override {
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
        return best;
    }

    void print_best() override {
        std::cout << "Best: " << getBestGene() << " (" << population.at(getBestGeneIndex()).fitnessVal << ")" << std::endl;
    }

    virtual std::string getBestGene() const = 0;
    virtual int getBestGeneIndex() const {return 0;}

    virtual void swap() override {
        std::swap(population, buffer);
    }

    double get_average_fitness() override {
        double avg = 0;

        for (const auto& citizen : population)
            avg += citizen.fitnessVal;

        return avg / GA_POPSIZE;
    }

    double get_standard_deviation(const double averagedFitnessValue) override {
        double sum = 0;
        for (const auto& citizen : population)
            sum += pow(citizen.fitnessVal - averagedFitnessValue, 2);
        return sqrt(sum / GA_POPSIZE);
    }

    virtual std::vector<double> get_weights_vector(double avg) override {
        std::vector<double> weights;
        for (int j = 0; j < GA_POPSIZE; j++) {
            if (j != 0)
                // we add previous weight for later use in rws function
                weights.push_back(population.at(j).fitnessVal / (avg * GA_POPSIZE) + weights[j - 1]);
            else
                weights.push_back(population.at(j).fitnessVal / (avg * GA_POPSIZE));
        }
        return weights;
    }

    virtual bool isAtLocalOptima(const double standartDeviation, const int iterationNumber){
        if (iterationNumber < 5)
            return false;
        if (standartDeviation < 0.1)
            return true;
        int count = 0, i1, i2, distance;
        for (int i = 0; i < GA_POPSIZE / 2; i++) {
            i1 = rand() % (GA_POPSIZE / 2);
            i2 = rand() % (GA_POPSIZE / 2);
            distance = this->calculateDistanceBetweenTwoCitizens(population[i1], population[i2]);
            if (distance <= 1)
                count++;
        }
        if (count >= GA_POPSIZE / 2)
            return true;
        return false;
    }

    virtual int kendallTau(const std::vector<int>& a, const std::vector<int>& b){
        int count = 0, x = 0;
        int** ary = new int* [numberOfItems];
        for (int i = 0; i < numberOfItems; i++)
            ary[i] = new int[numberOfItems];
        for (int i = 0; i < numberOfItems; i++) {
            for (int j = i + 1; j < numberOfItems; j++) {
                if (a[i] >= numberOfItems || a[j] >= numberOfItems)
                    continue;
                // if num1 is before num2 in array a, we add 1
                if (a[i] < a[j]) {
                    ary[a[i]][a[j]] = 1;
                    ary[a[j]][a[i]] = 1;
                }
                else {
                    ary[a[i]][a[j]] = -1;
                    ary[a[j]][a[i]] = -1;
                }
            }
        }
        for (int i = 0; i < numberOfItems; i++) {
            for (int j = i + 1; j < numberOfItems; j++) {
                if (b[i] >= numberOfItems || b[j] >= numberOfItems || i == j)
                    continue;
                if (b[i] < b[j])
                    x = 1;
                else
                    x = -1;
                // if zero it means num1 and num2 not apper in the same order in the arrays
                if (ary[b[i]][b[j]] + x == 0)
                    count++;
            }
        }
        // free memory
        for (int i = 0; i < numberOfItems; i++)
            delete[] ary[i];
        delete[] ary;

        return count;
    }

    virtual void resetCitizenProps(PopulationStruct& citizen) = 0;
    virtual void setCitizenProps(PopulationStruct& citizen) = 0;

    virtual void immigration(PopulationStruct& citizen) {
        this->resetCitizenProps(citizen);
        this->setCitizenProps(citizen);
    }

    virtual int levenshtein(const std::vector<char>& citizen1Vec, const std::vector<char>& citizen2Vec) {
        std::string s1{citizen1Vec.begin(), citizen1Vec.end()};
        std::string s2{citizen2Vec.begin(), citizen2Vec.end()};
        int m = citizen1Vec.size();
        int n = citizen2Vec.size();
        int x = 0;
        int** a = new int*[m + 1];
        for (int i = 0; i < m + 1; i++) {
            a[i] = new int[n + 1];
        }
        for (int i = 0;i <= m;i++)
            a[i][0] = i;
        for (int i = 0;i <= n;i++)
            a[0][i] = i;
        // we prepend char before the strings because the algorithem assums first char is in index 1
        s1 = " " + s1;
        s2 = " " + s2;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i] == s2[j])
                    x = 0;
                else x = 1;
                a[i][j] = std::min(std::min(a[i - 1][j] + 1, a[i][j - 1] + 1), a[i - 1][j - 1] + x);
            }
        }
        int ret = a[m][n];
        for (int i = 0; i < m + 1; i++)
            delete[] a[i];
        delete[] a;
        return ret;
    }


protected:
    // this function is necessary for specific structs we handle in this algorithm
    virtual void handle_specific_elitism(const int index) = 0;

    virtual void set_data_in_buffer_vec_for_single_point_selection(const int indexInBuffer, const int startIndex, const int endIndex, int spos, int tsize) {};
    virtual void set_data_in_buffer_vec_for_two_points_selection(const int indexInBuffer, const int startIndex, const int endIndex, int spos, int spos2, int tsize) {};

    SelectionMethod selectionMethod;
    CrossoverMethod crossoverMethod;
    std::vector<PopulationStruct> population;
    std::vector<PopulationStruct> buffer;
    const int numberOfItems;
    int threshold;
    const int maxAge;
    const int maxSpecis;
    int specis;
    bool isInLocalOptima;
};


#endif //AILABGENETICALGORITHM_ABSTRACTGENETICSOLVER_H
