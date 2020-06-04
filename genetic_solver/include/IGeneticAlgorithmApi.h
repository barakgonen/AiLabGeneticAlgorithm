//
// Created by barak on 05/05/2020.
//

#ifndef AILABGENETICALGORITHM_IGENETICALGORITHMAPI_H
#define AILABGENETICALGORITHM_IGENETICALGORITHMAPI_H

#include "vector"

template <typename ObjectName>
class IGeneticAlgorithmApi
{
public:
    virtual int start_solve() = 0;
    virtual void print_results() = 0;
    virtual void init_population() = 0;
    virtual void calc_fitness() = 0;
    virtual void sort_population_by_fitnes() = 0;
    virtual int elitism(const int esize) = 0;
    virtual void aging(int& i1, int& i2, int esize) = 0;
    virtual void calc_rws(int& i1, int& i2) = 0;
    virtual void random_selection(int& i1, int& i2) = 0;
    virtual int rws(const std::vector<double>& weights) = 0;
    virtual int mate() = 0;
    virtual int tournament() = 0;
    virtual void print_best() = 0;
    virtual void swap() = 0;
    virtual void mutate(ObjectName& member) = 0;
    virtual double get_average_fitness() = 0;
    virtual double get_standard_deviation(const double averagedFitnessValue) = 0;
    virtual std::vector<double> get_weights_vector(double avg) = 0;
    virtual void uniform_crossover(const int indexInBuffer, const int i1, const int i2, const int spos, int tsize){};
    virtual void pmx(const int i, const int i1, const int i2){};
    virtual void ox(const int i, const int i1, const int i2){};
    virtual int calculateDistanceBetweenTwoCitizens(const ObjectName& citizenOne, const ObjectName& citizenTwo) = 0;
    virtual bool isAtLocalOptima(const double standartDeviation, const int iterationNumber) = 0;

};

#endif //AILABGENETICALGORITHM_IGENETICALGORITHMAPI_H
