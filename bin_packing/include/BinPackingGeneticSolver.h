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
                            const int expectedResult,
                            const int numberOfProccessors = 1,
                            const int maxSpecis = 30,
                            const int specis = 0);
    virtual ~BinPackingGeneticSolver() = default;

    int start_solve() override;

    void resetCitizenProps(BinPackingGeneticStruct &citizen) override;

    void setCitizenProps(BinPackingGeneticStruct &citizen) override;

    virtual int mate() override;

    int kendallTau(const std::vector<int> &a, const std::vector<int> &b) override;

protected:
    void print_results() override;
    std::string getBestGene() const override;
    void init_population() override;
    void calc_fitness() override;
    void mutate(BinPackingGeneticStruct &member) override;
    virtual int calculateDistanceBetweenTwoCitizens(const BinPackingGeneticStruct& citizenOne,
                                                    const BinPackingGeneticStruct& citizenTwo) override;
    void handle_specific_elitism(const int index) override;
    int runFirstFitAlgorithm(const std::vector<int>& items);

    void runGeneticAlgo() override;

    void setFitnessInRange(const unsigned int startIndex, const unsigned int endIndex) override;

    const int binsCapacity;
    std::vector<int> weights;
    const int expectedResult;
};


#endif //AILABGENETICALGORITHM_BINPACKINGGENETICSOLVER_H
