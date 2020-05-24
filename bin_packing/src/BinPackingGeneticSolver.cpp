//
// Created by barak on 22/05/2020.
//

#include "../include/BinPackingGeneticSolver.h"
#include <set>

BinPackingGeneticSolver::BinPackingGeneticSolver(const int numberOfItems,
                                                 const int binsCapacity,
                                                 const std::vector<int>&& itemWeight,
                                                 const SelectionMethod selectionMethod,
                                                 const CrossoverMethod crossoverMethod,
                                                 const int maxAge,
                                                 const int maxSpecis,
                                                 const int specis)
: AbstractGeneticSolver<BinPackingGeneticStruct>(selectionMethod,
                                                 crossoverMethod,
                                                 numberOfItems,
                                                 maxAge,
                                                 maxSpecis,
                                                 specis)
, binsCapacity{binsCapacity}
, weights{std::move(itemWeight)}
{
}

std::string BinPackingGeneticSolver::getBestGene() const {
    return std::string();
}

int BinPackingGeneticSolver::start_solve() {
    init_population();
    clock_t t;
    int count = 0;
    double avg, standart_deviation;

    // We assume best solution would be the number of available bins, of course it's in worse case
    int best = numberOfItems;
    t = clock();
    for (int i = 0; i < GA_MAXITER; i++) {
        count++;
        calc_fitness();		          // calculate fitness
        sort_population_by_fitnes(); // sort them

        if (population.front().fitnessVal < best) {
            best = population.front().fitnessVal;
            print_best();
            std::cout << "clock time: " << clock() - t << std::endl;
            std::cout << "elapsed time " << ((float) (clock() - t)) / CLOCKS_PER_SEC << " seconds" << std::endl;
            std::cout << "total iterations: " << count << std::endl;
            std::cout << std::endl;
            // Checking if the next 10 are identical, if they are, we assume we got best solution
            bool isBestSolution = true;
            for (int i = 0; i < 30 && isBestSolution; i++)
                isBestSolution = isBestSolution && population[i].fitnessVal == population[i + 1].fitnessVal;
            if (isBestSolution)
                break;
        }
        avg = get_average_fitness();
        standart_deviation = get_standard_deviation(avg);

        if (count > 1 && isAtLocalOptima(standart_deviation, count)) {
            isInLocalOptima = true;
            threshold = pow(numberOfItems, 2);
        }
        else
            isInLocalOptima = false;
        auto weightsVector = get_weights_vector(avg);
        specis = mate();

        if (specis > maxSpecis - 2)
            threshold += 1;
        else if (specis < maxSpecis + 2)
            threshold -= 1;
        swap();		// swap buffers
    }

    return best;
}

int BinPackingGeneticSolver::mate(){
    int esize = GA_POPSIZE * GA_ELITRATE;
    int tsize = numberOfItems, spos, i1, i2;
    int parent1, parent2;
    int count, distance, specis = 0;
    elitism(esize);

    // Mate the rest
    for (int i = esize; i < GA_POPSIZE; i++) {
        count = 0;
        do {
            count++;
            if (selectionMethod == SelectionMethod::Random) {
                // choose random parents
                parent1 = rand() % (GA_POPSIZE / 2);
                parent2 = rand() % (GA_POPSIZE / 2);
            }
            else if (selectionMethod == SelectionMethod::Rws) {
                auto weights = get_weights_vector(get_average_fitness());
                parent1 = rws(weights);
                parent2 = rws(weights);
            }
            distance = calculateDistanceBetweenTwoCitizens(population[parent1], population[parent2]);
            if (distance > threshold)
                specis++;
        } while (distance > threshold && count < 1000);

        std::set<int> gene;
        // we take the even items from parent1, and odd items from parent2 and combine it
        // std::set can not contain the same element twice, so we will get premutation
        for (int j = 0; j < 2 * numberOfItems; j++) {
            // if even copy parent 1 item
            if (j % 2 == 0)
                gene.insert(population[parent1].items[j / 2]);
                // if odd copy parent 2 item
            else
                gene.insert(population[parent2].items[(j - 1) / 2]);
        }
        std::set<int>::iterator it;
        buffer[i].items.clear();
        for (const auto val : gene)
            buffer[i].items.push_back(val);

        if (rand() < GA_MUTATION)
            mutate(buffer[i]);
        if (isInLocalOptima)
            immigration(buffer[i]);
    }
    return specis;
}

int BinPackingGeneticSolver::calculateDistanceBetweenTwoCitizens(const BinPackingGeneticStruct& citizenOne,
                                                                 const BinPackingGeneticStruct& citizenTwo){
    return kendallTau(citizenOne.items, citizenTwo.items);
}

void BinPackingGeneticSolver::elitism(const int esize){
    int j = 0, i = 0;
    while (i < GA_POPSIZE && j < esize) {
        if (population[i].ageVal < maxAge) {
            for (int m = 0; m < numberOfItems; m++)
                buffer[j].items[m] = population[i].items[m];
            buffer[j].fitnessVal = population[i].fitnessVal;
            buffer[j].ageVal = population[i].ageVal + 1;
            if (isInLocalOptima && j > 10)
                immigration(buffer[j]);
            j++;
        }
        i++;
    }
}

void BinPackingGeneticSolver::immigration(BinPackingGeneticStruct& citizen) {
    citizen.fitnessVal = 0;
    citizen.ageVal = 0;
    int pos;
    citizen.items.clear();
    // initilaize array to -1
    for (int j = 0; j < numberOfItems; j++) {
        citizen.items.push_back(-1);
    }
    // initilize array to possible position of the items
    for (int j = 0; j < numberOfItems; j++) {
        // choose random column for the queen in row j
        pos = rand() % numberOfItems;
        while (citizen.items[pos] != -1)
            pos = rand() % numberOfItems;
        citizen.items[pos] = j;
    }
}

// Calculation of required bins, following First Fit algorithm
int BinPackingGeneticSolver::runFirstFitAlgorithm(const std::vector<int> items) {
    // Initialize result (Count of bins)
    int res = 0;

    // Create an array to store remaining space in bins
    // there can be at most n bins
    int bin_rem[numberOfItems];

    // Place items one by one
    for (int i = 0; i < numberOfItems; i++) {
        // Find the first bin that can accommodate
        // weight[i]
        int j;
        for (j = 0; j < res; j++) {
            if (bin_rem[j] >= weights[items[i]]) {
                bin_rem[j] = bin_rem[j] - weights[items[i]];
                break;
            }
        }
        // If no bin could accommodate weight[i]
        if (j == res) {
            bin_rem[res] = binsCapacity - weights[items[i]];
            res++;
        }
    }

    return res;
}

void BinPackingGeneticSolver::print_results() {

}

void BinPackingGeneticSolver::init_population() {
    for (int i = 0; i < GA_POPSIZE; i++) {
        BinPackingGeneticStruct item;
        BinPackingGeneticStruct bufferedItem;
        // initilaize items vector to -1
        for (int index = 0; index < numberOfItems; index++){
            item.items.push_back(-1);
            bufferedItem.items.push_back(-1);
        }
        buffer.push_back(bufferedItem);
        // initilize array to possible position of the items
        for (int j = 0; j < numberOfItems; j++) {
            // choose random column for the queen in row j
            int pos = rand() % numberOfItems;
            while (item.items.at(pos) != -1)
                pos = rand() % numberOfItems;
            item.items.at(pos) = j;
        }
        population.push_back(item);
    }
}

void BinPackingGeneticSolver::calc_fitness() {
    // the fitness calculate by first fit algorithm
    for (auto &citizen : population)
        citizen.fitnessVal = runFirstFitAlgorithm(citizen.items);
}

void BinPackingGeneticSolver::mutate(BinPackingGeneticStruct &member) {
    int pos1 = rand() % numberOfItems;
    int pos2 = rand() % numberOfItems;
    // change positions of two items
    int temp = member.items[pos1];
    member.items[pos1] = member.items[pos2];
    member.items[pos2] = temp;
}

void BinPackingGeneticSolver::handle_specific_elitism(const int index) {

}
