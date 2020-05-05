//
// Created by barak on 30/04/2020.
//

#include <iostream>
#include "../string_matching/include/consts.h"
#include "../string_matching/include/StringMatchingGeneticSolver.h"

#include "../nQueens/include/nQueensGeneticSolver.h"
#include "../string_matching/include/StringMatchingOutputFileWriter.h"
#include "../nQueens/include/consts.h"
#include "../nQueens/include/nQueensMinimalConflictsSolver.h"

using namespace std;

std::string getMethodToRun(int argc, char **argv) {
    std::string method_to_run;
    if (argc >= 2) {
        method_to_run = argv[1];
    } else {
        cout << "Choose lab to run: string_matching / nQueens" << endl;
        getline(cin, method_to_run);
    }
    return method_to_run;
}

std::string getStringToWorkWith(int argc, char **argv) {
    std::string stringToWorkWith = GA_TARGET;
    if (argc >= 2)
        stringToWorkWith = argv[2];
    return stringToWorkWith;
}

HeuristicsEnum getHeuristicToWorkWith(int argc, char **argv) {
    string heuristicType;
    HeuristicsEnum hType;
    if (argc >= 3) {
        heuristicType = argv[3];
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

SelectionMethod getSelectionMethod(int argc, char **argv) {
    SelectionMethod selectionMethod;
    std::string selectionMethodStr = "";
    if (argc >= 4) {
        selectionMethodStr = argv[4];
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

    } else {
        cout << "Choose selection method: DefaultHeuristic / Tournament / Rws" << endl;
        getline(cin, selectionMethodStr);
        if (selectionMethodStr == "Random")
            selectionMethod = SelectionMethod::Random;
        else if (selectionMethodStr == "Tournament")
            selectionMethod = SelectionMethod::Tournament;
        else if (selectionMethodStr == "Rws")
            selectionMethod = SelectionMethod::Rws;
        else if (selectionMethodStr == "Aging")
            selectionMethod = SelectionMethod::Aging;
        else {
            cout << "Unrecognized selectionMethod, setting by default to random selection" << endl;
            selectionMethod = SelectionMethod::Random;
        }
    }
    return selectionMethod;
}

CrossoverMethod getCrossoverMethod(int argc, char **argv) {
    CrossoverMethod crossoverMethod;
    std::string crossoverMethodStr = "";
    if (argc >= 5) {
        crossoverMethodStr = argv[5];
        if (crossoverMethodStr == "SinglePoint")
            crossoverMethod = CrossoverMethod::SinglePoint;
        else if (crossoverMethodStr == "TwoPoints")
            crossoverMethod = CrossoverMethod::TwoPoints;
        else if (crossoverMethodStr == "UniformCrossover")
            crossoverMethod = CrossoverMethod::UniformCrossover;
        else {
            cout << "Unrecognized crossover method, setting to SinglePoint" << endl;
            crossoverMethod = CrossoverMethod::SinglePoint;
        }
    } else {
        cout << "Choose selection method: TwoPoints / Tournament " << endl;
        getline(cin, crossoverMethodStr);
        if (crossoverMethodStr == "SinglePoint")
            crossoverMethod = CrossoverMethod::SinglePoint;
        else if (crossoverMethodStr == "TwoPoints")
            crossoverMethod = CrossoverMethod::TwoPoints;
        else if (crossoverMethodStr == "UniformCrossover")
            crossoverMethod = CrossoverMethod::UniformCrossover;
        else {
            cout << "Unrecognized crossover method, setting to SinglePoint" << endl;
            crossoverMethod = CrossoverMethod::SinglePoint;
        }
    }
    return crossoverMethod;
}

std::string getOutputPath(int argc, char **argv) {
    std::string outputPath = "output/";
    std::string basePath = argv[0];
    int index = basePath.find_last_of("\\");
    basePath = basePath.substr(0, index);
    index = basePath.find_last_of("\\");
    basePath = basePath.substr(0, index);
    if (argc >= 7)
        outputPath = argv[6];
    basePath += "\\" + outputPath;
    return basePath;
}

int getBoardSizeAndNumberOfQueens(int argc, char **argv) {
    int boardSizeAndNumberOfQueens = DEFAULT_NUMBER_OF_QUEENS_AND_BOARD_SIZE;
    if (argc > 2)
        boardSizeAndNumberOfQueens = atoi(argv[2]);
    return boardSizeAndNumberOfQueens;
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
    } else if (labSelector == "nQueens") {
        std::cout << "you would like to run nqueens" << std::endl;
        NqBoard board{getBoardSizeAndNumberOfQueens(argc, argv)};
        std::cout << "~~~~~~~~~~~~~~~~~~~~MIINIMAL CONFLICTS BEFORE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
        nQueensMinimalConflictsSolver minimalConflictsSolver{board};
        std::cout << "~~~~~~~~~~~~~~~~~~~~GENETICS BEFORE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
        nQueensGeneticSolver geneticSolver{board};
        minimalConflictsSolver.solvePuzzle();
        std::cout << "~~~~~~~~~~~~~~~~~~~~MIINIMAL CONFLICTS AFTER~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
        minimalConflictsSolver.printPuzzle();
        std::cout << "~~~~~~~~~~~~~~~~~~~~GENETICS AFTER~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
        geneticSolver.printPuzzle();
    }
    return 0;
}