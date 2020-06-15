//
// Created by barak on 13/06/2020.
//

#include "../include/ExpressionTreeNode.h"
#include <iostream>

ExpressionTreeNode::ExpressionTreeNode(const ExpressionTreeFunctions nodeFunc)
: nodeFunc{nodeFunc}
, terminal{nullptr}
, rnode{nullptr}
, lnode{nullptr}
{
}

ExpressionTreeNode *ExpressionTreeNode::getLeftChild() const {
    return lnode;
}

ExpressionTreeNode *ExpressionTreeNode::getRightChild() const {
    return rnode;
}

ExpressionTreeFunctions ExpressionTreeNode::getNodeFunc() const {
    return nodeFunc;
}

void ExpressionTreeNode::setLeftChild(ExpressionTreeNode *lnode) {
    lnode = lnode;
}

void ExpressionTreeNode::setRightChild(ExpressionTreeNode *rnode) {
    rnode = rnode;
}



