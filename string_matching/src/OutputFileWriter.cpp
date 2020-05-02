//
// Created by barak on 30/04/2020.
//

#include <fstream>
#include <io.h>
#include "../include/OutputFileWriter.h"

OutputFileWriter::OutputFileWriter(const std::string &testedString, const HeuristicsEnum heuristicType,
                                   const SelectionMethod selectionMethod, const CrossoverMethod crossoverMethod,
                                   const std::string &outputPath)
        : testedString{testedString}, heuristicType{heuristicType}, selectionMethod{selectionMethod},
          crossoverMethod{crossoverMethod}, outputPath{outputPath} {
}

void OutputFileWriter::openOutputFolderIfNeeded() {
    mkdir(outputPath.c_str());
    std::string baseOutputPath = outputPath;
    baseOutputPath.append(LAB2OutputPath);
    mkdir(baseOutputPath.c_str());
    baseOutputPath = outputPath;
    baseOutputPath.append(sortedFilesPath);
    mkdir(baseOutputPath.c_str());
    baseOutputPath = outputPath;
    baseOutputPath.append(sortedFilesPath);
    baseOutputPath.append(std::to_string(testedString.length()));
    mkdir(baseOutputPath.c_str());
    baseOutputPath = outputPath;
    baseOutputPath.append(sortedFilesPath);
    baseOutputPath.append(std::to_string(testedString.length()) + "/");
    baseOutputPath.append(testedString);
    mkdir(baseOutputPath.c_str());
    baseOutputPath = outputPath;
    baseOutputPath.append(LAB2OutputPath);
    baseOutputPath.append("stats/");
    mkdir(baseOutputPath.c_str());
}

void OutputFileWriter::writeToOutputFile(const std::string outputFileName, int totalDurationInMs,
                                         IterationRawOutput rawOutputArr[GA_MAXITER]) {
    std::ofstream outputFile(outputFileName, std::ofstream::out);
    std::string lineToWrite = "";

    lineToWrite += "Averaged Fitness Value,Standard Deviation value,ELAPSED time(milis),CLOCK TICKS\n";
    outputFile.write(lineToWrite.c_str(), lineToWrite.size());
    for (int i = 0; i < GA_MAXITER && rawOutputArr[i].id != -1; i++) {
        lineToWrite.clear();
        lineToWrite += std::to_string(rawOutputArr[i].averageFitnessValue) + "," +
                       std::to_string(rawOutputArr[i].standardDeviation) + "," +
                       std::to_string(rawOutputArr[i].elapsedTimeSeconds) + "," +
                       std::to_string(rawOutputArr[i].clockTicks) + "\n";
        outputFile.write(lineToWrite.c_str(), lineToWrite.size());
    }
    lineToWrite += "String tested,Total calculation time(milis)\n";
    outputFile.write(lineToWrite.c_str(), lineToWrite.size());
    lineToWrite.clear();
    lineToWrite += testedString + "," + std::to_string(totalDurationInMs) + "\n";
    outputFile.write(lineToWrite.c_str(), lineToWrite.size());
    outputFile.close();
}

void OutputFileWriter::writeToFile(int totalDurationInMs, IterationRawOutput rawOutputArr[GA_MAXITER]) {
    openOutputFolderIfNeeded();
    writeToOutputFile(getOutputFileName(outputPath + LAB2OutputPath), totalDurationInMs, rawOutputArr);
    writeSortedToFile(totalDurationInMs, rawOutputArr);
    // Writing to regular textfile

    std::ofstream outputFile(outputPath + LAB2OutputPath + "stats/" + getUsedHeuristicStr() + "_" + getSelectionMethodStr() + "_" + getCrossoverMethodStr() + ".csv", std::ofstream::app);
    std::string lineToWrite = std::to_string(testedString.length());
    lineToWrite.append(",").append(std::to_string(totalDurationInMs)).append("\n");
    outputFile.write(lineToWrite.c_str(), lineToWrite.size());
    outputFile.close();
}

void OutputFileWriter::writeSortedToFile(int totalDurationInMs, IterationRawOutput rawOutputArr[GA_MAXITER]) {
    std::string baseOutputPath = outputPath;
    baseOutputPath.append(sortedFilesPath);
    baseOutputPath.append(std::to_string(testedString.length()) + "/");
    baseOutputPath.append(testedString + "/");
    baseOutputPath.append(std::to_string(totalDurationInMs));
    writeToOutputFile( getOutputFileName(baseOutputPath), totalDurationInMs, rawOutputArr);
}

std::string OutputFileWriter::getOutputFileName(const std::string& basePath) {
    std::string outputFileName = basePath;
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
        case BullsAndCows:
            usedHeuristic = "BullsAndCows";
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
