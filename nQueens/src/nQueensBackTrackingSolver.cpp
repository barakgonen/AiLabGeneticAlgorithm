////
//// Created by barak on 03/05/2020.
////
//
//#include "../include/nQueensBackTrackingSolver.h"
//
//nQueensBackTrackingSolver::nQueensBackTrackingSolver(int boardSize)
//: board(boardSize)
//{
//}
//
//void nQueensBackTrackingSolver::solvePuzzle() {
//    solveNQUtil(0);
//}
//
//void nQueensBackTrackingSolver::printPuzzle(){
//    board.printBoard();
//}
//
//bool nQueensBackTrackingSolver::solveNQUtil(int col)
//{
////    if (col >= board.getBoardSize())
////        return true;
////    for (int i = 0; i < board.getBoardSize(); i++)
////    {
////        if (board.isSafeCell(i, col) )
////        {
////            board.setValue(i, col, 1);
////            if (solveNQUtil(col + 1))
////                return true;
////            board.setValue(i, col, 0);
////        }
////    }
//    return false;
//}