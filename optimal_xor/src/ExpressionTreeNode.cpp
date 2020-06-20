////
//// Created by barak on 13/06/2020.
////
//
//#include "../include/ExpressionTreeNode.h"
//#include "../include/ExpressionTree.h"
//#include <iostream>
//
//ExpressionTreeNode::ExpressionTreeNode()
////ExpressionTreeNode::ExpressionTreeNode(const int maxDepth)
////: maxDepth{maxDepth}
//: numberOfSpacesForPrint{NUMBER_OF_SPACES}
//, terminal{' '}
//, nodeFunc{ExpressionTreeFunctions::UKNOWN}
//, rnode{nullptr}
//, lnode{nullptr}
//{
//}
//
//ExpressionTreeNode::ExpressionTreeNode(const ExpressionTreeFunctions nodeFunc)
//: ExpressionTreeNode()
//{
//    this->nodeFunc = nodeFunc;
//}
//
//ExpressionTreeNode::ExpressionTreeNode(ExpressionTreeFunctions nodeFunc, char rightTerminal)
//: ExpressionTreeNode(nodeFunc)
//{
//    setRightChild(rightTerminal);
//}
//
//ExpressionTreeNode::ExpressionTreeNode(char leftTerminal, ExpressionTreeFunctions nodeFunc)
//: ExpressionTreeNode(nodeFunc)
//{
//    setLeftChild(leftTerminal);
//}
//
//ExpressionTreeNode::ExpressionTreeNode(const ExpressionTreeFunctions nodeFunc,
//                                       char leftTerminal,
//                                       const ExpressionTreeFunctions rightFunc)
//: ExpressionTreeNode(nodeFunc)
//{
//    setLeftChild(leftTerminal);
//    setRightChild(rightFunc);
//}
//
//ExpressionTreeNode::ExpressionTreeNode(char leftTerminal)
//: ExpressionTreeNode()
//{
//    setLeftChild(leftTerminal);
//}
////ExpressionTreeNode::ExpressionTreeNode(ExpressionTreeFunctions nodeFunc,
////                                       char rightTerminal,
////                                       ExpressionTreeFunctions leftFunc)
////: ExpressionTreeNode(nodeFunc, rightTerminal)
////{
////    setLeftChild(leftFunc);
////}
//
//bool ExpressionTreeNode::isLeaf() const {
//    return lnode == nullptr && rnode == nullptr;
//}
//
//ExpressionTreeNode *ExpressionTreeNode::getLeftChild() const {
//    return lnode;
//}
//
//ExpressionTreeNode *ExpressionTreeNode::getRightChild() const {
//    return rnode;
//}
//
//const ExpressionTreeFunctions ExpressionTreeNode::getNodeFunc() const {
//    return nodeFunc;
//}
//
//const char ExpressionTreeNode::getNodeTerminal() const {
//    return terminal;
//}
//
//ExpressionTreeNode* ExpressionTreeNode::setLeftChild(ExpressionTreeFunctions lnodee) {
////    lnode{lnode};
//    lnode = new ExpressionTreeNode{lnodee};
//    return this;
//}
//
//ExpressionTreeNode* ExpressionTreeNode::setRightChild(ExpressionTreeFunctions rnodee) {
//    rnode = new ExpressionTreeNode{rnodee};
//    return this;
//}
//
//void ExpressionTreeNode::setLeftChild(char leftTerminal){
//    ExpressionTreeNode* node = new ExpressionTreeNode{};
//    node->terminal = leftTerminal;
//    node->nodeFunc = ExpressionTreeFunctions::UKNOWN;
//    if (lnode == nullptr) {
//        lnode = node;
//    } else {
//        lnode->terminal = leftTerminal;
//    }
//}
//
//void ExpressionTreeNode::setRightChild(char rightTerminal) {
//    ExpressionTreeNode* node = new ExpressionTreeNode{};
//    node->terminal = rightTerminal;
//    node->nodeFunc = ExpressionTreeFunctions::UKNOWN;
//    if (rnode == nullptr){
//        rnode = node;
//    } else{
//        rnode->terminal = rightTerminal;
//    }
//}
//
//ExpressionTreeNode* ExpressionTreeNode::setRightChild(ExpressionTreeNode *rootOfSubtree) {
//    rnode = rootOfSubtree;
//    return this;
//}
//
//ExpressionTreeNode* ExpressionTreeNode::setLeftChild(ExpressionTreeNode *rootOfSubtree) {
//    lnode = rootOfSubtree;
//    return this;
//}
//
//void ExpressionTreeNode::printTree() const {
//    printTree(this, 1, true);
//    std::cout << std::endl;
//}
//
//void ExpressionTreeNode::printTree(const ExpressionTreeNode *root, int height, bool isLeftChild) const {
//    if (root == nullptr)
//        return;
//    printReservedSpacesByHeight(height);
////    if (isLeftChild || root->getLeftChild() != nullptr)
////        printReservedSpacesByHeight(height);
////    else if (root->getLeftChild() == nullptr && root->getRightChild() != nullptr)
////        printReservedSpacesByHeight(height);
//    printNodeContent(root, height);
//    printTree(root->getLeftChild(), height + 2, true);
//    printTree(root->getRightChild(), height + 2);
//}
//
//void ExpressionTreeNode::printNodeContent(const ExpressionTreeNode *root, const int heightInTree) const {
//    if (root->getNodeFunc() == ExpressionTreeFunctions::UKNOWN)
//        printNodeTerminal(root);
//    else
//        printNodeFunction(root, heightInTree);
//}
//
//void ExpressionTreeNode::printNodeFunction(const ExpressionTreeNode *root, const int heightInTree) const {
//    std::string valueToPrint = "";
//    switch (root->getNodeFunc()) {
//        case AND:
//            valueToPrint += "AND";
//            break;
//        case OR:
//            valueToPrint += "OR";
//            break;
//        case NOT:
//            valueToPrint += "NOT";
//            break;
//    }
////    printReservedSpacesByHeight(heightInTree);
//    printByHeight({valueToPrint/*, s*/});
//    std::cout << std::endl;
//    if (!root->isLeaf()) {
//        std::string s = "/   \\";
//        printReservedSpacesByHeight(heightInTree + 1);
//        printByHeight(s);
//        std::cout << std::endl;
//    }
//}
//
//void ExpressionTreeNode::printNodeTerminal(const ExpressionTreeNode *root) const {
//    printByHeight(std::string{root->getNodeTerminal()});
//}
//
//void ExpressionTreeNode::printByHeight(const std::string& val) const {
//    std::cout << val << "     ";
//}
//
//void ExpressionTreeNode::printReservedSpacesByHeight(const int heightInTree) const {
//    for (int i = 0; i < numberOfSpacesForPrint - heightInTree; i++)
//        std::cout << " ";
//}
//
//bool ExpressionTreeNode::operator==(const ExpressionTreeNode& other) const {
//    return numberOfSpacesForPrint == other.numberOfSpacesForPrint &&
//           terminal == other.terminal &&
//           nodeFunc == other.nodeFunc &&
//           rnode == other.rnode &&
//           lnode == other.lnode;
//}
//
//
//std::string ExpressionTreeNode::getNodeValue() const {
//    if (terminal == ' ' && nodeFunc != ExpressionTreeFunctions::UKNOWN)
//        return expressionTreeFuncToString.at(nodeFunc);
//    else
//        return std::string{terminal};
//}
//
//////
////// Created by barak on 13/06/2020.
//////
////
////#include "../include/ExpressionTree.h"
////#include <iostream>
////
////ExpressionTree::ExpressionTree(const ExpressionTreeFunctions rootTreeFunc, const int depth)
////: maxDepth{depth}
////, root{new ExpressionTreeNode{rootTreeFunc}}
////, numberOfSpacesForPrint{50}
////{
////}
////
////ExpressionTree::ExpressionTree(ExpressionTreeFunctions rootTreeFunc,
////                               char leftTerminal,
////                               char rightTerminal,
////                               const int depth)
////: ExpressionTree{rootTreeFunc, depth}
////{
////    root->setLeftChild(leftTerminal);
////    root->setRightChild(rightTerminal);
////}
////
////ExpressionTree ExpressionTree::addRightChild(ExpressionTreeFunctions rightFunc) {
////    root->setRightChild(rightFunc);
////    return *this;
////}
////
////ExpressionTree ExpressionTree::addLeftChild(ExpressionTreeFunctions leftFunc) {
////    root->setLeftChild(leftFunc);
////    return *this;
////}
////
////ExpressionTree ExpressionTree::addRightChild(char rightTerminal) {
////    root->setRightChild(rightTerminal);
////    return *this;
////}
////
////ExpressionTree ExpressionTree::addLeftChild(char leftTerminal) {
////    root->setLeftChild(leftTerminal);
////    return *this;
////}
////
////// Trying to append to root, if not, to the left side, than trying for the right side
////// first of all - searching for the expected function, when we find it, appending to it's subtree if it's free
////void ExpressionTree::appendToSpecificFunction(ExpressionTreeFunctions funcToAppendFrom,
////                                              const ExpressionTree &treeToAppend) {
////    auto* temp = root;
////    bool hasFound = false;
////    hasFound = appendToRoot(funcToAppendFrom, treeToAppend);
////    if (hasFound)
////        return;
////    hasFound = appendToLeftSide(funcToAppendFrom, treeToAppend);
////    if (hasFound)
////        return;
////    hasFound = appendToRightSide(funcToAppendFrom, treeToAppend);
////    if (hasFound)
////        return;
////}
////
////bool ExpressionTree::appendToRoot(ExpressionTreeFunctions funcToAppendFrom, const ExpressionTree &treeToAppend) {
////    if (root->getNodeFunc() == funcToAppendFrom)
////    {
////        // As we defined this function, it will try to set left child and than right child
////        if (root->getLeftChild() == nullptr)
////            root->se
////    }
////    return false;
////}
////
////bool ExpressionTree::appendToLeftSide(ExpressionTreeFunctions funcToAppendFrom, const ExpressionTree &treeToAppend) {
////    return false;
////}
////
////bool ExpressionTree::appendToRightSide(ExpressionTreeFunctions funcToAppendFrom, const ExpressionTree &treeToAppend) {
////    return false;
////}
//
//
//
