//
// Created by barak on 20/06/2020.
//

#ifndef AILABGENETICALGORITHM_CALCULATEDEXPRESSION_H
#define AILABGENETICALGORITHM_CALCULATEDEXPRESSION_H

#include <GeneticAlgorithmBaseStruct.h>
#include "ExpressionTree.h"
#include "../../string_matching/include/GeneticStringMatchingAlgStruct.h"

// This class represents expression in "cheaper" way, a few bits only
class CalculatedExpression : public GeneticAlgorithmBaseStruct{
public:
    CalculatedExpression(const ExpressionTree& calculatedTree)
    : GeneticAlgorithmBaseStruct{}
    , expressionTree{calculatedTree}
    {}

    std::vector<bool> getCalculatedResult() const {
        return expressionTree.getEvaluatedResults();
    }

    void printTruthTable() const {
        expressionTree.printTruthTable();
    }

    int getNumberOfLogicalGates() const {
        auto funcs = expressionTree.getAllFunctions();

        return funcs.size();
    }

    int getNumberOfOperands() const {
        return expressionTree.getNumberOfOperands();
    }

    std::string getOriginalExpr() const {
        return expressionTree.getOriginalExpr();
    }

    ExpressionTree getExpressionTree() const{
        return expressionTree;
    }


    std::vector<int> items;
protected:
    ExpressionTree expressionTree;
};
#endif //AILABGENETICALGORITHM_CALCULATEDEXPRESSION_H