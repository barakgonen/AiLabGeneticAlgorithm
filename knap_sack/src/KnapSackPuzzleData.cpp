//
// Created by barak on 12/05/2020.
//

#include "../include/KnapSackPuzzleData.h"
#include <fstream>
#include <iostream>

KnapSackPuzzleData::KnapSackPuzzleData(const int ID, const std::string basePath)
: puzzleID{ID}
{
    // Reading capacity from file
    std::string capacityAsString;
    std::ifstream capacityReader{basePath + "/knap_sack/static_input_files/" + std::to_string(ID) + "/capacity.txt"};
    while (getline(capacityReader, capacityAsString)) {
        // Output the text from the file
        capacity = atoi(capacityAsString.c_str());
    }
    capacityReader.close();

    std::string weightsAsString;
    std::ifstream weightsReader{basePath + "/knap_sack/static_input_files/" + std::to_string(ID) + "/weights.txt"};
    while (getline(weightsReader, weightsAsString)) {
        // Output the text from the file
        auto it = weights.end();
        weights.insert(it, atoi(weightsAsString.c_str()));
        weightsAsString = "";
    }
    weightsReader.close();

    std::string profitsAsString;
    std::ifstream profitsReader{basePath + "/knap_sack/static_input_files/" + std::to_string(ID) + "/profits.txt"};
    while (getline(profitsReader, profitsAsString)) {
        // Output the text from the file
        auto it = profits.end();
        profits.insert(it, atoi(profitsAsString.c_str()));
        capacityAsString = "";
    }
    profitsReader.close();

    std::string optimalSolutionAsString;
    std::ifstream optimalSolutionReader{basePath + "/knap_sack/static_input_files/" + std::to_string(ID) + "/optimalSelection.txt"};
    while (getline(optimalSolutionReader, optimalSolutionAsString)) {
        // Output the text from the file
        auto it = optimalSelection.end();
        optimalSelection.insert(it, atoi(optimalSolutionAsString.c_str()));
        optimalSolutionAsString = "";
    }
    optimalSolutionReader.close();
}



const int KnapSackPuzzleData::getCapacity() const {
    return capacity;
}

const std::vector<int> KnapSackPuzzleData::getWeights() const {
    return weights;
}

const std::vector<int> KnapSackPuzzleData::getProfits() const {
    return profits;
}

const std::vector<int> KnapSackPuzzleData::getOptimalSelection() const {
    return optimalSelection;
}