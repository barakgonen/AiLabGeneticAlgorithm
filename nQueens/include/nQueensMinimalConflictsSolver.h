//
// Created by barak on 03/05/2020.
//

#ifndef AILABGENETICALGORITHM_NQUEENSMINIMALCONFLICTSSOLVER_H
#define AILABGENETICALGORITHM_NQUEENSMINIMALCONFLICTSSOLVER_H

#include "nQueensGenericSolver.h"

class nQueensMinimalConflictsSolver : public nQueensGenericSolver{
public:
    nQueensMinimalConflictsSolver(const NqBoard& board);
    void solvePuzzle() override;

private:
    void initializeBoard();
    void MinConflicts();
    int HighestConflicts();
    void setQueenPosition(const int index, const int val);

    void addToConflictsVec(int& currentMinConflicts, int& currentConflictsNumber, std::vector<int> &conflictsVec, int i) const;

    void addToMaxConflictRowsVec(int& rowConflicts, int& tempConflicts, std::vector<int> &maxConflictRows, int i) const;
};

#endif //AILABGENETICALGORITHM_NQUEENSMINIMALCONFLICTSSOLVER_H
