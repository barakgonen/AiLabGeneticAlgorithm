//
// Created by barak on 22/05/2020.
//

#include "../include/BinPackingGeneticSolver.h"

BinPackingGeneticSolver::BinPackingGeneticSolver(const int numberOfItems,
                                                 const int binsCapacity,
                                                 const std::vector<int>&& itemWeight,
                                                 const SelectionMethod selectionMethod,
                                                 const CrossoverMethod crossoverMethod,
                                                 const int maxAge,
                                                 const int maxSpecis,
                                                 const int specis)
: AbstractGeneticSolver<BinPackingGeneticStruct>(selectionMethod, crossoverMethod)
, numberOfBins{numberOfItems}
, binsCapacity{binsCapacity}
, weights{std::move(itemWeight)}
, threshold{static_cast<int>(pow(numberOfItems, 2))}
, maxSpecis{maxSpecis}
, specis{specis}
, isInLocalOptima{false}
, maxAge{maxAge}
{
}

std::string BinPackingGeneticSolver::getBestGene() const {
    return std::string();
}

int BinPackingGeneticSolver::start_solve() {
    init_population();
    clock_t t;

//    double weights[GA_POPSIZE];
//
//    // we put in item numbers 0-(n-1) for applying the first fit algorithm
//    for (int i = 0; i < n; i++)
//        item[i] = i;
//    // calculate minimal bins in first fit algorithem
//    int res = firstFit(weight, item, n, v);
//    cout << "first fit result: " << res << endl;
//    cout << endl;
//    int count = 0;


//    int best = numberOfBins;
//    t = clock();
//    for (int i = 0; i < GA_MAXITER; i++) {
//        count++;
//        calc_fitness(*population, weight, n, v);		// calculate fitness
//        sort_by_fitness(*population);	// sort them
//
//        if ((*population)[0].fitness < best) {
//            best = (*population)[0].fitness;
//            print_best(*population, weight, n);
//            cout << "clock time: " << clock() - t << endl;
//            cout << "elapsed time " << ((float)(clock() - t)) / CLOCKS_PER_SEC << " seconds" << endl;
//            cout << "total iterations: " << count << endl;
//            cout << endl;
//        }
//
//        avg = avrg(*population);
//        standart_deviation = standartDeviation(*population, avg);
//
//        if (count > 1 && localOptima(*population, standart_deviation, count, n)) {
//            isInLocalOptima = true;
//            threshold = pow(numberOfBins, 2);
//        }
//        else
//            isInLocalOptima = false;
//
//        weightsCalu(*population, weights, avg);
//        specis = mate(*population, *buffer, selection, weight, n, weights, threshold, localOptima, age);		// mate the population together
//
//        if (specis > maxSpecis - 2)
//            threshold += 1;
//        else if (specis < maxSpecis + 2)
//            threshold -= 1;
//        swap(population, buffer);		// swap buffers

    return 0;
}

// Calculation of required bins, following First Fit algorithm
int BinPackingGeneticSolver::runFirstFitAlgorithm() {
    int numOfRequiredBins = 0;

    // Create an array to store remaining space in bins
    // there can be at most n bins
//    int bin_rem[weights.size()];
//
//    // Place items one by one
//    for (int i = 0; i < n; i++) {
//        // Find the first bin that can accommodate
//        // weight[i]
//        int j;
//        for (j = 0; j < res; j++) {
//            if (bin_rem[j] >= weight[i]) {
//                bin_rem[j] = bin_rem[j] - weight[i];
//                break;
//            }
//        }
//
//        // If no bin could accommodate weight[i]
//        if (j == res) {
//            bin_rem[res] = c - weight[i];
//            res++;
//        }
//    }

    return numOfRequiredBins;
}
void BinPackingGeneticSolver::print_results() {

}

void BinPackingGeneticSolver::init_population() {
    for (int i = 0; i < GA_POPSIZE; i++) {
        BinPackingGeneticStruct item;
        BinPackingGeneticStruct bufferedItem;
        // initilaize items vector to -1
        for (int index = 0; index < numberOfBins; index++){
            item.items.push_back(-1);
            bufferedItem.items.push_back(-1);
        }
        buffer.push_back(bufferedItem);
        // initilize array to possible position of the items
        for (int j = 0; j < numberOfBins; j++) {
            // choose random column for the queen in row j
            int pos = rand() % numberOfBins;
            while (item.items.at(pos) != -1)
                pos = rand() % numberOfBins;
            item.items.at(pos) = j;
        }
        population.push_back(item);
    }
}

void BinPackingGeneticSolver::calc_fitness() {


}

void BinPackingGeneticSolver::mutate(BinPackingGeneticStruct &member) {

}

int BinPackingGeneticSolver::get_input_size() {
    return numberOfBins;
}

void BinPackingGeneticSolver::handle_specific_elitism(const int index) {

}
