//
// Created by barak on 12/05/2020.
//

#ifndef AILABGENETICALGORITHM_KNAPSACKGENETICSOLVER_H
#define AILABGENETICALGORITHM_KNAPSACKGENETICSOLVER_H
#include "vector"
#include "KnapSackStaticDataSetInitializer.h"
#include "memory"

#define W 26

struct ga_struct {
    ga_struct() = default;

    unsigned int fitness;
    double sumweight;
    std::vector<double> sack;
//    double sack[N];
//    std::unique_ptr<int[]> sack;
};

typedef std::vector<ga_struct> ga_vector;// for brevity

class KnapSackGeneticSolver {

public:
    KnapSackGeneticSolver(const int puzzleKey, const KnapSackStaticDataSetInitializer& staticDataSetInitializer);

    std::vector<int> solve();
protected:
    void init_population(ga_vector &population, ga_vector &buffer);
    void calc_fitness(ga_vector &population);
    void Standard_deviation(double avg);
    double calcStandardDeviation(ga_vector &population, double avg);
    double calcAvgFitness(ga_vector &population);
    void sort_by_fitness(ga_vector &population);
    void elitism(ga_vector &population, ga_vector &buffer, int esize);
    void mutate(ga_struct &member);
    void mutate2(ga_struct &member);
    int tournamentSelection(ga_vector &population);
    int RWS(ga_vector &population);
    void mate(ga_vector &population, ga_vector &buffer, int TournamentSelection = 0, int rws = 0, int twoPointCross = 0,
                                     int Mutate = 0);
    void set_profits(const int puzzleID, const KnapSackStaticDataSetInitializer& staticDataSetInitializer);
    void set_weights(const int puzzleID, const KnapSackStaticDataSetInitializer& staticDataSetInitializer);
    void print_best(ga_vector &gav);
    void swap(ga_vector *&population, ga_vector *&buffer);
    const int sackSize;
    std::vector<int> optimalSelection;
    std::vector<int> profits;
    std::vector<int> weights;
    const int N;
};


#endif //AILABGENETICALGORITHM_KNAPSACKGENETICSOLVER_H
