//
// Created by barak on 03/05/2020.
//

#ifndef AILABGENETICALGORITHM_BOARD_H
#define AILABGENETICALGORITHM_BOARD_H

#include "vector"
#include "string"

#define queensAttack std::pair<int, int>

class NqBoard {
public:
    // Empty ctor
    NqBoard();
    NqBoard(int size);
    NqBoard(const std::vector<int>& v);
    // Copy ctor in order to copy the board for each solver in order to compare them correctly
    NqBoard(const NqBoard& other) = default;
    virtual ~NqBoard() = default;

    virtual bool operator==(const NqBoard& other) {return boardSize == other.boardSize && qN == other.qN;}

    void printBoard() const;
    int getBoardSize() const ;
    int calculateCollisionsAtColumn(int col);
    std::vector<std::pair<std::string, std::string>> bla(int testColumn);
    void printQueensPosition() const;
    int countTotalBoardsConflicts();
    int getQueenRow(const int queenCol) const;
    void myMoveQueenToColumn(const int col, const int val);
    std::vector<int> getVector() {return qN;}
    void setVec(std::vector<int>&& s) {qN = s;}
private:
    std::pair<std::string, std::string> addToCollisionsSet(const int testCol, const int testRow, const int collisunedCol, const int collisunedRaw);
    int boardSize;
    std::vector<int> qN;
};
#endif //AILABGENETICALGORITHM_BOARD_H