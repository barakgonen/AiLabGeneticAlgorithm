//
// Created by barak on 12/05/2020.
//

#include "../include/KnapSackStaticDataSetInitializer.h"

KnapSackStaticDataSetInitializer::KnapSackStaticDataSetInitializer(const std::string basePath){
    addToStaticDataSet(1, basePath);
    addToStaticDataSet(2, basePath);
    addToStaticDataSet(3, basePath);
    addToStaticDataSet(4, basePath);
    addToStaticDataSet(5, basePath);
    addToStaticDataSet(6, basePath);
    addToStaticDataSet(7, basePath);
//    addToStaticDataSet(8, basePath);
}

bool KnapSackStaticDataSetInitializer::isOptimalSelectionReached(const int exampleNum,
                                                                 std::vector<int> actualOptimalSelection) const {
    const auto& expectedOptimalSelection = dataSet.at(exampleNum).getOptimalSelection();
    for (int index = 0; index < actualOptimalSelection.size(); index++)
        if (expectedOptimalSelection.at(index) != actualOptimalSelection.at(index))
            return false;
    return true;
}

void KnapSackStaticDataSetInitializer::addToStaticDataSet(const int exampleNum, const std::string basePath) {
    dataSet.insert(std::make_pair(exampleNum, KnapSackPuzzleData{exampleNum, basePath}));
}

std::vector<int> KnapSackStaticDataSetInitializer::getPuzzlesIDs() const{
    std::vector<int> puzzleKeys;
    for (const auto staticPuzzle : dataSet)
    {
        auto end = puzzleKeys.end();
        puzzleKeys.insert(end, staticPuzzle.first);
    }
    return puzzleKeys;
}

const int KnapSackStaticDataSetInitializer::getCapacity(const int puzzleID) const {
    for (const auto val : dataSet)
        if (val.first == puzzleID)
            return val.second.getCapacity();
}
const std::vector<int> KnapSackStaticDataSetInitializer::getWeights(const int puzzleID) const {
    for (const auto val : dataSet)
        if (val.first == puzzleID)
            return val.second.getWeights();
}

const std::vector<int> KnapSackStaticDataSetInitializer::getProfits(const int puzzleID) const{
    for (const auto val : dataSet)
        if (val.first == puzzleID)
            return val.second.getProfits();
}

const std::vector<int> KnapSackStaticDataSetInitializer::getOptimalSelection(const int puzzleID) const{
    for (const auto val : dataSet)
        if (val.first == puzzleID)
            return val.second.getOptimalSelection();
}