//
// Created by barak on 30/04/2020.
//

#include <fstream>
#include <io.h>
#include "../include/OutputFileWriter.h"

OutputFileWriter::OutputFileWriter(const std::string &testedString, const HeuristicsEnum heuristicType,
                                   const SelectionMethod selectionMethod, const CrossoverMethod crossoverMethod)
: testedString{testedString}
, heuristicType{heuristicType}
, selectionMethod{selectionMethod}
, crossoverMethod{crossoverMethod}
{
}

void OutputFileWriter::openOutputFolderIfNeeded(){
    mkdir("output/");
}
void OutputFileWriter::writeToFile(int totalDurationInMs, IterationRawOutput rawOutputArr[GA_MAXITER]){
    openOutputFolderIfNeeded();
    std::ofstream outputFile(getOutputFileName(), std::ofstream::out);
    std::string lineToWrite = "";

    lineToWrite += "Averaged Fitness Value,Standard Deviation value,calculation time(milis)\n";
    outputFile.write(lineToWrite.c_str(), lineToWrite.size());
    for (int i = 0; i < GA_MAXITER && rawOutputArr[i].id != -1; i++) {
        lineToWrite.clear();
        lineToWrite +=  std::to_string(rawOutputArr[i].averageFitnessValue) + "," +
                        std::to_string(rawOutputArr[i].standardDeviation) + "," +
                        std::to_string(rawOutputArr[i].timeInMillis) + "\n";
        outputFile.write(lineToWrite.c_str(), lineToWrite.size());
    }
    lineToWrite += "String tested,Total calculation time(milis)\n";
    outputFile.write(lineToWrite.c_str(), lineToWrite.size());
    lineToWrite.clear();
    lineToWrite += testedString + "," + std::to_string(totalDurationInMs) + "\n";
    outputFile.write(lineToWrite.c_str(), lineToWrite.size());
    outputFile.close();
}

std::string OutputFileWriter::getOutputFileName(){
    std::string outputFileName = "output/";
    outputFileName.append(testedString + "_");
    // Heuristic
    outputFileName += getUsedHeuristicStr() + "_";
    // selection
    outputFileName += getSelectionMethodStr() + "_";
    // crossover
    outputFileName += getCrossoverMethodStr() + "_";
    outputFileName += ".csv";
    return outputFileName;
}

std::string OutputFileWriter::getUsedHeuristicStr() const {
    std::string usedHeuristic = "";
    switch (heuristicType) {
        case DefaultHeuristic:
            usedHeuristic = "DefaultHeuristic";
        break;
        case BullAndCow:
            usedHeuristic = "BullAndCow";
        break;
    }
    return usedHeuristic;
}

std::string OutputFileWriter::getSelectionMethodStr() const {
    std::string selectionMethod = "";
    switch (OutputFileWriter::selectionMethod) {
        case Random:
            selectionMethod = "Random";
            break;
        case Tournament:
            selectionMethod = "Tournament";
            break;
        case Sus:
            selectionMethod = "Sus";
            break;
        case Rws:
            selectionMethod = "Rws";
            break;
        case Aging:
            selectionMethod = "Aging";
            break;
    }
    return selectionMethod;
}

std::string OutputFileWriter::getCrossoverMethodStr() const {
    std::string crossoverMethodStr = "";
    switch (crossoverMethod) {
        case SinglePoint:
            crossoverMethodStr = "SinglePoint";
            break;
        case TwoPoints:
            crossoverMethodStr = "TwoPoints";
            break;
        case UniformCrossover:
            crossoverMethodStr = "UniformCrossover";
            break;
    }
    return crossoverMethodStr;
}
