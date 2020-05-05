//
// Created by barak on 03/05/2020.
//

#include <iostream>
#include <limits>
#include <chrono>
#include "../include/nQueensMinimalConflictsSolver.h"

nQueensMinimalConflictsSolver::nQueensMinimalConflictsSolver(const NqBoard &board)
: nQueensGenericSolver{board}
{
}

// First step of the algorithm, is assigning columns greedily minimizing conflicts, and then solver starts to work
void nQueensMinimalConflictsSolver::initializeBoard() {
    std::vector<int> minConflictCols;

    // choose first queen randomly
    setQueenPosition(0, rand() % boardSize);

    // i=row index
    for (int i = 1; i < boardSize; i++) {
        minConflictCols.clear();
        int minConflicts = std::numeric_limits<int>::max();
        // j=col index
        for (int j = 0; j < boardSize; j++) {
            int tempConflicts = ((board.getColCount()[j] + 1) * board.getColCount()[j]) / 2;
            tempConflicts += ((board.getUpperDiagCount()[j + i] + 1) * board.getUpperDiagCount()[j + i]) / 2;
            tempConflicts += ((board.getLowerDiagCount()[(boardSize - j) + i - 1] + 1) *
                              board.getLowerDiagCount()[(boardSize - j) + i - 1]) / 2;

            addToConflictsVec(minConflicts, tempConflicts, minConflictCols, i);
        }
        // Setting initial position for ith queen
        setQueenPosition(i, minConflictCols[rand() % minConflictCols.size()]);
    }
}

void nQueensMinimalConflictsSolver::setQueenPosition(const int index, const int val) {
    board.setQueenValue(index, val);
    board.getColCount()[board.getQueenValue(index)] += 1;
    board.getUpperDiagCount()[board.getQueenValue(index) + index] += 1;
    board.getLowerDiagCount()[(boardSize - board.getQueenValue(index)) + index - 1] += 1;
}

void nQueensMinimalConflictsSolver::solvePuzzle() {
    auto startTimeStamp = std::chrono::high_resolution_clock::now();
    initializeBoard();
    int previousConflicts = board.conflicts();
    int newConflicts;

    std::cout << "Initial conflicts: " << previousConflicts << std::endl;

    int count = 0;
    int steps = 0;

    std::cout << "Solving..." << std::endl;

    while (previousConflicts != 0) {
        MinConflicts();
        steps++;
        newConflicts = board.conflicts();
        if (previousConflicts == newConflicts) {
            count++;
            if (count > 1) {
                board.setQueenValue(rand() % board.getBoardSize(), rand() % board.getBoardSize());
                count = 0;
            }
        }
        previousConflicts = newConflicts;
    }

    auto endTimeStamp = std::chrono::high_resolution_clock::now();
    auto calculationTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTimeStamp - startTimeStamp);
    std::cout << "number of steps is: " << steps << ", it took just: " << calculationTime.count() << " millis" << std::endl;
}

void nQueensMinimalConflictsSolver::MinConflicts() {
    int highestConflictRow = HighestConflicts();

    int minConflicts = std::numeric_limits<int>::max();
    int tempConflicts;
    // min conflicts cols for queen
    std::vector<int> minConflictCols;
    board.conflicts(highestConflictRow);

    // i=col index
    for (int i = 0; i < board.getBoardSize(); i++) {
        tempConflicts = ((board.getColCount()[i] + 1) * board.getColCount()[i]) / 2;
        tempConflicts += ((board.getUpperDiagCount()[i + highestConflictRow] + 1) *
                          board.getUpperDiagCount()[i + highestConflictRow]) / 2;
        tempConflicts += ((board.getLowerDiagCount()[(board.getBoardSize() - i) + highestConflictRow - 1] + 1) *
                          board.getLowerDiagCount()[(board.getBoardSize() - i) + highestConflictRow - 1]) / 2;

        addToConflictsVec(minConflicts, tempConflicts, minConflictCols, i);
    }
    board.setQueenValue(highestConflictRow, minConflictCols[rand() % minConflictCols.size()]);
}

void nQueensMinimalConflictsSolver::addToConflictsVec(int &currentMinConflicts,
                                                      int &currentConflictsNumber,
                                                      std::vector<int> &conflictsVec,
                                                      int i) const {
    if (currentConflictsNumber < currentMinConflicts) {
        currentMinConflicts = currentConflictsNumber;
        conflictsVec.clear();
        conflictsVec.push_back(i);
    } else if (currentConflictsNumber == currentMinConflicts) {
        conflictsVec.push_back(i);
    }
}

int nQueensMinimalConflictsSolver::HighestConflicts() {
    int rowConflicts = 0;
    int tempConflicts;
    std::vector<int> maxConflictRows;

    for (int i = 0; i < board.getBoardSize(); i++) {
        tempConflicts =
                ((board.getColCount()[board.getQueenValue(i)] - 1) * board.getColCount()[board.getQueenValue(i)]) / 2;
        tempConflicts += ((board.getUpperDiagCount()[board.getQueenValue(i) + i] - 1) *
                          board.getUpperDiagCount()[board.getQueenValue(i) + i]) / 2;
        tempConflicts += ((board.getLowerDiagCount()[(board.getBoardSize() - board.getQueenValue(i)) + i - 1] - 1) *
                          board.getLowerDiagCount()[(board.getBoardSize() - board.getQueenValue(i)) + i - 1]) / 2;

        addToMaxConflictRowsVec(rowConflicts, tempConflicts, maxConflictRows, i);
    }
    return maxConflictRows[rand() % maxConflictRows.size()];
}

void nQueensMinimalConflictsSolver::addToMaxConflictRowsVec(int &rowConflicts, int &tempConflicts,
                                                            std::vector<int> &maxConflictRows, int i) const {
    if (tempConflicts > rowConflicts) {
        rowConflicts = tempConflicts;
        maxConflictRows.clear();
        maxConflictRows.push_back(i);
    } else if (tempConflicts == rowConflicts) {
        maxConflictRows.push_back(i);
    }
}
