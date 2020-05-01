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
                     const SelectionMethod selectionMethod, const CrossoverMethod crossoverMethod);

    void writeToFile(int totalDurationInMs, IterationRawOutput values[GA_MAXITER]);

protected:
    std::string testedString;
    const HeuristicsEnum heuristicType;
    const SelectionMethod selectionMethod;
    const CrossoverMethod crossoverMethod;
private:
    std::string getOutputFileName();
    void openOutputFolderIfNeeded();
    std::string getCrossoverMethodStr() const;
    std::string getSelectionMethodStr() const;
    std::string getUsedHeuristicStr() const;
};


#endif //AILABGENETICALGORITHM_OUTPUTFILEWRITER_H
