//
// Created by barak on 30/04/2020.
//

#include <fstream>
#include <io.h>
#include "../include/OutputFileWriter.h"

OutputFileWriter::OutputFileWriter(std::string testedString, bool usedAging, bool usedRws, std::string usedHeuristic)
: testedString{testedString}
, usedAging{usedAging}
, usedRws{usedRws}
, usedHeuristic{usedHeuristic}
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
    outputFileName += usedHeuristic + "_";
    outputFileName.append((usedAging) ? "Aging" : "NotAging");
    outputFileName.append((usedRws) ? "Rws" : "NotRws");
    outputFileName += ".csv";
    return outputFileName;
}