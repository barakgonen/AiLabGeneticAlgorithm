//
// Created by barak on 09/05/2020.
//

#ifndef AILABGENETICALGORITHM_RANDOM_COLLECTOR_GENERATOR_H
#define AILABGENETICALGORITHM_RANDOM_COLLECTOR_GENERATOR_H

#include <algorithm>
#include <random>
#include <time.h>
#include <ctime>
#include "vector"

class RandomCollectionGenerator {
public:
    static std::vector<int> getUniqueVectorWithValuesInRange(const int boardSize, const int min=0) {
        std::vector<int> boardCells(boardSize);

        int pos;
        // if something bad happens, it's becasue i started the loop from 0 instead of 1
        for (int j = 0; j < boardSize; j++) {
            // choose random column for the queen in row j
            pos = rand() % boardSize;
            while (boardCells[pos] != 0)
                pos = rand() % boardSize;
            boardCells[pos] = j;
        }
        return boardCells;
    }


};


#endif //AILABGENETICALGORITHM_RANDOM_COLLECTOR_GENERATOR_H
