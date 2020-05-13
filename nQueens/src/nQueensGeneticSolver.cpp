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
, AbstractGeneticSolver<nQueensGeneticAlgoStruct>(selectionMethod, crossoverMethod)
, mutataionOperator{mutationOperator}{
}

void nQueensGeneticSolver::init_population() {
    for (int i = 0; i < GA_POPSIZE; i++) {
        nQueensGeneticAlgoStruct citizen{board};
        std::vector<int> minConflictCols;
        population.push_back(citizen);
        buffer.push_back(citizen);
    }

//    buffer.reserve(GA_POPSIZE);
//    std::copy(population.begin(), population.end(), buffer);
//    buffer.resize(GA_POPSIZE); todo understand what are the differences!
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
//            population.at(0).nQueensBoard.printBoard();
            std::cout << "clock time: " << clock() - t << std::endl;
            std::cout << "elapsed time " << ((float) (clock() - t)) / CLOCKS_PER_SEC << " seconds" << std::endl;
            std::cout << "total iterations: " << numberOfMoves << std::endl;
            break;
        }

        double avg = get_average_fitness();
        double standart_deviation = get_standard_aviation(avg);
        std::cout << "Avg: " << avg << " standart Deviation: " << standart_deviation << std::endl;
//
        mate();        // mate the population together
        swap();        // swap buffers
//
    }
    return numberOfMoves;
}

void nQueensGeneticSolver::print_results() {

}

// Fitness value is the number of conflicts for queen
void nQueensGeneticSolver::calc_fitness() {
    int tsize = board.getBoardSize();
    unsigned int fitness;

    for (auto& board : population)
        board.fitnessVal = board.nQueensBoard.conflicts();

//    for (int k = 0; k < GA_POPSIZE; k++) {
//        fitness = 0;
//        for (int i = 0; i < tsize - 1; i++) {
//            for (int j = i + 1; j < tsize; j++) {
//                //horiz
//                /*if ((population[k].Board[i] == population[k].Board[j])) {
//                    fitness++;
//                }*/
//                // diag down left
//                if (((population[k].nQueensBoard.getQueenValue(i)) ==
//                     (population[k].nQueensBoard.getQueenValue(j) + abs(j - i))) ||
//                    ((population[k].nQueensBoard.getQueenValue(i) + abs(j - i)) ==
//                     population[k].nQueensBoard.getQueenValue(j))) {
//                    fitness++;
//                }
//
//            }
//        }
//
//        population[k].fitnessVal = fitness;

//    }
}

void nQueensGeneticSolver::elitism(const int esize) {
    int j = 0, i = 0;
    int popSize = population.size();
    while (i < GA_POPSIZE && j < esize) {
        if (this->population.at(i).ageVal < 10) {
            for (int m = 0; m < board.getBoardSize(); m++)
                this->buffer[j].nQueensBoard.setQueenValue(m, this->population.at(i).nQueensBoard.getQueenValue(m));
            this->buffer[j].fitnessVal = this->population[i].fitnessVal;
            this->buffer[j].ageVal = population[i].ageVal + 1;
            j++;
        }
        i++;
    }
}

    void nQueensGeneticSolver::mutate(nQueensGeneticAlgoStruct &member) {
        const int numberOfQueens = board.getBoardSize();
        int pos1 = rand() % numberOfQueens;
        int pos2 = rand() % numberOfQueens;
        int temp;
        switch (mutataionOperator) {
            case MutationOperator::Exchange:
                // change positions of two queens
                temp = member.nQueensBoard.getQueenValue(pos1);
                member.nQueensBoard.setQueenValue(pos1, member.nQueensBoard.getQueenValue(pos2));
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
                    a.push_back(member.nQueensBoard.getQueenValue(i));
                }
                reverse(a.begin(), a.end());
                // remove the element that should be re-position
                for (int i = pos2 + 1; i <= pos3; i++) {
                    member.nQueensBoard.setQueenValue(pos1, member.nQueensBoard.getQueenValue(i));
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

    void nQueensGeneticSolver::ox(const int i, const int i1, const int i2) {
        int half = board.getBoardSize() / 2;
        const int boardSize = board.getBoardSize();
        int pos;
        // initilaize array
        for (int j = 0; j < boardSize; j++)
            buffer[i].nQueensBoard.setQueenValue(j, -1);
        // copy parent1 half elements
        for (int j = 0; j < half; j++) {
            pos = rand() % boardSize;
            // while pos already chosen
            while (buffer[i].nQueensBoard.getQueenValue(pos) != -1)
                pos = rand() % boardSize;
            buffer[i].nQueensBoard.setQueenValue(pos, population[i1].nQueensBoard.getQueenValue(pos));
        }
    }