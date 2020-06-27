

#include <iostream>
#include <set>
#include "../include/ExpressionTree.h"

#include "../include/consts.h"
#include <algorithm>
#include "../include/TooLargeExpressionTreeException.h"
#include <experimental/random>


ExpressionTree::ExpressionTree(std::string initializationExpression, const int treeDepth, const int maxDepth)
: numberOfSpaces{static_cast<int>(1 + 2 * initializationExpression.size())}
, left{nullptr}
, right{nullptr}
, height{0}
, func{ExpressionTreeFunctions::UKNOWN}
, originalExpression{initializationExpression}
, maxDepth{maxDepth}
, depth{treeDepth}
{
    auto rootIndexes = getRootIndexes(originalExpression);
    if (rootIndexes.first == -1 && rootIndexes.second == -1) {
        const auto notPos = originalExpression.find_first_of('!');
        if (notPos != std::string::npos && originalExpression.size() > 1) {
            // Found NOT
            func = stringToExpressionTreeFunc.at(std::string{originalExpression[notPos]});
            left = new ExpressionTree{originalExpression.at(1), depth + 1, maxDepth};
            height = 1;
        } else if (initializationExpression.size() == 1 && initializationExpression != "!") {
            height = 1;
            val = initializationExpression.at(0);
        } else {
            try {
                func = stringToExpressionTreeFunc.at(originalExpression);
                val = EMPTY_VALUE;
            }
            catch (std::out_of_range &exc) {

            }
        }
    }
    else if (isSingleOperandExpression(originalExpression)) {
        int spaceIndex = originalExpression.find(' ');
        func = stringToExpressionTreeFunc.at(originalExpression.substr(spaceIndex + 1));
        // if operator is between () need to simplify it
        if (originalExpression.at(0) == '(' && originalExpression.at(2) == ')' && 3 == spaceIndex)
            // almost sure index 1 is the variable
            left = new ExpressionTree{originalExpression.at(1), depth + 1, maxDepth};
        else
            left = new ExpressionTree{originalExpression.at(0), depth + 1, maxDepth};
    } else {
        // Extracting sub trees - left and right
        std::string leftSide = extractSubTree(originalExpression.substr(0, rootIndexes.first));
        if (leftSide.size() > 1)
            left = new ExpressionTree{leftSide, depth + 1, maxDepth};
        else
            left = new ExpressionTree{leftSide.at(0), depth + 1, maxDepth};
        std::string rightSide = extractSubTree(originalExpression.substr(rootIndexes.second));
        if (rightSide.size() > 1)
            right = new ExpressionTree{rightSide, depth + 1, maxDepth};
        else if (0 < rightSide.size())
            right = new ExpressionTree{rightSide.at(0), depth + 1, maxDepth};
        func = parseExpressionTreeFunc(originalExpression, rootIndexes.first + 1);
    }
    // Setting the height manually, because in cases such the root is a function, it's height is still 0
    if (left == nullptr && right == nullptr)
        height = 0;
    else
        height = std::max(getHeight(left), getHeight(right)) + 1;
//    if (height > maxDepth)
//        throw TooLargeExpressionTreeException{height, maxDepth};
    operands = getAllOperands(this);
}

ExpressionTree::ExpressionTree(char v, const int currentDepth, const int maxDepth)
: numberOfSpaces{static_cast<int>(1 + 2 * 1)}
, left{nullptr}
, right{nullptr}
, height{0}
, func{ExpressionTreeFunctions::UKNOWN}
, originalExpression{v}
, maxDepth{maxDepth}
, depth{currentDepth}
{
    val = v;
}

ExpressionTree::ExpressionTree(const std::vector<char>& operands,
                               const InitializationMethod initializationMethod,
                               const int currentDepth,
                               const int maxDepth)
: left{nullptr}
, right{nullptr}
, depth{currentDepth}
, maxDepth{maxDepth}
, operands{operands}
{
    switch (initializationMethod) {
        case Grow:
            growInitMethod(operands, initializationMethod, maxDepth);
            break;
        case Full:
            fullInitMethod(operands, initializationMethod, maxDepth, currentDepth);
            break;

    }
    // Setting the height manually, because in cases such the root is a function, it's height is still 0
    if (left == nullptr && right == nullptr)
        height = 0;
    else
        height = std::max(getHeight(left), getHeight(right)) + 1;
}

void ExpressionTree::growInitMethod(const std::vector<char> &operands, const InitializationMethod &initializationMethod, const int maxDepth) {
    // According to lesson - each branch might have different depth, while it's less that maxDepth
    if (depth < maxDepth){
        int branchDepth = std::experimental::randint(0, maxDepth);
        bool terminalOrFunction = std::experimental::randint(0, 1);
        if (terminalOrFunction) {
            // terminal
            val = operands.at(std::experimental::randint(0, (int)operands.size() - 1));
            func = UKNOWN;
            originalExpression = treeToString(this);
            ExpressionTree::operands.clear();
            ExpressionTree::operands.push_back(val);
            numberOfSpaces = 4 * 2 + 1;
        } else {
            //function
            // this is function generation
            // pick random function of known funcs, and call for ctor for both right and left childs. decreasde max depth by 1 for each recursive call!
            func = keyToExpressionFunc.at(std::experimental::randint(0, (int)keyToExpressionFunc.size()-1));

            val = EMPTY_VALUE;
            left = new ExpressionTree(operands, initializationMethod, depth + 1, maxDepth);
            if (func != NOT)
                right = new ExpressionTree(operands, initializationMethod, depth + 1, maxDepth);
            height = std::max(getHeight(left), getHeight(right)) + 1;
            originalExpression = treeToString(this);
            numberOfSpaces = static_cast<int>(1 + 2 * originalExpression.size());
        }
    } else if (depth == maxDepth){ // need to set terminals}
        val = operands.at(std::experimental::randint(0, (int)operands.size() - 1));
        func = UKNOWN;
        originalExpression = std::string{val};
        ExpressionTree::operands.clear();
        ExpressionTree::operands.push_back(val);
        numberOfSpaces = 4 * 2 + 1;
    }
}

void ExpressionTree::fullInitMethod(const std::vector<char> &operands, const InitializationMethod &initializationMethod, const int maxDepth, const int currentDepth) {
    if (currentDepth == maxDepth){
        // Should set the kids values as leafs TERMINAL
        val = operands.at(std::experimental::randint(0, (int)operands.size() - 1));
        func = ExpressionTreeFunctions::UKNOWN;
        originalExpression = std::string{val};
    } else{
        // Should set as function
        // this is function generation
        // pick random function of known funcs, and call for ctor for both right and left childs. decreasde max depth by 1 for each recursive call!
        func = keyToExpressionFunc.at(std::experimental::randint(0, (int)keyToExpressionFunc.size()-1));
        val = EMPTY_VALUE;
        left = new ExpressionTree(operands, initializationMethod, currentDepth  + 1, maxDepth);
        if (func != ExpressionTreeFunctions::NOT)
            right = new ExpressionTree(operands, initializationMethod, currentDepth  + 1, maxDepth);
        height = std::max(getHeight(left), getHeight(right)) + 1;
        originalExpression = treeToString(this);
        numberOfSpaces = static_cast<int>(1 + 2 * originalExpression.size());
//        if (height > maxDepth)
//            throw TooLargeExpressionTreeException{height, maxDepth};
    }
}

int ExpressionTree::getTreeHeight() const {
    return height;
}

int ExpressionTree::getMaxDepth() const{
    return maxDepth;
}

int ExpressionTree::getNumberOfOperands() const{
    return operands.size();
}

std::vector<char> ExpressionTree::getAllOperands() const {
    return operands;
}

std::vector<char> ExpressionTree::getAllOperands(const ExpressionTree *root) const {
    std::vector<char> oper;
    if (root != nullptr) {
        if (root->left == nullptr && root->right == nullptr && root->val != EMPTY_VALUE)
            oper.push_back(root->val);
        else {
            const auto lef = getAllOperands(root->left);
            const auto rght = getAllOperands(root->right);
            for (const auto o : lef){
                if (std::find(oper.begin(), oper.end(), o) == oper.end())
                    oper.insert(oper.end(), o);
            }
            for (const auto o : rght)
                if (std::find(oper.begin(), oper.end(), o) == oper.end())
                    oper.insert(oper.end(), o);
        }
    }
    return oper;
}

std::vector<ExpressionTreeFunctions> ExpressionTree::getAllFunctions() const {
    std::vector<ExpressionTreeFunctions> funcs;
    auto leftSide = getAllFunctions(left);
    auto rightSide = getAllFunctions(right);
    for (const auto funC : leftSide)
        funcs.push_back(funC);
    if (func != UKNOWN)
        funcs.push_back(func);
    for (const auto funC : rightSide)
        funcs.push_back(funC);
    return funcs;
}

void ExpressionTree::print() const {
    std::cout << "Used Operands are:" << std::endl;
    for (const auto& v : operands)
        std::cout << v << ", ";
    std::cout << std::endl;
    std::cout << "Used funcs are:" << std::endl;
    for (const auto& v : getAllFunctions())
        if (v != ExpressionTreeFunctions::UKNOWN)
            std::cout << expressionTreeFuncToString.at(v) << ", ";
    std::cout << std::endl;
    std::cout << "Height is: " << height << std::endl;
    std::cout << "Tree depth is: " << depth << std::endl;
}

void ExpressionTree::printTruthTable() const {
    auto allOperatorsPermutations = getPermutation(operands);
    printTableBorder();
    printTruthTableHeaderLine();
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
    printTableBorder();
}

bool ExpressionTree::evaluateExpression(const std::vector<std::pair<char, bool>> &operands) const {
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
ExpressionTree::evaluateExpression(const std::vector<std::pair<char, bool>> &operands, const ExpressionTree *root, int startIndex) const {
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

void ExpressionTree::printTableBorder() const {
    // how many '=' needed? 4 * 2 + 1 -> for each operand + 4 * 2 + sizeOfOriginalExpression
    // operands[0].size() => number of pairs -> operands, each one of them needs (4 * 2) by const + 1 because its the size of char, +2 for | begin, | end
//    for (int i = 0; i <= (operators[0].size() * ((4 * 2) + 1)) + (1 + (2 * originalExpression.size())) + 3; i++)
    int numberOfCharactersToPrint = (operands.size() * ((4 * 2) + 1)) + (1 + (2 * originalExpression.size()));
    for (int i = 0; i < numberOfCharactersToPrint; i++)
        std::cout << '=';
    std::cout << std::endl;
}

void ExpressionTree::printTruthTableHeaderLine() const {
    std::cout << "|";
    for (const auto permutation : operands) {
        printExpression(permutation);
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

void ExpressionTree::printExpression(const std::string& expr) const {
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

void ExpressionTree::printExpression(const char expr) const {
    printExpression(std::string{expr});
}

std::vector<std::vector<std::pair<char, bool>>> ExpressionTree::getPermutation(const std::vector<char>& operators) const {
    std::vector<std::vector<std::pair<char, bool>>> allOperandsPemutate;
    if (operators.empty())
        return allOperandsPemutate;
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
        const char x = operators.at(0);
        const char y = operators.at(1);
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
        std::vector<char> tmp;
        std::copy(++operators.begin(), operators.end(), std::inserter(tmp, tmp.end()) );
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

int ExpressionTree::getHeight(ExpressionTree *root) const {
    if (root == nullptr || (root->right == nullptr && root->left == nullptr))
        return 0;
    return std::max(getHeight(root->right), getHeight(root->left)) + 1;
}

std::vector<ExpressionTreeFunctions> ExpressionTree::getAllFunctions(ExpressionTree *root) const {
    std::vector<ExpressionTreeFunctions> funcs;
    if (root != nullptr && !(root->left == nullptr && root->right == nullptr)) {
        const auto lef = getAllFunctions(root->left);
        const auto right = getAllFunctions(root->right);
        funcs.push_back(root->func);
        for (const auto o : lef)
            if (o != UKNOWN)
                funcs.push_back(o);
        for (const auto o : right)
            if (o != UKNOWN)
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

std::string ExpressionTree::extractSubTree(const std::string& rawSubTree) const {
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

bool ExpressionTree::isComplexTree(const std::string &initializationExpression) const {
    // non-complex expression is an expression without '(' / ')'
    int anyBracketsCounter = 0;
    for (const auto c : initializationExpression)
        if (c == ')' || c == '(')
            anyBracketsCounter++;
    return anyBracketsCounter != 0;
}

std::pair<int, int> ExpressionTree::getRootIndexes(const std::string &initializationExpression) const {
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

std::vector<bool> ExpressionTree::getEvaluatedResults() const {
    std::vector<bool> evaluatedResults;
    for (const auto& permutate : getPermutation(operands))
        evaluatedResults.push_back(evaluateExpression(permutate));
    return evaluatedResults;
}

int ExpressionTree::getDepth(ExpressionTree* root) const
{
    if (root == nullptr || root->left == nullptr && root->right == nullptr)
        return 0;
    else
        return std::max(getDepth(root->right), getDepth(root->left)) + 1;
}

bool ExpressionTree::isSingleOperandExpression(const std::string &initializationExpression) const {
    bool spacesValidation = std::count(initializationExpression.begin(), initializationExpression.end(), ' ') == 1;
    // Just not can be relevant
    std::string function = initializationExpression.substr(initializationExpression.find(' ') + 1);
    // Checking like that becase if the function is NOT just space validation is relevant
    if (function == "NOT")
        return spacesValidation;
    return false;
}

std::string ExpressionTree::treeToString(ExpressionTree *root) const {
    std::string expr;
    if (root == nullptr)
        expr = "";
    else if (root->func != ExpressionTreeFunctions::UKNOWN)
        expr = ((root->left != nullptr ? "(" + root->left->originalExpression + ") " : ""))
                    + expressionTreeFuncToString.at(root->func) +
                ((root->right != nullptr ? " (" + root->right->originalExpression + ")" : ""));
    else if (root->val != EMPTY_VALUE)
        expr = root->val;
    return expr;
}

void ExpressionTree::treeCrossover(ExpressionTree &other, int crossoverDepth, bool isTestingMode,
                                   bool movementDirectionWithThisTree, bool movementDirectionWithOtherTree) {
    if (this->depth == crossoverDepth || other.depth == crossoverDepth) {
        // when crossover depth is 0, it means were preforming root substitution
        if (crossoverDepth == 0)
            rootNodeSub(other);
        else
            std::swap(*this, other);
    } else {

        if (!isTestingMode) {
            movementDirectionWithThisTree = std::experimental::randint(0, 1);
            movementDirectionWithOtherTree = std::experimental::randint(0, 1);
        }

        if (movementDirectionWithThisTree && movementDirectionWithOtherTree) {
            if (right != nullptr && other.right != nullptr)
                right->treeCrossover(*other.right, crossoverDepth, isTestingMode, movementDirectionWithThisTree,
                                     movementDirectionWithOtherTree);
            else if (right != nullptr && other.right == nullptr)
                right->treeCrossover(other, crossoverDepth, isTestingMode, movementDirectionWithThisTree,
                                     movementDirectionWithOtherTree);
        } else if (movementDirectionWithThisTree && !movementDirectionWithOtherTree) {
            if (right != nullptr && other.left != nullptr)
                right->treeCrossover(*other.left, crossoverDepth, isTestingMode, movementDirectionWithThisTree,
                                     movementDirectionWithOtherTree);
            else if (right != nullptr && other.left == nullptr)
                right->treeCrossover(other, crossoverDepth, isTestingMode, movementDirectionWithThisTree,
                                     movementDirectionWithOtherTree);
        } else if (!movementDirectionWithThisTree && movementDirectionWithOtherTree) {
            if (left != nullptr && other.right != nullptr)
                left->treeCrossover(*other.right, crossoverDepth, isTestingMode, movementDirectionWithThisTree,
                                    movementDirectionWithOtherTree);
            else if (left != nullptr && other.right == nullptr)
                left->treeCrossover(other, crossoverDepth, isTestingMode, movementDirectionWithThisTree,
                                    movementDirectionWithOtherTree);
        } else if (!movementDirectionWithThisTree && !movementDirectionWithOtherTree) {
            if (left != nullptr && other.left != nullptr)
                left->treeCrossover(*other.left, crossoverDepth, isTestingMode, movementDirectionWithThisTree,
                                    movementDirectionWithOtherTree);
            else if (left != nullptr && other.left == nullptr)
                left->treeCrossover(other, crossoverDepth, isTestingMode, movementDirectionWithThisTree,
                                    movementDirectionWithOtherTree);
        }
    }
    postSubActions(other);
}

bool ExpressionTree::isTreeBuiltSuccessfully() {
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

bool ExpressionTree::operator==(const ExpressionTree &lhs) {
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

void ExpressionTree::postSubActions(ExpressionTree &other) {
    originalExpression = treeToString(this);
    other.originalExpression = treeToString(&other);
    operands = getAllOperands(this);
    other.operands = getAllOperands(&other);
}

void ExpressionTree::rootNodeSub(ExpressionTree &other) {
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
}

bool ExpressionTree::isStructureOK(ExpressionTree *root) {
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
