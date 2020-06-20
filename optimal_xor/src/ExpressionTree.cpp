

#include <iostream>
#include "../include/ExpressionTree.h"

#include "../include/consts.h"

ExpressionTree::ExpressionTree(std::string initializationExpression, const int maxHeight)
: numberOfSpaces{static_cast<int>(1 + 2 * initializationExpression.size())}
, left{nullptr}
, right{nullptr}
, currentHeight{0}
, func{ExpressionTreeFunctions::UKNOWN}
, originalExpression{initializationExpression}
{
    auto rootIndexes = getRootIndexes(originalExpression);
    if (rootIndexes.first == -1 && rootIndexes.second == -1) {
        const auto notPos = originalExpression.find_first_of('!');
        if (notPos != std::string::npos && originalExpression.size() > 1) {
            // Found NOT
            func = stringToExpressionTreeFunc.at(std::string{originalExpression[notPos]});
            left = new ExpressionTree{originalExpression.at(1)};
        } else {
            try {
                func = stringToExpressionTreeFunc.at(originalExpression);
            }
            catch (std::out_of_range &exc) {

            }
        }
    } else {
        // Extracting sub trees - left and right
        std::string leftSide = extractSubTree(originalExpression.substr(0, rootIndexes.first));
        if (leftSide.size() > 1)
            left = new ExpressionTree{leftSide};
        else
            left = new ExpressionTree{leftSide.at(0)};
        std::string rightSide = extractSubTree(originalExpression.substr(rootIndexes.second));
        if (rightSide.size() > 1)
            right = new ExpressionTree{rightSide};
        else
            right = new ExpressionTree{rightSide.at(0)};
        func = parseExpressionTreeFunc(originalExpression, rootIndexes.first + 1);
    }
    currentHeight = std::max(getHeight(left), getHeight(right)) + 1;
}

ExpressionTree::ExpressionTree(char v)
: numberOfSpaces{static_cast<int>(1 + 2 * 1)}
, left{nullptr}
, right{nullptr}
, currentHeight{0}
, func{ExpressionTreeFunctions::UKNOWN}
, originalExpression{v}
{
    val = v;
}

int ExpressionTree::getTreeHeight() {
    return currentHeight;
}

std::vector<char> ExpressionTree::getAllOperands() {
    std::vector<char> operands;
    auto leftSide = getAllOperands(left);
    auto rightSide = getAllOperands(right);
    for (const auto operand : leftSide)
        operands.push_back(operand);
    for (const auto operand : rightSide)
        operands.push_back(operand);
    return operands;
}

std::vector<ExpressionTreeFunctions> ExpressionTree::getAllFunctions() {
    std::vector<ExpressionTreeFunctions> funcs;
    auto leftSide = getAllFunctions(left);
    auto rightSide = getAllFunctions(right);
    funcs.push_back(func);
    for (const auto funC : leftSide)
        funcs.push_back(funC);
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
        std::cout << expressionTreeFuncToString.at(v) << ", ";
    std::cout << std::endl;
    std::cout << "Height is: " << currentHeight << std::endl;
}

void ExpressionTree::printTruthTable() {
    auto allOperatorsPermutations = getAllPermutationsForOperands();
    printTableBorder(allOperatorsPermutations);
    printTruthTableHeaderLine(allOperatorsPermutations);
    for (int line = 0; line < allOperatorsPermutations.size(); line++) {
        for (const auto operand : allOperatorsPermutations.at(line))
            std::cout << operand.second << "    |    ";
        for (int index = 0; index < numberOfSpaces / 2 - 4; index++)
            std::cout << ' ';
        std::cout << evaluateExpression(allOperatorsPermutations[line]);
        for (int index = 0; index < numberOfSpaces / 2; index++)
            std::cout << ' ';
        std::cout << '|';
        // just for not printing the pattern in the last line, for identation
        if (line <= allOperatorsPermutations.size() - 2) {
            std::cout << std::endl;
            std::cout << "|    ";
        }
    }
    std::cout << std::endl;
    printTableBorder(allOperatorsPermutations);
}

bool ExpressionTree::evaluateExpression(const std::vector<std::pair<char, bool>> &operands) {
    const auto leftSubtree = evaluateExpression(operands, this->left);
    const auto rightSubtree = evaluateExpression(operands, this->right);
    switch (func) {
        case (AND):
            return *leftSubtree && *rightSubtree;
        case (OR):
            return *leftSubtree || *rightSubtree;
            break;
        case (NOT):
            if (left == nullptr && right != nullptr)
                return !*rightSubtree;
            else if (left != nullptr && right == nullptr)
                return !*leftSubtree;
            break;
        case (XOR):
            return *leftSubtree ^ *rightSubtree;
            break;
    }
}

std::unique_ptr<bool>
ExpressionTree::evaluateExpression(const std::vector<std::pair<char, bool>> &operands, const ExpressionTree *root) {
    if (root == nullptr)
        return {};
    else if (root->right == nullptr && root->left == nullptr && root->func == ExpressionTreeFunctions::UKNOWN) {
        for (const auto& operand : operands)
            if (operand.first == root->val)
                return std::make_unique<bool>(operand.second); // must refactor from string to char
    }
    const auto leftSubtree = evaluateExpression(operands, root->left);
    const auto rightSubtree = evaluateExpression(operands, root->right);
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
}

void ExpressionTree::printTableBorder(const std::vector<std::vector<std::pair<char, bool>>> &operators) {
    // how many '=' needed? 4 * 2 + 1 -> for each operand + 4 * 2 + sizeOfOriginalExpression
    // operators[0].size() => number of pairs -> operators, each one of them needs (4 * 2) by const + 1 because its the size of char, +2 for | begin, | end
    for (int i = 0; i <= (operators[0].size() * ((4 * 2) + 1)) + (1 + (2 * originalExpression.size())) + 3; i++)
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
    std::cout << "|";
    for (int i = 0; i < operators[0].size(); i++) {
        // why is it 9? because it's 4 * 2 + size of operator (4 is constant for spaces)
        for (int j = 0; j < 4 * 2 + 1; j++)
            std::cout << '-';
        std::cout << '|';
    }
    for (int j = 0; j < originalExpression.size() * 2 + 1; j++)
        std::cout << '-';
    std::cout << '|';
    std::cout << std::endl;
    std::cout << "|    ";

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
    return getPermutation(getAllOperands());
}

std::vector<std::vector<std::pair<char, bool>>> ExpressionTree::getPermutation(std::vector<char> operators) {
    std::vector<std::vector<std::pair<char, bool>>> allOperandsPemutate;
    if (operators.size() == 2) {
        const char x = operators.at(0);
        const char y = operators.at(1);
        // in case we have 2 operators, we have 4 lines
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
        for (auto &per : getPermutation({operators.begin() + 1, operators.end()})) {
            per.insert(per.begin(), std::make_pair(operators[0], true));
            allOperandsPemutate.push_back(per);
        }
        for (auto &per : getPermutation({operators.begin() + 1, operators.end()})) {
            per.insert(per.begin(), std::make_pair(operators[0], false));
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

std::vector<char> ExpressionTree::getAllOperands(ExpressionTree *root) {
    std::vector<char> operands;
    if (root != nullptr) {
        if (root->left == nullptr && root->right == nullptr)
            operands.push_back(root->val);
        else {
            const auto lef = getAllOperands(root->left);
            const auto right = getAllOperands(root->right);
            for (const auto o : lef)
                operands.push_back(o);
            for (const auto o : right)
                operands.push_back(o);
        }
    }
    return operands;
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
    while (rawSubTree.at(end) != ' ')
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
            while (initializationExpression.at(tempIndex) != ' ' && tempIndex < initializationExpression.size())
                ++tempIndex;
            rootEndIndex = tempIndex + 1;
        }
        return std::make_pair(rootStartIndex, rootEndIndex);
    } else {
        // Dealing with simple expression
        int firstSpace = initializationExpression.find_first_of(' ');
        int lastSpace = initializationExpression.find_last_of(' ');
        return std::make_pair(firstSpace, lastSpace);
    }
}