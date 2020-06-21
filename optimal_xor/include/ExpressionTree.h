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

    int getTreeHeight() const;
    int getMaxDepth() const;
    int getNumberOfOperands() const;

    std::vector<char> getAllOperands() const;
    std::vector<ExpressionTreeFunctions> getAllFunctions();
    std::vector<bool> getEvaluatedResults();

    void print();
    void printTruthTable();

protected:
    ExpressionTree(char v, const int maxDepth);

    ExpressionTreeFunctions getRandomFunc() const;

    int getHeight(ExpressionTree* root);

    void printExpression(const char expr);
    void printExpression(const std::string expr);

    bool isComplexTree(const std::string& initializationExpression);
    bool evaluateExpression(const std::vector<std::pair<char, bool>>& operands);
    void printTableBorder();

    void printTruthTableHeaderLine();

    std::vector<char> getAllOperands(const ExpressionTree* root) const;
    std::vector<ExpressionTreeFunctions> getAllFunctions(ExpressionTree* root);
    std::vector<std::vector<std::pair<char, bool>>> getPermutation(const std::vector<char>& operators);

    std::unique_ptr<bool> evaluateExpression(const std::vector<std::pair<char, bool>>& operands, const ExpressionTree* root, int startIndex);

    ExpressionTreeFunctions parseExpressionTreeFunc(const std::string& rawSubTree, const int rootStartIndex);

    std::string extractSubTree(std::string rawSubTree);

    std::pair<int, int> getRootIndexes(const std::string& initializationExpression);

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