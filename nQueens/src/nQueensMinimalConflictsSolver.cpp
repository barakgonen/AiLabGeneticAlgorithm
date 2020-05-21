//
// Created by barak on 09/05/2020.
//

#include <cstdlib>
#include "../include/nQueensMinimalConflictsSolver.h"
#include "../../string_matching/include/consts.h"

nQueensMinimalConflictsSolver::nQueensMinimalConflictsSolver(const NqBoard &board, bool isQuietMode)
: nQueensGenericSolver{board, "MINIMAL CONFLICTS "}
, isQuietMode{isQuietMode}
{
}

int nQueensMinimalConflictsSolver::runSolver() {
    std::vector <int> worstColumns;
    int maxConflicts = 0;
    int conflicts = 0;
    int iterationsCounter = 0;
    while (iterationsCounter < GA_MAXITER) {
        maxConflicts = 0;
        // search for the worst queen
        for (int i = 0; i < board.getBoardSize(); i++) {
            // calculate conflicts of the queen in column i
            conflicts = board.calculateCollisionsAtColumn(i);
            if (conflicts == maxConflicts) {
                // push to the vector of the max queen's conflicts
                worstColumns.push_back(i);
            }
            else if (conflicts > maxConflicts) {
                worstColumns.clear();
                worstColumns.push_back(i);
                maxConflicts = conflicts;
            }
        }
        // meaning no conflicts
        if (maxConflicts == 0)
            break;
        // choose among the max conflicts queens randomly
        int columnChosen = worstColumns[rand() % worstColumns.size()];
        worstColumns.clear();
        std::vector <int> bestRows;
        int minConflicts = board.getBoardSize() * board.getBoardSize();
        // search for best row for queen in the chosen column
        for (int i = 0; i < board.getBoardSize(); i++) {
            // change row
            board.myMoveQueenToColumn(columnChosen, i);
            conflicts = (board, columnChosen);
            // meaning we have several queens with the same minimal conflicts number
            if (conflicts == minConflicts)
                bestRows.push_back(i);
            else if (conflicts < minConflicts) {
                // clear vector
                bestRows.clear();
                bestRows.push_back(i);
                minConflicts = conflicts;
            }

        }
        // choose row for the column among the rows with minimal conflicts
        if (!bestRows.empty())
            board.myMoveQueenToColumn(columnChosen, bestRows[rand() % bestRows.size()]);
        bestRows.clear();
        iterationsCounter++;
    }
    return iterationsCounter;
}