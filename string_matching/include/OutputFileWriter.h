//
// Created by barak on 30/04/2020.
//

#ifndef AILABGENETICALGORITHM_OUTPUTFILEWRITER_H
#define AILABGENETICALGORITHM_OUTPUTFILEWRITER_H

#include <string>
#include "IterationRawOutput.h"
#include "consts.h"

class OutputFileWriter {
public:
    OutputFileWriter(std::string testedString, bool usedAging, bool usedRws, std::string usedHeuristic);
    void writeToFile(int totalDurationInMs, IterationRawOutput values[GA_MAXITER]);
protected:
    std::string testedString;
    bool usedAging;
    bool usedRws;
    std::string usedHeuristic;
private:
    std::string getOutputFileName();
    void openOutputFolderIfNeeded();
};


#endif //AILABGENETICALGORITHM_OUTPUTFILEWRITER_H
