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

NqBoard::NqBoard(int size)
: boardSize{size}
, qN{RandomCollectionGenerator::getUniqueVectorWithValuesInRange(boardSize)}
{}

int NqBoard::calculateCollisionsAtColumn(int column){
    int count = 0;
    // pass over all columns
    for (int i = 0; i < boardSize; i++) {
        if (i == column)
            continue;
        // diagnol collisions
        if (abs(i - column) == abs(qN.at(i) - qN.at(column)))
            count++;
            // if there are queens in the same row
        else if (qN.at(column) == qN.at(i))
            count++;
    }
    return count;
}

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

int NqBoard::myGetQueenCol(const int col) const{
    return qN.at(col);
}

void NqBoard::myMoveQueenToColumn(const int col, const int val){
    qN.at(col) = val;
}