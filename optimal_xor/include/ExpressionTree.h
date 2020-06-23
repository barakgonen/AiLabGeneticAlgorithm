#ifndef AILABGENETICALGORITHM_EXPRESSIONTREE_H
#define AILABGENETICALGORITHM_EXPRESSIONTREE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <unordered_set>
#include <experimental/random>
#include "ExpressionTreeFunctions.h"
#include "consts.h"
#include "InitializationMethod.h"

class ExpressionTree{
public:
    ExpressionTree(std::string initializationExpression, const int maxDepth = MAX_PARSE_TREE_DEPTH);

    // Construction of fully generated tree, gets as parameter the depth to go down and flag indicates if node is function or terminal
    ExpressionTree(const std::vector<char>& operands, const InitializationMethod initializationMethod, const int currentDepth = 0, const int maxDepth = MAX_PARSE_TREE_DEPTH);
    ExpressionTree(const std::vector<char>& operands, const int maxDepth);
    virtual ~ExpressionTree() = default;

    int getMaxDepth() const;
    int getCurrentDepth() const;
    int getTreeHeight() const;
    int getNumberOfOperands() const;
    std::vector<char> getAllOperands() const;
    std::vector<bool> getEvaluatedResults() const;
    std::vector<ExpressionTreeFunctions> getAllFunctions() const;
    std::string getOriginalExpr()const{return originalExpression;};
    void print() const;
    void printTruthTable() const;

    void treeCrossover(ExpressionTree& other, int depth){
        if (currentDepth == depth && other.currentDepth == depth){
            // Were in the correct depth
            if (currentDepth == 0 && other.currentDepth == 0){
                // need to preform root change
                if (func != ExpressionTreeFunctions::UKNOWN && other.func != ExpressionTreeFunctions::UKNOWN){
                    // swappings terminals
                    std::swap(this->func, other.func);
                }
                else if (this->val== EMPTY_VALUE && other.val == EMPTY_VALUE) {
                    std::swap(this->val, other.val);
                }
            }
        }
        else{
            std::cout << "TO BE CONTINUED" << std::endl;

        }

        operands = getAllOperands();
    }

protected:
    bool isSingleOperandExpression(const std::string& initializationExpression) const;
    ExpressionTree(char v, const int maxDepth);
    ExpressionTreeFunctions getRandomFunc() const;
    ExpressionTree(const std::vector<char>& operands, const int maxDepth, const int currentDepth);

    void printTableBorder() const;
    void printTruthTableHeaderLine() const;
    void printExpression(const char expr) const;
    void printExpression(const std::string& expr) const;
    std::string extractSubTree(const std::string& rawSubTree) const;
    bool isComplexTree(const std::string& initializationExpression) const;

    bool evaluateExpression(const std::vector<std::pair<char, bool>>& operands) const ;
    int getHeight(ExpressionTree* root) const;
    int getDepth(ExpressionTree* root) const;
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
    int currentDepth;
    ExpressionTreeFunctions func;
    char val;
    std::string originalExpression;
    int maxDepth;
    std::vector<char> operands;

    void growInitMethod(const std::vector<char> &operands, const InitializationMethod &initializationMethod,
                   const int maxDepth);
};

#endif //AILABGENETICALGORITHM_EXPRESSIONTREE_H