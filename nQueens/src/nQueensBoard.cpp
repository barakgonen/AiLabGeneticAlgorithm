//
// Created by barak on 03/05/2020.
//

#include <iostream>
#include "../include/nQueensBoard.h"
#include "../../general_utilities/include/random_collection_generator.h"

NqBoard::NqBoard()
: boardSize{-1}
{
}

void NqBoard::myInitializeBoard(const int boardSize)
{
    this->boardSize = boardSize;
    qN = RandomCollectionGenerator::getUniqueVectorWithValuesInRange(boardSize);
}

NqBoard::NqBoard(int size)
: boardSize{size}
//, colCount{new int[boardSize]}
//, upperDiagCount{new int[(2*boardSize)-1]}
//, lowerDiagCount{new int[(2*boardSize)-1]}
, qN{RandomCollectionGenerator::getUniqueVectorWithValuesInRange(boardSize)}
{
//    for(int i=0; i<2*boardSize-1; i++) {
//        if(i<boardSize) {
//            colCount[i]=0;
//        }
//        upperDiagCount[i]=lowerDiagCount[i]=0;
//    }
}
//int NqBoard::conflicts() const {
//    return conflicts(-1);
//}

bool NqBoard::shareDiagonal(const int row0, const int col0, const int row1, const int col1) const{
    int dy = std::abs(col1 - col0);
    int dx = std::abs(row1 - row0);
    return dx == dy;
}

int NqBoard::myConflicts() const {
    int conflictsCounter = 0;
    for (int row = 1; row < qN.size(); row++)
        for (int i = 0; i < row; i++)
            if (shareDiagonal(i, qN[i], row, qN[row]))
                conflictsCounter++;
    return conflictsCounter;
}
//int NqBoard::conflicts(int excludeRow) const {
//    int conflicts=0;
//
//    for(int i=0; i<2*boardSize-1; i++) {
//        if(i<boardSize) {
//            colCount[i]=0;
//        }
//        upperDiagCount[i]=lowerDiagCount[i]=0;
//    }
//
//    for(int i=0; i<boardSize; i++) {
//        if(i != excludeRow) {
//            colCount[qN[i]] += 1;
//            upperDiagCount[qN[i] + i] += 1;
//            lowerDiagCount[(boardSize - qN[i]) + i - 1] += 1;
//        }
//    }
//
//    for(int i=0; i<2*boardSize-1; i++) {
//        if(i<boardSize) {
//            conflicts += ((colCount[i]-1)*colCount[i])/2;
//        }
//        conflicts += ((upperDiagCount[i]-1)*upperDiagCount[i])/2;
//        conflicts += ((lowerDiagCount[i]-1)*lowerDiagCount[i])/2;
//    }
//    return conflicts;
//}

int NqBoard::getBoardSize() const {
    return boardSize;
}

void NqBoard::printBoard() const {
    std::cout << "board size is: " << boardSize << std::endl;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < qN[i]; j++) {
            std::cout << "| ";
        }
        std::cout << "|Q";
        for (int j = 0; j < boardSize - qN[i] - 1; j++) {
            std::cout << "| ";
        }
        std::cout << "|\n";
    }
}

void NqBoard::printQueensPosition() const {
    std::cout << "Queens positions are: " << std::endl;
    std::cout << "|  Row  |  Col  |" << std::endl;
    std::cout << "|-------|-------|" << std::endl;
    for (int row = 0; row < qN.size(); row++)
        std::cout << "|   " << row << "   |   " << qN.at(row) << "   |" << std::endl;
}

void NqBoard::setQueenValue(int index, int val){
    qN[index] = val;
}

int NqBoard::getQueenValue(int index){
    return qN[index];
}

//int* NqBoard::getColCount()
//{
//    return colCount;
//}
//
//int* NqBoard::getUpperDiagCount(){
//    return upperDiagCount;
//}
//
//int* NqBoard::getLowerDiagCount(){
//    return lowerDiagCount;
//}

int NqBoard::myGetQueenCol(const int raw) const{
    return qN.at(raw);
}

void NqBoard::myMoveQueenToColumn(const int raw, const int val){
    qN.at(raw) = val;
}