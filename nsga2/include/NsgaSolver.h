//
// Created by barak on 06/06/2020.
//

#ifndef AILABGENETICALGORITHM_NSGASOLVER_H
#define AILABGENETICALGORITHM_NSGASOLVER_H


#include "nsgaStruct.h"
#include "AbstractGeneticSolver.h"

class NsgaSolver : public AbstractGeneticSolver<Nsga2Struct>{

public:
    NsgaSolver(const SelectionMethod selectionMethod,
               const CrossoverMethod crossoverMethod,
               const int numberOfCouples,
               const int numberOfProccessors = 1);
    virtual ~NsgaSolver() = default;

    int start_solve() override;

    int tournament(int startIndex = 0, int endIndex = 0) override;

protected:
    std::string getBestGene() const override;
    void resetCitizenProps(Nsga2Struct &citizen) override;
    void setCitizenProps(Nsga2Struct &citizen) override;
    int elitism(const int esize) override;
    int mate() override;
    void aging(int &i1, int &i2, int esize) override;
    void print_best() override;
    void print_results() override;
    void init_population() override;
    void mutate(Nsga2Struct &member) override;
    int calculateDistanceBetweenTwoCitizens(const Nsga2Struct &citizenOne,
            const Nsga2Struct &citizenTwo) override;
    void handle_specific_elitism(const int index) override;

    void runGeneticAlgo() override;

    void setFitnessInRange(const unsigned int startIndex, const unsigned int endIndex) override;

    bool mutateKind; // true for insertion false for swap
};


#endif //AILABGENETICALGORITHM_NSGASOLVER_H
