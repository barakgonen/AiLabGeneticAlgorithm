//
// Created by barak on 09/05/2020.
//

#include <limits>
#include <cstdlib>
#include <chrono>
#include <iostream>
#include <math.h>
#include "../include/barakMinimalConflictsSolver.h"
barakMinimalConflictsSolver::barakMinimalConflictsSolver(const NqBoard &board)
: nQueensGenericSolver{board}
{
}

int barakMinimalConflictsSolver::calculateConflictsForSpecificQueen(int queenRow) {
    int count = 0;
    // iterate every raw
    for (int rawToTest = 0; rawToTest < board.getBoardSize(); rawToTest++) {
        if (rawToTest == queenRow)
            continue;
        // diagonal collisions or if in the same col
        if ((abs(rawToTest - queenRow) == abs(board.myGetQueenCol(rawToTest) - board.myGetQueenCol(queenRow))))
            count++;
    }
//    std::cout << "raw number: " << queenRow << ", num of conflicts is: " << count << std::endl;
    return count;
}

void barakMinimalConflictsSolver::solvePuzzle() {
    auto startTimeStamp = std::chrono::high_resolution_clock::now();
    std::vector <int> worstRows;
    int steps = 0;
    int maxConflicts = 0;
    int currentRowConflicts = 0;
    int j = 0;
    while (j<16384) {
        maxConflicts = 0;
        // search for the worst queen
        for (int row = 0; row < board.getBoardSize(); row++) {
            // calculate currentRowConflicts of the queen in column row
            currentRowConflicts = calculateConflictsForSpecificQueen(row);
            if (currentRowConflicts == maxConflicts) {
                // push to the vector of the max queen's currentRowConflicts
                worstRows.push_back(row);
            }
            else if (currentRowConflicts > maxConflicts) {
                worstRows.clear();
                worstRows.push_back(row);
                maxConflicts = currentRowConflicts;
            }
        }

        if (maxConflicts == 0)
            break;
        // choose among the max currentRowConflicts queens randomly
        int chosenRow = worstRows[rand() % worstRows.size()];
        worstRows.clear();
        std::vector <int> bestRows;
        int minConflicts = pow(board.getBoardSize(), 2);
        // search for best row for queen in the chosen column
        for (int row = 0; row < board.getBoardSize(); row++) {
            // change row
            board.myMoveQueenToColumn(chosenRow, row);
            currentRowConflicts = calculateConflictsForSpecificQueen(chosenRow);
            // meaning we have several queens with the same minimal currentRowConflicts number
            if (currentRowConflicts == minConflicts)
                bestRows.push_back(row);
            else if (currentRowConflicts < minConflicts) {
                // clear vector
                bestRows.clear();
                bestRows.push_back(row);
                minConflicts = currentRowConflicts;
            }
        }
        // choose row for the column among the rows with minimal currentRowConflicts
        if (!bestRows.empty())
            board.myMoveQueenToColumn(chosenRow, bestRows[rand() % bestRows.size()]);
        bestRows.clear();
        j++;
        steps++;
    }

    auto endTimeStamp = std::chrono::high_resolution_clock::now();
    auto calculationTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTimeStamp - startTimeStamp);
    std::cout << "number of steps is: " << steps << ", it took just: " << calculationTime.count() << " millis" << std::endl;
}