//
// Created by barak on 30/04/2020.
//

#ifndef AILABGENETICALGORITHM_STRINGMATCHINGOUTPUTFILEWRITER_H
#define AILABGENETICALGORITHM_STRINGMATCHINGOUTPUTFILEWRITER_H

#include <string>
#include <vector>
#include "../../genetic_solver/include/IterationRawOutput.h"
#include "consts.h"
#include "../../genetic_solver/include/SelectionMethodEnum.h"
#include "HeuristicsEnum.h"
#include "../../genetic_solver/include/CrossoverMethod.h"
#include "../../general_utilities/include/OutputFileWriter.h"

class StringMatchingOutputFileWriter : public OutputFileWriter{
public:
    StringMatchingOutputFileWriter(const std::string &testedString, const HeuristicsEnum heuristicType,
                                   const SelectionMethod selectionMethod, const CrossoverMethod crossoverMethod,
                                   const std::string &outputPath);

protected:
    const HeuristicsEnum heuristicType;
    const SelectionMethod selectionMethod;
    const CrossoverMethod crossoverMethod;
    void create_output_directories() override;

private:
    std::string getOutputFileName(const std::string& basePath) override;
    std::string getOutputFileProperties() override;
    std::string getCrossoverMethodStr() const;
    std::string getSelectionMethodStr() const;
    std::string getUsedHeuristicStr() const;
};


#endif //AILABGENETICALGORITHM_STRINGMATCHINGOUTPUTFILEWRITER_H
