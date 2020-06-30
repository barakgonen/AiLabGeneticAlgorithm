//
// Created by barak on 05/05/2020.
//

#include <io.h>
#include <fstream>
#include "../include/OutputFileWriter.h"
#include "../../string_matching/include/consts.h"

OutputFileWriter::OutputFileWriter(const std::string& outputPath, const std::string testedObject,
                                   const SelectionMethod selectionMethod, const CrossoverMethod crossoverMethod,
                                   const bool isParralelized)
: outputPath{outputPath}
, testedObject{testedObject}
, selectionMethod{selectionMethod}
, crossoverMethod{crossoverMethod}
, isParallelized{isParralelized}
{
    create_output_directories();
}

void OutputFileWriter::writeToFile(int totalDurationInMs, const std::vector<IterationRawOutput>& rawOutputArr) {
    create_output_directories();
    writeToOutputFile(getOutputFileName(outputPath + LAB2OutputPath), totalDurationInMs, rawOutputArr);
    writeSortedToFile(totalDurationInMs, rawOutputArr);
    // Writing to regular textfile

    std::ofstream outputFile(outputPath + LAB2OutputPath + "stats/" + getOutputFileProperties() + ".csv", std::ofstream::app);
    std::string lineToWrite = std::to_string(testedObject.length());
    lineToWrite.append(",").append(std::to_string(totalDurationInMs)).append("\n");
    outputFile.write(lineToWrite.c_str(), lineToWrite.size());
    outputFile.close();
}

void OutputFileWriter::create_output_directories(){
    mkdir(outputPath.c_str());
    std::string baseOutputPath = outputPath;
    baseOutputPath.append(LAB2OutputPath);
    mkdir(baseOutputPath.c_str());
    baseOutputPath = outputPath;
    baseOutputPath.append(sortedFilesPath);
    mkdir(baseOutputPath.c_str());
    baseOutputPath = outputPath;
    baseOutputPath.append(LAB2OutputPath);
    baseOutputPath.append("stats/");
    mkdir(baseOutputPath.c_str());
    baseOutputPath = outputPath;
    baseOutputPath.append("nQueensRes/");
    mkdir(baseOutputPath.c_str());
}

void OutputFileWriter::writeSortedToFile(int totalDurationInMs, const std::vector<IterationRawOutput>& rawOutputArr) {
    std::string baseOutputPath = outputPath;
    baseOutputPath.append(sortedFilesPath);
    baseOutputPath.append(std::to_string(testedObject.length()) + "/");
    baseOutputPath.append(testedObject + "/");
    baseOutputPath.append(std::to_string(totalDurationInMs));
    writeToOutputFile( getOutputFileName(baseOutputPath), totalDurationInMs, rawOutputArr);
}

void OutputFileWriter::writeToOutputFile(const std::string outputFileName, int totalDurationInMs,
                                                       const std::vector<IterationRawOutput>& values) {
    std::ofstream outputFile(outputFileName, std::ofstream::out);
    std::string lineToWrite = "";

    lineToWrite += "Averaged Fitness Value,Standard Deviation value,ELAPSED time(milis),CLOCK TICKS\n";
    outputFile.write(lineToWrite.c_str(), lineToWrite.size());
    for (const auto& rawData : values) {
        lineToWrite.clear();
        lineToWrite += std::to_string(rawData.averageFitnessValue) + "," +
                       std::to_string(rawData.standardDeviation) + "," +
                       std::to_string(rawData.elapsedTimeSeconds) + "," +
                       std::to_string(rawData.clockTicks) + "\n";
        outputFile.write(lineToWrite.c_str(), lineToWrite.size());
    }

    lineToWrite += "String tested,Total calculation time(milis)\n";
    outputFile.write(lineToWrite.c_str(), lineToWrite.size());
    lineToWrite.clear();
    lineToWrite += testedObject + "," + std::to_string(totalDurationInMs) + "\n";
    outputFile.write(lineToWrite.c_str(), lineToWrite.size());
    outputFile.close();
}

std::string OutputFileWriter::getSelectionMethodStr() const {
    std::string selectionMethodStr = "";
    switch (selectionMethod) {
        case Random:
            selectionMethodStr = "Random";
            break;
        case Tournament:
            selectionMethodStr = "Tournament";
            break;
        case Rws:
            selectionMethodStr = "Rws";
            break;
        case Aging:
            selectionMethodStr = "Aging";
            break;
    }
    return selectionMethodStr;
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
        case Ox:
            crossoverMethodStr = "Ox";
            break;
        case Pmx:
            crossoverMethodStr = "Pmx";
            break;
    }
    return crossoverMethodStr;
}