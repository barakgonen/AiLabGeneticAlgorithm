//
// Created by barak on 12/05/2020.
//

#ifndef AILABGENETICALGORITHM_KNAPSACKDATASTATICDATASETINITIALIZER_H
#define AILABGENETICALGORITHM_KNAPSACKDATASTATICDATASETINITIALIZER_H

#include <map>
#include "vector"
#include "KnapSackPuzzleData.h"

class KnapSackStaticDataSetInitializer {
public:
    KnapSackStaticDataSetInitializer(const std::string basePath);
    virtual ~KnapSackStaticDataSetInitializer() = default;

    bool isOptimalSelectionReached(const int exampleNum, const std::vector<int> optimalSelection) const;
    std::vector<int> getPuzzlesIDs() const;
    const int getCapacity(const int puzzleID) const;
    const std::vector<int> getWeights(const int puzzleID) const;
    const std::vector<int> getProfits(const int puzzleID) const;
    const std::vector<int> getOptimalSelection(const int puzzleID) const;

protected:
    void addToStaticDataSet(const int exampleNum, const std::string basePath);

    std::map<int, KnapSackPuzzleData> dataSet;
};


#endif //AILABGENETICALGORITHM_KNAPSACKDATASTATICDATASETINITIALIZER_H
