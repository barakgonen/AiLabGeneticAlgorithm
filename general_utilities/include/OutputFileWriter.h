//
// Created by barak on 05/05/2020.
//

#ifndef AILABGENETICALGORITHM_OUTPUTFILEWRITER_H
#define AILABGENETICALGORITHM_OUTPUTFILEWRITER_H


#include <string>
#include <vector>
#include <SelectionMethodEnum.h>
#include <CrossoverMethod.h>
#include "../../genetic_solver/include/IterationRawOutput.h"

class OutputFileWriter {
public:
    OutputFileWriter(const std::string& outputPath, const std::string testedObject,
                     const SelectionMethod selectionMethod, const CrossoverMethod crossoverMethod);
    virtual ~OutputFileWriter() = default;

    void writeToFile(int totalDurationInMs, const std::vector<IterationRawOutput>& values);

protected:
    virtual std::string getOutputFileName(const std::string& basePath) = 0;
    virtual std::string getOutputFileProperties() = 0;
    virtual void create_output_directories();
    void writeSortedToFile(int totalDurationInMs, const std::vector<IterationRawOutput>& values);
    void writeToOutputFile(const std::string outputFileName, int totalDurationInMs, const std::vector<IterationRawOutput>& values);
    std::string getCrossoverMethodStr() const;
    std::string getSelectionMethodStr() const;
    const std::string& outputPath;
    const std::string testedObject;
    const SelectionMethod selectionMethod;
    const CrossoverMethod crossoverMethod;
};


#endif //AILABGENETICALGORITHM_OUTPUTFILEWRITER_H
