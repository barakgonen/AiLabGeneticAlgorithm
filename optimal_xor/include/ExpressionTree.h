#ifndef AILABGENETICALGORITHM_EXPRESSIONTREE_H
#define AILABGENETICALGORITHM_EXPRESSIONTREE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <unordered_set>
#include <random>
#include "ExpressionTreeFunctions.h"
#include "consts.h"
#include "InitializationMethod.h"

class ExpressionTree{
public:
    // Construction of fully generated tree, gets as parameter the depth to go down and flag indicates if node is function or terminal
    ExpressionTree(std::string initializationExpression, const int currentDepth = 0, const int maxDepth = MAX_PARSE_TREE_DEPTH);
    ExpressionTree(const std::vector<char>& operands, const InitializationMethod initializationMethod, const int currentDepth = 0, const int maxDepth = MAX_PARSE_TREE_DEPTH);

    virtual ~ExpressionTree() = default;

    int getMaxDepth() const;
    int getTreeHeight() const;
    int getNumberOfOperands() const;
    std::vector<char> getAllOperands() const;
    std::vector<bool> getEvaluatedResults() const;
    std::vector<ExpressionTreeFunctions> getAllFunctions() const;
    std::string getOriginalExpr()const{return originalExpression;};
    void print() const;
    void printTruthTable() const;

    std::string treeToString(ExpressionTree* root) const;
    // In cases whether substitution is not available, expect to do NOTHING
    void treeCrossover(ExpressionTree& other,
                       int crossoverDepth,
                       bool isTestingMode = false,
                       bool movementDirectionWithThisTree = false,
                       bool movementDirectionWithOtherTree = false);
    bool isTreeBuiltSuccessfully();
    virtual inline bool operator==(const ExpressionTree& lhs);

protected:
    // Protected ctors for recurse
    ExpressionTree(char v, const int currentDepth, const int maxDepth);
    ExpressionTree(const std::vector<char>& operands, const int maxDepth, const int currentDepth);

    // Initialization methods
    void growInitMethod(const std::vector<char> &operands, const InitializationMethod &initializationMethod,
                        const int maxDepth);
    void fullInitMethod(const std::vector<char> &operands, const InitializationMethod &initializationMethod,
                        const int maxDepth, const int currentDepth = 0);

    // Truth table methods
    void printTableBorder() const;
    void printTruthTableHeaderLine() const;
    void printExpression(const char expr) const;
    void printExpression(const std::string& expr) const;
    std::vector<char> getAllOperands(const ExpressionTree* root) const;
    bool isComplexTree(const std::string& initializationExpression) const;
    std::vector<ExpressionTreeFunctions> getAllFunctions(ExpressionTree* root) const;
    bool evaluateExpression(const std::vector<std::pair<char, bool>>& operands) const;
    std::vector<std::vector<std::pair<char, bool>>> getPermutation(const std::vector<char>& operators) const;
    std::unique_ptr<bool> evaluateExpression(const std::vector<std::pair<char, bool>>& operands, const ExpressionTree* root, int startIndex) const;

    void rootNodeSub(ExpressionTree &other);
    bool isStructureOK(ExpressionTree* root);
    int getDepth(ExpressionTree* root) const;
    int getHeight(ExpressionTree* root) const;

    void postSubActions(ExpressionTree &other);
    std::string extractSubTree(const std::string& rawSubTree) const;
    bool isSingleOperandExpression(const std::string& initializationExpression) const;
    std::pair<int, int> getRootIndexes(const std::string& initializationExpression) const;
    ExpressionTreeFunctions parseExpressionTreeFunc(const std::string& rawSubTree, const int rootStartIndex);

    int numberOfSpaces;
    ExpressionTree* left;
    ExpressionTree* right;
    int height;
    int depth;
    ExpressionTreeFunctions func;
    char val;
    std::string originalExpression;
    int maxDepth;
    std::vector<char> operands;


};

#endif //AILABGENETICALGORITHM_EXPRESSIONTREE_H