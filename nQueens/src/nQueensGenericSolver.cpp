//
// Created by barak on 04/05/2020.
//

#include <chrono>
#include <iostream>
#include "../include/nQueensGenericSolver.h"

nQueensGenericSolver::nQueensGenericSolver(const NqBoard& board, std::string solverType)
: board{board}
, solverType{solverType}
{
}

void nQueensGenericSolver::printPuzzle() {
    board.printBoard();
}

nQueensSolutionData nQueensGenericSolver::solvePuzzle() {
    nQueensSolutionData solutionData;
    std::cout << "~~~~~~~~~~~~~~~~~~~~" << solverType << " SOLVER BEFORE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    printPuzzle();
    auto startTimeStamp = std::chrono::high_resolution_clock::now();
    int iterationsCounter = runSolver();
    auto endTimeStamp = std::chrono::high_resolution_clock::now();
    auto calculationTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTimeStamp - startTimeStamp);
    std::cout << "number of steps is: " << iterationsCounter << ", it took just: "
              << calculationTime.count() << " millis" << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~" << solverType << " SOLVER AFTER~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    printPuzzle();
    solutionData.boardSize = board.getBoardSize();
    solutionData.numberOfSteps = iterationsCounter;
    solutionData.timeToSolve = calculationTime.count();
    fillAditionalSolutionData(solutionData);
    return std::move(solutionData);
}