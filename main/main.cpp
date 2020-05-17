//
// Created by barak on 30/04/2020.
//

#include <iostream>
#include <functional>
#include <set>
#include "../string_matching/include/consts.h"
#include "../string_matching/include/StringMatchingGeneticSolver.h"

#include "../nQueens/include/nQueensGeneticSolver.h"
#include "../string_matching/include/StringMatchingOutputFileWriter.h"
#include "../nQueens/include/consts.h"
#include "../nQueens/include/nQueensMinimalConflictsSolver.h"
#include "../general_utilities/include/random_collection_generator.h"
#include "../nQueens/include/nQueensMinimalConflictsSolver.h"
#include "../knap_sack/include/KnapSackGeneticSolver.h"
#include "../knap_sack/include/KnapSackStaticDataSetInitializer.h"

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
        cout << "Choose crossover method: SinglePoint / TwoPoints / UniformCrossover / Ox / Pmx " << endl;
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
    if (argc >= 6) {
        heuristicType = argv[5];
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

// String matching specifics!
std::string getStringToWorkWith(int argc, char **argv) {
    std::string stringToWorkWith = GA_TARGET;
    if (argc >= 7)
        stringToWorkWith = argv[6];
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
    outputPath = argv[argc];
    basePath += "\\" + outputPath;
    return basePath;
}

int main(int argc, char *argv[]) {
    string labSelector = getMethodToRun(argc, argv);

    if (labSelector == "string_matching") {
        string workOnString = getStringToWorkWith(argc, argv);
        HeuristicsEnum heuristicMethod = getHeuristicToWorkWith(argc, argv);
        SelectionMethod selectionMethod = getSelectionMethod(argc, argv);
        CrossoverMethod crossoverMethod = getCrossoverMethod(argc, argv);
        std::string outputPath = getOutputPath(argc, argv);
        StringMatchingOutputFileWriter outputWriter{workOnString, heuristicMethod, selectionMethod, crossoverMethod, outputPath};
        StringMatchingGeneticSolver matcher{workOnString, heuristicMethod, selectionMethod, crossoverMethod};
        // Initializing each cell
        int totalRuntime = matcher.start_solve();
        std::cout << "Total runtime is: " << totalRuntime << " miliseconds" << std::endl;

        outputWriter.writeToFile(totalRuntime, matcher.getRawOutput());
    }
    else if (labSelector == "nQueens") {
        std::cout << "you would like to run nqueens" << std::endl;
        SelectionMethod selectionMethod = getSelectionMethod(argc, argv);
        CrossoverMethod crossoverMethod = getCrossoverMethod(argc, argv);
        MutationOperator mutationOperator = getMutationOperator(argc, argv);
        NqBoard board{getBoardSizeAndNumberOfQueens(argc, argv)};
        int errorsCounter = 0;
        int passed = 0;
      std::vector<int> ssv{3,0,4,1,4,2}; // value 1 trusted
//      std::vector<int> ssv{0, 1, 1, 6, 1, 2, 5, 4}; // value 9 trusted
//      std::vector<int> ssv{0, 1, 3, 6, 2, 1, 4, 4, 6}; // value 8 trusted
//      std::vector<int> ssv{0, 3, 7, 9, 8, 4, 5, 2, 1, 7}; // value 9 trusted
//      std::vector<int> ssv{1, 9, 2, 11, 4, 1, 13, 6, 0, 4, 2, 1}; // value 11 trusted

//        std::srand(std::time(nullptr)); // use current time as seed for random generator
//        for (int i = 0; i < 100000; i++)
//        {
//            int x =rand() % getBoardSizeAndNumberOfQueens(argc, argv) + 3;
//            NqBoard board{x};
//            if (board.myConflicts() != board.conflicts()){
//                std::cout << "Diff, orig: " << board.conflicts() << ", mine: " << board.myConflicts() << std::endl;
//                errorsCounter++;
//            } else
//                passed++;
//        }
//        std::cout << "Total number of errors: " << errorsCounter << std::endl;
//        std::cout << "Total tests passed: " << passed << std::endl;

//        nQueensMinimalConflictsSolver minimalConflictsSolver{board};
//        minimalConflictsSolver.solvePuzzle();

            // My OX
//            std::vector<int> parent1Vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
//            std::vector<int> parent2Vec = {5, 7, 4, 9, 1, 3, 6, 2, 8};
//            std::vector<int> copyOfParent2Vec;
//            std::copy(parent2Vec.begin(), parent2Vec.end(), back_inserter(copyOfParent2Vec));
//            std::vector<int> indexesFromParent1 = {2,3,4,5};
//            std::generate(indexesFromParent1.begin(), indexesFromParent1.end(), [n = random(0, half-1)] () mutable { return n++; });
//            std::vector<int> oxVec(parent2Vec.size());
//            std::fill(oxVec.begin(), oxVec.end(), -1);
//            // First loop initializing first part
//            for (const auto parentOneIndex : indexesFromParent1){
//                oxVec.at(parentOneIndex) = parent1Vec.at(parentOneIndex);
//                copyOfParent2Vec.erase(std::find(copyOfParent2Vec.begin(), copyOfParent2Vec.end(), parent1Vec.at(parentOneIndex)));
//            }
//
//            for (const auto parent2Val : copyOfParent2Vec){
//                for (int i = 0; i < oxVec.size(); i++) {
//                    if (oxVec.at(i) == -1) {
//                        oxVec.at(i) = parent2Val;
//                        break;
//                    }
//                }
//            }
//
//            std::cout << "BLA" << std::endl;
        nQueensGeneticSolver geneticSolver{board, SelectionMethod::None, crossoverMethod, mutationOperator};
        geneticSolver.solvePuzzle();
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
        int c = 5;

        for (i = 0; i < c; i++){
            for (const auto key : initializer.getPuzzlesIDs()) {
//                int key = 1;
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
        std::cout << "i is: " << i << std::endl;
        std::cout << "Totally solved: " << passedCounter << "/" << initializer.getPuzzlesIDs().size() * c << " puzzles!" << std::endl;
        std::cout << "failures: "<<failures << std::endl;
    }

    return 0;
}
