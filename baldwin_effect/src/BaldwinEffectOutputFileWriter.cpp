//
// Created by barak on 06/06/2020.
//

#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>
#include "../include/BaldwinEffectOutputFileWriter.h"
BaldwinEffectOutputFileWriter::BaldwinEffectOutputFileWriter(std::string outputPath)
: numberOfIterations{0}
, outputPath{outputPath}
{

}

void BaldwinEffectOutputFileWriter::storeResult(const std::vector<BaldwinCsvStruct>& results){

    for (const auto res : results) {
        if (calculatedData.find(res.iterationNumber) == calculatedData.end()) {
            // Insert new result to map
            calculatedData.insert(std::make_pair(res.iterationNumber, res.data));
        } else {
            // Need to update an existing one
            auto &data = calculatedData.at(res.iterationNumber);
            data.questionMarkPerc += res.data.questionMarkPerc;
            data.onePerc += res.data.onePerc;
            data.zeroPerc += res.data.zeroPerc;
        }
        // Need to calculate average
    }
    std::cout << "<BaldwinEffectOutputFileWriter::storeResult()> Result stored successfully!" << std::endl;
    numberOfIterations++;
}

void BaldwinEffectOutputFileWriter::writeCalculatedResults(){
    scaleResults();
    std::time_t ct = std::time(0);
    char* cc = ctime(&ct);

    std::string fileName = "BaldwinTest_";
    fileName.append(cc);
    for (auto& c : fileName){
        if (c == ' ' || c == ':')
            c = '_';
    }
    fileName.erase(fileName.find("\n"));
    fileName += ".csv";
    outputPath.append(fileName);
    std::cout << "WRITING TO FILE, named = " << outputPath <<std::endl;
    std::ofstream outputFile(outputPath, std::ofstream::out);
    std::string lineToWrite = "";

    lineToWrite += "Iteration-Number,?,correct,incorrect\n";
    outputFile.write(lineToWrite.c_str(), lineToWrite.size());
    for (const auto& rawData : calculatedData) {
        lineToWrite.clear();
        const auto& data = rawData.second;
        lineToWrite += std::to_string(rawData.first) + "," +
                       std::to_string(data.questionMarkPerc) + "," +
                       std::to_string(data.onePerc) + "," +
                       std::to_string(data.zeroPerc) + "\n";
        outputFile.write(lineToWrite.c_str(), lineToWrite.size());
    }
    outputFile.close();
}

void BaldwinEffectOutputFileWriter::scaleResults(){
    for (auto& res : calculatedData){
        auto& data = res.second;
        data.zeroPerc /= (double) numberOfIterations;
        data.onePerc /= (double) numberOfIterations;
        data.questionMarkPerc /= (double) numberOfIterations;
    }
}