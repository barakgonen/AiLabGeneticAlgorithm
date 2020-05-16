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
    int calculateCollisionsAtColumn(int col);
    void printQueensPosition() const;
    int myGetQueenCol(const int col) const;
    void myMoveQueenToColumn(const int col, const int val);
private:
    int boardSize;
    std::vector<int> qN;
};
#endif //AILABGENETICALGORITHM_BOARD_H
