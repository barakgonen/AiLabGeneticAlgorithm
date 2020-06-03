//
// Created by barak on 03/05/2020.
//

#include <iostream>
#include "../include/nQueensBoard.h"
#include "../../general_utilities/include/random_collection_generator.h"
#include "set"

NqBoard::NqBoard()
: boardSize{-1}
{
}

NqBoard::NqBoard(int size)
: boardSize{size}
, qN{RandomCollectionGenerator::getUniqueVectorWithValuesInRange(boardSize)}
{}

// qN.at(i) = j --> the queen is the col, means i, the value, raw is j
NqBoard::NqBoard(const std::vector<int>& v)
: boardSize{static_cast<int>(v.size())}
, qN{v}
{
}

int NqBoard::calculateCollisionsAtColumn(int column){
    int count = 0;
    // pass over all columns
    for (int i = 0; i < boardSize; i++) {
        if (i == column)
            continue;
        // diagnol collisions
        if (abs(i - column) == abs(qN.at(i) - qN.at(column)))
            count++;
            // if there are items in the same row
        else if (qN.at(column) == qN.at(i))
            count++;
    }
    return count;
}
std::pair<std::string, std::string> NqBoard::addToCollisionsSet(const int testCol, const int testRow,
        const int collisunedCol, const int collisunedRaw)
{
    if (testCol < collisunedCol)
        return std::make_pair(std::to_string(testCol) + std::to_string(testRow),
                std::to_string(collisunedCol) + std::to_string(collisunedRaw));
    else
        return std::make_pair(std::to_string(collisunedCol) + std::to_string(collisunedRaw),
                                std::to_string(testCol) + std::to_string(testRow));
}

std::vector<std::pair<std::string, std::string>> NqBoard::bla(int testColumn)
{
    std::vector<std::pair<std::string, std::string>> conflicts;
    for (int currentColumn = 0; currentColumn < boardSize; currentColumn++) {
        if (currentColumn == testColumn)
            continue;
        // same row
        else if (qN.at(testColumn) == qN.at(currentColumn))
            conflicts.push_back(addToCollisionsSet(testColumn, qN.at(testColumn), currentColumn, qN.at(currentColumn)));
        // diagonal
        if (abs(currentColumn - testColumn) == abs(qN.at(currentColumn) - qN.at(testColumn)))
            conflicts.push_back(addToCollisionsSet(testColumn, qN.at(testColumn), currentColumn, qN.at(currentColumn)));
    }
    return conflicts;
}
int NqBoard::countTotalBoardsConflicts() {
    std::set<std::pair<std::string, std::string>> conflicts;
    for (int i = 0; i < boardSize; i++){
        for (const auto& s : bla(i))
            conflicts.insert(s);
    }
    return conflicts.size();
}

int NqBoard::getBoardSize() const {
    return boardSize;
}

void NqBoard::printBoard() const {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (qN[j] != i)
                std::cout << " * ";
            else
                std::cout << " Q ";
        }
        std::cout << std::endl;
    }
}

void NqBoard::printQueensPosition() const {
    std::cout << "Queens positions are: " << std::endl;
    std::cout << "|  Col  |  Row  |" << std::endl;
    std::cout << "|-------|-------|" << std::endl;
    for (int col = 0; col < qN.size(); col++)
        std::cout << "|   " << col << "   |   " << qN.at(col) << "   |" << std::endl;
}

int NqBoard::getQueenRow(const int queenCol) const{
    return qN.at(queenCol);
}

void NqBoard::myMoveQueenToColumn(const int col, const int val){
    qN.at(col) = val;
}