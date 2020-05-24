//
// Created by barak on 22/05/2020.
//

#ifndef AILABGENETICALGORITHM_BINPACKINGGENETICSOLVER_H
#define AILABGENETICALGORITHM_BINPACKINGGENETICSOLVER_H

#include "BinPackingGeneticStruct.h"
#include "../../genetic_solver/include/AbstractGeneticSolver.h"

class BinPackingGeneticSolver : public AbstractGeneticSolver<BinPackingGeneticStruct>{
public:
    BinPackingGeneticSolver(const int numberOfItems,
                            const int binsCapacity,
                            const std::vector<int>&& itemWeight,
                            const SelectionMethod selectionMethod,
                            const CrossoverMethod crossoverMethod,
                            const int maxAge,
                            const int maxSpecis = 30,
                            const int specis = 0);
    virtual ~BinPackingGeneticSolver() = default;

    std::string getBestGene() const override;

    int start_solve() override;

    void print_results() override;

    void init_population() override;

    void calc_fitness() override;

    void mutate(BinPackingGeneticStruct &member) override;


protected:
    virtual int calculateDistanceBetweenTwoCitizens(const BinPackingGeneticStruct& citizenOne, const BinPackingGeneticStruct& citizenTwo) override;
    void elitism(const int esize) override;
    void immigration(BinPackingGeneticStruct& citizen);
    int mate() override;
    void handle_specific_elitism(const int index) override;
    int runFirstFitAlgorithm(const std::vector<int> items);
    const int binsCapacity;
    std::vector<int> weights;
};


#endif //AILABGENETICALGORITHM_BINPACKINGGENETICSOLVER_H