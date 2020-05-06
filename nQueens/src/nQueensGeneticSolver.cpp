//
// Created by barak on 30/04/2020.
//

#include "../include/nQueensGeneticSolver.h"

nQueensGeneticSolver::nQueensGeneticSolver(const NqBoard &board, const SelectionMethod selectionMethod, const CrossoverMethod crossoverMethod)
: nQueensGenericSolver{board}
, AbstractGeneticSolver<nQueensGeneticAlgoStruct>(selectionMethod, crossoverMethod)
{
}

void nQueensGeneticSolver::solvePuzzle() {

}

int nQueensGeneticSolver::start_solve() {
    return 0;
}

void nQueensGeneticSolver::print_results() {

}

void nQueensGeneticSolver::init_population() {

}

void nQueensGeneticSolver::calc_fitness() {

}

void nQueensGeneticSolver::mutate(nQueensGeneticAlgoStruct &member) {

}

int nQueensGeneticSolver::get_input_size() {
    return 0;
}

void nQueensGeneticSolver::handle_specific_elitism(const int index){

}

void
nQueensGeneticSolver::set_data_in_buffer_vec_for_single_point_selection(const int indexInBuffer, const int startIndex,
                                                                        const int endIndex, int spos, int tsize) {

}

void
nQueensGeneticSolver::set_data_in_buffer_vec_for_two_points_selection(const int indexInBuffer, const int startIndex,
                                                                      const int endIndex, int spos, int spos2,
                                                                      int tsize) {

}

std::string nQueensGeneticSolver::getBestGene() const {
    return std::string();
}

void nQueensGeneticSolver::uniform_crossover(const int indexInBuffer, const int i1, const int i2, const int spos,
                                             int tsize) {

}
