//
// Created by barak on 03/05/2020.
//

#ifndef AILABGENETICALGORITHM_BOARD_H
#define AILABGENETICALGORITHM_BOARD_H

#include "vector"

#define queensAttack std::pair<int, int>

class NqBoard {
public:
    // Empty ctor
    NqBoard();
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
    void printQueensPosition() const;
    int myConflicts() const;
    int myGetQueenCol(const int raw) const;
    void myMoveQueenToColumn(const int raw, const int val);
    void myInitializeBoard(const int boardSize);
private:
    bool rowHasDiagonalClashes(int row) const;
    bool shareDiagonal(const int row0, const int col0, const int row1, const int col1) const;
    int boardSize;
//    int* colCount;
//    int* upperDiagCount;
//    int* lowerDiagCount;
    std::vector<int> qN;
};
#endif //AILABGENETICALGORITHM_BOARD_H
