//
// Created by barak on 27/06/2020.
//

#ifndef AILABGENETICALGORITHM_PARALLELIZEDSTRINGMATCHING_H
#define AILABGENETICALGORITHM_PARALLELIZEDSTRINGMATCHING_H


#include <parallelizedGeneticSolver.h>
#include <IterationRawOutput.h>
#include "GeneticStringMatchingAlgStruct.h"
#include "HeuristicsEnum.h"

class ParallelizedStringMatching : public AbstractParallelizedGeneticSolver<GeneticStringMatchingAlgStruct> {
public:
    ParallelizedStringMatching(const std::string &inputString,
                                const HeuristicsEnum heuristicType,
                                const SelectionMethod selectionMethod,
                                const CrossoverMethod crossoverMethod,
                                const int numberOfProccessors);

    virtual ~ParallelizedStringMatching() = default;

    void init_population() override;

    void calc_fitness() override;

    void mutate(GeneticStringMatchingAlgStruct &member);

    int start_solve() override;

    void print_results() override;

    std::vector<IterationRawOutput> getRawOutput() const;

    std::string getBestGene() const override;

    void uniform_crossover(const int indexInBuffer, const int i1, const int i2, const int spos, int tsize) override;

    int calculateDistanceBetweenTwoCitizens(const GeneticStringMatchingAlgStruct &citizenOne,
                                            const GeneticStringMatchingAlgStruct &citizenTwo) override;

    void resetCitizenProps(GeneticStringMatchingAlgStruct &citizen) override;

    void setCitizenProps(GeneticStringMatchingAlgStruct &citizen) override;

protected:
    char getRandomChar(int index) const;

    void handle_specific_elitism(const int index) override;

    void
    set_data_in_buffer_vec_for_single_point_selection(const int indexInBuffer, const int startIndex, const int endIndex,
                                                      int spos, int tsize) override;

    void
    set_data_in_buffer_vec_for_two_points_selection(const int indexInBuffer, const int startIndex, const int endIndex,
                                                    int spos, int spos2, int tsize) override;

private:
    const std::string inputString;
    HeuristicsEnum heuristicMethod;
    IterationRawOutput rawOutputArr[GA_MAXITER];
};


#endif //AILABGENETICALGORITHM_PARALLELIZEDSTRINGMATCHING_H
