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
#include "KnapSackGeneticStruct.h"

class KnapSackGeneticSolver : public AbstractGeneticSolver<KnapSackGeneticStruct>{

public:
    KnapSackGeneticSolver(const int puzzleKey, const KnapSackStaticDataSetInitializer& staticDataSetInitializer,
                            SelectionMethod selectionMethod, CrossoverMethod crossoverMethod,
                            const int numberOfProccessors = 1);
    std::vector<int> solve();
    std::string getBestGene() const override;
    int start_solve() override;
    void print_results() override;
    void init_population() override;
    void mutate(KnapSackGeneticStruct &member) override;
    void handle_specific_elitism(const int index) override;
    virtual void set_data_in_buffer_vec_for_single_point_selection(const int indexInBuffer, const int startIndex, const int endIndex, int spos, int tsize) override ;
    virtual void set_data_in_buffer_vec_for_two_points_selection(const int indexInBuffer, const int startIndex, const int endIndex, int spos, int spos2, int tsize) override ;
    virtual int getBestGeneIndex() const override;

    int calculateDistanceBetweenTwoCitizens(const KnapSackGeneticStruct &citizenOne,
                                            const KnapSackGeneticStruct &citizenTwo) override;

    void resetCitizenProps(KnapSackGeneticStruct &citizen) override;

    void setCitizenProps(KnapSackGeneticStruct &citizen) override;
    void runGeneticAlgo() override;

protected:
    void setFitnessInRange(const unsigned int startIndex, const unsigned int endIndex) override;

protected:
    const int capacity;
    std::vector<int> profits;
    std::vector<int> weights;
};


#endif //AILABGENETICALGORITHM_KNAPSACKGENETICSOLVER_H
