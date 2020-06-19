//
// Created by barak on 30/04/2020.
//

#include <iostream>
#include <functional>
#include <set>
#include "../string_matching/include/consts.h"
#include "../string_matching/include/StringMatchingGeneticSolver.h"
#include <optional>
#include "../nQueens/include/nQueensGeneticSolver.h"
#include "../string_matching/include/StringMatchingOutputFileWriter.h"
#include "../nQueens/include/consts.h"
#include "../nQueens/include/nQueensMinimalConflictsSolver.h"
#include "../general_utilities/include/random_collection_generator.h"
#include "../nQueens/include/nQueensMinimalConflictsSolver.h"
#include "../knap_sack/include/KnapSackGeneticSolver.h"
#include "../knap_sack/include/KnapSackStaticDataSetInitializer.h"
#include "../nQueens/include/nQueensOutputFileWriter.h"
#include "../bin_packing/include/BinPackingGeneticSolver.h"
#include "../bin_packing/include/BinPackingInputReader.h"
#include "../baldwin_effect/include/baldwin_solver.h"
#include "../baldwin_effect/include/BaldwinIterationStruct.h"
#include "../baldwin_effect/include/BaldwinEffectOutputFileWriter.h"
#include "../nsga2/include/NsgaSolver.h"
#include "../optimal_xor/include/ExpressionTree.h"
#include "../optimal_xor/include/ExpressionTreeNode.h"

#include <chrono>
#include <ratio>

using namespace std;

// .exe path always is the fist program argument
std::string getRunningPath(char **argv) {
    std::string basePath = argv[0];
    int index = basePath.find_last_of("\\");
    basePath = basePath.substr(0, index);
    index = basePath.find_last_of("\\");
    basePath = basePath.substr(0, index);
    return basePath;
}

// Command to execute always is the second parameter
std::string getMethodToRun(int argc, char **argv) {
    std::string method_to_run;
    if (argc >= 2) {
        method_to_run = argv[1];
    } else {
        cout << "Choose lab to run: string_matching / nQueens / KnapSack" << endl;
        getline(cin, method_to_run);
    }
    return method_to_run;
}

// Selection method always is the 3rd argument, index = 2
SelectionMethod getSelectionMethod(int argc, char **argv) {
    SelectionMethod selectionMethod;
    std::string selectionMethodStr = "";
    if (argc >= 3)
        selectionMethodStr = argv[2];
    else {
        cout << "Choose selection method: Random / Tournament / Rws / Aging " << endl;
        getline(cin, selectionMethodStr);
    }
    if (selectionMethodStr == "Random")
        selectionMethod = SelectionMethod::Random;
    else if (selectionMethodStr == "Tournament")
        selectionMethod = SelectionMethod::Tournament;
    else if (selectionMethodStr == "Rws")
        selectionMethod = SelectionMethod::Rws;
    else if (selectionMethodStr == "Aging")
        selectionMethod = SelectionMethod::Aging;
    else {
        cout << "Unrecognized selectionMethod, setting by to default selection method" << endl;
        selectionMethod = SelectionMethod::Random;
    }
    return selectionMethod;
}

// Crossover method always the 4th argument, index = 3
CrossoverMethod getCrossoverMethod(int argc, char **argv) {
    CrossoverMethod crossoverMethod;
    std::string crossoverMethodStr = "";
    if (argc >= 4)
        crossoverMethodStr = argv[3];
    else {
        cout << "Choose crossover method: SinglePoint / TwoPoints / UniformCrossover / Ox / Pmx / None " << endl;
        getline(cin, crossoverMethodStr);
    }
    if (crossoverMethodStr == "SinglePoint")
        crossoverMethod = CrossoverMethod::SinglePoint;
    else if (crossoverMethodStr == "TwoPoints")
        crossoverMethod = CrossoverMethod::TwoPoints;
    else if (crossoverMethodStr == "UniformCrossover")
        crossoverMethod = CrossoverMethod::UniformCrossover;
    else if (crossoverMethodStr == "Ox")
        crossoverMethod = CrossoverMethod::Ox;
    else if (crossoverMethodStr == "Pmx")
        crossoverMethod = CrossoverMethod::Pmx;
    else if (crossoverMethodStr == "Empty")
        crossoverMethod = CrossoverMethod::Empty;
    else {
        cout << "Unrecognized crossover method, setting to SinglePoint" << endl;
        crossoverMethod = CrossoverMethod::SinglePoint;
    }
    return crossoverMethod;
}

// nQueens specific!
MutationOperator getMutationOperator(int argc, char **argv) {
    MutationOperator mutationOperator;
    std::string mutationOperatorStr = "";
    if (argc >= 5) {
        mutationOperatorStr = argv[4];
        if (mutationOperatorStr == "Inversion")
            mutationOperator = MutationOperator::Inversion;
        else if (mutationOperatorStr == "Exchange")
            mutationOperator = MutationOperator::Exchange;
        else {
            cout << "Unrecognized mutation operator, setting to Inversion" << endl;
            mutationOperator = MutationOperator::Inversion;
        }
    } else {
        cout << "Choose mutation operator Inversion / Exchange " << endl;
        getline(cin, mutationOperatorStr);
        if (mutationOperatorStr == "Inversion")
            mutationOperator = MutationOperator::Inversion;
        else if (mutationOperatorStr == "Exchange")
            mutationOperator = MutationOperator::Exchange;
        else {
            cout << "Unrecognized crossover method, setting to Inversion" << endl;
            mutationOperator = MutationOperator::Inversion;
        }
    }
    return mutationOperator;
}

// Relevant for nQueens & String matching
HeuristicsEnum getHeuristicToWorkWith(int argc, char **argv) {
    string heuristicType;
    HeuristicsEnum hType;
    if (argc >= 5) {
        heuristicType = argv[4];
        if (heuristicType == defaultHeuristic)
            hType = HeuristicsEnum::DefaultHeuristic;
        else if (heuristicType == bullsAndCows)
            hType = HeuristicsEnum::BullsAndCows;
        else {
            cout << "Unrecognized heuristic method, setting by default to random heuristic" << endl;
            hType = HeuristicsEnum::DefaultHeuristic;
        }
    } else {
        cout << "Choose heuristic method: " << defaultHeuristic << " / " << bullsAndCows << endl;
        getline(cin, heuristicType);
        if (heuristicType == defaultHeuristic)
            hType = HeuristicsEnum::DefaultHeuristic;
        else if (heuristicType == bullsAndCows)
            hType = HeuristicsEnum::BullsAndCows;
        else {
            cout << "Unrecognized heuristic method, setting by default to default heuristic" << endl;
            hType = HeuristicsEnum::DefaultHeuristic;
        }
    }
    return hType;
}

// Baldwin effect specific
int getNumberOfIterations(int argc, char **argv) {
    std::string numberOfIterationsAsString = "";
    if (argc >= 3)
        numberOfIterationsAsString = argv[2];
    else {
        cout << "Insert number of Iterations to run " << endl;
        getline(cin, numberOfIterationsAsString);
    }
    return std::stoi(numberOfIterationsAsString);
}

// Baldwin effect specific
int getNumberOfTests(int argc, char **argv) {
    std::string numberOfIterationsAsString = "";
    if (argc >= 4)
        numberOfIterationsAsString = argv[3];
    else {
        cout << "Insert number of tests to preform " << endl;
        getline(cin, numberOfIterationsAsString);
    }
    return std::stoi(numberOfIterationsAsString);
}

// String matching specifics!
std::string getStringToWorkWith(int argc, char **argv) {
    std::string stringToWorkWith = GA_TARGET;
    if (argc >= 6)
        stringToWorkWith = argv[5];
    return stringToWorkWith;
}

// Nqueens specific, it's the same function as the one above, they will share the same index
int getBoardSizeAndNumberOfQueens(int argc, char **argv) {
    int boardSizeAndNumberOfQueens = DEFAULT_NUMBER_OF_QUEENS_AND_BOARD_SIZE;
    if (argc >= 6)
        boardSizeAndNumberOfQueens = atoi(argv[5]);
    return boardSizeAndNumberOfQueens;
}

// Assuming output path always is the last argument given
std::string getOutputPath(int argc, char **argv) {
    std::string outputPath = "output/";
    std::string basePath = argv[0];
    int index = basePath.find_last_of("\\");
    basePath = basePath.substr(0, index);
    index = basePath.find_last_of("\\");
    basePath = basePath.substr(0, index);
    outputPath = argv[argc - 1];
    basePath += "\\" + outputPath;
    return basePath;
}

std::pair<int, int> firstFit(int weight[], int n, int c)
{
    auto startTimeStamp = std::chrono::high_resolution_clock::now();

    // Initialize result (Count of bins)
    int res = 0;

    // Create an array to store remaining space in bins
    // there can be at most n bins
    int bin_rem[n];

    // Place items one by one
    for (int i = 0; i < n; i++) {
        // Find the first bin that can accommodate
        // weight[i]
        int j;
        for (j = 0; j < res; j++) {
            if (bin_rem[j] >= weight[i]) {
                bin_rem[j] = bin_rem[j] - weight[i];
                break;
            }
        }

        // If no bin could accommodate weight[i]
        if (j == res) {
            bin_rem[res] = c - weight[i];
            res++;
        }
    }
    auto endTimeStemp = std::chrono::high_resolution_clock::now();
    auto total = std::chrono::duration_cast<std::chrono::microseconds>(endTimeStemp - startTimeStamp);

    return std::make_pair(res, total.count());
}

void runScenario(std::vector<int> weight, int binCapacity, int expectedNumberOfNodes) {
    std::pair<int, long> nSquareRes = firstFit(weight.data(), weight.size(), binCapacity);
//    cout << "Number of bins required in First Fit : " << nSquareRes.first << ", Runtime: "
//                                                << nSquareRes.second << " microSec" << std::endl;
    if (nSquareRes.first != expectedNumberOfNodes){
        std::cout << "=============================================================================" << std::endl;
        std::cout << "ERROR, expected: " << expectedNumberOfNodes << ", actual: " << nSquareRes.first << std::endl;
        std::cout << "=============================================================================" << std::endl;
    }
//    std::cout << "=============================================================================" << std::endl;
}

void testBinPackingFitness(const string &basePath, int numOfIterations) {
    int errorCounter = 0;
    for (int i = 0; i < numOfIterations; i++) {
        runScenario({1, 2, 3, 1, 2, 3}, 4, 4);
        runScenario({1, 4, 2, 3, 3, 4, 4, 5}, 5, 6);
        runScenario({2, 5, 4, 7, 1, 3, 8}, 10, 4);
        runScenario({2, 5, 4, 7, 1, 3, 8}, 11, 3);
        runScenario({2, 5, 4, 7, 1, 3, 8}, 12, 3);
        runScenario({2, 5, 4, 7, 1, 3, 8}, 18, 2);
        runScenario({2, 5, 4, 7, 1, 3, 8}, 29, 2);
        runScenario({2, 5, 4, 7, 1, 3, 8}, 30, 1);
        runScenario({98, 98, 96, 2, 1, 4, 12, 7, 96}, 150, 4);
        BinPackingInputReader inputReader20{basePath, 20};
        runScenario(inputReader20.getItemsWeight(), inputReader20.getBinsCapacity(), 20);
        BinPackingInputReader inputReader21{basePath, 21};
        runScenario(inputReader21.getItemsWeight(), inputReader21.getBinsCapacity(), 21);
        BinPackingInputReader inputReader22{basePath, 22};
        runScenario(inputReader22.getItemsWeight(), inputReader22.getBinsCapacity(), 21);
        BinPackingInputReader inputReader23{basePath, 23};
        runScenario(inputReader23.getItemsWeight(), inputReader23.getBinsCapacity(), 22);
        BinPackingInputReader inputReader25{basePath, 25};
        runScenario(inputReader25.getItemsWeight(), inputReader25.getBinsCapacity(), 23);
        BinPackingInputReader inputReader30{basePath, 30};
        runScenario(inputReader30.getItemsWeight(), inputReader30.getBinsCapacity(), 25);
        BinPackingInputReader inputReader31{basePath, 31};
        runScenario(inputReader31.getItemsWeight(), inputReader31.getBinsCapacity(), 26);
        BinPackingInputReader inputReader32{basePath, 32};
        runScenario(inputReader32.getItemsWeight(), inputReader32.getBinsCapacity(), 26);
        BinPackingInputReader inputReader33{basePath, 33};
        runScenario(inputReader33.getItemsWeight(), inputReader33.getBinsCapacity(), 26);
        BinPackingInputReader inputReader34{basePath, 34};
        runScenario(inputReader34.getItemsWeight(), inputReader34.getBinsCapacity(), 26);
        BinPackingInputReader inputReader35{basePath, 35};
        runScenario(inputReader35.getItemsWeight(), inputReader35.getBinsCapacity(), 26);
        BinPackingInputReader inputReader37{basePath, 37};
        runScenario(inputReader37.getItemsWeight(), inputReader37.getBinsCapacity(), 27);
        BinPackingInputReader inputReader40{basePath, 40};
        runScenario(inputReader40.getItemsWeight(), inputReader40.getBinsCapacity(), 38);
        BinPackingInputReader inputReader120{basePath, 120};
        runScenario(inputReader120.getItemsWeight(), inputReader120.getBinsCapacity(), 49);
        BinPackingInputReader inputReader250{basePath, 250};
        runScenario(inputReader250.getItemsWeight(), inputReader250.getBinsCapacity(), 100);
        BinPackingInputReader inputReader500{basePath, 500};
        runScenario(inputReader500.getItemsWeight(), inputReader500.getBinsCapacity(), 201);
        BinPackingInputReader inputReader1000{basePath, 1000};
        runScenario(inputReader1000.getItemsWeight(), inputReader1000.getBinsCapacity(), 403);
    }
}
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <random>

using std::vector;
using std::string;
using std::cout;

template <typename T>
class BinTree {
    struct Node {
        T value;
        Node *left,*right;
        Node() : left(nullptr),right(nullptr) {}
        Node(const T& value) :value(value),left(nullptr),right(nullptr) {}
        // stack-abusing recursion everywhere, for small code
        ~Node() { delete left; delete right; }
        int max_depth() const {
            const int left_depth = left ? left->max_depth() : 0;
            const int right_depth = right ? right->max_depth() : 0;
            return (left_depth > right_depth ? left_depth : right_depth) + 1;
        }
    };

    Node *root;

public:
    BinTree() : root(nullptr) {}
    ~BinTree() { delete root; }

    int get_max_depth() const { return root ? root->max_depth() : 0; }
    void clear() { delete root; root = nullptr; }
    void insert() {}
    template <typename ...Args>
    void insert(const T& value, Args...more) {
        if(!root) {
            root = new Node(value);
        } else {
            Node* p = root;
            for(;;) {
                if(value == p->value) return;
                Node* &pchild = value < p->value ? p->left : p->right;
                if(!pchild) {
                    pchild = new Node(value);
                    break;
                }
                p = pchild;
            }
        }
        insert(more...);
    }

    struct cell_display {
        string   valstr;
        bool     present;
        cell_display() : present(false) {}
        cell_display(std::string valstr) : valstr(valstr), present(true) {}
    };

    using display_rows = vector< vector< cell_display > >;

    // The text tree generation code below is all iterative, to avoid stack faults.

    // get_row_display builds a vector of vectors of cell_display structs
    // each vector of cell_display structs represents one row, starting at the root
    display_rows get_row_display() const {
        // start off by traversing the tree to
        // build a vector of vectors of Node pointers
        vector<Node*> traversal_stack;
        vector< std::vector<Node*> > rows;
        if(!root) return display_rows();

        Node *p = root;
        const int max_depth = root->max_depth();
        rows.resize(max_depth);
        int depth = 0;
        for(;;) {
            // Max-depth Nodes are always a leaf or null
            // This special case blocks deeper traversal
            if(depth == max_depth-1) {
                rows[depth].push_back(p);
                if(depth == 0) break;
                --depth;
                continue;
            }

            // First visit to node?  Go to left child.
            if(traversal_stack.size() == depth) {
                rows[depth].push_back(p);
                traversal_stack.push_back(p);
                if(p) p = p->left;
                ++depth;
                continue;
            }

            // Odd child count? Go to right child.
            if(rows[depth+1].size() % 2) {
                p = traversal_stack.back();
                if(p) p = p->right;
                ++depth;
                continue;
            }

            // Time to leave if we get here

            // Exit loop if this is the root
            if(depth == 0) break;

            traversal_stack.pop_back();
            p = traversal_stack.back();
            --depth;
        }

        // Use rows of Node pointers to populate rows of cell_display structs.
        // All possible slots in the tree get a cell_display struct,
        // so if there is no actual Node at a struct's location,
        // its boolean "present" field is set to false.
        // The struct also contains a string representation of
        // its Node's value, created using a std::stringstream object.
        display_rows rows_disp;
        std::stringstream ss;
        for(const auto& row : rows) {
            rows_disp.emplace_back();
            for(Node* pn : row) {
                if(pn) {
                    ss << pn->value;
                    rows_disp.back().push_back(cell_display(ss.str()));
                    ss = std::stringstream();
                } else {
                    rows_disp.back().push_back(cell_display());
                }   }   }
        return rows_disp;
    }

    // row_formatter takes the vector of rows of cell_display structs
    // generated by get_row_display and formats it into a test representation
    // as a vector of strings
    vector<string> row_formatter(const display_rows& rows_disp) const {
        using s_t = string::size_type;

        // First find the maximum value string length and put it in cell_width
        s_t cell_width = 0;
        for(const auto& row_disp : rows_disp) {
            for(const auto& cd : row_disp) {
                if(cd.present && cd.valstr.length() > cell_width) {
                    cell_width = cd.valstr.length();
                }   }   }

        // make sure the cell_width is an odd number
        if(cell_width % 2 == 0) ++cell_width;

        // formatted_rows will hold the results
        vector<string> formatted_rows;

        // some of these counting variables are related,
        // so its should be possible to eliminate some of them.
        s_t row_count = rows_disp.size();

        // this row's element count, a power of two
        s_t row_elem_count = 1 << (row_count-1);

        // left_pad holds the number of space charactes at the beginning of the bottom row
        s_t left_pad = 0;

        // Work from the level of maximum depth, up to the root
        // ("formatted_rows" will need to be reversed when done)
        for(s_t r=0; r<row_count; ++r) {
            const auto& cd_row = rows_disp[row_count-r-1]; // r reverse-indexes the row
            // "space" will be the number of rows of slashes needed to get
            // from this row to the next.  It is also used to determine other
            // text offsets.
            s_t space = (s_t(1) << r) * (cell_width + 1) / 2 - 1;
            // "row" holds the line of text currently being assembled
            string row;
            // iterate over each element in this row
            for(s_t c=0; c<row_elem_count; ++c) {
                // add padding, more when this is not the leftmost element
                row += string(c ? left_pad*2+1 : left_pad, ' ');
                if(cd_row[c].present) {
                    // This position corresponds to an existing Node
                    const string& valstr = cd_row[c].valstr;
                    // Try to pad the left and right sides of the value string
                    // with the same number of spaces.  If padding requires an
                    // odd number of spaces, right-sided children get the longer
                    // padding on the right side, while left-sided children
                    // get it on the left side.
                    s_t long_padding = cell_width - valstr.length();
                    s_t short_padding = long_padding / 2;
                    long_padding -= short_padding;
                    row += string(c%2 ? short_padding : long_padding, ' ');
                    row += valstr;
                    row += string(c%2 ? long_padding : short_padding, ' ');
                } else {
                    // This position is empty, Nodeless...
                    row += string(cell_width, ' ');
                }
            }
            // A row of spaced-apart value strings is ready, add it to the result vector
            formatted_rows.push_back(row);

            // The root has been added, so this loop is finsished
            if(row_elem_count == 1) break;

            // Add rows of forward- and back- slash characters, spaced apart
            // to "connect" two rows' Node value strings.
            // The "space" variable counts the number of rows needed here.
            s_t left_space  = space + 1;
            s_t right_space = space - 1;
            for(s_t sr=0; sr<space; ++sr) {
                string row;
                for(s_t c=0; c<row_elem_count; ++c) {
                    if(c % 2 == 0) {
                        row += string(c ? left_space*2 + 1 : left_space, ' ');
                        row += cd_row[c].present ? '/' : ' ';
                        row += string(right_space + 1, ' ');
                    } else {
                        row += string(right_space, ' ');
                        row += cd_row[c].present ? '\\' : ' ';
                    }
                }
                formatted_rows.push_back(row);
                ++left_space;
                --right_space;
            }
            left_pad += space + 1;
            row_elem_count /= 2;
        }

        // Reverse the result, placing the root node at the beginning (top)
        std::reverse(formatted_rows.begin(), formatted_rows.end());

        return formatted_rows;
    }

    // Trims an equal number of space characters from
    // the beginning of each string in the vector.
    // At least one string in the vector will end up beginning
    // with no space characters.
    static void trim_rows_left(vector<string>& rows) {
        if(!rows.size()) return;
        auto min_space = rows.front().length();
        for(const auto& row : rows) {
            auto i = row.find_first_not_of(' ');
            if(i==string::npos) i = row.length();
            if(i == 0) return;
            if(i < min_space) min_space = i;
        }
        for(auto& row : rows) {
            row.erase(0, min_space);
        }   }

    // Dumps a representation of the tree to cout
    void Dump() const {
        const int d = get_max_depth();

        // If this tree is empty, tell someone
        if(d == 0) {
            cout << " <empty tree>\n";
            return;
        }

        // This tree is not empty, so get a list of node values...
        const auto rows_disp = get_row_display();
        // then format these into a text representation...
        auto formatted_rows = row_formatter(rows_disp);
        // then trim excess space characters from the left sides of the text...
        trim_rows_left(formatted_rows);
        // then dump the text to cout.
        for(const auto& row : formatted_rows) {
            std::cout << ' ' << row << '\n';
        }
    }
};

void assertHeightCalculationIsCorrect(const int expectedHeight, const int actualHeight) {
    if (expectedHeight != actualHeight)
        std::cout << "ERROR, expected: " << expectedHeight << ", actual:"
                                                << actualHeight << std::endl;
}


class ExpressionTree{
public:
    ExpressionTree(std::string initializationExpression)
    : left{nullptr}
    , right{nullptr}
    , currentHeight{0}
    , originalExpression{initializationExpression}
    {
        auto rootIndexes = getRootIndexes(initializationExpression);
        if (rootIndexes.first == -1 && rootIndexes.second == -1){
            try{
                func = stringToExpressionTreeFunc.at(initializationExpression);
            }
            catch (std::out_of_range& exc) {

            }
        } else{
            // Extracting sub trees - left and right
            std::string leftSide = extractSubTree(initializationExpression.substr(0, rootIndexes.first));
            if (leftSide.size() > 1)
                left = new ExpressionTree{leftSide};
            else
                left = new ExpressionTree{leftSide.at(0)};
            std::string rightSide = extractSubTree(initializationExpression.substr(rootIndexes.second));
            if (rightSide.size() > 1)
                right = new ExpressionTree{rightSide};
            else
                right = new ExpressionTree{rightSide.at(0)};
            func = parseExpressionTreeFunc(initializationExpression, rootIndexes.first + 1);

//        std::cout << "root is: " << expressionTreeFuncToString.at(func) << std::endl;
//        if (left != nullptr)
//            std::cout << "Left side: " << leftSide << std::endl;
//        if (right != nullptr)
//            std::cout << "Right side: " << rightSide << std::endl;

        }
        currentHeight = max(getHeight(left), getHeight(right)) + 1;

    }

    int getTreeHeight(){
        return currentHeight;
    }
    std::vector<char> getAllOperands(){
        std::vector<char> operands;
        auto leftSide = getAllOperands(left);
        auto rightSide = getAllOperands(right);
        for (const auto operand : leftSide)
            operands.push_back(operand);
        for (const auto operand : rightSide)
            operands.push_back(operand);
        return operands;
    }

    std::vector<ExpressionTreeFunctions> getAllFunctions(){
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

    void print(){
        std::cout << "BLA" << std::endl;
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

    void printTruthTable() {
        auto allOperatorsPermutations = getAllPermutationsForOperands();
        printTableBorder(allOperatorsPermutations);
        printTruthTableHeaderLine(allOperatorsPermutations);
        for (int line = 0; line < allOperatorsPermutations.size(); line++){
            for (const auto operand : allOperatorsPermutations.at(line))
                std::cout << operand.second << "    |    ";

            int numberOfSpaces = 1 + (2 * originalExpression.size());
            for (int index = 0; index < numberOfSpaces / 2 - 4; index++)
                std::cout << ' ';
            std::cout << evaluateExpression(allOperatorsPermutations[line]);
            for (int index = 0; index < numberOfSpaces / 2; index++)
                std::cout << ' ';
            std::cout << '|';
            // just for not printing the pattern in the last line, for identation
            if (line <= allOperatorsPermutations.size() - 2){
                std::cout << std::endl;
                std::cout << "|    ";
            }
        }
        std::cout << std::endl;
        printTableBorder(allOperatorsPermutations);
    }

protected:
    bool evaluateExpression(const std::map<char, bool>& operands){
        const auto leftSubtree = evaluateExpression(operands, this->left);
        const auto rightSubtree = evaluateExpression(operands, this->right);
        switch (func) {
            case(AND):
                return *leftSubtree && *rightSubtree;
            case(OR):
                return *leftSubtree || *rightSubtree;
                break;
            case(NOT):
                if (left == nullptr && right != nullptr)
                    return !*rightSubtree;
                else if (left != nullptr && right == nullptr)
                    return !*leftSubtree;
                break;
            case(XOR):
                return *leftSubtree ^ *rightSubtree;
                break;

        }
    }

    std::unique_ptr<bool> evaluateExpression(const std::map<char, bool>& operands, const ExpressionTree* root){
        if (root == nullptr)
            return {};
        else if (root->right == nullptr && root->left == nullptr && root->func == ExpressionTreeFunctions::UKNOWN){
            return std::make_unique<bool>(operands.at(root->val)); // must refactor from string to char
        }
        return {};
    }
    void printTableBorder(const std::vector<std::map<char, bool>>& operators){
        // how many '=' needed? 4 * 2 + 1 -> for each operand + 4 * 2 + sizeOfOriginalExpression
        // operators[0].size() => number of pairs -> operators, each one of them needs (4 * 2) by const + 1 because its the size of char, +2 for | begin, | end
        for (int i = 0; i <= (operators[0].size() * ((4 * 2) + 1)) + (1 + (2 * originalExpression.size())) + 3; i++)
            std::cout << '=';
        std::cout << std::endl;
    }

    void printTruthTableHeaderLine(const std::vector<std::map<char, bool>>& operators) {
        std::cout << "|";
        for (const auto permutation : operators[0]) {
            printExpression(permutation.first);
        }
        printExpression(originalExpression);

        std::cout << std::endl;
        std::cout << "|";
        for (int i = 0; i < operators[0].size(); i++){
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
    void printExpression(const std::string expr){
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

    void printExpression(const char expr){
        printExpression(std::string{expr});
    }

    std::vector<std::map<char, bool>> getAllPermutationsForOperands() {
        // Hard coded example
        std::vector<std::map<char, bool>> allOperandsPemutate;
        // A = true, B = true
        std::map<char, bool> lineOne;
        lineOne.insert(std::make_pair('A', true));
        lineOne.insert(std::make_pair('B', true));
        allOperandsPemutate.push_back(lineOne);
        // A = true B = false
        std::map<char, bool> lineTwo;
        lineTwo.insert(std::make_pair('A', true));
        lineTwo.insert(std::make_pair('B', false));
        allOperandsPemutate.push_back(lineTwo);
        // A = false B = true
        std::map<char, bool> lineThree;
        lineThree.insert(std::make_pair('A', false));
        lineThree.insert(std::make_pair('B', true));
        allOperandsPemutate.push_back(lineThree);
        // A = false B = false
        std::map<char, bool> lineFour;
        lineFour.insert(std::make_pair('A', false));
        lineFour.insert(std::make_pair('B', false));
        allOperandsPemutate.push_back(lineFour);
        return allOperandsPemutate;
    }

    ExpressionTree(char v)
    : left{nullptr}
    , right{nullptr}
    , currentHeight{0}
    , val{v}
    , func{ExpressionTreeFunctions::UKNOWN}
    {
    }

    int getHeight(ExpressionTree* root){
        if (root == nullptr)
            return 0;
        else if (root->right == nullptr && root->left == nullptr)
            return 1;
        return getHeight(root->right) + getHeight(root->left);
    }

    std::vector<char> getAllOperands(ExpressionTree* root){
        std::vector<char> operands;
        if (root != nullptr) {
            if (root->left == nullptr && root->right == nullptr)
                operands.push_back(root->val);
            else{
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

    std::vector<ExpressionTreeFunctions> getAllFunctions(ExpressionTree* root){
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

    ExpressionTreeFunctions parseExpressionTreeFunc(const std::string& rawSubTree, const int rootStartIndex) {
        int end = rootStartIndex + 1;
        while (rawSubTree.at(end) != ' ')
            end++;
        std::string bla = rawSubTree.substr(rootStartIndex, end - rootStartIndex);
        return stringToExpressionTreeFunc.at(bla);
    }
    std::string extractSubTree(std::string rawSubTree){
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
        }
        else
            extractedSubTree = rawSubTree.substr(start, endd - start + 1);
        return extractedSubTree;
    }

    bool isComplexTree(const std::string& initializationExpression){
        // non-complex expression is an expression without '(' / ')'
        int anyBracketsCounter = 0;
        for (const auto c : initializationExpression)
            if (c == ')' || c == '(')
                anyBracketsCounter++;
        return anyBracketsCounter != 0;
    }
    std::pair<int, int> getRootIndexes(const std::string& initializationExpression){
        if (isComplexTree(initializationExpression)){
            int rootStartIndex;
            int rootEndIndex;
            int openedBracketsCounter = 0;
            bool hasRootFound = false;
            std::string initalizationExpressionNonWrapped;
            // remove wrapping brackets
            int endIndex = initializationExpression.size() - 1;
            for (int i = 0; i <= endIndex; i++){
                if (initializationExpression.at(i) == '(' && initializationExpression.at(endIndex) == ')'){
                    endIndex--;
                }
                else
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
            if (rootEndIndex == -1){
                int tempIndex = rootStartIndex + 1;
                while (initializationExpression.at(tempIndex) != ' ' && tempIndex < initializationExpression.size())
                    ++tempIndex;
                rootEndIndex = tempIndex + 1;
            }
            return std::make_pair(rootStartIndex, rootEndIndex);
        } else{
            // Dealing with simple expression
            int firstSpace = initializationExpression.find_first_of(' ');
            int lastSpace = initializationExpression.find_last_of(' ');
            return std::make_pair(firstSpace, lastSpace);
        }
    }
    std::string getSubTreeAsString(int startIndex, int endIndex);
    ExpressionTree* left;
    ExpressionTree* right;
    int currentHeight;
    ExpressionTreeFunctions func;
//    std::string val;
    char val;
    std::string originalExpression;
};

void testTree(const std::string treeAsString, const int expectedHeight){
    ExpressionTree exprTree{treeAsString};
    assertHeightCalculationIsCorrect(expectedHeight, exprTree.getTreeHeight());
    exprTree.print();
    exprTree.printTruthTable();
    std::cout << "==================" << std::endl;
}
int main() {
    testTree("NOT", 1);
//    testTree("!", 1);
//    testTree("OR", 1);
//    testTree("||", 1);
//    testTree("AND", 1);
//    testTree("&&", 1);
//
//    testTree("(a) AND (b)", 2);
//    testTree("a AND (b)", 2);
//    testTree("(a) AND b", 2);
//    testTree("a AND b", 2);
//    testTree("(a) && (b)", 2);
//    testTree("a && (b)", 2);
//    testTree("(a) && b", 2);
//    testTree("a && b", 2);
//
//    testTree("a && (b && c)", 3);
//    testTree("(a) && ((b) && ((c) || (d)))", 4);
////    testTree("(a) && ((b && c) || (((A || B) && (!C))))", 5);
//    testTree("a XOR b", 2);
//    testTree("A XOR B", 2);

//    ExpressionTree s{"A XOR B"};
//    s.printTruthTable();
//    std::cout << "==================" << std::endl;
//    bt.insert("8","5","2","6","10","9","11");
//    cout << "Tree from OP:\n\n";
//    bt.Dump();
//    cout << "\n\n";
//
//    bt.clear();
    // Build a random tree
    // This toy tree can't balance, so random
    // trees often look more like linked lists.
    // Just keep trying until a nice one shows up.
//    std::random_device rd;
//    std::mt19937 rng(rd());
//
//    int MaxCount=20;
//    int MaxDepth=5;
//    const int Min=0, Max=1000;
//
//    std::uniform_int_distribution<int> dist(Min,Max);
//
//    while(MaxCount--) {
//        bt.insert(dist(rng));
//        if(bt.get_max_depth() >= MaxDepth) break;
//    }
//
//    cout << "Randomly generated tree:\n\n";
//    bt.Dump();
}

    // Build a random tree
    // This toy tree can't balance, so random
    // trees often look more like linked lists.
    // Just keep trying until a nice one shows up.
//    std::random_device rd;
//    std::mt19937 rng(rd());

//    int MaxCount=20;
//    int MaxDepth=5;
//    const int Min=0, Max=1000;
//
//    std::uniform_int_distribution<int> dist(Min,Max);
//
//    while(MaxCount--) {
//        bt.insert(dist(rng));
//        if(bt.get_max_depth() >= MaxDepth) break;
//    }
//
//    cout << "Randomly generated tree:\n\n";
//    bt.Dump();

/*
int main(int argc, char *argv[]) {
    string labSelector = getMethodToRun(argc, argv);

    if (labSelector == "string_matching") {
        SelectionMethod selectionMethod = getSelectionMethod(argc, argv);
        CrossoverMethod crossoverMethod = getCrossoverMethod(argc, argv);
        HeuristicsEnum heuristicMethod = getHeuristicToWorkWith(argc, argv);
        string workOnString = getStringToWorkWith(argc, argv);
        std::string outputPath = getOutputPath(argc, argv);
        StringMatchingOutputFileWriter outputWriter{workOnString, heuristicMethod, selectionMethod, crossoverMethod, outputPath};
        StringMatchingGeneticSolver matcher{workOnString, heuristicMethod, selectionMethod, crossoverMethod};
        // Initializing each cell
        int totalRuntime = matcher.start_solve();
        std::cout << "Total runtime is: " << totalRuntime << " miliseconds" << std::endl;

        outputWriter.writeToFile(totalRuntime, matcher.getRawOutput());

        int a = 4;

    }
    else if (labSelector == "nQueens") {
        std::cout << "you would like to run nqueens" << std::endl;
        SelectionMethod selectionMethod = getSelectionMethod(argc, argv);
        CrossoverMethod crossoverMethod = getCrossoverMethod(argc, argv);
        MutationOperator mutationOperator = getMutationOperator(argc, argv);
        int boardSize = getBoardSizeAndNumberOfQueens(argc, argv);
        if (boardSize == 9999)
        {
            std::vector<int> staticBoardSizes = {10, 15, 20, 40, 50, 60, 70, 80, 100, 110, 120, 150};
            std::vector<nQueensSolutionData> pmxInversionresults;
            std::vector<nQueensSolutionData> pmxExchangeresults;
            std::vector<nQueensSolutionData> oxInversionresults;
            std::vector<nQueensSolutionData> oxExchangeresults;
            std::vector<nQueensSolutionData> minimalConflictsResults;
            std::cout << "This is performance mode, generating different board maxDepth each time and collecting data" << std::endl;
            int repets = 500;
            for (int i = 0; i < repets; i++)
            {
                for (const int boardSize : staticBoardSizes){
                    NqBoard board{boardSize};
                    nQueensGeneticSolver oxInversionSolver{board, SelectionMethod::None, CrossoverMethod::Ox, MutationOperator::Inversion, true};
                    oxInversionresults.push_back(oxInversionSolver.solvePuzzle());
                    nQueensGeneticSolver oxExchangeSolver{board, SelectionMethod::Rws, CrossoverMethod::Ox, MutationOperator::Exchange, true};
                    oxExchangeresults.push_back(oxExchangeSolver.solvePuzzle());
                    nQueensGeneticSolver pmxInversionSolver{board, SelectionMethod::None, CrossoverMethod::Pmx, MutationOperator::Inversion, true};
                    pmxInversionresults.push_back(pmxInversionSolver.solvePuzzle());
                    nQueensGeneticSolver pmxExchangeSolver{board, SelectionMethod::None, CrossoverMethod::Pmx, MutationOperator::Exchange, true};
                    pmxExchangeresults.push_back(pmxExchangeSolver.solvePuzzle());
                    nQueensMinimalConflictsSolver minimalConflictsSolver{board, true};
                    minimalConflictsResults.push_back(minimalConflictsSolver.solvePuzzle());
                }
                std::cout << "============== " <<  i << "/" << repets << " ===========================================" << std::endl;
            }
            nQueensOutputFileWriter oxExchangeWriter{getOutputPath(argc, argv), "OX_Exchange", MutationOperator::Exchange, CrossoverMethod::Ox};
            oxExchangeWriter.writeToFile(oxExchangeresults);
            nQueensOutputFileWriter oxInversionWriter{getOutputPath(argc, argv), "nQueens", MutationOperator::Inversion, CrossoverMethod::Ox};
            oxExchangeWriter.writeToFile(oxInversionresults);
            nQueensOutputFileWriter pmxExchangeWriter{getOutputPath(argc, argv), "Pmx_Exchange", MutationOperator::Exchange, CrossoverMethod::Pmx};
            pmxExchangeWriter.writeToFile(pmxExchangeresults);
            nQueensOutputFileWriter pmxInversionWriter{getOutputPath(argc, argv), "Pmx_Inversion", MutationOperator::Inversion, CrossoverMethod::Pmx};
            pmxInversionWriter.writeToFile(pmxInversionresults);
            nQueensOutputFileWriter minimalConflictsWriter{getOutputPath(argc, argv), "MinimalConflicts", MutationOperator::Inversion, CrossoverMethod::Empty};
            minimalConflictsWriter.writeToFile(minimalConflictsResults);
        } else{
            NqBoard board{getBoardSizeAndNumberOfQueens(argc, argv)};
            nQueensGeneticSolver geneticSolver{board, selectionMethod, crossoverMethod, mutationOperator, false};
            geneticSolver.solvePuzzle();
            nQueensMinimalConflictsSolver minimalConflictsSolver{board};
            minimalConflictsSolver.solvePuzzle();
        }

    }
    else if (labSelector == "KnapSack") {
        std::cout << "You have chosen KnapSack" << std::endl;
        string basePath = getRunningPath(argv);
        SelectionMethod selectionMethod = getSelectionMethod(argc, argv);
        CrossoverMethod crossoverMethod = getCrossoverMethod(argc, argv);
        KnapSackStaticDataSetInitializer initializer{basePath};
        int i;
        int failures = 0;
        int passedCounter = 0;
        int c = 1;

        for (i = 0; i < c; i++){
            for (const auto key : initializer.getPuzzlesIDs()) {
                KnapSackGeneticSolver solver{key, initializer, selectionMethod, crossoverMethod};
                const auto result = solver.solve();
                if (initializer.isOptimalSelectionReached(key, result)) {
                    std::cout << "Puzzle " << key << " solved in optiomal solution!" << std::endl;
                    passedCounter++;
                } else {
                    failures++;
                }
            }
        }
        std::cout << "Totally solved: " << passedCounter << "/" << initializer.getPuzzlesIDs().size() * c << " puzzles!" << std::endl;
        std::cout << "failures: "<<failures << std::endl;
    }
    else if (labSelector == "BinPacking") {
        std::cout << "You requested for bin packing solver, good luck! ;)" << std::endl;
        string basePath = getRunningPath(argv);
        SelectionMethod selectionMethod = getSelectionMethod(argc, argv);
        CrossoverMethod crossoverMethod = getCrossoverMethod(argc, argv);

        // This map, holds pairs of integers - key is the number of items, value is the optimal number of bins,
        // according to tests we preformed with tree & BinPackingTestFitness mode
        std::map<int, int> expectedResultsKeyVal;
        expectedResultsKeyVal[120] = 49;
        expectedResultsKeyVal[250] = 100;
        expectedResultsKeyVal[500] = 201;
        expectedResultsKeyVal[1000] = 403;
        for (const auto expectedKeyVal : expectedResultsKeyVal){
            int maxAge = 5;
            BinPackingInputReader inputReader{basePath, expectedKeyVal.first};
            BinPackingGeneticSolver binPackingGeneticSolver{inputReader.getNumberOfItems(),
                                                            inputReader.getBinsCapacity(),
                                                            inputReader.getItemsWeight(),
                                                            selectionMethod,
                                                            crossoverMethod,
                                                            maxAge,
                                                            expectedKeyVal.second};
            int optimalNumberOfBins = binPackingGeneticSolver.start_solve();
            if (optimalNumberOfBins != expectedKeyVal.second)
                std::cout << "ERROR, on example number: " << expectedKeyVal.first << std::endl;
            std::cout << "===========================================================" << std::endl;
        }
    }
    else if (labSelector == "BinPackingTestFitness") {
        int numOfIterations=3000;
        std::cout << "You requested for testing bin packing fitness, running " << numOfIterations
        << " times from input files located at bin_packing/static_input_files/Falkernauer*.txt" << std::endl;
        string basePath = getRunningPath(argv);
        std::cout << "Running" << std::endl;
        testBinPackingFitness(basePath, numOfIterations);
        std::cout << "Finished, if the console looks clean, your'e good! XD" << std::endl;
    }
    else if (labSelector == "BaldwinEffect"){
        const int numberOfIterations = getNumberOfIterations(argc, argv);
        Baldwin_Solver solver{numberOfIterations};
        solver.solve();
    }
    else if (labSelector == "BaldwinEffectTester"){
        std::string outputPath = getOutputPath(argc, argv);
        BaldwinEffectOutputFileWriter outputFileWriter{outputPath};
        const int numberOfIterations = getNumberOfIterations(argc, argv);
        const int numberOfTests = getNumberOfTests(argc, argv);
        for (int i = 0; i < numberOfTests; i++) {
            Baldwin_Solver solver{numberOfIterations};
            const auto results = solver.solve();
            outputFileWriter.storeResult(results);
        }
        outputFileWriter.writeCalculatedResults();
    }
    else if (labSelector == "Nsga"){
        SelectionMethod selectionMethod = getSelectionMethod(argc, argv);
        CrossoverMethod crossoverMethod = getCrossoverMethod(argc, argv);
        const int numberOfCuples = 5;
        NsgaSolver solver{selectionMethod, crossoverMethod, numberOfCuples};
        solver.start_solve();
    }
    else if (labSelector == "OptimalXor") {
        std::cout << "Example1: " << std::endl;
        ExpressionTreeNode root{ExpressionTreeFunctions::AND};
        root.printTree();
        std::cout << "Example2: " << std::endl;
        ExpressionTreeNode root2{'B', ExpressionTreeFunctions::AND};
        root2.printTree();
        std::cout << "Example3: " << std::endl; // with A
        ExpressionTreeNode root3{ExpressionTreeFunctions::AND, 'B'};
        root3.printTree();
//        std::cout << "Example4: " << std::endl;
//        ExpressionTreeNode root4{ExpressionTreeFunctions::AND, 'B', ExpressionTreeFunctions::OR};
//        root4.printTree();
//        std::cout << "Example5: " << std::endl; // with A & B
//        ExpressionTreeNode root5{ExpressionTreeFunctions::AND, 'B', ExpressionTreeFunctions::OR};
//        root5.printTree();
    }

    return 0;
}
*/
