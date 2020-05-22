//
// Created by barak on 22/05/2020.
//

#ifndef AILABGENETICALGORITHM_BINPACKINGGENETICSOLVER_H
#define AILABGENETICALGORITHM_BINPACKINGGENETICSOLVER_H

#include "binPackingGeneticStruct.h"
#include "../../genetic_solver/include/AbstractGeneticSolver.h"

class BinPackingGeneticSolver : public AbstractGeneticSolver<binPackingGeneticStruct>{
public:
    BinPackingGeneticSolver(const SelectionMethod selectionMethod, const CrossoverMethod crossoverMethod);
    virtual ~BinPackingGeneticSolver() = default;

    std::string getBestGene() const override;

    int start_solve() override;

    void print_results() override;

    void init_population() override;

    void calc_fitness() override;

    void mutate(binPackingGeneticStruct &member) override;

    int get_input_size() override;

protected:
    void handle_specific_elitism(const int index) override;

};


#endif //AILABGENETICALGORITHM_BINPACKINGGENETICSOLVER_H
