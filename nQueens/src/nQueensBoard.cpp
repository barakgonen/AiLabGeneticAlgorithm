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

int NqBoard::conflicts() const {
    return conflicts(-1);
}

int NqBoard::conflicts(int excludeRow) const {
    int conflicts=0;

    for(int i=0; i<2*boardSize-1; i++) {
        if(i<boardSize) {
            colCount[i]=0;
        }
        upperDiagCount[i]=lowerDiagCount[i]=0;
    }

    for(int i=0; i<boardSize; i++) {
        if(i != excludeRow) {
            colCount[queens[i]] += 1;
            upperDiagCount[queens[i] + i] += 1;
            lowerDiagCount[(boardSize - queens[i]) + i - 1] += 1;
        }
    }

    for(int i=0; i<2*boardSize-1; i++) {
        if(i<boardSize) {
            conflicts += ((colCount[i]-1)*colCount[i])/2;
        }
        conflicts += ((upperDiagCount[i]-1)*upperDiagCount[i])/2;
        conflicts += ((lowerDiagCount[i]-1)*lowerDiagCount[i])/2;
    }
    return conflicts;
}

int NqBoard::getBoardSize() const {
    return boardSize;
}

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