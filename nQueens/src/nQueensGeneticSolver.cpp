//
// Created by barak on 30/04/2020.
//

#include <ctime>
#include <set>
#include "unordered_set"
#include <bits/unordered_set.h>
#include "../include/nQueensGeneticSolver.h"
#include "../../string_matching/include/consts.h"

nQueensGeneticSolver::nQueensGeneticSolver(const NqBoard &board,
                                           const SelectionMethod selectionMethod,
                                           const CrossoverMethod crossoverMethod,
                                           const MutationOperator mutationOperator)
: nQueensGenericSolver{board, "GENETIC"}
, AbstractGeneticSolver<nQueensGeneticAlgoStruct>{selectionMethod, crossoverMethod}
, mutataionOperator{mutationOperator} {
}

void nQueensGeneticSolver::init_population() {
    population.reserve(GA_POPSIZE);
    for (int i = 0; i < GA_POPSIZE; i++) {
//        nQueensGeneticAlgoStruct citizen{board.getBoardSize()};
        nQueensGeneticAlgoStruct citizen{board};
        population.push_back(citizen);
        buffer.push_back(citizen);
    }
}

// Fitness value is the number of conflicts for queen
void nQueensGeneticSolver::calc_fitness() {
    for (auto &board : population)
        board.fitnessVal = board.nQueensBoard.countTotalBoardsConflicts();
}

int nQueensGeneticSolver::runSolver() {
    init_population();
    int numberOfMoves = 0;
    clock_t t;
    t = clock();

    for (int i = 0; i < GA_MAXITER; i++) {
        numberOfMoves++;
        calc_fitness();        // calculate fitness
        sort_population_by_fitnes();    // sort them
        print_best();
        if (population.at(0).fitnessVal == 0 || i == 30) {
            auto v = population.at(0).nQueensBoard.getVector();
            std::cout << "clock time: " << clock() - t << std::endl;
            std::cout << "elapsed time " << ((float) (clock() - t)) / CLOCKS_PER_SEC << " seconds" << std::endl;
            std::cout << "total iterations: " << numberOfMoves << std::endl;
            board = population.at(0).nQueensBoard;
            break;
        }

        double avg = get_average_fitness();
        double standart_deviation = get_standard_deviation(avg);
        std::cout << "Avg: " << avg << " standard Deviation: " << standart_deviation << std::endl;
        mate();        // mate the population together
        swap();        // swap buffers
    }
    return numberOfMoves;
}

int random(int lower, int upper)
{
    return (rand() %
            (upper - lower + 1)) + lower;
}

void nQueensGeneticSolver::mutate(nQueensGeneticAlgoStruct &member) {
    const int numberOfQueens = member.nQueensBoard.getBoardSize();
    int pos1 = rand() % numberOfQueens;
    int pos2 = rand() % numberOfQueens;

    int temp;
    switch (mutataionOperator) {
        case MutationOperator::Exchange: {
            // change positions of two queens
            int pos1 = random(0, member.nQueensBoard.getBoardSize() - 1);
            int pos2 = random(0, member.nQueensBoard.getBoardSize() - 1);
            // change positions of two queens
            int temp = member.nQueensBoard.getQueenRow(pos1);
            member.nQueensBoard.myMoveQueenToColumn(pos1, member.nQueensBoard.getQueenRow(pos2));
            member.nQueensBoard.myMoveQueenToColumn(pos2, temp);
        }
            break;
        case MutationOperator::Inversion:
            // the new position of the reversed elements
            int pos3 = rand() % numberOfQueens;
            // will contain elements to reverse
//            std::vector<int> a;
//            // pos1 will hold the smaller index
//            if (pos1 > pos2) {
//                int temp = pos1;
//                pos1 = pos2;
//                pos2 = temp;
//            }
//            // copy element for reverse
//            for (int i = pos1; i <= pos2; i++) {
//                a.push_back(member.nQueensBoard.getQueenRow(i));
//            }
//            reverse(a.begin(), a.end());
//            // remove the element that should be re-position
//            for (int i = pos2 + 1; i <= pos3; i++) {
//                member.nQueensBoard.myMoveQueenToColumn(pos1, member.nQueensBoard.getQueenRow(i));
//                pos1++;
//            }
//            int j = 0;
//            // copy the reversed elements
//            for (int i = pos1; i < a.size(); i++) {
//                member.nQueensBoard.myMoveQueenToColumn(i, a[j]);
//                j++;
//            }
            break;
    }
}

int nQueensGeneticSolver::get_input_size() {
    return board.getBoardSize();
}

void nQueensGeneticSolver::handle_specific_elitism(const int index) {
    buffer.at(index).nQueensBoard = population.at(index).nQueensBoard;
}

void
nQueensGeneticSolver::set_data_in_buffer_vec_for_single_point_selection(const int indexInBuffer,
                                                                        const int startIndex,
                                                                        const int endIndex, int spos, int tsize) {

}

void
nQueensGeneticSolver::set_data_in_buffer_vec_for_two_points_selection(const int indexInBuffer, const int startIndex,
                                                                      const int endIndex, int spos, int spos2,
                                                                      int tsize) {

}

std::string nQueensGeneticSolver::getBestGene() const {
    return std::string("");
}

void nQueensGeneticSolver::pmx(const int i) {
    // select two random parents
    int parent1 = rand() % (GA_POPSIZE / 2);
    int parent2 = rand() % (GA_POPSIZE / 2);

    // select position of elements to swap
    int pos = rand() % board.getBoardSize();
    // two numbers we need to swap
    int num1 = population[parent1].nQueensBoard.getQueenRow(pos);
    int num2 = population[parent2].nQueensBoard.getQueenRow(pos);
    for (int j = 0; j < board.getBoardSize(); j++) {
        // if we found num1 we need to swap with num2
        if (population[parent1].nQueensBoard.getQueenRow(j) == num1)
            buffer[i].nQueensBoard.myMoveQueenToColumn(j, num2);
        else if (population[parent1].nQueensBoard.getQueenRow(j) == num2)
            buffer[i].nQueensBoard.myMoveQueenToColumn(j, num1);
            // if not num1 or and not num2 we copy from parent1
        else
            buffer[i].nQueensBoard.myMoveQueenToColumn(j, population[parent1].nQueensBoard.getQueenRow(j));
    }
}

void nQueensGeneticSolver::ox(const int i) {
    int parent1 = rand() % (GA_POPSIZE / 2);
    int parent2 = rand() % (GA_POPSIZE / 2);
    std::vector<int> parent1Vec = buffer.at(parent1).nQueensBoard.getVector();
    std::vector<int> parent2Vec = buffer.at(parent2).nQueensBoard.getVector();
    std::vector<int> copyOfParent2Vec;
    int numberOfChanges = random(0, board.getBoardSize() -1);
    std::vector<int> indexesFromParent1(numberOfChanges);
    std::generate(indexesFromParent1.begin(), indexesFromParent1.end(),
                  [n = random(0, board.getBoardSize() - numberOfChanges)] () mutable { return n++; });
    std::copy(parent2Vec.begin(), parent2Vec.end(), back_inserter(copyOfParent2Vec));
    std::vector<int> oxVec(parent2Vec.size());
    std::fill(oxVec.begin(), oxVec.end(), -1);
    // First loop initializing first part
    for (const auto parentOneIndex : indexesFromParent1){
        oxVec.at(parentOneIndex) = parent1Vec.at(parentOneIndex);
        auto valToRemove = std::find(copyOfParent2Vec.begin(), copyOfParent2Vec.end(), parent1Vec.at(parentOneIndex));
        if (valToRemove != copyOfParent2Vec.end())
            copyOfParent2Vec.erase(valToRemove);
        else{
            return;
        }
    }

    for (const auto parent2Val : copyOfParent2Vec){
        for (int ia = 0; i < oxVec.size(); ia++) {
            if (oxVec.at(ia) == -1) {
                oxVec.at(ia) = parent2Val;
                break;
            }
        }
    }
//
//
    for (int iaa = 0; i < oxVec.size(); iaa++)
        if (oxVec.at(iaa) == -1)
            exit(-1);
    buffer.at(i).nQueensBoard.setVec(std::move(oxVec));

//    int parent1 = rand() % (GA_POPSIZE / 2);
//    int parent2 = rand() % (GA_POPSIZE / 2);
//    int half = board.getBoardSize() / 2;
//    int pos;
//    std::set<int> paren1Indexes;
//    std::vector<int> rest;
//    std::vector<int> v(half);
//
//    std::generate(v.begin(), v.end(), [n = random(0, half-1)] () mutable { return n++; });
//    // Need to rebuild current citizen from 2 random parents
//    // Step 1, set all it's values to -1
////    for (int j = 0; j < board.getBoardSize(); j++){
////        buffer[i].nQueensBoard.myMoveQueenToColumn(j, -1);
////        if (std::find(v.begin(), v.end(), j) != v.end())
////            paren1Indexes.insert(j);
////        else
////            parent2Indexes.insert(j);
////    }
//    // copy parent1 half elements
////    for (int j = 0; j < half; j++) {
////        pos = rand() % board.getBoardSize();
////        // while pos already chosen
////        while (buffer[i].nQueensBoard.getQueenRow(pos) != -1)
////            pos = rand() % board.getBoardSize();
////        buffer[i].nQueensBoard.myMoveQueenToColumn(pos, population[parent1].nQueensBoard.getQueenRow(pos));
////        paren1Indexes.insert(pos);
////        parent2Indexes.erase(pos);
////    }
////std::cout << "first: ";
////    for (const auto val : paren1Indexes)
////        std::cout << val << " ";
////    std::cout << std::endl;
////    std::cout << "second: ";
////    for (const auto val : parent2Indexes)
////        std::cout << val << " ";
////    std::cout << std::endl;
//    for (const auto val : paren1Indexes)
//        buffer[i].nQueensBoard.myMoveQueenToColumn(val, population[parent1].nQueensBoard.getQueenRow(val));
//    for (const auto val : parent2Indexes)
//        buffer[i].nQueensBoard.myMoveQueenToColumn(val, population[parent2].nQueensBoard.getQueenRow(val));
}

int nQueensGeneticSolver::start_solve() {
    return runSolver();
}

void nQueensGeneticSolver::print_results() {
    board.printBoard();
}

