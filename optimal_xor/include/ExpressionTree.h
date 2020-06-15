//
// Created by barak on 13/06/2020.
//

#ifndef AILABGENETICALGORITHM_EXPRESSIONTREE_H
#define AILABGENETICALGORITHM_EXPRESSIONTREE_H


#include "consts.h"
#include "ExpressionTreeNode.h"
#include <string>

class ExpressionTree {
public:
    ExpressionTree(const ExpressionTreeFunctions rootTreeFunc = ExpressionTreeFunctions::AND, const int depth = MAX_PARSE_TREE_DEPTH);
    virtual ~ExpressionTree() = default;

    void printTree() const;

    ExpressionTreeNode addRightChild(ExpressionTreeNode* rightChild);
    ExpressionTreeNode addLeftChild(ExpressionTreeNode* leftChild);

protected:
    void printTree(const ExpressionTreeNode *root, int height=1) const;
    void printNodeFunc(const ExpressionTreeFunctions func, const int heightInTree) const;
    void printByHeight(const std::string valueToPrint, const int heightInTree) const;
    const int size;
    ExpressionTreeNode root;
};

#endif //AILABGENETICALGORITHM_EXPRESSIONTREE_H
