//
// Created by barak on 12/05/2020.
//

#ifndef AILABGENETICALGORITHM_KNAPSACKGENETICSOLVER_H
#define AILABGENETICALGORITHM_KNAPSACKGENETICSOLVER_H

#include <GeneticAlgorithmBaseStruct.h>
#include "vector"
#include "KnapSackStaticDataSetInitializer.h"
#include "memory"
#include "AbstractGeneticSolver.h"

struct KnapSackGeneticStruct : public GeneticAlgorithmBaseStruct {
    KnapSackGeneticStruct() = default;
    double sigmaWeight;
    std::vector<int> items;
};

class KnapSackGeneticSolver : public AbstractGeneticSolver<KnapSackGeneticStruct>{

public:
    KnapSackGeneticSolver(const int puzzleKey, const KnapSackStaticDataSetInitializer& staticDataSetInitializer,
                            SelectionMethod selectionMethod, CrossoverMethod crossoverMethod);
    std::vector<int> solve();
    std::string getBestGene() const override;
    int start_solve() override;
    void print_results() override;
    void init_population() override;
    void calc_fitness() override;
    void mutate(KnapSackGeneticStruct &member) override;
    void handle_specific_elitism(const int index) override;
    virtual void set_data_in_buffer_vec_for_single_point_selection(const int indexInBuffer, const int startIndex, const int endIndex, int spos, int tsize) override ;
    virtual void set_data_in_buffer_vec_for_two_points_selection(const int indexInBuffer, const int startIndex, const int endIndex, int spos, int spos2, int tsize) override ;
    virtual int getBestGeneIndex() const override;
protected:
    const int capacity;
    std::vector<int> profits;
    std::vector<int> weights;
};


#endif //AILABGENETICALGORITHM_KNAPSACKGENETICSOLVER_H
