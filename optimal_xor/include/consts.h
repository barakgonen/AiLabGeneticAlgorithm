//
// Created by barak on 13/06/2020.
//

#ifndef AILABGENETICALGORITHM_CONSTS_H
#define AILABGENETICALGORITHM_CONSTS_H

#include <string>
#include <map>
#include <random>

static const int MAX_PARSE_TREE_DEPTH = 2;
static const int NUMBER_OF_SPACES = 50;

static const std::map<ExpressionTreeFunctions, std::string> expressionTreeFuncToString{
    std::make_pair(ExpressionTreeFunctions::UKNOWN, "UKNOWN"),
    std::make_pair(ExpressionTreeFunctions::OR, "OR"),
    std::make_pair(ExpressionTreeFunctions::AND, "AND"),
    std::make_pair(ExpressionTreeFunctions::NOT, "NOT"),
    std::make_pair(ExpressionTreeFunctions::XOR, "XOR")};

static const std::map<std::string, ExpressionTreeFunctions> stringToExpressionTreeFunc{
        std::make_pair("UKNOWN", ExpressionTreeFunctions::UKNOWN),
        std::make_pair("OR", ExpressionTreeFunctions::OR),
        std::make_pair("AND", ExpressionTreeFunctions::AND),
        std::make_pair("NOT", ExpressionTreeFunctions::NOT),
        std::make_pair("||", ExpressionTreeFunctions::OR),
        std::make_pair("&&", ExpressionTreeFunctions::AND),
        std::make_pair("!", ExpressionTreeFunctions::NOT),
        std::make_pair("XOR", ExpressionTreeFunctions::XOR)};

static const std::map<int, ExpressionTreeFunctions> keyToExpressionFunc{
        std::make_pair(ExpressionTreeFunctions::OR, ExpressionTreeFunctions::OR),
        std::make_pair(ExpressionTreeFunctions::AND, ExpressionTreeFunctions::AND),
        std::make_pair(ExpressionTreeFunctions::NOT, ExpressionTreeFunctions::NOT)
//        std::make_pair(ExpressionTreeFunctions::XOR, ExpressionTreeFunctions::XOR)
};

static const char EMPTY_VALUE = ' ';

template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_randomly(start, end, gen);
}

#endif //AILABGENETICALGORITHM_CONSTS_H
