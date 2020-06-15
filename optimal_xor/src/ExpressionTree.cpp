//
// Created by barak on 13/06/2020.
//

#include "../include/ExpressionTree.h"
#include <iostream>

ExpressionTree::ExpressionTree(const ExpressionTreeFunctions rootTreeFunc, const int depth)
: size{depth}
, root{rootTreeFunc}
{
}

ExpressionTreeNode ExpressionTree::addRightChild(ExpressionTreeNode *rightChild) {
    root.setRightChild(rightChild);
    return root;
}

ExpressionTreeNode ExpressionTree::addLeftChild(ExpressionTreeNode *leftChild) {
    root.setLeftChild(leftChild);
    return root;
}


void ExpressionTree::printTree() const {
    printTree(&root);
}

void ExpressionTree::printTree(const ExpressionTreeNode *root, int height) const {
    if (root == nullptr)
        return;
    printTree(root->getLeftChild(), height + 1);
    printNodeFunc(root->getNodeFunc(), height);
    printTree(root->getRightChild(), height + 1);
}

void ExpressionTree::printNodeFunc(const ExpressionTreeFunctions func, const int heightInTree) const {
    std::string valueToPrint = " ";
    switch (func) {
        case AND:
            valueToPrint += "AND";
            break;
        case OR:
            valueToPrint += "OR";
            break;
        case NOT:
            valueToPrint += "NOT";
            break;
    }
    printByHeight(valueToPrint, heightInTree);
    printByHeight("/   \\", heightInTree);
}

void ExpressionTree::printByHeight(const std::string valueToPrint, const int heightInTree) const{
    for (int i = 0; i < heightInTree * 50; i++)
        std::cout << " ";
    std::cout << valueToPrint;
    std::cout << std::endl;
}