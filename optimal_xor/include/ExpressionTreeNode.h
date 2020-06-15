//
// Created by barak on 13/06/2020.
//

#ifndef AILABGENETICALGORITHM_EXPRESSIONTREENODE_H
#define AILABGENETICALGORITHM_EXPRESSIONTREENODE_H

#include "ExpressionTreeFunctions.h"
#include "ExpressionTree.h"
#include "consts.h"
#include <string>

class ExpressionTreeNode {
public:

    ExpressionTreeNode(const ExpressionTreeFunctions nodeFunc, char leftTerminal, const ExpressionTreeFunctions rightFunc);
    ExpressionTreeNode(const ExpressionTreeFunctions nodeFunc, char rightTerminal);
    ExpressionTreeNode(char leftTerminal, const ExpressionTreeFunctions nodeFunc);

    // I beleive those are the relevant ctors!`
    ExpressionTreeNode(char terminal);
    ExpressionTreeNode(const ExpressionTreeFunctions nodeFunc);
//    ExpressionTreeNode(const ExpressionTreeFunctions nodeFunc, char leftTerminal, char rightTerninal);

    virtual ~ExpressionTreeNode() = default;

    bool isLeaf() const;
    ExpressionTreeNode* getLeftChild() const;
    ExpressionTreeNode* getRightChild() const;

    const ExpressionTreeFunctions getNodeFunc() const;
    const char getNodeTerminal() const;
    ExpressionTreeNode* setLeftChild(ExpressionTreeFunctions nodeFunc);
    ExpressionTreeNode* setRightChild(ExpressionTreeFunctions nodeFunc);
    void setLeftChild(char leftTerminal);
    void setRightChild(char rightTerminal);
    ExpressionTreeNode* setRightChild(ExpressionTreeNode* rootOfSubtree);
    ExpressionTreeNode* setLeftChild(ExpressionTreeNode* rootOfSubtree);
    void printTree() const;
    bool operator==(const ExpressionTreeNode& other) const;
    std::string getNodeValue() const;

protected:
    ExpressionTreeNode();
    ExpressionTreeNode(const int maxDepth,
                       const ExpressionTreeFunctions nodeFunc=ExpressionTreeFunctions::UKNOWN);
    void printTree(const ExpressionTreeNode *root, int height=1, bool isLeftChildOrRoot = false) const;
    void printNodeContent(const ExpressionTreeNode* root, const int heightInTree) const;
    void printNodeFunction(const ExpressionTreeNode *root, const int heightInTree) const;
    void printNodeTerminal(const ExpressionTreeNode *root) const;
    void printByHeight(const std::string& val) const;
    void printReservedSpacesByHeight(const int heightInTree) const;
//    const int maxDepth;
    const int numberOfSpacesForPrint;
    char terminal;
    ExpressionTreeFunctions nodeFunc;
    ExpressionTreeNode* rnode;
    ExpressionTreeNode* lnode;
};
#endif //AILABGENETICALGORITHM_EXPRESSIONTREENODE_H


////
//// Created by barak on 13/06/2020.
////
//
//#ifndef AILABGENETICALGORITHM_EXPRESSIONTREE_H
//#define AILABGENETICALGORITHM_EXPRESSIONTREE_H
//
//
//#include "consts.h"
//#include "ExpressionTreeNode.h"
//#include <string>
//
//class ExpressionTree {
//public:
//    ExpressionTree(const ExpressionTreeFunctions rootTreeFunc = ExpressionTreeFunctions::AND, const int depth = MAX_PARSE_TREE_DEPTH);
//    ExpressionTree(const ExpressionTreeFunctions rootTreeFunc, char leftTerminal, char rightTerminal, const int depth = MAX_PARSE_TREE_DEPTH);
//    virtual ~ExpressionTree() = default;
//
//    void printTree() const;
//
//    void appendToSpecificFunction(ExpressionTreeFunctions funcToAppendFrom, const ExpressionTree& treeToAppend);
//    ExpressionTree addRightChild(ExpressionTreeFunctions rightChild);
//    ExpressionTree addLeftChild(ExpressionTreeFunctions leftChild);
//    ExpressionTree addRightChild(char rightTerminal);
//    ExpressionTree addLeftChild(char leftTerminal);
//protected:

//
//    bool appendToRoot(ExpressionTreeFunctions funcToAppendFrom, const ExpressionTree& treeToAppend);
//    bool appendToLeftSide(ExpressionTreeFunctions funcToAppendFrom, const ExpressionTree& treeToAppend);
//    bool appendToRightSide(ExpressionTreeFunctions funcToAppendFrom, const ExpressionTree& treeToAppend);

//};
//
//#endif //AILABGENETICALGORITHM_EXPRESSIONTREE_H
