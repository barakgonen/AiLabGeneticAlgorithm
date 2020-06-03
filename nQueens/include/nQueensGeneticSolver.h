//
// Created by barak on 30/04/2020.
//

#ifndef AILABGENETICALGORITHM_NQUEENSGENETICSOLVER_H
#define AILABGENETICALGORITHM_NQUEENSGENETICSOLVER_H


#include "nQueensGenericSolver.h"
#include "nQueensGeneticAlgoStruct.h"
#include "../../genetic_solver/include/AbstractGeneticSolver.h"
#include "../../genetic_solver/include/MutationOperators.h"

class nQueensGeneticSolver : public nQueensGenericSolver, public AbstractGeneticSolver<nQueensGeneticStruct>{
public:
    nQueensGeneticSolver(const NqBoard& board,
                         const SelectionMethod selectionMethod,
                         const CrossoverMethod crossoverMethod,
                         const MutationOperator mutationOperator,
                         bool quietMode = false);

    std::string getBestGene() const override;

    int start_solve() override;
    void print_results() override;
    void init_population() override;
    void calc_fitness() override;
    void fillAditionalSolutionData(nQueensSolutionData&) override;

protected:
    void handle_specific_elitism(const int index) override;
    void ox(const int i) override;
    void pmx(const int i) override;

protected:
    int runSolver() override;
    void mutate(nQueensGeneticStruct& member) override ;
    int contain(nQueensGeneticStruct& member, int num);
    MutationOperator mutataionOperator;
    bool quietMode;
};


#endif //AILABGENETICALGORITHM_NQUEENSGENETICSOLVER_H
