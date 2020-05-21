//
// Created by barak on 18/05/2020.
//

#ifndef AILABGENETICALGORITHM_NQUEENSOUTPUTFILEWRITER_H
#define AILABGENETICALGORITHM_NQUEENSOUTPUTFILEWRITER_H


#include <MutationOperators.h>
#include "../../general_utilities/include/OutputFileWriter.h"
#include "nQueensSolutionData.h"

class nQueensOutputFileWriter : public OutputFileWriter {
public:
    nQueensOutputFileWriter(const std::string &outputPath, std::string testedObject,
                            const MutationOperator mutationOperator, const CrossoverMethod crossoverMethod);
    virtual ~nQueensOutputFileWriter() = default;
    void writeToFile(const std::vector<nQueensSolutionData>& sol);
protected:
    std::string my;
    MutationOperator mutationOper;
    std::string getOutputFileName(const std::string &basePath) override;

    std::string getOutputFileProperties() override;

};


#endif //AILABGENETICALGORITHM_NQUEENSOUTPUTFILEWRITER_H
