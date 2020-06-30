//
// Created by barak on 27/06/2020.
//

#ifndef AILABGENETICALGORITHM_PARALLELIZEDGENETICSOLVER_H
#define AILABGENETICALGORITHM_PARALLELIZEDGENETICSOLVER_H

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
#include <future>

// This abstract class defines generic behavior of any genetic solver, each specific
// solver (for specific problem such as string matching / nQueens) should inherit this function
// and implement specific logic, like heuristics for example

template<typename PopulationStruct>
class AbstractParallelizedGeneticSolver : public IGeneticAlgorithmApi<PopulationStruct> {
public:
    AbstractParallelizedGeneticSolver(const SelectionMethod selectionMethod,
                          const CrossoverMethod crossoverMethod,
                          const int numberOfItems,  // problem maxDepth - string length, number of items, number of bins, items, etc..
                          int minimumIterationsForLocalMinima,
                          double minimalStandardDeviationForLocalMinima,
                          const int numberOfProccessors,
                          const int maxAge = 5,
                          const int maxSpecis = 30,
                          const int specis = 0,
                          const int populationSize = GA_POPSIZE)
            : selectionMethod{selectionMethod}
            , crossoverMethod{crossoverMethod}
            , population{std::vector<PopulationStruct>()}
            , buffer{std::vector<PopulationStruct>()}
            , numberOfItems{numberOfItems}
            , threshold{static_cast<int>(pow(numberOfItems, 2))}
//    , threshold{numberOfItems}
            , numberOfProccessors{numberOfProccessors}
            , maxAge{maxAge}
            , maxSpecis{maxSpecis}
            , specis{specis}
            , isInLocalOptima{false}
            , minimumIterationsForLocalMinima{minimumIterationsForLocalMinima}
            , minimalStandardDeviationForLocalMinima{minimalStandardDeviationForLocalMinima}
            , populationSize{populationSize}{
//        std::cout << "Starting GeneticSolver with the following parameters:" << std::endl;
//        std::cout << "selection: " << selectionMethod << std::endl;
//        std::cout << "crossover: " << crossoverMethod << std::endl;
    }

    virtual ~AbstractParallelizedGeneticSolver() = default;

    virtual void sort_population_by_fitnes() override {
        std::sort(population.begin(),
                  population.end(),
                  [](const PopulationStruct &x, const PopulationStruct &y) {
                      return (x.fitnessVal < y.fitnessVal);
                  });
    }

    // todo: FIXME IF NEEDED
    virtual int elitism(const int esize) override {
        int j = 0, i = 0;
        while (i < populationSize && j < esize) {
            if (population[i].ageVal < maxAge) {
                buffer[j].items.clear();
                std::copy(population[i].items.begin(), population[i].items.end(), back_inserter(buffer[j].items));
                buffer[j].fitnessVal = population[i].fitnessVal;
                buffer[j].ageVal = population[i].ageVal + 1;
                if (isInLocalOptima && j > GENES_TO_LEAVE)
                    immigration(buffer[j]);
                j++;
            }
            i++;
        }
        return j;
    }

    void aging(int &i1, int &i2, int esize) override {
        std::vector<int> temp;
        for (int i = i1; i < i2; i++) {
            if (population[i].ageVal < 10) {
                temp.push_back(i);
            }
        }
        random_shuffle(temp.begin(), temp.end());
        int elsize = (int) (populationSize * GA_ELITRATE);

        for (int i = 0; i < elsize; i++) {
            population[i].ageVal = population[i].ageVal + 1;
        }
        i1 = (rand() % temp.size()) + i1;
        i2 = (rand() % temp.size()) + i1;
    }

    int rws(const std::vector<double> &weights) override {
        // get a random value in the range
        double value = (rand() / (double) (RAND_MAX + 1)) * weights.at(populationSize - 1);
        // locate the random value based on the weights
        for (int i = 0; i < populationSize; i++) {
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

    void random_selection(int &i1, int &i2) {
        // Select 2 random parents from top half
        if (i1 == 0){
            i1 = rand() % + i2;
            i2 = rand() % + i2;
        }
        else if (i2 == populationSize)
        {
            i1 = (rand() % i2 + i1) -1;
            i2 = (rand() % i2 + i1) -1;
        } else{
            i1 = rand() % (populationSize / numberOfProccessors) + i1;
            i2 = rand() % (populationSize / numberOfProccessors) + i1;
        }

        if (i1 >= populationSize)
            i1 = i1 / 2;
        if (i2 >= populationSize)
            i2 = i2 / 2;

    }

    void runMate(std::vector<PopulationStruct>& islandsPop, const unsigned int beginIndex, const unsigned int endIndex, int* specisCounter) {
        // Mate the rest
        int spos, i1, i2, count, distance, index = 0;
        for (auto& citizen : islandsPop) {
            count = 0;
            do {
                i1 = beginIndex;
                i2 = endIndex;
                count++;
                switch (selectionMethod)
                {
                    case SelectionMethod::Aging:
//                        aging(i1, i2, beginIndex);
                        break;
                    case SelectionMethod::Rws:
//                        calc_rws(i1, i2);
                        break;
                    case SelectionMethod::Random:
//                  random_selection(i1, i2);
                        do
                        {
                            i1 = rand() % (populationSize / numberOfProccessors);
                            i2 = rand() % (populationSize / numberOfProccessors);
                        }
                        while(index == i1 || index == i2);
                        break;
                    case SelectionMethod::Tournament:
//                        i1 = tournament(beginIndex, endIndex);
//                        i2 = tournament(beginIndex, endIndex);
                        break;
                }
                distance = this->calculateDistanceBetweenTwoCitizens(islandsPop[i1], islandsPop[i2]);
                if (distance > threshold)
                    *specisCounter = *specisCounter + 1;
            }
            while(distance > threshold && count < 1000);
            switch (crossoverMethod) {
                // this is the selection method given in the beginning
                case CrossoverMethod::SinglePoint:{
                    spos = rand() % numberOfItems;
                    // might need to change
//                    set_data_in_buffer_vec_for_single_point_selection(i, i1, i2, spos, numberOfItems);

                    islandsPop[index].ageVal = 0;
                    auto& citizenToMutate = islandsPop.at(index).items;
                    citizenToMutate.clear();
                    const auto& populationStartIndexItems = islandsPop.at(i1).items;
                    const auto& populationEndIndexItems = islandsPop.at(i2).items;
                    int index = 0;
                    for (int i = index; i < spos; i++, index++)
                        citizenToMutate.push_back(populationStartIndexItems.at(i));
                    for (int i = index; i < numberOfItems - spos ; i++, index++)
                        citizenToMutate.push_back(populationEndIndexItems.at(i));
                    for (int i = index; i < populationStartIndexItems.size(); i++, index++)
                        citizenToMutate.push_back(populationStartIndexItems.at(i));
                    if (rand() < GA_MUTATION)
                        this->mutate(islandsPop.at(index));
                }
                    break;
                case CrossoverMethod::TwoPoints:{
//                    // choose two positions
//                    spos = rand() % numberOfItems;
//                    int spos2 = rand() % numberOfItems;
//                    // spos will hold the smaller index
//                    if (spos > spos2) {
//                        int temp = spos2;
//                        spos2 = spos;
//                        spos = temp;
//                    }
//                    // two point crossover
//                    set_data_in_buffer_vec_for_two_points_selection(i, i1, i2, spos, spos2, numberOfItems);
                    break;
                }
                case CrossoverMethod::UniformCrossover:
//                    this->uniform_crossover(i, i1, i2, spos, numberOfItems);
                    break;
                case CrossoverMethod::Ox:
//                    this->ox(i, i1, i2);
                    break;
                case CrossoverMethod::Pmx:
//                    this->pmx(i, i1, i2);
                    break;
                default:
                    break;
            }

            if (rand() < GA_MUTATION){
                this->mutate(buffer.at(index));
            }
            if (isInLocalOptima)
                immigration(buffer[index]);
            if (selectionMethod == SelectionMethod::Rws) {
//                // need to preform scailling
//                for (int j = beginIndex; j < endIndex; i++) {
//                    double fitness = population[i].fitnessVal;
//                    if (fitness != 0)
//                        population[i].fitnessVal = sqrt(population[i].fitnessVal);
//                }
            }
            index++;
        }
    }

    virtual int mate() override {
        // this part is about to be multi threaded

        int esize = populationSize * GA_ELITRATE;
        esize = this->elitism(esize);

        islands.clear();

        // need to assign start index an end index for each thread
        std::vector<std::pair<std::pair<unsigned int, unsigned int>, int>> indexes2Counter;
        for (int i = 0; i < numberOfProccessors; i++)
            indexes2Counter.push_back(std::make_pair(std::make_pair(((i) * populationSize) / numberOfProccessors, (((i+1) * populationSize) / numberOfProccessors) - 1), 0));


        // saperating to islands, numberOfIslands = number of threads
        int islandsIndex = 0;
        for (auto& callable : indexes2Counter) {
            const auto &indexPair = callable.first;
            islands.push_back({});
            for (int index = indexPair.first; index <= indexPair.second; index++) {
                islands.at(islandsIndex).emplace_back(std::move(population.at(index)));
            }
            islandsIndex++;
        }
//            std::thread t(std::bind(&AbstractParallelizedGeneticSolver<PopulationStruct>::runMate, this, callable.first.first, callable.first.second, &callable.second));
//            thread2Future.push_back(std::move(t));
//        }
//        int j = 0;
//        for (const auto& island : islands){
//            for (const auto& citizen : island){
//                auto & citizenFromPop = population.at(j);
//                if (citizen.items != citizenFromPop.items)
//                    std::cout << "ERROR!!" << std::endl;
//                j++;
//            }
//
//        }
        population.clear();
        islandsIndex = 0;
        std::vector<std::thread> thread2Future;
        for (auto& callable : indexes2Counter){
            std::thread t(std::bind(&AbstractParallelizedGeneticSolver<PopulationStruct>::runMate, this, std::ref(islands.at(islandsIndex)), 0, islands.at(islandsIndex).size() - 1, &callable.second));
            thread2Future.push_back(std::move(t));
            islandsIndex++;
        }

        for (std::thread& th : thread2Future)
            if (th.joinable())
                th.join();

        // need to restore population
        for (const auto& islandCitizens : islands)
            for(const auto& citizen : islandCitizens)
                population.emplace_back(citizen);

        int numberOfSpecis = 0;
        for (const auto& calculatedResult : indexes2Counter)
            numberOfSpecis += calculatedResult.second;

        return numberOfSpecis;
    }

    int tournament(int beginIndex, int endIndex) override {
        // choose k genes
        int best = INT_MAX, secondBest = INT_MAX, i1 = 0, i2 = 0;
        for (int i = 0; i < K; i++) {
            // random gene
            int temp = rand() % endIndex + beginIndex;
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

    virtual double getValueToPrint(const PopulationStruct& citizen) {
        return citizen.fitnessVal;
    }

    void print_best() override {
        std::cout << "Best: " << getBestGene() << " (" << getValueToPrint(population.at(getBestGeneIndex())) << ")" << std::endl;
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

        return avg / populationSize;
    }

    double get_standard_deviation(const double averagedFitnessValue) override {
        double sum = 0;
        for (const auto& citizen : population)
            sum += pow(citizen.fitnessVal - averagedFitnessValue, 2);
        return sqrt(sum / populationSize);
    }

    virtual std::vector<double> get_weights_vector(double avg) override {
        std::vector<double> weights;
        for (int j = 0; j < populationSize; j++) {
            if (j != 0)
                // we add previous weight for later use in rws function
                weights.push_back(population.at(j).fitnessVal / (avg * populationSize) + weights[j - 1]);
            else
                weights.push_back(population.at(j).fitnessVal / (avg * populationSize));
        }
        return weights;
    }

    virtual bool isStandardDeviationIndicatesLocalOptima(const double standardDeviation){
        return standardDeviation < minimalStandardDeviationForLocalMinima;
    }

    virtual bool isAtLocalOptima(const double standartDeviation, const int iterationNumber){
        if (iterationNumber < minimumIterationsForLocalMinima)
            return false;
        if (this->isStandardDeviationIndicatesLocalOptima(standartDeviation))
            return true;
        int count = 0, i1, i2, distance;
        for (int i = 0; i < populationSize / 2; i++) {
            i1 = rand() % (populationSize / 2);
            i2 = rand() % (populationSize / 2);
            distance = this->calculateDistanceBetweenTwoCitizens(population[i1], population[i2]);
            if (distance <= 1)
                count++;
        }
        if (count >= populationSize / 2)
            return true;
        return false;
    }

    virtual int kendallTau(const std::vector<int>& a, const std::vector<int>& b){
        int count = 0;
        int ary[numberOfItems][numberOfItems];
        int length = numberOfItems;
        for (int i = 0; i < length; i++) {
            for (int j = i + 1; j < length; j++) {
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
        for (int i = 0; i < length; i++) {
            for (int j = i + 1; j < length; j++) {
                if (b[i] >= length || b[j] >= length || i == j)
                    continue;
                int x;
                if (b[i] < b[j])
                    x = 1;
                else
                    x = -1;
                // if zero it means num1 and num2 not apper in the same order in the arrays
                if (ary[b[i]][b[j]] + x == 0)
                    count++;
            }
        }
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
    const int numberOfProccessors;
    const int maxSpecis;
    int specis;
    bool isInLocalOptima;
    int minimumIterationsForLocalMinima;
    double minimalStandardDeviationForLocalMinima;
    const int populationSize;
    std::vector<std::vector<PopulationStruct>> islands;
};
#endif //AILABGENETICALGORITHM_PARALLELIZEDGENETICSOLVER_H
