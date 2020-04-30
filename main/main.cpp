//
// Created by barak on 30/04/2020.
//

#include <iostream>
#include "chrono"

#include "../string_matching/include/consts.h"
#include "../string_matching/include/GeneticStringMatcher.h"

#include "../nQueens/include/nQueensSolver.h"
#include "../string_matching/include/OutputFileWriter.h"
#include "../string_matching/include/IterationRawOutput.h"

using namespace std;

std::string get_method_to_run(int argc, char *argv[]){
    std::string method_to_run;
    if (argc >= 2){
        method_to_run = argv[1];
    } else{
        cout << "Choose lab to run: string_matching / nQueens" << endl;
        getline(cin, method_to_run);
    }
    return method_to_run;
}

std::string get_string_to_work_with(int argc, char *argv[]){
    std::string stringToWorkWith = GA_TARGET;
    if (argc >= 2)
        stringToWorkWith = argv[2];
    return stringToWorkWith;
}

std::string get_heuristic_to_work_with(int argc, char *argv[]){
    string heuristicType;
    if (argc >= 3){
        heuristicType = argv[3];
    } else{
        cout << "Choose heuristic method: " << defaultHeuristic << " / " << bullAndCow << endl;
        getline(cin, heuristicType);
    }
    return heuristicType;
}

bool get_rws_usage(int argc, char *argv[]){
    string rwsUsage;
    if (argc >= 4){
        rwsUsage = argv[4];
    } else{
        cout << "Should use RWS? (y/n): " << endl;
        getline(cin, rwsUsage);
    }
    return  rwsUsage == "y" ? true : false;;
}

bool get_aging_usage(int argc, char *argv[]){
    string shouldUseAging;
    if (argc >= 5){
        shouldUseAging = argv[5];
    } else{
        cout << "Should use Aging? (y/n): " << endl;
        getline(cin, shouldUseAging);
    }
    return shouldUseAging == "y" ? true : false;
}


int main(int argc, char *argv[]) {
    std::cout << "argc is: " << argc << std::endl;
    string labSelector = get_method_to_run(argc, argv);

    if (labSelector == "string_matching") {
        vector<GeneticAlgorithmStruct> pop_alpha, pop_beta;
        vector<GeneticAlgorithmStruct> *population, *buffer;
        IterationRawOutput rawOutputArr[GA_MAXITER];
        // Initializing each cell
        for (auto &res : rawOutputArr)
            res.id = -1;
        string workOnString = get_string_to_work_with(argc, argv);
        string heuristicType = get_heuristic_to_work_with(argc, argv);
        bool shouldUseRws = get_rws_usage(argc, argv);
        bool shouldUseAging = get_aging_usage(argc, argv);

        OutputFileWriter outputWriter{workOnString, shouldUseAging, shouldUseRws, heuristicType};
        GeneticStringMatcher matcher{workOnString, heuristicType, shouldUseRws, shouldUseAging};

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
    }
    else if (labSelector == "nQueens"){
        nQueensSolver solver;
        std::cout << "you would like to run nqueens" << std::endl;
    }
    return 0;
}