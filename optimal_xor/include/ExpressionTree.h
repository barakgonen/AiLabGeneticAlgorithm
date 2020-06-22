#ifndef AILABGENETICALGORITHM_EXPRESSIONTREE_H
#define AILABGENETICALGORITHM_EXPRESSIONTREE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <unordered_set>
#include "ExpressionTreeFunctions.h"
#include "consts.h"

class ExpressionTree{
public:
    ExpressionTree(std::string initializationExpression, const int maxDepth = MAX_PARSE_TREE_DEPTH);

    // Construction of fully generated tree, gets as parameter the depth to go down and flag indicates if node is function or terminal
    ExpressionTree(bool functionOrTerminal, const std::vector<char>& operands, const int maxDepth = MAX_PARSE_TREE_DEPTH);
    virtual ~ExpressionTree() = default;

    int getMaxDepth() const;
    int getTreeHeight() const;
    int getNumberOfOperands() const;
    std::vector<char> getAllOperands() const;
    std::vector<bool> getEvaluatedResults() const;
    std::vector<ExpressionTreeFunctions> getAllFunctions() const;

    void print() const;
    void printTruthTable() const;

protected:
    ExpressionTree(char v, const int maxDepth);
    ExpressionTreeFunctions getRandomFunc() const;

    void printTableBorder() const;
    void printTruthTableHeaderLine() const;
    void printExpression(const char expr) const;
    void printExpression(const std::string& expr) const;
    std::string extractSubTree(const std::string& rawSubTree) const;
    bool isComplexTree(const std::string& initializationExpression) const;

    bool evaluateExpression(const std::vector<std::pair<char, bool>>& operands) const ;
    int getHeight(ExpressionTree* root) const;
    std::vector<char> getAllOperands(const ExpressionTree* root) const;
    std::vector<ExpressionTreeFunctions> getAllFunctions(ExpressionTree* root) const;
    std::pair<int, int> getRootIndexes(const std::string& initializationExpression) const;

    std::vector<std::vector<std::pair<char, bool>>> getPermutation(const std::vector<char>& operators) const;

    std::unique_ptr<bool> evaluateExpression(const std::vector<std::pair<char, bool>>& operands, const ExpressionTree* root, int startIndex) const;

    ExpressionTreeFunctions parseExpressionTreeFunc(const std::string& rawSubTree, const int rootStartIndex);

    int numberOfSpaces;
    ExpressionTree* left;
    ExpressionTree* right;
    int currentHeight;
    ExpressionTreeFunctions func;
    char val;
    std::string originalExpression;
    const int maxDepth;
    std::vector<char> operands;
};

#endif //AILABGENETICALGORITHM_EXPRESSIONTREE_H