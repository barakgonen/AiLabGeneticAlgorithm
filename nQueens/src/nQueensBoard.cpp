//
// Created by barak on 03/05/2020.
//

#include <iostream>
#include <time.h>
#include "../include/nQueensBoard.h"

NqBoard::NqBoard(int size)
: boardSize{size}
, colCount{new int[boardSize]}
, upperDiagCount{new int[(2*boardSize)-1]}
, lowerDiagCount{new int[(2*boardSize)-1]}
{
    srand((unsigned) time(0));
    for (int j = 0; j < boardSize; j++) {
        queens.push_back(rand() % boardSize);
    }
    for(int i=0; i<2*boardSize-1; i++) {
        if(i<boardSize) {
            colCount[i]=0;
        }
        upperDiagCount[i]=lowerDiagCount[i]=0;
    }
}

NqBoard::NqBoard(const NqBoard& other)
: boardSize{other.getBoardSize()}
, colCount{other.colCount}
, upperDiagCount{other.upperDiagCount}
, lowerDiagCount{other.lowerDiagCount}
, queens(other.queens)
{
}

/*
bool NqBoard::isSafeCell(const int row, const int col) const {
    for (int i = 0; i < col; i++){
        if(m[row][i])
            return false;
    }

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (m[i][j])
            return false;
    }

    for (int i = row, j = col; j >= 0 && i < boardSize; i++, j--) {
        if (m[i][j])
            return false;
    }
    return true;
}
*/

int NqBoard::conflicts() const {
    int* colCount = new int[boardSize];
    int* upperDiagCount = new int[(2*boardSize)-1];
    int* lowerDiagCount = new int[(2*boardSize)-1];
    int conflicts=0;

    for(int i=0; i<2*boardSize-1; i++) {
        if(i<boardSize) {
            colCount[i]=0;
        }
        upperDiagCount[i]=lowerDiagCount[i]=0;
    }

    for(int i=0; i<boardSize; i++) {
            colCount[queens[i]] += 1;
            upperDiagCount[queens[i]+i] += 1;
            lowerDiagCount[(boardSize-queens[i])+i-1] += 1;
    }

    for(int i=0; i<2*boardSize-1; i++) {
        if(i<boardSize) {
            conflicts += ((colCount[i]-1)*colCount[i])/2;
        }
        conflicts += ((upperDiagCount[i]-1)*upperDiagCount[i])/2;
        conflicts += ((lowerDiagCount[i]-1)*lowerDiagCount[i])/2;
    }
    return conflicts;
//    std::vector<int> colCount;
//    std::vector<int> upperDiagCount;
//    std::vector<int> lowerDiagCount;
//    colCount.reserve(boardSize);
//    upperDiagCount.reserve((2 * boardSize) - 1);
//    lowerDiagCount.reserve((2 * boardSize) - 1);
//    int x = queens[21];
//    std::fill(colCount.begin(), colCount.end(), 0);
//    std::fill(upperDiagCount.begin(), upperDiagCount.end(), 0);
//    std::fill(lowerDiagCount.begin(), lowerDiagCount.end(), 0);
//
//    for (int i = 0; i < boardSize; i++) {
//        colCount[queens[i]] += 1;
//        upperDiagCount[queens[i] + i] += 1;
//        lowerDiagCount[(boardSize - queens[i]) + i - 1] += 1;
//    }
//    int conflicts = 0;
//    for (int i = 0; i < 2 * boardSize - 1; i++) {
//        if (i < boardSize) {
//            conflicts += ((colCount[i] - 1) * colCount[i]) / 2;
//        }
//        conflicts += ((upperDiagCount[i] - 1) * upperDiagCount[i]) / 2;
//        conflicts += ((lowerDiagCount[i] - 1) * lowerDiagCount[i]) / 2;
//    }
//    return conflicts;
}

int NqBoard::getBoardSize() const {
    return boardSize;
}

//void NqBoard::setValue(const int row, const int col, const int val) {
//    m[row][col] = val;
//}

void NqBoard::printBoard() const {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < queens[i]; j++) {
            std::cout << "| ";
        }
        std::cout << "|Q";
        for (int j = 0; j < boardSize - queens[i] - 1; j++) {
            std::cout << "| ";
        }
        std::cout << "|\n";
    }
}

void NqBoard::setQueenValue(int index, int val){
    queens[index] = val;
}

int NqBoard::getQueenValue(int index){
    return queens[index];
}

int* NqBoard::getColCount()
{
    return colCount;
}

int* NqBoard::getUpperDiagCount(){
    return upperDiagCount;
}

int* NqBoard::getLowerDiagCount(){
    return lowerDiagCount;
}