//
// Created by barak on 30/04/2020.
//

#ifndef AILABGENETICALGORITHM_NQUEENSGENETICSOLVER_H
#define AILABGENETICALGORITHM_NQUEENSGENETICSOLVER_H


#include "nQueensGenericSolver.h"
#include "nQueensGeneticAlgoStruct.h"
#include "../../genetic_solver/include/AbstractGeneticSolver.h"

class nQueensGeneticSolver : public nQueensGenericSolver, public AbstractGeneticSolver<nQueensGeneticAlgoStruct>{
public:
    nQueensGeneticSolver(const NqBoard& board, const SelectionMethod selectionMethod, const CrossoverMethod crossoverMethod);

    void solvePuzzle() override;

    int start_solve() override;

    void print_results() override;

    void init_population() override;

    void calc_fitness() override;

    void mutate(nQueensGeneticAlgoStruct &member) override;

    int get_input_size() override;

    std::string getBestGene() const override;

    void uniform_crossover(const int indexInBuffer, const int i1, const int i2, const int spos, int tsize) override;


protected:
    void handle_specific_elitism(const int index) override;

    void
    set_data_in_buffer_vec_for_single_point_selection(const int indexInBuffer, const int startIndex, const int endIndex,
                                                      int spos, int tsize) override;

    void
    set_data_in_buffer_vec_for_two_points_selection(const int indexInBuffer, const int startIndex, const int endIndex,
                                                    int spos, int spos2, int tsize) override;
};


#endif //AILABGENETICALGORITHM_NQUEENSGENETICSOLVER_H
