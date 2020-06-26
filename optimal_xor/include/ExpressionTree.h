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
    // Construction of fully generated tree, gets as parameter the depth to go down and flag indicates if node is function or terminal
    ExpressionTree(std::string initializationExpression, const int currentDepth = 0, const int maxDepth = MAX_PARSE_TREE_DEPTH);
    ExpressionTree(const std::vector<char>& operands, const InitializationMethod initializationMethod, const int currentDepth = 0, const int maxDepth = MAX_PARSE_TREE_DEPTH);

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

    std::string treeToString(ExpressionTree* root) const;
    // In cases whether substitution is not available, expect to do NOTHING
    void treeCrossover(ExpressionTree& other,
                       int crossoverDepth,
                       bool isTestingMode = false,
                       bool movementDirectionWithThisTree = false,
                       bool movementDirectionWithOtherTree = false) {
        if (this->depth == crossoverDepth || other.depth == crossoverDepth) {
            // when crossover depth is 0, it means were preforming root substitution
            if (crossoverDepth == 0)
                rootNodeSub(other);
            else
                std::swap(*this, other);
        }else {

            if (!isTestingMode){
                movementDirectionWithThisTree = std::experimental::randint(0, 1);
                movementDirectionWithOtherTree = std::experimental::randint(0, 1);
            }

            if (movementDirectionWithThisTree && movementDirectionWithOtherTree){
                if (right != nullptr && other.right != nullptr)
                    right->treeCrossover(*other.right, crossoverDepth, isTestingMode, movementDirectionWithThisTree, movementDirectionWithOtherTree);
                else if (right != nullptr && other.right == nullptr)
                    right->treeCrossover(other, crossoverDepth, isTestingMode, movementDirectionWithThisTree, movementDirectionWithOtherTree);
            } else if (movementDirectionWithThisTree && !movementDirectionWithOtherTree){
                if (right != nullptr && other.left != nullptr)
                    right->treeCrossover(*other.left, crossoverDepth, isTestingMode, movementDirectionWithThisTree, movementDirectionWithOtherTree);
                else if (right != nullptr && other.left == nullptr)
                    right->treeCrossover(other, crossoverDepth, isTestingMode, movementDirectionWithThisTree, movementDirectionWithOtherTree);
            } else if (!movementDirectionWithThisTree && movementDirectionWithOtherTree){
                if (left != nullptr && other.right != nullptr)
                    left->treeCrossover(*other.right, crossoverDepth, isTestingMode, movementDirectionWithThisTree, movementDirectionWithOtherTree);
                else if (left != nullptr && other.right == nullptr)
                    left->treeCrossover(other, crossoverDepth, isTestingMode, movementDirectionWithThisTree, movementDirectionWithOtherTree);
            } else if (!movementDirectionWithThisTree && !movementDirectionWithOtherTree){
                if (left != nullptr && other.left != nullptr)
                    left->treeCrossover(*other.left, crossoverDepth, isTestingMode, movementDirectionWithThisTree, movementDirectionWithOtherTree);
                else if (left != nullptr && other.left == nullptr)
                    left->treeCrossover(other, crossoverDepth, isTestingMode, movementDirectionWithThisTree, movementDirectionWithOtherTree);
            }
        }
        postSubActions(other);
    }

    bool isOK() {
        if (func != UKNOWN){
            if (func != NOT)
                return ((left != nullptr && right != nullptr)) ? (isStructureOK(left) && isStructureOK(right)) : false;
            else
                return isStructureOK(left) && right == nullptr;
        } else{
            // means funct is UKNOWN, need to make sure there is terminal
            return val != EMPTY_VALUE;
        }
    }

    virtual inline bool operator==(const ExpressionTree& lhs) {
        return
            this->numberOfSpaces == lhs.numberOfSpaces         &&
            this->left == lhs.left                             &&
            this->right == lhs.right                           &&
            this->height == lhs.height                         &&
            this->depth == lhs.depth                           &&
            this->func == lhs.func                             &&
            this->val == lhs.val                               &&
            this->originalExpression == lhs.originalExpression &&
            this->maxDepth == lhs.maxDepth                     &&
            this->operands == lhs.operands;
    }

protected:
    bool isStructureOK(ExpressionTree* root){
        if (root == nullptr)
            return true;
        // if leaf
        if (root->right == nullptr && root->left == nullptr) {
            // if im bad leaf -> leaf without terminal data or with func
            if (root->val == EMPTY_VALUE || root->func != UKNOWN)
                return false;
            return true;
        }

        if (root->func != UKNOWN)
            if (root->func != NOT)
                return isStructureOK(root->left) && isStructureOK(root->right);
            else
                return isStructureOK(root->left) && root->right == nullptr;
        // because it means im not a leaf and im a terminal, which is wrong
        return false;
    }
    ExpressionTree(char v, const int currentDepth, const int maxDepth);
    ExpressionTree(const std::vector<char>& operands, const int maxDepth, const int currentDepth);

    bool isSingleOperandExpression(const std::string& initializationExpression) const;

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

    void rootNodeSub(ExpressionTree &other) {// need to preform root change
        if (func != UKNOWN && other.func != UKNOWN){
            if (func == NOT || other.func == NOT){
                // I'm not and the other is not
                if (func == NOT && other.func != NOT){
                    // in case like i'm NOT and the other isn't, like the following:
                    //    this                other
                    //     NOT                 OR
                    //    /                   /  \
                    //   a                   NOT  a
                    //                      /
                    //                     b
                    //
                    // Expected result should be the following:
                    //    this                other
                    //     NOT                  OR
                    //    /                    /  \
                    //   b                    a   NOT
                    //                            /
                    //                           a
                    std::swap(*this, other);
                }
                // other is NOT
                if (func != NOT && other.func == NOT){
                    // in case like i'm not NOT and the other is yes, like the following:
                    //    this                other
                    //     OR                   NOT
                    //    /  \                  /
                    //   a   NOT               b
                    //       /
                    //      a
                    // Expected result should be the following:
                    //    this                other
                    //     NOT                  OR
                    //    /                    /  \
                    //   b                    a   NOT
                    //                            /
                    //                           a

                    std::swap(*this, other);
                }
                else {
                    // both are NOT
                    std::swap(this->left, other.left);
                }

            }
            else{
                std::swap(this->func, other.func);
            }
        }
        else if (val != EMPTY_VALUE && other.val != EMPTY_VALUE) {
            std::swap(val, other.val);
        }

//        else{
//            std::swap(*this, other);
//        }
    };

    void postSubActions(ExpressionTree &other) {
        originalExpression = treeToString(this);
        other.originalExpression = treeToString(&other);
        operands = getAllOperands(this);
        other.operands = getAllOperands(&other);
    };

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

    void growInitMethod(const std::vector<char> &operands, const InitializationMethod &initializationMethod,
                   const int maxDepth);
    void fullInitMethod(const std::vector<char> &operands, const InitializationMethod &initializationMethod,
                        const int maxDepth, const int currentDepth = 0);
};

#endif //AILABGENETICALGORITHM_EXPRESSIONTREE_H