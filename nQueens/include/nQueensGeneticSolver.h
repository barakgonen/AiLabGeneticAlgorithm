//
// Created by barak on 30/04/2020.
//

#ifndef AILABGENETICALGORITHM_NQUEENSGENETICSOLVER_H
#define AILABGENETICALGORITHM_NQUEENSGENETICSOLVER_H


#include "nQueensGenericSolver.h"
#include "nQueensGeneticAlgoStruct.h"
#include "../../genetic_solver/include/AbstractGeneticSolver.h"
#include "../../genetic_solver/include/MutationOperators.h"

class nQueensGeneticSolver : public nQueensGenericSolver, public AbstractGeneticSolver<nQueensGeneticAlgoStruct>{
public:
    nQueensGeneticSolver(const NqBoard& board,
                         const SelectionMethod selectionMethod,
                         const CrossoverMethod crossoverMethod,
                         const MutationOperator mutationOperator);

protected:
    void ox(const int i) override;
    std::string getBestGene() const override;
    void handle_specific_elitism(const int index) override;
    void pmx(const int i) override;
    int start_solve() override;
    int get_input_size() override;
    void init_population() override;
    void calc_fitness() override;
    void mutate(nQueensGeneticAlgoStruct &member) override;
    void set_data_in_buffer_vec_for_single_point_selection(const int indexInBuffer, const int startIndex,
                                                            const int endIndex, int spos, int tsize) override;
    void set_data_in_buffer_vec_for_two_points_selection(const int indexInBuffer, const int startIndex,
                                                         const int endIndex, int spos, int spos2, int tsize) override;

    int runSolver() override;
    void print_results() override;

    MutationOperator mutataionOperator;
};


#endif //AILABGENETICALGORITHM_NQUEENSGENETICSOLVER_H
