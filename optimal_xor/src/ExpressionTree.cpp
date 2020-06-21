

#include <iostream>
#include <set>
#include "../include/ExpressionTree.h"

#include "../include/consts.h"
#include "../include/TooLargeExpressionTreeException.h"

ExpressionTree::ExpressionTree(std::string initializationExpression, const int maxDepth)
: numberOfSpaces{static_cast<int>(1 + 2 * initializationExpression.size())}
, left{nullptr}
, right{nullptr}
, currentHeight{0}
, func{ExpressionTreeFunctions::UKNOWN}
, originalExpression{initializationExpression}
, maxDepth{maxDepth}
{
    auto rootIndexes = getRootIndexes(originalExpression);
    if (rootIndexes.first == -1 && rootIndexes.second == -1) {
        const auto notPos = originalExpression.find_first_of('!');
        if (notPos != std::string::npos && originalExpression.size() > 1) {
            // Found NOT
            func = stringToExpressionTreeFunc.at(std::string{originalExpression[notPos]});
            left = new ExpressionTree{originalExpression.at(1), maxDepth};
            currentHeight = 1;
        } else if (initializationExpression.size() == 1 && initializationExpression != "!") {
            currentHeight = 1;
            val = initializationExpression.at(0);
        } else {
            try {
                func = stringToExpressionTreeFunc.at(originalExpression);
                val = EMPTY_VALUE;
            }
            catch (std::out_of_range &exc) {

            }
        }
    } else {
        // Extracting sub trees - left and right
        std::string leftSide = extractSubTree(originalExpression.substr(0, rootIndexes.first));
        if (leftSide.size() > 1)
            left = new ExpressionTree{leftSide, maxDepth};
        else
            left = new ExpressionTree{leftSide.at(0), maxDepth};
        std::string rightSide = extractSubTree(originalExpression.substr(rootIndexes.second));
        if (rightSide.size() > 1)
            right = new ExpressionTree{rightSide, maxDepth};
        else if (0 < rightSide.size())
            right = new ExpressionTree{rightSide.at(0), maxDepth};
        func = parseExpressionTreeFunc(originalExpression, rootIndexes.first + 1);
    }
    currentHeight = std::max(getHeight(left), getHeight(right)) + 1;
    if (currentHeight > maxDepth)
        throw TooLargeExpressionTreeException{currentHeight, maxDepth};
    operands = getAllOperands();
}

ExpressionTree::ExpressionTree(char v, const int maxDepth)
: numberOfSpaces{static_cast<int>(1 + 2 * 1)}
, left{nullptr}
, right{nullptr}
, currentHeight{0}
, func{ExpressionTreeFunctions::UKNOWN}
, originalExpression{v}
, maxDepth{maxDepth}
{
    val = v;
}

ExpressionTree::ExpressionTree(bool functionOrTerminal, const std::set<char>& operands, const int maxDepth)
: left{nullptr}
, right{nullptr}
, currentHeight{0}
, maxDepth{maxDepth}
{
    if (maxDepth <= 1)
    {
        if (functionOrTerminal) {
            // this is function generation
            // pick random function of known funcs, and call for ctor for both right and left childs. decreasde max depth by 1 for each recursive call!
            func = select_randomly(keyToExpressionFunc.begin(), keyToExpressionFunc.end())->second;
            if (func == ExpressionTreeFunctions::UKNOWN)
                std::cout << "PROBLEM BRO" << std::endl;

            val = EMPTY_VALUE;
            left = new ExpressionTree(!functionOrTerminal, operands, maxDepth - 1);
            if (func != ExpressionTreeFunctions::NOT)
                right = new ExpressionTree(!functionOrTerminal, operands, maxDepth - 1);
            currentHeight = std::max(getHeight(left), getHeight(right)) + 1;
            originalExpression = std::string{"(" + left->originalExpression + ") " + expressionTreeFuncToString.at(func)
                                             + ((right != nullptr ? " (" + right->originalExpression + ")" : ""))};
            numberOfSpaces = static_cast<int>(1 + 2 * originalExpression.size());
        } else {
            val = *(select_randomly(operands.begin(), operands.end()));
            func = ExpressionTreeFunctions::UKNOWN;
            originalExpression = std::string{val};
        }
    } else {
        func = select_randomly(keyToExpressionFunc.begin(), keyToExpressionFunc.end())->second;
        if (func == ExpressionTreeFunctions::UKNOWN)
            std::cout << "PROBLEM BRO" << std::endl;
        val = EMPTY_VALUE;
        left = new ExpressionTree(!functionOrTerminal, operands, maxDepth - 1);
        if (func != ExpressionTreeFunctions::NOT)
            right = new ExpressionTree(!functionOrTerminal, operands, maxDepth - 1);
        currentHeight = std::max(getHeight(left), getHeight(right)) + 1;
        originalExpression = std::string{"(" + left->originalExpression + ") " + expressionTreeFuncToString.at(func)
                                         + ((right != nullptr ? " (" + right->originalExpression + ")" : ""))};
        numberOfSpaces = static_cast<int>(1 + 2 * originalExpression.size());
    }
}

ExpressionTreeFunctions ExpressionTree::getRandomFunc() const {

}
int ExpressionTree::getTreeHeight() const {
    return currentHeight;
}

int ExpressionTree::getMaxDepth() const{
    return maxDepth;
}

int ExpressionTree::getNumberOfOperands() const{
    return operands.size();
}

std::set<char> ExpressionTree::getAllOperands() const {
    return getAllOperands(this);
}

std::set<char> ExpressionTree::getAllOperands(const ExpressionTree *root) const {
    std::set<char> operands;
    if (root != nullptr) {
        if (root->left == nullptr && root->right == nullptr && root->val != EMPTY_VALUE)
            operands.insert(root->val);
        else {
            const auto lef = getAllOperands(root->left);
            const auto right = getAllOperands(root->right);
            for (const auto o : lef)
                operands.insert(o);
            for (const auto o : right)
                operands.insert(o);
        }
    }
    return operands;
}

std::vector<ExpressionTreeFunctions> ExpressionTree::getAllFunctions() {
    std::vector<ExpressionTreeFunctions> funcs;
    auto leftSide = getAllFunctions(left);
    auto rightSide = getAllFunctions(right);
    for (const auto funC : leftSide)
        funcs.push_back(funC);
    funcs.push_back(func);
    for (const auto funC : rightSide)
        funcs.push_back(funC);
    return funcs;
}

void ExpressionTree::print() {
    std::cout << "Used Operands are:" << std::endl;
    for (const auto v : getAllOperands())
        std::cout << v << ", ";
    std::cout << std::endl;
    std::cout << "Used funcs are:" << std::endl;
    for (const auto v : getAllFunctions())
        if (v != ExpressionTreeFunctions::UKNOWN)
            std::cout << expressionTreeFuncToString.at(v) << ", ";
    std::cout << std::endl;
    std::cout << "Height is: " << currentHeight << std::endl;
}

void ExpressionTree::printTruthTable() {
    auto allOperatorsPermutations = getAllPermutationsForOperands();
    printTableBorder(allOperatorsPermutations);
    printTruthTableHeaderLine(allOperatorsPermutations);
    for (int line = 0; line < allOperatorsPermutations.size(); line++) {
        std::cout << "|";
        for (const auto operand : allOperatorsPermutations.at(line))
            std::cout << "    " << (operand.second == true ? "1" : "0")  << "    |";
        for (int index = 0; index < numberOfSpaces / 2 - 4; index++)
            std::cout << ' ';
        std::cout << (evaluateExpression(allOperatorsPermutations[line]) == true ? "1" : "0");
        for (int index = 0; index < numberOfSpaces / 2; index++)
            std::cout << ' ';
        std::cout << '|';
        // just for not printing the pattern in the last line, for identation
        if (line <= allOperatorsPermutations.size() - 2) {
            std::cout << std::endl;
//            std::cout << "|    ";
        }
    }
    std::cout << std::endl;
    printTableBorder(allOperatorsPermutations);
}

bool ExpressionTree::evaluateExpression(const std::vector<std::pair<char, bool>> &operands) {
    const auto leftSubtree = evaluateExpression(operands, this->left, 0);
    const auto rightSubtree = evaluateExpression(operands, this->right, operands.size());
    switch (func) {
        case (AND):
            return *leftSubtree && *rightSubtree;
        case (OR):
            return *leftSubtree || *rightSubtree;
            break;
        case (NOT):
            if (!leftSubtree.get() && rightSubtree.get())
                return !*rightSubtree;
            else if (leftSubtree.get() && !rightSubtree.get())
                return !*leftSubtree;
            break;
        case (XOR):
            return *leftSubtree ^ *rightSubtree;
        case (UKNOWN):
            if (!leftSubtree.get() && !rightSubtree.get())
                for (const auto& operand : operands)
                    if (operand.first == this->val)
                        return operand.second;
            break;
    }
}

std::unique_ptr<bool>
ExpressionTree::evaluateExpression(const std::vector<std::pair<char, bool>> &operands, const ExpressionTree *root, int startIndex) {
    if (root == nullptr)
        return {};
    else if (root->right == nullptr && root->left == nullptr && root->func == ExpressionTreeFunctions::UKNOWN) {
        if (startIndex == 0) {
            for (const auto& operand : operands)
                if (operand.first == root->val)
                    return std::make_unique<bool>(operand.second);
        } else{
            for (int index = operands.size() - 1; index >= 0; index--){
                if (operands.at(index).first == root->val)
                    return std::make_unique<bool>(operands.at(index).second);
            }
        }
    }
    const auto leftSubtree = evaluateExpression(operands, root->left, startIndex);
    const auto rightSubtree = evaluateExpression(operands, root->right, startIndex);
    switch (root->func) {
        case (AND):
            return std::make_unique<bool>(*leftSubtree && *rightSubtree);
        case (OR):
            return std::make_unique<bool>(*leftSubtree || *rightSubtree);
            break;
        case (NOT):
            if (root->left == nullptr && root->right != nullptr)
                return std::make_unique<bool>(!*rightSubtree);
            else if (root->left != nullptr && root->right == nullptr)
                return std::make_unique<bool>(!*leftSubtree);
            break;
        case (XOR):
            return std::make_unique<bool>(*leftSubtree ^ *rightSubtree);
            break;
    }
    return {};
}

void ExpressionTree::printTableBorder(const std::vector<std::vector<std::pair<char, bool>>> &operators) {
    // how many '=' needed? 4 * 2 + 1 -> for each operand + 4 * 2 + sizeOfOriginalExpression
    // operands[0].size() => number of pairs -> operands, each one of them needs (4 * 2) by const + 1 because its the size of char, +2 for | begin, | end
//    for (int i = 0; i <= (operators[0].size() * ((4 * 2) + 1)) + (1 + (2 * originalExpression.size())) + 3; i++)
    int numberOfCharactersToPrint = (operators[0].size() * ((4 * 2) + 1)) + (1 + (2 * originalExpression.size()));
    for (int i = 0; i < numberOfCharactersToPrint; i++)
        std::cout << '=';
    std::cout << std::endl;
}

void ExpressionTree::printTruthTableHeaderLine(const std::vector<std::vector<std::pair<char, bool>>> &operators) {
    std::cout << "|";
    for (const auto permutation : operators[0]) {
        printExpression(permutation.first);
    }
    printExpression(originalExpression);

    std::cout << std::endl;
//    std::cout << "|";
//    for (int i = 0; i < operators[0].size(); i++) {
//        for (int j = 0; j < numberOfSpaces * 2 + 1; j++)
//            std::cout << '-';
//        std::cout << '|';
//    }
//    for (int j = 0; j < originalExpression.size() * 2 + 1; j++)
//        std::cout << '-';
//    std::cout << '|';
//    std::cout << std::endl;
//    std::cout << "|    ";

}

void ExpressionTree::printExpression(const std::string expr) {
    const int numberOfSpaces = 4;
    for (int i = 0; i < numberOfSpaces; i++) {
        std::cout << ' ';
    }
    std::cout << expr;
    for (int i = 0; i < numberOfSpaces; i++) {
        std::cout << ' ';
    }
    std::cout << "|";
}

void ExpressionTree::printExpression(const char expr) {
    printExpression(std::string{expr});
}

std::vector<std::vector<std::pair<char, bool>>> ExpressionTree::getAllPermutationsForOperands() {
    // Hard coded example
    auto operands = getAllOperands();
    return getPermutation(operands);
}

std::vector<std::vector<std::pair<char, bool>>> ExpressionTree::getPermutation(std::set<char> operators) {
    std::vector<std::vector<std::pair<char, bool>>> allOperandsPemutate;
    if (operators.size() == 1){
        const char x = operators.begin().operator*();
        // in case we have 1 operands, we have 2 lines
        // A = true
        std::vector<std::pair<char, bool>> lineOne;
        lineOne.push_back(std::make_pair(x, true));
        allOperandsPemutate.push_back(lineOne);
        // A = false
        std::vector<std::pair<char, bool>> lineTwo;
        lineTwo.push_back(std::make_pair(x, false));
        allOperandsPemutate.push_back(lineTwo);
    } else if (operators.size() == 2) {
        auto oper = operators.begin();
        const char x = *oper;
        oper++;
        const char y = *oper;
        // in case we have 2 operands, we have 4 lines
        std::vector<std::pair<char, bool>> lineOne;
        lineOne.push_back(std::make_pair(x, true));
        lineOne.push_back(std::make_pair(y, true));
        allOperandsPemutate.push_back(lineOne);
        // A = true B = false
        std::vector<std::pair<char, bool>> lineTwo;
        lineTwo.push_back(std::make_pair(x, true));
        lineTwo.push_back(std::make_pair(y, false));
        allOperandsPemutate.push_back(lineTwo);
        // A = false B = true
        std::vector<std::pair<char, bool>> lineThree;
        lineThree.push_back(std::make_pair(x, false));
        lineThree.push_back(std::make_pair(y, true));
        allOperandsPemutate.push_back(lineThree);
        // A = false B = false
        std::vector<std::pair<char, bool>> lineFour;
        lineFour.push_back(std::make_pair(x, false));
        lineFour.push_back(std::make_pair(y, false));
        allOperandsPemutate.push_back(lineFour);
    } else {
        std::set<char> tmp;
        auto beg = operators.begin();
        beg++;
        while (beg != operators.end()){
            tmp.insert(*beg);
            beg++;
        }
        for (auto &per : getPermutation(tmp)) {
            per.insert(per.begin(), std::make_pair(operators.begin().operator*(), true));
            allOperandsPemutate.push_back(per);
        }
        for (auto &per : getPermutation(tmp)) {
            per.insert(per.begin(), std::make_pair(operators.begin().operator*(), false));
            allOperandsPemutate.push_back(per);
        }
    }
    return allOperandsPemutate;
}

int ExpressionTree::getHeight(ExpressionTree *root) {
    if (root == nullptr)
        return 0;
    else if (root->right == nullptr && root->left == nullptr)
        return 1;
    return getHeight(root->right) + getHeight(root->left);
}

std::vector<ExpressionTreeFunctions> ExpressionTree::getAllFunctions(ExpressionTree *root) {
    std::vector<ExpressionTreeFunctions> funcs;
    if (root != nullptr && !(root->left == nullptr && root->right == nullptr)) {
        const auto lef = getAllFunctions(root->left);
        const auto right = getAllFunctions(root->right);
        funcs.push_back(root->func);
        for (const auto o : lef)
            funcs.push_back(o);
        for (const auto o : right)
            funcs.push_back(o);
    }
    return funcs;
}

ExpressionTreeFunctions ExpressionTree::parseExpressionTreeFunc(const std::string &rawSubTree,
                                                                const int rootStartIndex) {
    int end = rootStartIndex + 1;
    while (end < rawSubTree.size() && rawSubTree.at(end) != ' ')
        end++;
    std::string bla = rawSubTree.substr(rootStartIndex, end - rootStartIndex);
    return stringToExpressionTreeFunc.at(bla);
}

std::string ExpressionTree::extractSubTree(std::string rawSubTree) {
    std::string extractedSubTree;
    int start = rawSubTree.find_first_of('(') + 1;
    int endd = rawSubTree.find_last_of(')') - 1;
    if (start == endd)
        extractedSubTree = rawSubTree.at(endd);
    else if (start == 0 && endd < 0) // means there are no brackets here, need to remove leading spaces
    {
        for (const auto c : rawSubTree)
            if (c != ' ')
                extractedSubTree.append(std::string{c});
    } else
        extractedSubTree = rawSubTree.substr(start, endd - start + 1);
    return extractedSubTree;
}

bool ExpressionTree::isComplexTree(const std::string &initializationExpression) {
    // non-complex expression is an expression without '(' / ')'
    int anyBracketsCounter = 0;
    for (const auto c : initializationExpression)
        if (c == ')' || c == '(')
            anyBracketsCounter++;
    return anyBracketsCounter != 0;
}

std::pair<int, int> ExpressionTree::getRootIndexes(const std::string &initializationExpression) {
    if (isComplexTree(initializationExpression)) {
        int rootStartIndex;
        int rootEndIndex;
        int openedBracketsCounter = 0;
        bool hasRootFound = false;
        std::string initalizationExpressionNonWrapped;
        // remove wrapping brackets
        int endIndex = initializationExpression.size() - 1;
        for (int i = 0; i <= endIndex; i++) {
            if (initializationExpression.at(i) == '(' && initializationExpression.at(endIndex) == ')') {
                endIndex--;
            } else
                initalizationExpressionNonWrapped.append(std::string{initializationExpression[i]});
        }
        for (rootStartIndex = 0; rootStartIndex < initializationExpression.size() && !hasRootFound; rootStartIndex++) {
            const auto c = initializationExpression.at(rootStartIndex);
            if (c == '(')
                openedBracketsCounter++;
            if (c == ')')
                openedBracketsCounter--;
            if (openedBracketsCounter < 0)
                std::cout << "ERROR MATE!" << std::endl;
            if (openedBracketsCounter == 0)
                hasRootFound = true;
        }
        rootEndIndex = initializationExpression.find_first_of('(', rootStartIndex);
        if (rootEndIndex == -1) {
            int tempIndex = rootStartIndex + 1;
            while (tempIndex < initializationExpression.size() && initializationExpression.at(tempIndex) != ' ')
                ++tempIndex;
            rootEndIndex = tempIndex + 1;
            if (rootEndIndex > initializationExpression.size())
                rootEndIndex = initializationExpression.size();
        }
        return std::make_pair(rootStartIndex, rootEndIndex);
    } else {
        // Dealing with simple expression
        int firstSpace = initializationExpression.find_first_of(' ');
        int lastSpace = initializationExpression.find_last_of(' ');
        return std::make_pair(firstSpace, lastSpace);
    }
}

std::vector<bool> ExpressionTree::getEvaluatedResults() {
    std::vector<bool> evaluatedResults;
    for (const auto& permutate : getAllPermutationsForOperands())
        evaluatedResults.push_back(evaluateExpression(permutate));
    return evaluatedResults;
}