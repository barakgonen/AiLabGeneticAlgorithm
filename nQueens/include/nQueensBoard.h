//
// Created by barak on 03/05/2020.
//

#ifndef AILABGENETICALGORITHM_BOARD_H
#define AILABGENETICALGORITHM_BOARD_H

#include "vector"

class NqBoard {
public:
    // Default ctor
    NqBoard(int size);
    // Copy ctor in order to copy the board for each solver in order to compare them correctly
    NqBoard(const NqBoard& other);
    virtual ~NqBoard() = default;

//    bool isSafeCell(const int row, const int col) const;
    void printBoard() const;
    int getBoardSize() const ;
    int conflicts() const;
    void setQueenValue(int index, int val);
    int getQueenValue(int index);
    int* getColCount();
    int* getUpperDiagCount();
    int* getLowerDiagCount();

private:
    const int boardSize;
    int* colCount;
    int* upperDiagCount;
    int* lowerDiagCount;
    std::vector<int> queens;
};
#endif //AILABGENETICALGORITHM_BOARD_H
