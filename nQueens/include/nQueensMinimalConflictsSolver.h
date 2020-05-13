//
// Created by barak on 09/05/2020.
//

#ifndef AILABGENETICALGORITHM_BARAKMINIMALCONFLICTSSOLVER_H
#define AILABGENETICALGORITHM_BARAKMINIMALCONFLICTSSOLVER_H


#include "nQueensGenericSolver.h"

class barakMinimalConflictsSolver : public nQueensGenericSolver{
public:
    barakMinimalConflictsSolver(const NqBoard& board);
    void solvePuzzle() override;

private:
//    void initializeBoard();
//    void MinConflicts();
//    int HighestConflicts();
//    void setQueenPosition(const int index, const int val);

//    void addToConflictsVec(int& currentMinConflicts, int& currentConflictsNumber, std::vector<int> &conflictsVec, int i) const;

//    void addToMaxConflictRowsVec(int& rowConflicts, int& tempConflicts, std::vector<int> &maxConflictRows, int i) const;
    int calculateConflictsForSpecificQueen(int queenRow);
};


#endif //AILABGENETICALGORITHM_BARAKMINIMALCONFLICTSSOLVER_H
