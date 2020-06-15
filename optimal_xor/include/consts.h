//
// Created by barak on 13/06/2020.
//

#ifndef AILABGENETICALGORITHM_CONSTS_H
#define AILABGENETICALGORITHM_CONSTS_H

#include <string>
#include <map>

static const int MAX_PARSE_TREE_DEPTH = 2;
static const int NUMBER_OF_SPACES = 50;

const std::map<ExpressionTreeFunctions, std::string> expressionTreeFuncToString{
    std::make_pair(ExpressionTreeFunctions::UKNOWN, "UKNOWN"),
    std::make_pair(ExpressionTreeFunctions::OR, "OR"),
    std::make_pair(ExpressionTreeFunctions::AND, "AND"),
    std::make_pair(ExpressionTreeFunctions::NOT, "NOT")};
#endif //AILABGENETICALGORITHM_CONSTS_H
