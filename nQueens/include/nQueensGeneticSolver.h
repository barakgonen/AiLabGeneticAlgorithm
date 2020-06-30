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
                         const int numberOfProccessors = 1,
                         bool quietMode = false);

    std::string getBestGene() const override;

    int start_solve() override;
    void print_results() override;
    void init_population() override;
    void fillAditionalSolutionData(nQueensSolutionData&) override;

    int calculateDistanceBetweenTwoCitizens(const nQueensGeneticStruct &citizenOne,
                                            const nQueensGeneticStruct &citizenTwo) override;

    void resetCitizenProps(nQueensGeneticStruct &citizen) override;

    void setCitizenProps(nQueensGeneticStruct &citizen) override;

protected:
    void handle_specific_elitism(const int index) override;
    void set_data_in_buffer_vec_for_single_point_selection(const int indexInBuffer, const int startIndex, const int endIndex, int spos, int tsize) override;
    void ox(const int i, const int i1, const int i2) override;
    void pmx(const int i, const int i1, const int i2) override;
    bool isStandardDeviationIndicatesLocalOptima(const double standardDeviation) override;
    void scale_results();
    int runSolver() override;
    void mutate(nQueensGeneticStruct& member) override ;

    void runGeneticAlgo() override;

    void setFitnessInRange(const unsigned int startIndex, const unsigned int endIndex) override;

    MutationOperator mutataionOperator;
    bool quietMode;
};


#endif //AILABGENETICALGORITHM_NQUEENSGENETICSOLVER_H
