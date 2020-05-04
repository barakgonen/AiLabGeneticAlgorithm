//
// Created by barak on 03/05/2020.
//

#include <iostream>
#include <limits>
#include "../include/nQueensMinimalConflictsSolver.h"

nQueensMinimalConflictsSolver::nQueensMinimalConflictsSolver(const NqBoard &board)
: nQueensGenericSolver{board}
{
    initialize();
}

void nQueensMinimalConflictsSolver::initialize() {
    const int boardSize = board.getBoardSize();
//    int* colCount = new int[boardSize];
//    int* upperDiagCount = new int[(2*boardSize)-1];
//    int* lowerDiagCount = new int[(2*boardSize)-1];
//    colCount = new int[boardSize];

//    for(int i=0; i<2*boardSize-1; i++) {
//        if(i<boardSize) {
//            colCount[i]=0;
//        }
//        upperDiagCount[i]=lowerDiagCount[i]=0;
//    }

    std::vector<int> minConflictCols;
    int minConflicts=std::numeric_limits<int>::max();
    int tempConflicts;

    // choose first queen randomly
    board.setQueenValue(0, rand()%boardSize);

    board.getColCount()[board.getQueenValue(0)] += 1;
    board.getUpperDiagCount()[board.getQueenValue(0)+0] += 1;
    board.getLowerDiagCount()[(boardSize-board.getQueenValue(0))+0-1] += 1;

    // i=row index
    for(int i=1; i<boardSize; i++) {
        minConflictCols.clear();
        minConflicts = std::numeric_limits<int>::max();
        // j=col index
        for(int j=0; j<boardSize; j++) {
            tempConflicts = ((board.getColCount()[j]+1)*board.getColCount()[j])/2;
            tempConflicts += ((board.getUpperDiagCount()[j+i]+1)*board.getUpperDiagCount()[j+i])/2;
            tempConflicts += ((board.getLowerDiagCount()[(boardSize-j)+i-1]+1)*board.getLowerDiagCount()[(boardSize-j)+i-1])/2;

            if(tempConflicts < minConflicts) {
                minConflicts=tempConflicts;
                minConflictCols.clear();
                minConflictCols.push_back(j);
            } else if(tempConflicts == minConflicts) {
                minConflictCols.push_back(j);
            }
        }
        board.setQueenValue(i, minConflictCols[rand()%minConflictCols.size()]);

        board.getColCount()[board.getQueenValue(i)] += 1;
        board.getUpperDiagCount()[board.getQueenValue(i)+i] += 1;
        board.getLowerDiagCount()[(boardSize-board.getQueenValue(i))+i-1] += 1;
    }
//    std::vector<int> colCount = std::vector<int>{board.getBoardSize()};
//    std::vector<int> upperDiagCount = std::vector<int>{(2 * board.getBoardSize()) - 1};
//    std::vector<int> lowerDiagCount = std::vector<int>{(2 * board.getBoardSize()) - 1};
//    std::fill(colCount.begin(), colCount.end(), 0);
//    std::fill(upperDiagCount.begin(), upperDiagCount.end(), 0);
//    std::fill(lowerDiagCount.begin(), lowerDiagCount.end(), 0);
//
//    for (int i = 0; i < 2 * board.getBoardSize() - 1; i++) {
//        if (i < board.getBoardSize()) {
//            colCount[i] = 0;
//        }
//        upperDiagCount[i] = lowerDiagCount[i] = 0;
//    }
//
//    std::vector<int> minConflictCols;
//    int minConflicts = std::numeric_limits<int>::max();
//    int tempConflicts;
//
//    // choose first queen randomly
//    board.setQueenValue(0, rand() % board.getBoardSize());
//
//    colCount[board.getQueenValue(0)] += 1;
//    upperDiagCount[board.getQueenValue(0) + 0] += 1;
//    lowerDiagCount[(board.getBoardSize() - board.getQueenValue(0) + 0 - 1)] += 1;
//
//    // i=row index
//    for (int i = 1; i < board.getBoardSize(); i++) {
//        minConflictCols.clear();
//        minConflicts = std::numeric_limits<int>::max();
//        // j=col index
//        for (int j = 0; j < board.getBoardSize(); j++) {
//            tempConflicts = ((colCount[j] + 1) * colCount[j]) / 2;
//            tempConflicts += ((upperDiagCount[j + i] + 1) * upperDiagCount[j + i]) / 2;
//            tempConflicts += ((lowerDiagCount[(board.getBoardSize() - j) + i - 1] + 1) *
//                              lowerDiagCount[(board.getBoardSize() - j) + i - 1]) / 2;
//
//            if (tempConflicts < minConflicts) {
//                minConflicts = tempConflicts;
//                minConflictCols.clear();
//                minConflictCols.push_back(j);
//            } else if (tempConflicts == minConflicts) {
//                minConflictCols.push_back(j);
//            }
//        }
//        board.setQueenValue(i, minConflictCols[rand() % minConflictCols.size()]);
//
//        colCount[board.getQueenValue(i)] += 1;
//        upperDiagCount[board.getQueenValue(i) + i] += 1;
//        lowerDiagCount[(board.getBoardSize() - board.getQueenValue(i)) + i - 1] += 1;
//    }
}

void nQueensMinimalConflictsSolver::solvePuzzle() {
    int previousConflicts = board.conflicts();
    int newConflicts;

    std::cout << "Initial conflicts: " << previousConflicts << std::endl;

    int count = 0;
    int steps = 0;

    while(previousConflicts != 0)	{
        MinConflicts();
        steps++;
        newConflicts = board.conflicts();
        if(previousConflicts == newConflicts) {
            count++;
            if(count>1) {
                board.setQueenValue(rand()%board.getBoardSize(), rand()%board.getBoardSize());
                count = 0;
            }
        }
        previousConflicts = newConflicts;
    }

    std::cout << "Solving..." << std::endl;
}

void nQueensMinimalConflictsSolver::MinConflicts() {
//    int highestConflictRow = HighestConflicts();
//
//    int minConflicts=std::numeric_limits<int>::max();
//    int tempConflicts;
//    // min conflicts cols for queen
//    std::vector<int> minConflictCols;
//
//    //Print();
//    BoardConflicts(highestConflictRow);
//
//    // i=col index
//    for(int i=0; i<board.getBoardSize(); i++) {
//        tempConflicts = ((colCount[i]+1)*colCount[i])/2;
//        tempConflicts += ((upperDiagCount[i+highestConflictRow]+1)*upperDiagCount[i+highestConflictRow])/2;
//        tempConflicts += ((lowerDiagCount[(N-i)+highestConflictRow-1]+1)*lowerDiagCount[(N-i)+highestConflictRow-1])/2;
//
//        if(tempConflicts < minConflicts) {
//            minConflicts=tempConflicts;
//            minConflictCols.clear();
//            minConflictCols.push_back(i);
//        } else if(tempConflicts == minConflicts) {
//            minConflictCols.push_back(i);
//        }
//    }
//    queens[highestConflictRow]=minConflictCols[rand()%minConflictCols.size()];
}

int nQueensMinimalConflictsSolver::HighestConflicts() {
//    int rowConflicts=0;
//    int tempConflicts;
//    std::vector<int> maxConflictRows;
//
//    for(int i=0; i<board.getBoardSize(); i++) {
//        tempConflicts = ((colCount[queens[i]]-1)*colCount[queens[i]])/2;
//        tempConflicts += ((upperDiagCount[queens[i]+i]-1)*upperDiagCount[queens[i]+i])/2;
//        tempConflicts += ((lowerDiagCount[(N-queens[i])+i-1]-1)*lowerDiagCount[(N-queens[i])+i-1])/2;
//
//        if(tempConflicts > rowConflicts) {
//            rowConflicts=tempConflicts;
//            maxConflictRows.clear();
//            maxConflictRows.push_back(i);
//        } else if(tempConflicts == rowConflicts) {
//            maxConflictRows.push_back(i);
//        }
//    }
//    return maxConflictRows[rand()%maxConflictRows.size()];
return 1;
}
