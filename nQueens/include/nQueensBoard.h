//
// Created by barak on 03/05/2020.
//

#ifndef AILABGENETICALGORITHM_BOARD_H
#define AILABGENETICALGORITHM_BOARD_H

#include "vector"

class NqBoard {
public:
    NqBoard(int size);
    // Copy ctor in order to copy the board for each solver in order to compare them correctly
    NqBoard(const NqBoard& other) = default;
    virtual ~NqBoard() = default;

    void printBoard() const;
    int getBoardSize() const ;
    int conflicts(int exludeRow) const;
    int conflicts() const;
    void setQueenValue(int index, int val);
    int getQueenValue(int index);
    int* getColCount();
    int* getUpperDiagCount();
    int* getLowerDiagCount();

private:
    int boardSize;
    int* colCount;
    int* upperDiagCount;
    int* lowerDiagCount;
    std::vector<int> queens;
};
#endif //AILABGENETICALGORITHM_BOARD_H
