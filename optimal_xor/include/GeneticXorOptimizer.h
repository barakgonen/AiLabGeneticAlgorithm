//
// Created by barak on 20/06/2020.
//

#ifndef AILABGENETICALGORITHM_GENETICXOROPTIMIZER_H
#define AILABGENETICALGORITHM_GENETICXOROPTIMIZER_H

#include <set>
#include "ExpressionTree.h"
#include "CalculatedExpression.h"
#include <AbstractGeneticSolver.h>

using Expr = std::unique_ptr<CalculatedExpression>;

class GeneticXorOptimizer : public AbstractGeneticSolver<CalculatedExpression>{
public:
    GeneticXorOptimizer(ExpressionTree& inputExpression);
    virtual ~GeneticXorOptimizer() = default;

    void optimizeExpression();

    std::string getBestGene() const override;

    void resetCitizenProps(CalculatedExpression &citizen) override;

    void setCitizenProps(CalculatedExpression &citizen) override;

    int start_solve() override;

    void print_results() override;

    void calc_fitness() override;

    void mutate(CalculatedExpression &member) override;

    int calculateDistanceBetweenTwoCitizens(const CalculatedExpression &citizenOne,
                                            const CalculatedExpression &citizenTwo) override;

protected:
    void handle_specific_elitism(const int index) override;

protected:
    void growMethod();
    void fullMethod();
    void init_population();

    // Those methods should override infra's
    void calculate_fitness();

    const ExpressionTree& inputExpression;
    const int maxDepth;
    const int numberOfCitizensInPopulationGroup;
    const std::vector<bool> target;
    const std::vector<char> operands;
    std::vector<std::vector<int>> populationGroups;
    const int numberOfTrues;
    const int numberOfFalses;
};


#endif //AILABGENETICALGORITHM_GENETICXOROPTIMIZER_H
