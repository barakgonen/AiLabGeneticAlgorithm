#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "ExpressionTreeFunctions.h"
#include "consts.h"

class ExpressionTree{
public:
    ExpressionTree(std::string initializationExpression, const int maxHeight = MAX_PARSE_TREE_DEPTH);
    virtual ~ExpressionTree() = default;
    int getTreeHeight();

    std::vector<char> getAllOperands();
    std::vector<ExpressionTreeFunctions> getAllFunctions();

    void print();
    void printTruthTable();

protected:
    ExpressionTree(char v);

    int getHeight(ExpressionTree* root);

    void printExpression(const char expr);
    void printExpression(const std::string expr);

    bool isComplexTree(const std::string& initializationExpression);
    bool evaluateExpression(const std::unordered_map<char, bool>& operands);
    void printTableBorder(const std::vector<std::unordered_map<char, bool>>& operators);

    void printTruthTableHeaderLine(const std::vector<std::unordered_map<char, bool>>& operators);

    std::vector<char> getAllOperands(ExpressionTree* root);
    std::vector<ExpressionTreeFunctions> getAllFunctions(ExpressionTree* root);
    std::vector<std::unordered_map<char, bool>> getAllPermutationsForOperands();
    std::vector<std::unordered_map<char, bool>> getPermutation(std::vector<char> operators);

    std::unique_ptr<bool> evaluateExpression(const std::unordered_map<char, bool>& operands, const ExpressionTree* root);

    ExpressionTreeFunctions parseExpressionTreeFunc(const std::string& rawSubTree, const int rootStartIndex);

    std::string extractSubTree(std::string rawSubTree);
    std::string getSubTreeAsString(int startIndex, int endIndex);

    std::pair<int, int> getRootIndexes(const std::string& initializationExpression);

    const int numberOfSpaces;
    ExpressionTree* left;
    ExpressionTree* right;
    int currentHeight;
    ExpressionTreeFunctions func;
    char val;
    std::string originalExpression;
};