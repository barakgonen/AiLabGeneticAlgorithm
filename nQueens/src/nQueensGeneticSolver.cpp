//
// Created by barak on 30/04/2020.
//

#include <ctime>
#include "../include/nQueensGeneticSolver.h"
#include "../../string_matching/include/consts.h"

nQueensGeneticSolver::nQueensGeneticSolver(const NqBoard &board,
                                           const SelectionMethod selectionMethod,
                                           const CrossoverMethod crossoverMethod,
                                           const MutationOperator mutationOperator)
: nQueensGenericSolver{board}
, AbstractGeneticSolver<nQueensGeneticAlgoStruct>{selectionMethod, crossoverMethod}
, mutataionOperator{mutationOperator} {
}

void nQueensGeneticSolver::init_population() {
    population.reserve(GA_POPSIZE);
    for (int i = 0; i < GA_POPSIZE; i++) {
        nQueensGeneticAlgoStruct citizen{board.getBoardSize()};
        population.push_back(citizen);
        buffer.push_back(citizen);
    }

//
//    for (int i = 0; i < GA_POPSIZE; i++) {
//        nQueensGeneticAlgoStruct citizen;
//        buffer.push_back(citizen);
//    }
//    buffer.reserve(GA_POPSIZE);
}

void nQueensGeneticSolver::solvePuzzle() {
    start_solve();
}

int nQueensGeneticSolver::start_solve() {
    init_population();
    int numberOfMoves = 0;
    clock_t t;
    t = clock();
    for (int i = 0; i < GA_MAXITER; i++) {
        numberOfMoves++;

        calc_fitness();        // calculate fitness
        sort_population_by_fitnes();    // sort them
//       //todo: scailing();
//        print_best();
//
        if (population.at(0).fitnessVal == 0) {
            std::cout << "~~~~~~~~~~~~~~~~~~~~GENETICS AFTER~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            std::cout << "clock time: " << clock() - t << std::endl;
            std::cout << "elapsed time " << ((float) (clock() - t)) / CLOCKS_PER_SEC << " seconds" << std::endl;
            std::cout << "total iterations: " << numberOfMoves << std::endl;
            population.at(0).nQueensBoard.printBoard();
            break;
        }

        double avg = get_average_fitness();
        double standart_deviation = get_standard_deviation(avg);
        std::cout << "Avg: " << avg << " standart Deviation: " << standart_deviation << std::endl;
//
        mate();        // mate the population together
        swap();        // swap buffers
//
    }
    return numberOfMoves;
}

void nQueensGeneticSolver::print_results() {
    board.printBoard();
}

// Fitness value is the number of conflicts for queen
void nQueensGeneticSolver::calc_fitness() {
    int tsize = board.getBoardSize();
    unsigned int fitness;
    for (auto &board : population)
        board.fitnessVal = board.nQueensBoard.myConflicts();
}

void nQueensGeneticSolver::mutate(nQueensGeneticAlgoStruct &member) {
    const int numberOfQueens = board.getBoardSize();
    int pos1 = rand() % numberOfQueens;
    int pos2 = rand() % numberOfQueens;
    int temp;
    switch (mutataionOperator) {
        case MutationOperator::Exchange:
            // change positions of two queens
            temp = member.nQueensBoard.myGetQueenCol(pos1);
            member.nQueensBoard.setQueenValue(pos1, member.nQueensBoard.myGetQueenCol(pos2));
            member.nQueensBoard.setQueenValue(pos2, temp);
            break;
        case MutationOperator::Inversion:
            // the new position of the reversed elements
            int pos3 = rand() % numberOfQueens;
            // will contain elements to reverse
            std::vector<int> a;
            // pos1 will hold the smaller index
            if (pos1 > pos2) {
                int temp = pos1;
                pos1 = pos2;
                pos2 = temp;
            }
            // copy element for reverse
            for (int i = pos1; i <= pos2; i++) {
                a.push_back(member.nQueensBoard.myGetQueenCol(i));
            }
            reverse(a.begin(), a.end());
            // remove the element that should be re-position
            for (int i = pos2 + 1; i <= pos3; i++) {
                member.nQueensBoard.setQueenValue(pos1, member.nQueensBoard.myGetQueenCol(i));
                pos1++;
            }
            int j = 0;
            // copy the reversed elements
            for (int i = pos1; i < a.size(); i++) {
                member.nQueensBoard.setQueenValue(i, a[j]);
                j++;
            }
            break;
    }
}

int nQueensGeneticSolver::get_input_size() {
    return board.getBoardSize();
}

void nQueensGeneticSolver::handle_specific_elitism(const int index) {
//    std::cout << "Barak" << std::endl;
    for (int j = 0; j < board.getBoardSize(); j++) {
//        std::cout << "BBBBBB" << std::endl;
        int val = population.at(index).nQueensBoard.myGetQueenCol(j);
        buffer.at(index).nQueensBoard.myMoveQueenToColumn(j, val);
    }
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

void nQueensGeneticSolver::pmx(const int i, const int i1, const int i2) {
    // select position of elements to swap
    int pos = rand() % board.getBoardSize();
    // two numbers we need to swap
    int num1 = population[i1].nQueensBoard.getQueenValue(pos);
    int num2 = population[i2].nQueensBoard.getQueenValue(pos);
    for (int j = 0; j < board.getBoardSize(); j++) {
        // if we found num1 we need to swap with num2
        if (population[i1].nQueensBoard.getQueenValue(j) == num1)
            buffer[i].nQueensBoard.setQueenValue(j, num2);
        else if (population[i1].nQueensBoard.getQueenValue(j) == num2)
            buffer[i].nQueensBoard.setQueenValue(j, num1);
            // if not num1 or and not num2 we copy from parent1
        else
            buffer[i].nQueensBoard.setQueenValue(j, population[i1].nQueensBoard.getQueenValue(j));
    }
}

int nQueensGeneticSolver::buffer_contains(const nQueensGeneticAlgoStruct& member, int num) {
    for (int i = 0;i < board.getBoardSize();i++)
        if (member.nQueensBoard.myGetQueenCol(i) == num)
            return 1;
    return 0;
}
void nQueensGeneticSolver::ox(const int i) {
    int parent1 = rand() % (GA_POPSIZE / 2);
    int parent2 = rand() % (GA_POPSIZE / 2);
    int half = board.getBoardSize() / 2;
    int pos;
//     initilaize array
    for (int j = 0; j < board.getBoardSize(); j++)
        buffer[i].nQueensBoard.setQueenValue(j, -1);
    // copy parent1 half elements
    for (int j = 0; j < half; j++) {
        pos = rand() % board.getBoardSize();
        // while pos already chosen
        while (buffer[i].nQueensBoard.getQueenValue(pos) != -1)
            pos = rand() % board.getBoardSize();
        buffer[i].nQueensBoard.setQueenValue(pos, population[parent1].nQueensBoard.getQueenValue(pos));
    }
    int k = 0;
    // copy parent2 elements
    for (int j = 0; j < board.getBoardSize(); j++) {
        if (buffer[i].nQueensBoard.getQueenValue(j) == -1) {
            // while parent2 element is already in the queens array
            while (buffer_contains(buffer.at(i), population.at(parent2).nQueensBoard.getQueenValue(k)))
                k++;
        }
        buffer[i].nQueensBoard.setQueenValue(j, population[parent2].nQueensBoard.getQueenValue(k));
    }
}