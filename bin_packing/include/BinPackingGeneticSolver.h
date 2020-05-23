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

    int get_input_size() override;

protected:
    bool isAtLocalOptima(const double standartDeviation, const int iterationNumber);
    int kendallTau(int a[], int  b[]);
    int elitism(const int esize) override;
    void immigration(BinPackingGeneticStruct& citizen);
    int mate() override;
    void handle_specific_elitism(const int index) override;
    int runFirstFitAlgorithm(const std::vector<int> items);
    const int numberOfBins;
    const int binsCapacity;
    std::vector<int> weights;
    int threshold;
    const int maxSpecis;
    int specis;
    bool isInLocalOptima;
    int maxAge;
};


#endif //AILABGENETICALGORITHM_BINPACKINGGENETICSOLVER_H
