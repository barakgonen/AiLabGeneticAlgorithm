//
// Created by barak on 13/06/2020.
//

#ifndef AILABGENETICALGORITHM_EXPRESSIONTREENODE_H
#define AILABGENETICALGORITHM_EXPRESSIONTREENODE_H

#include "ExpressionTreeFunctions.h"

class ExpressionTreeNode {
public:
    ExpressionTreeNode(const ExpressionTreeFunctions nodeFunc);
    virtual ~ExpressionTreeNode() = default;

    ExpressionTreeNode* getLeftChild() const;
    ExpressionTreeNode* getRightChild() const;
    ExpressionTreeFunctions getNodeFunc() const;
    void setLeftChild(ExpressionTreeNode* lnode);
    void setRightChild(ExpressionTreeNode* rnode);

protected:
    ExpressionTreeFunctions nodeFunc;
    char* terminal;
    ExpressionTreeNode* rnode;
    ExpressionTreeNode* lnode;
};
#endif //AILABGENETICALGORITHM_EXPRESSIONTREENODE_H
