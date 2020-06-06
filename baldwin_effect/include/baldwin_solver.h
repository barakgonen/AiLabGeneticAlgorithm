//
// Created by barak on 05/06/2020.
//

#ifndef AILABGENETICALGORITHM_BALDWIN_SOLVER_H
#define AILABGENETICALGORITHM_BALDWIN_SOLVER_H


#include "baldwin_struct.h"
#include "AbstractGeneticSolver.h"
#include "BaldwinIterationStruct.h"

class Baldwin_Solver {
public:
    Baldwin_Solver(const int numberOfIterations,
                   const int numberOfItems = 20,
                   const int populationSize = 1000);

    virtual void elitism(const int esize);
    virtual void mate();
    void sort_population_by_fitnes();
    std::vector<BaldwinCsvStruct> solve();

    void init_population();

    void calc_fitness();
    void mutate(Baldwin_Struct &member);

    int
    calculateDistanceBetweenTwoCitizens(const Baldwin_Struct &citizenOne, const Baldwin_Struct &citizenTwo);

protected:
    double calculateQM();
    double calculateFixed();
    void generateTargetGene();
    int rws(const std::vector<double>& weights);
    void calc_rws(int &i1, int &i2);
    void print_best();
    double get_average_fitness();
    std::vector<double> get_weights_vector(double avg);
    const int numberOfIterations;
    const int populationSize;
    const int numberOfItems;
    std::vector<Baldwin_Struct> population, buffer;
    std::vector<char> targetGene;
    std::string targetGeneStr;
};


#endif //AILABGENETICALGORITHM_BALDWIN_SOLVER_H
