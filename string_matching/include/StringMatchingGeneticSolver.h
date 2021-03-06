//
// Created by barak on 30/04/2020.
//

#ifndef AILABGENETICALGORITHM_STRINGMATCHINGGENETICSOLVER_H
#define AILABGENETICALGORITHM_STRINGMATCHINGGENETICSOLVER_H

#include <vector>
#include <algorithm>
#include "GeneticStringMatchingAlgStruct.h"
#include "../../genetic_solver/include/SelectionMethodEnum.h"
#include "../../genetic_solver/include/CrossoverMethod.h"
#include "HeuristicsEnum.h"
#include "../../genetic_solver/include/AbstractGeneticSolver.h"
#include "../../genetic_solver/include/IterationRawOutput.h"
#include "consts.h"
#include <map>

class StringMatchingGeneticSolver : public AbstractGeneticSolver<GeneticStringMatchingAlgStruct> {
public:
    StringMatchingGeneticSolver(const std::string &inputString,
                                const HeuristicsEnum heuristicType,
                                const SelectionMethod selectionMethod,
                                const CrossoverMethod crossoverMethod,
                                const int numberOfProccessors = 1);

    virtual ~StringMatchingGeneticSolver() = default;

    void init_population() override ;

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

    void setFitnessInRange(const unsigned int startIndex, const unsigned int endIndex) override ;

    void runGeneticAlgo() override ;
};

#endif //AILABGENETICALGORITHM_STRINGMATCHINGGENETICSOLVER_H