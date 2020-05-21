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
#include <random>
#include <functional>

class RandomCollectionGenerator {
public:
    static std::vector<int> getUniqueVectorWithValuesInRange(const int boardSize, const int min=0) {
        std::vector<int> randomizedVec(boardSize);
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(1, boardSize - 1);
        auto dice = std::bind(distribution, generator);
        for (auto& v : randomizedVec)
            v = dice();
        std::random_shuffle(randomizedVec.begin(), randomizedVec.end());
        std::vector<int> boardCells(boardSize);
        std::fill(boardCells.begin(), boardCells.end(), 0);

        for (int j = 1; j < boardSize; j++) {
            // choose random column for the queen in row j
            boardCells.at(j) = randomizedVec.at(j);
        }

        return boardCells;
    }

    static std::vector<int> getForGenetic(const int boardSize, const int min=0) {
        std::vector<int> randomizedVec(boardSize);
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(min, boardSize - 1);
        auto dice = std::bind(distribution, generator);
        for (auto& v : randomizedVec)
            v = dice();
        std::random_shuffle(randomizedVec.begin(), randomizedVec.end());
        std::vector<int> boardCells(boardSize);
        std::fill(boardCells.begin(), boardCells.end(), -1);

        for (int j = 0; j < boardSize; j++) {
            // choose random column for the queen in row j
            boardCells.at(j) = randomizedVec.at(j);
        }

        return boardCells;
    }

};


#endif //AILABGENETICALGORITHM_RANDOM_COLLECTOR_GENERATOR_H