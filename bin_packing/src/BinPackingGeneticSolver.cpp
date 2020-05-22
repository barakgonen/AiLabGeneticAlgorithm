//
// Created by barak on 22/05/2020.
//

#include "../include/BinPackingGeneticSolver.h"

BinPackingGeneticSolver::BinPackingGeneticSolver(const SelectionMethod selectionMethod,
                                                 const CrossoverMethod crossoverMethod)
: AbstractGeneticSolver<binPackingGeneticStruct>(selectionMethod, crossoverMethod)
{

}
std::string BinPackingGeneticSolver::getBestGene() const {
    return std::string();
}

int BinPackingGeneticSolver::start_solve() {
    return 0;
}

void BinPackingGeneticSolver::print_results() {

}

void BinPackingGeneticSolver::init_population() {

}

void BinPackingGeneticSolver::calc_fitness() {

}

void BinPackingGeneticSolver::mutate(binPackingGeneticStruct &member) {

}

int BinPackingGeneticSolver::get_input_size() {
    return 0;
}

void BinPackingGeneticSolver::handle_specific_elitism(const int index) {

}
