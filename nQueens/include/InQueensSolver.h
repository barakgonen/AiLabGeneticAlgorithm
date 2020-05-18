//
// Created by barak on 03/05/2020.
//

#ifndef AILABGENETICALGORITHM_INQUEENSSOLVER_H
#define AILABGENETICALGORITHM_INQUEENSSOLVER_H

#include <utility>
class InQueensSolver{
public:
    virtual std::pair<int, int> solvePuzzle() = 0;
    virtual void printPuzzle() = 0;
};

#endif //AILABGENETICALGORITHM_INQUEENSSOLVER_H
