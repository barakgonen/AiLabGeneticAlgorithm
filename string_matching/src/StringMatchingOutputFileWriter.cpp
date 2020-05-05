//
// Created by barak on 30/04/2020.
//

#include <fstream>
#include <io.h>
#include "../include/StringMatchingOutputFileWriter.h"

StringMatchingOutputFileWriter::StringMatchingOutputFileWriter(const std::string &testedString, const HeuristicsEnum heuristicType,
                                                               const SelectionMethod selectionMethod, const CrossoverMethod crossoverMethod,
                                                               const std::string &outputPath)
: OutputFileWriter{outputPath, testedString}
, heuristicType{heuristicType}
, selectionMethod{selectionMethod}
, crossoverMethod{crossoverMethod}
{
    create_output_directories();
}

std::string StringMatchingOutputFileWriter::getOutputFileName(const std::string& basePath) {
    std::string outputFileName = basePath;
    outputFileName.append(testedObject + "_");
    // Heuristic
    outputFileName += getUsedHeuristicStr() + "_";
    // selection
    outputFileName += getSelectionMethodStr() + "_";
    // crossover
    outputFileName += getCrossoverMethodStr() + "_";
    outputFileName += ".csv";
    return outputFileName;
}

std::string StringMatchingOutputFileWriter::getUsedHeuristicStr() const {
    std::string usedHeuristic = "";
    switch (heuristicType) {
        case DefaultHeuristic:
            usedHeuristic = "DefaultHeuristic";
            break;
        case BullsAndCows:
            usedHeuristic = "BullsAndCows";
            break;
    }
    return usedHeuristic;
}

std::string StringMatchingOutputFileWriter::getSelectionMethodStr() const {
    std::string selectionMethod = "";
    switch (StringMatchingOutputFileWriter::selectionMethod) {
        case Random:
            selectionMethod = "Random";
            break;
        case Tournament:
            selectionMethod = "Tournament";
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

std::string StringMatchingOutputFileWriter::getCrossoverMethodStr() const {
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

void StringMatchingOutputFileWriter::create_output_directories(){
    OutputFileWriter::create_output_directories();
    std::string baseOutputPath = outputPath;
    baseOutputPath = outputPath;
    baseOutputPath.append(sortedFilesPath);
    baseOutputPath.append(std::to_string(testedObject.length()));
    mkdir(baseOutputPath.c_str());
    baseOutputPath = outputPath;
    baseOutputPath.append(sortedFilesPath);
    baseOutputPath.append(std::to_string(testedObject.length()) + "/");
    baseOutputPath.append(testedObject);
    mkdir(baseOutputPath.c_str());
}

std::string StringMatchingOutputFileWriter::getOutputFileProperties() {
    return getUsedHeuristicStr() + "_" + getSelectionMethodStr() + "_" + getCrossoverMethodStr();
}
