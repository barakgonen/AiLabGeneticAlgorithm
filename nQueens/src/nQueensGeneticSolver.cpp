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
                                           const MutationOperator mutationOperator,
                                           bool quietMode)
: nQueensGenericSolver{board, "GENETIC"}
, AbstractGeneticSolver<nQueensGeneticStruct>{selectionMethod, crossoverMethod, board.getBoardSize()}
, mutataionOperator{mutationOperator}
, quietMode{quietMode}
{}

void nQueensGeneticSolver::init_population() {
    for (int i = 0; i < GA_POPSIZE; i++) {
        nQueensGeneticStruct citizen;
        nQueensGeneticStruct s;
        int pos;
        citizen.fitnessVal = 0;
        s.fitnessVal = 0;
        for (int j = 0; j < numberOfItems; j++) {
            s.items.push_back(0);
            citizen.items.push_back(-1);
        }
        buffer.push_back(s);
        // initilize array to possible position of items
        for (int j = 0; j < numberOfItems; j++) {
            // choose random column for the queen in row j
            pos = rand() % numberOfItems;
            while (citizen.items[pos] != -1)
                pos = rand() % numberOfItems;
            citizen.items[pos] = j;
        }
        population.push_back(citizen);
    }
}

int nQueensGeneticSolver::runSolver() {
    init_population();
    int numberOfMoves = 0;
    clock_t t;
    t = clock();
    srand(unsigned(time(NULL)));

    for (int i = 0; i < GA_MAXITER; i++) {
        numberOfMoves++;
        calc_fitness();        // calculate fitnessVal
        sort_population_by_fitnes();    // sort them
        if (!quietMode)
            print_best();
        if (population.front().fitnessVal == 0 || i > GA_MAXITER / 10) {
            std::cout << "clock time: " << clock() - t << std::endl;
            std::cout << "elapsed time " << ((float) (clock() - t)) / CLOCKS_PER_SEC << " seconds" << std::endl;
            std::cout << "total iterations: " << numberOfMoves << std::endl;
            board.setVec(std::move(population.front().items));
            break;
        }

        double avg = get_average_fitness();
        double standart_deviation = get_standard_deviation(avg);
        if (!quietMode)
        std::cout << "Avg: " << avg << " standard Deviation: " << standart_deviation << std::endl;
        mate();        // mate the population together
        swap();        // swap buffers
    }

    return numberOfMoves;
}

void nQueensGeneticSolver::calc_fitness() {
    for (int i = 0; i < GA_POPSIZE; i++) {
        // array for all the diagonals in board NXN
        std::vector<int> a((4 * numberOfItems) - 2);
        std::fill(a.begin(), a.end(), 0);
        unsigned int fitness = 0;
        for (int j = 0; j < numberOfItems; j++) {
            // diagnol 1
            a[j + population[i].items[j]]++;
            int p = abs(j - population[i].items[j]);
            // increase diagnol 2
            if (j > population[i].items[j])
                a[p + (2 * numberOfItems) - 1]++;
            else
                a[(4 * numberOfItems) - 2 - p - 1]++;
        }
        for (int l = 0; l < (4 * numberOfItems) - 2; l++) {
            // we calculate duplicated collisions as well
            a[l] = a[l] * (a[l] - 1);
            fitness += (a[l]);
            // initilazie array for next gene
            a[l] = 0;
        }
        population[i].fitnessVal = fitness;
    }
}

void nQueensGeneticSolver::mutate(nQueensGeneticStruct &member) {
    if (mutataionOperator == MutationOperator::Exchange) {
        int pos1 = rand() % numberOfItems;
        int pos2 = rand() % numberOfItems;
        // change positions of two items
        int temp = member.items[pos1];
        member.items[pos1] = member.items[pos2];
        member.items[pos2] = temp;
    } else if (mutataionOperator == MutationOperator::Inversion) {
        // pos1 - pos2 : elements to be reversed
        int pos1 = rand() % numberOfItems;
        int pos2 = rand() % numberOfItems;
        // the new position of the reversed elements
        int pos3 = rand() % numberOfItems;
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
            a.push_back(member.items[i]);
        }
        reverse(a.begin(), a.end());
        // remove the element that should be re-position
        for (int i = pos2 + 1; i <= pos3; i++) {
            member.items[pos1] = member.items[i];
            pos1++;
        }
        int j = 0;
        // copy the reversed elements
        for (int i = pos1; i < a.size(); i++) {
            member.items[i] = a[j];
            j++;
        }
    }
}

int nQueensGeneticSolver::contain(nQueensGeneticStruct &member, int num) {
    for (int i = 0; i < numberOfItems; i++)
        if (member.items[i] == num)
            return 1;
    return 0;
}

std::string nQueensGeneticSolver::getBestGene() const {
    return std::string();
}

int nQueensGeneticSolver::start_solve() {
    return runSolver();
}

void nQueensGeneticSolver::print_results() {
    board.printBoard();
}

void nQueensGeneticSolver::handle_specific_elitism(const int index) {
    for (int j = 0; j < numberOfItems; j++)
        buffer[index].items[j] = population[index].items[j];
}

void nQueensGeneticSolver::pmx(const int i) {
    // select two random parents
    int parent1 = rand() % (GA_POPSIZE / 2);
    int parent2 = rand() % (GA_POPSIZE / 2);
    // select position of elements to swap
    int pos = rand() % numberOfItems;
    // two numbers we need to swap
    int num1 = population[parent1].items[pos];
    int num2 = population[parent2].items[pos];
    for (int j = 0; j < numberOfItems; j++) {
        // if we found num1 we need to swap with num2
        if (population[parent1].items[j] == num1)
            buffer[i].items[j] = num2;
        else if (population[parent1].items[j] == num2)
            buffer[i].items[j] = num1;
        // if not num1 or and not num2 we copy from parent1
        else
            buffer[i].items[j] = population[parent1].items[j];
    }
}

void nQueensGeneticSolver::ox(const int i) {
    int parent1 = rand() % (GA_POPSIZE / 2);
    int parent2 = rand() % (GA_POPSIZE / 2);
    int half = numberOfItems / 2;
    int pos;
    // initilaize array
    for (int j = 0; j < numberOfItems; j++)
        buffer[i].items[j] = -1;
    // copy parent1 half elements
    for (int j = 0; j < half; j++) {
        pos = rand() % numberOfItems;
        // while pos already chosen
        while (buffer[i].items[pos] != -1)
            pos = rand() % numberOfItems;
        buffer[i].items[pos] = population[parent1].items[pos];
    }
    int k = 0;
    // copy parent2 elements
    for (int j = 0; j < numberOfItems; j++) {
        if (buffer[i].items[j] == -1) {
        // while parent2 element is already in the items array
            while (contain(buffer[i], population[parent2].items[k])) {
                k++;
            }
            buffer[i].items[j] = population[parent2].items[k];
        }
    }
}

void nQueensGeneticSolver::fillAditionalSolutionData(nQueensSolutionData& d){
    d.crossoverMethod = crossoverMethod;
    d.selectionMethod = selectionMethod;
}
