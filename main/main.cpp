//
// Created by barak on 30/04/2020.
//

#include <iostream>
#include "chrono"
#include <time.h>
#include "../string_matching/include/consts.h"
#include "../string_matching/include/GeneticStringMatcher.h"

#include "../nQueens/include/nQueensGeneticSolver.h"
#include "../string_matching/include/OutputFileWriter.h"
#include "../string_matching/include/HeuristicsEnum.h"
#include "../nQueens/include/nQueensBoard.h"
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
    std::string outputPath = "../output/";
    if (argc >= 7)
        outputPath = argv[6];
    return outputPath;
}

double calculateWeights(vector<GeneticAlgorithmStruct> &population, vector<double> &weights, double avg) {
    double sum = 0;
    for (int j = 0; j < GA_POPSIZE; j++) {
        if (j != 0)
            // we add previous weight for later use in rws function
            weights[j] = population[j].fitnessVal / (avg * GA_POPSIZE) + weights[j - 1];
        else
            weights[j] = population[j].fitnessVal / (avg * GA_POPSIZE);
    }
    return sum;
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
        vector<GeneticAlgorithmStruct> population, buffer;
        IterationRawOutput rawOutputArr[GA_MAXITER];
        // Initializing each cell
        for (auto &res : rawOutputArr)
            res.id = -1;
        string workOnString = getStringToWorkWith(argc, argv);
        HeuristicsEnum heuristicMethod = getHeuristicToWorkWith(argc, argv);
        SelectionMethod selectionMethod = getSelectionMethod(argc, argv);
        CrossoverMethod crossoverMethod = getCrossoverMethod(argc, argv);
        std::string outputPath = getOutputPath(argc, argv);
        clock_t t, totalTicks = 0;

//        std::cout << "Heuristic: " << heuristicMethod << std::endl;
//        std::cout << "selection: " << selectionMethod << std::endl;
//        std::cout << "crossover: " << crossoverMethod << std::endl;
//        std::cout << "input string is: " << workOnString << std::endl;
        OutputFileWriter outputWriter{workOnString, heuristicMethod, selectionMethod, crossoverMethod, outputPath};
        GeneticStringMatcher matcher{workOnString, heuristicMethod, selectionMethod, crossoverMethod};

        matcher.init_population(population, buffer);
        std::vector<double> weights;
        std::fill_n(std::back_inserter(weights), GA_POPSIZE, 0);

        auto startTimeStamp = std::chrono::high_resolution_clock::now();
        t = clock();
        for (int i = 0; i < GA_MAXITER; i++) {
            matcher.calc_fitness(population);        // calculate fitness
            matcher.sort_by_fitness(population);    // sort them
            matcher.print_best(population);        // print the best one

            double averageFitnessValue = matcher.calculateFitnessAvg(population);
            double standardDeviation = matcher.calculateStandardDeviation(population, averageFitnessValue);

            rawOutputArr[i].id = i;
            rawOutputArr[i].standardDeviation = standardDeviation;
            rawOutputArr[i].averageFitnessValue = averageFitnessValue;
            rawOutputArr[i].elapsedTimeSeconds = ((float) (clock() - t)) / CLOCKS_PER_SEC;
            rawOutputArr[i].clockTicks = clock() - t;
            if (population[0].fitnessVal == 0) {
                break;
            }

            calculateWeights(population, weights, averageFitnessValue);
            matcher.mate(population, buffer, weights);        // mate the population together
            swap(population, buffer);        // swap buffers

            t = clock();
        }

        auto endTimeStamp = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTimeStamp - startTimeStamp);

        // Initializing each cell
        int totalIterations = 0;
        for (int i = 0; i < GA_MAXITER && rawOutputArr[i].id != -1; i++) {
            std::cout << "Averaged Fitness Value: " << rawOutputArr[i].averageFitnessValue
                      << ", Standard Deviation val: " << rawOutputArr[i].standardDeviation
                      << ", ticks: " << rawOutputArr[i].clockTicks
                      << ", calculation time: " << rawOutputArr[i].elapsedTimeSeconds << " seconds" << std::endl;
            totalIterations++;
        }
        std::cout << "Total runtime is: " << duration.count() << " miliseconds" << std::endl;
        std::cout << "Total iterations: " << totalIterations << std::endl;

        outputWriter.writeToFile(duration.count(), rawOutputArr);
    } else if (labSelector == "nQueens") {
        std::cout << "you would like to run nqueens" << std::endl;
//        nQueensGeneticSolver solver;
//        nQueensBackTrackingSolver solver{29};
//        solver.printPuzzle();
//        solver.solvePuzzle();
//        solver.printPuzzle();
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