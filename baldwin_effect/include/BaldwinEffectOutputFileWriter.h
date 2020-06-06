//
// Created by barak on 06/06/2020.
//

#ifndef AILABGENETICALGORITHM_BALDWINEFFECTOUTPUTFILEWRITER_H
#define AILABGENETICALGORITHM_BALDWINEFFECTOUTPUTFILEWRITER_H


#include <vector>
#include "BaldwinIterationStruct.h"
#include "map"

class BaldwinEffectOutputFileWriter {
public:
    BaldwinEffectOutputFileWriter(std::string outputPath);
    virtual ~BaldwinEffectOutputFileWriter() = default;
    void storeResult(const std::vector<BaldwinCsvStruct>& results);
    void writeCalculatedResults();

protected:
    void scaleResults();
    int numberOfIterations;
    std::string outputPath;
    std::map<int, BaldwinIterationStruct> calculatedData;

};


#endif //AILABGENETICALGORITHM_BALDWINEFFECTOUTPUTFILEWRITER_H
