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
#include "../nQueens/include/nQueensOutputFileWriter.h"
#include "../bin_packing/include/BinPackingGeneticSolver.h"
#include "../bin_packing/include/BinPackingInputReader.h"
#include "../baldwin_effect/include/baldwin_solver.h"
#include "../baldwin_effect/include/BaldwinIterationStruct.h"
#include "../baldwin_effect/include/BaldwinEffectOutputFileWriter.h"
#include "../nsga2/include/NsgaSolver.h"

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
            std::cout << "This is performance mode, generating different board size each time and collecting data" << std::endl;
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

    return 0;
}

