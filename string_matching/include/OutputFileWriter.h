//
// Created by barak on 30/04/2020.
//

#ifndef AILABGENETICALGORITHM_OUTPUTFILEWRITER_H
#define AILABGENETICALGORITHM_OUTPUTFILEWRITER_H

#include <string>
#include "IterationRawOutput.h"
#include "consts.h"
#include "SelectionMethodEnum.h"
#include "HeuristicsEnum.h"
#include "CrossoverMethod.h"

class OutputFileWriter {
public:

    OutputFileWriter(const std::string &testedString, const HeuristicsEnum heuristicType,
                     const SelectionMethod selectionMethod, const CrossoverMethod crossoverMethod,
                     const std::string &outputPath);

    void writeToFile(int totalDurationInMs, IterationRawOutput values[GA_MAXITER]);

protected:
    std::string testedString;
    const HeuristicsEnum heuristicType;
    const SelectionMethod selectionMethod;
    const CrossoverMethod crossoverMethod;
    const std::string& outputPath;
private:
    std::string getOutputFileName(const std::string& basePath);
    void openOutputFolderIfNeeded();
    std::string getCrossoverMethodStr() const;
    std::string getSelectionMethodStr() const;
    std::string getUsedHeuristicStr() const;
    void writeToOutputFile(const std::string outputFileName, int totalDurationInMs, IterationRawOutput values[GA_MAXITER]);
    // Using os ability to sort, ill just paste the file name with total time
    void writeSortedToFile(int totalDurationInMs, IterationRawOutput values[GA_MAXITER]);
};


#endif //AILABGENETICALGORITHM_OUTPUTFILEWRITER_H
