//
// Created by barak on 30/04/2020.
//

#include <iostream>
#include "chrono"

#include "../string_matching/include/consts.h"
#include "../string_matching/include/GeneticStringMatcher.h"

#include "../nQueens/include/nQueensSolver.h"
#include "../string_matching/include/OutputFileWriter.h"
#include "../string_matching/include/HeuristicsEnum.h"

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
        else if (heuristicType == bullAndCow)
            hType = HeuristicsEnum::BullAndCow;
        else {
            cout << "Unrecognized heuristic method, setting by default to random heuristic" << endl;
            hType = HeuristicsEnum::DefaultHeuristic;
        }
    } else {
        cout << "Choose heuristic method: " << defaultHeuristic << " / " << bullAndCow << endl;
        getline(cin, heuristicType);
        if (heuristicType == defaultHeuristic)
            hType = HeuristicsEnum::DefaultHeuristic;
        else if (heuristicType == bullAndCow)
            hType = HeuristicsEnum::BullAndCow;
        else {
            cout << "Unrecognized heuristic method, setting by default to default heuristic" << endl;
            hType = HeuristicsEnum::DefaultHeuristic;
        }
    }
    return hType;
}

/*
    Aging
 */
SelectionMethod getSelectionMethod(int argc, char **argv) {
    SelectionMethod selectionMethod;
    std::string selectionMethodStr = "";
    if (argc >= 4) {
        selectionMethodStr = argv[4];
        if (selectionMethodStr == "Random")
            selectionMethod = SelectionMethod::Random;
        else if (selectionMethodStr == "Tournament")
            selectionMethod = SelectionMethod::Tournament;
        else if (selectionMethodStr == "Sus")
            selectionMethod = SelectionMethod::Sus;
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
        else if (selectionMethodStr == "Sus")
            selectionMethod = SelectionMethod::Sus;
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
    if (argc >= 4) {
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


int main(int argc, char *argv[]) {
    string labSelector = getMethodToRun(argc, argv);

    if (labSelector == "string_matching") {
        vector<GeneticAlgorithmStruct> pop_alpha, pop_beta;
        vector<GeneticAlgorithmStruct> *population, *buffer;
        IterationRawOutput rawOutputArr[GA_MAXITER];
        // Initializing each cell
        for (auto &res : rawOutputArr)
            res.id = -1;
        string workOnString = getStringToWorkWith(argc, argv);
        HeuristicsEnum heuristicMethod = getHeuristicToWorkWith(argc, argv);
        SelectionMethod selectionMethod = getSelectionMethod(argc, argv);
        CrossoverMethod crossoverMethod = getCrossoverMethod(argc, argv);

        OutputFileWriter outputWriter{workOnString, heuristicMethod, selectionMethod, crossoverMethod};
        GeneticStringMatcher matcher{workOnString, heuristicMethod, selectionMethod, crossoverMethod};

        matcher.init_population(pop_alpha, pop_beta);
        population = &pop_alpha;
        buffer = &pop_beta;

        auto startTimeStamp = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < GA_MAXITER; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            matcher.calc_fitness(*population);        // calculate fitness
            matcher.sort_by_fitness(*population);    // sort them
            matcher.print_best(*population);        // print the best one

            if ((*population)[0].getFitnessValue() == 0)
                break;
            matcher.mate(*population, *buffer);        // mate the population together
            swap(population, buffer);        // swap buffers
            double averageFitnessValue = matcher.calculateFitnessAvg(*population);
            double standardDeviation = matcher.calculateStandardDeviation(*population, averageFitnessValue);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            rawOutputArr[i].id = i;
            rawOutputArr[i].standardDeviation = standardDeviation;
            rawOutputArr[i].averageFitnessValue = averageFitnessValue;
            rawOutputArr[i].timeInMillis = duration.count();
        }

        auto endTimeStamp = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTimeStamp - startTimeStamp);

        // Initializing each cell
        for (int i = 0; i < GA_MAXITER && rawOutputArr[i].id != -1; i++) {
            std::cout << "Averaged Fitness Value: " << rawOutputArr[i].averageFitnessValue
                      << ", Standard Deviation val: " << rawOutputArr[i].standardDeviation
                      << " calculation time: " << rawOutputArr[i].timeInMillis << " millis" << std::endl;
        }
        std::cout << "Total runtime is: " << duration.count() << " millis" << std::endl;

        outputWriter.writeToFile(duration.count(), rawOutputArr);
    } else if (labSelector == "nQueens") {
        nQueensSolver solver;
        std::cout << "you would like to run nqueens" << std::endl;
    }
    return 0;
}