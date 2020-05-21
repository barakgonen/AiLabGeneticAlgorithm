//
// Created by barak on 18/05/2020.
//

#include <fstream>
#include <io.h>
#include <map>
#include "../include/nQueensOutputFileWriter.h"

nQueensOutputFileWriter::nQueensOutputFileWriter(const std::string &outputPath, std::string testedObject,
                                                 const MutationOperator mutationOperator, const CrossoverMethod crossoverMethod)
: OutputFileWriter("", testedObject, SelectionMethod::None, crossoverMethod)
, my{outputPath}
, mutationOper{mutationOperator}
{
    mkdir(my.c_str());
}
std::string nQueensOutputFileWriter::getOutputFileName(const std::string &basePath) {
    std::string outputFileName = my + "\\";
    outputFileName += testedObject + ".csv";
    return outputFileName;
}

std::string nQueensOutputFileWriter::getOutputFileProperties() {
    return "";
}

void nQueensOutputFileWriter::writeToFile(const std::vector<nQueensSolutionData>& solLst){

    std::ofstream outputFile(getOutputFileName(my), std::ofstream::out);
    std::string lineToWrite = "";


    // Key of the map is board size, value is a pair of repititions & sum data, in order to write average data
    std::map<int, std::pair<int, nQueensSolutionData>> resultsMap;

    // Building histogram
    for (const auto& sol : solLst) {
        if (resultsMap.find(sol.boardSize) != resultsMap.end()) {
            auto& mapItem = resultsMap.at(sol.boardSize);
            mapItem.first++;
            auto& val = mapItem.second;
            val.timeToSolve += sol.timeToSolve;
            val.numberOfSteps += sol.numberOfSteps;
        }
        else{
            resultsMap.insert(std::make_pair(sol.boardSize, std::make_pair(1, sol)));
        }
    }

    // Average calculation
    for (auto& sol : resultsMap) {
        auto& result = sol.second;
        auto& solData = sol.second.second;
        solData.numberOfSteps = solData.numberOfSteps / result.first;
        solData.timeToSolve = solData.timeToSolve / result.first;
    }

    lineToWrite += "Board-Size,Steps-To-Solution,Calculation-Time(Millis)\n";
    outputFile.write(lineToWrite.c_str(), lineToWrite.size());
    for (const auto& sol : resultsMap) {
        lineToWrite.clear();
        lineToWrite += std::to_string(sol.second.second.boardSize) + "," +
                       std::to_string(sol.second.second.numberOfSteps) + "," +
                       std::to_string(sol.second.second.timeToSolve) + "," +
//                       std::to_string(sol.second.second.crossoverMethod) +
                       "\n";
        outputFile.write(lineToWrite.c_str(), lineToWrite.size());
    }

    outputFile.close();
}
