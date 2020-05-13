//
// Created by barak on 12/05/2020.
//

#ifndef AILABGENETICALGORITHM_KNAPSACKPUZZLEDATA_H
#define AILABGENETICALGORITHM_KNAPSACKPUZZLEDATA_H

#include "vector"
#include "string"

class KnapSackPuzzleData {
public:
    KnapSackPuzzleData(const int ID, const std::string basePath); // Initialize from input file
    KnapSackPuzzleData(const KnapSackPuzzleData& other) = default;

    const int getCapacity() const;
    const std::vector<int> getWeights() const;
    const std::vector<int> getProfits() const;
    const std::vector<int> getOptimalSelection() const;

protected:
    const int puzzleID;
    int capacity;
    std::vector<int> weights;
    std::vector<int> profits;
    std::vector<int> optimalSelection;
};


#endif //AILABGENETICALGORITHM_KNAPSACKPUZZLEDATA_H
