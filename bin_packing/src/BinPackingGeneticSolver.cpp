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
                                                 const int expectedResult,
                                                 const int maxSpecis,
                                                 const int specis)
: AbstractGeneticSolver<BinPackingGeneticStruct>(selectionMethod,
                                                 crossoverMethod,
                                                 numberOfItems,
                                                 5,
                                                 0.1,
                                                 5,
                                                 maxSpecis,
                                                 specis,
                                                 100)
, binsCapacity{binsCapacity}
, weights{std::move(itemWeight)}
, expectedResult{expectedResult}
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
    bool hasFound = false;

    // We assume best solution would be the number of available bins, of course it's in worse case
    int best = numberOfItems;
    t = clock();
    for (int i = 0; i < GA_MAXITER && !hasFound; i++) {
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
            if (population.front().fitnessVal == expectedResult)
                hasFound = true;
        }
        avg = get_average_fitness();
        standart_deviation = get_standard_deviation(avg);

        if (count > 1 && isAtLocalOptima(standart_deviation, count)) {
            isInLocalOptima = true;
            threshold = pow(numberOfItems, 2);
        }
        else
            isInLocalOptima = false;

        specis = mate();
        if (specis > maxSpecis - 2)
            threshold += 1;
        else if (specis < maxSpecis + 2)
            threshold -= 1;
        swap();		// swap buffers
    }

    return best;
}

int BinPackingGeneticSolver::calculateDistanceBetweenTwoCitizens(const BinPackingGeneticStruct& citizenOne,
                                                                 const BinPackingGeneticStruct& citizenTwo){
    return kendallTau(citizenOne.items, citizenTwo.items);
}

// Calculation of required bins, following First Fit algorithm
int BinPackingGeneticSolver::runFirstFitAlgorithm(const std::vector<int>& items) {
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
    for (int i = 0; i < populationSize; i++) {
        BinPackingGeneticStruct item;
        BinPackingGeneticStruct bufferedItem;

        resetCitizenProps(item);
        resetCitizenProps(bufferedItem);

        buffer.push_back(bufferedItem);

        setCitizenProps(item);
        population.push_back(item);
    }
}

void BinPackingGeneticSolver::setCitizenProps(BinPackingGeneticStruct &citizen) {
    // initilize array to possible position of the items
    for (int j = 0; j < numberOfItems; j++) {
        // choose random column for the queen in row j
        int pos = rand() % numberOfItems;
        while (citizen.items[pos] != -1)
            pos = rand() % numberOfItems;
        citizen.items[pos] = j;
    }
}

void BinPackingGeneticSolver::resetCitizenProps(BinPackingGeneticStruct &citizen) {
    citizen.fitnessVal = 0;
    citizen.ageVal = 0;
    citizen.items.clear();
    // initilaize array to -1
    for (int j = 0; j < numberOfItems; j++)
        citizen.items.push_back(-1);
    citizen.resetMembers();
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

int BinPackingGeneticSolver::mate() {
    int esize = populationSize * GA_ELITRATE;
    int spos, i1, i2;
    int count, distance, specis = 0;
//        esize = elitism(esize);
    elitism(esize);

    // Mate the rest
    for (int i = esize; i < populationSize; i++)  {
        count = 0;
        do {
            count++;
            switch (selectionMethod)
            {
                case SelectionMethod::Aging:
                    aging(i1, i2, esize);
                    break;
                case SelectionMethod::Rws:
                    calc_rws(i1, i2);
                    break;
                case SelectionMethod::Random:
                    random_selection(i1, i2);
                    break;
                case SelectionMethod::Tournament:
                    i1 = tournament();
                    i2 = tournament();
                    break;
                case SelectionMethod::None:
                    break;
            }
            distance = this->calculateDistanceBetweenTwoCitizens(population[i1], population[i2]);
            if (distance > threshold)
                specis++;
        }
        while(distance > threshold && count < 1000);

        switch (crossoverMethod) {
//                // this is the selection method given in the beginning
            case CrossoverMethod::SinglePoint:
                spos = rand() % numberOfItems;
                set_data_in_buffer_vec_for_single_point_selection(i, i1, i2, spos, numberOfItems);
//                    buffer[i].ageVal = 0;
                if (rand() < GA_MUTATION)
                    this->mutate(buffer.at(i));
                break;
            case CrossoverMethod::TwoPoints:{
                // choose two positions
                spos = rand() % numberOfItems;
                int spos2 = rand() % numberOfItems;
                // spos will hold the smaller index
                if (spos > spos2) {
                    int temp = spos2;
                    spos2 = spos;
                    spos = temp;
                }
                // two point crossover
                set_data_in_buffer_vec_for_two_points_selection(i, i1, i2, spos, spos2, numberOfItems);
                break;
            }
            case CrossoverMethod::UniformCrossover:
                this->uniform_crossover(i, i1, i2, spos, numberOfItems);
                break;
            case CrossoverMethod::Ox:
                this->ox(i, i1, i2);
                break;
            case CrossoverMethod::Pmx:
                this->pmx(i, i1, i2);
                break;
            default:
                break;
        }
//            std::set<int> gene;
//            // we take the even items from parent1, and odd items from parent2 and combine it
//            // std::set can not contain the same element twice, so we will get premutation
//            for (int j = 0; j < 2 * numberOfItems; j++) {
//                // if even copy parent 1 item
//                if (j % 2 == 0)
//                    gene.insert(buffer[i1].items[j / 2]);
//                    // if odd copy parent 2 item
//                else
//                    gene.insert(buffer[i2].items[(j - 1) / 2]);
//            }
//            std::set<int>::iterator it;
//            buffer[i].items.clear();
//            for (const auto val : gene)
//                buffer[i].items.push_back(val);
        std::set<int> gene;
        // we take the even items from parent1, and odd items from parent2 and combine it
        // std::set can not contain the same element twice, so we will get premutation
        for (int j = 0;j < 2 * numberOfItems;j++) {
            // if even copy parent 1 item
            if (j % 2 == 0)
                gene.insert(population[i1].items[j / 2]);
                // if odd copy parent 2 item
            else
                gene.insert(population[i2].items[(j - 1) / 2]);
        }
        int j = 0;
        std::set<int>::iterator it;
//            buffer[i].items = new int[numberOfItems];
        buffer[i].items.clear();
        // put the new items permutation in buffer[i]
        for (it = gene.begin(); it != gene.end(); ++it) {
            buffer[i].items.push_back(*it);
//                buffer[i].item[j] = *it;
            j++;
        }

        if (rand() < GA_MUTATION){
            this->mutate(buffer.at(i));
        }
        if (isInLocalOptima)
            immigration(buffer[i]);
        if (selectionMethod == SelectionMethod::Rws) {
            // need to preform scailling
            for (int i = 0; i < populationSize; i++) {
                double fitness = population[i].fitnessVal;
                if (fitness != 0)
                    population[i].fitnessVal = sqrt(population[i].fitnessVal);
            }
        }
    }
    return specis;
    }

int BinPackingGeneticSolver::kendallTau(const std::vector<int> &a, const std::vector<int> &b) {
    int count = 0, x = 0;
    int** ary = new int* [numberOfItems];
    for (int i = 0; i < numberOfItems; i++)
        ary[i] = new int[numberOfItems];
    for (int i = 0; i < numberOfItems; i++) {
        for (int j = i + 1; j < numberOfItems; j++) {
            if (a[i] >= numberOfItems || a[j] >= numberOfItems)
                continue;
            // if num1 is before num2 in array a, we add 1
            if (a[i] < a[j]) {
                ary[a[i]][a[j]] = 1;
                ary[a[j]][a[i]] = 1;
            }
            else {
                ary[a[i]][a[j]] = -1;
                ary[a[j]][a[i]] = -1;
            }
        }
    }
    for (int i = 0; i < numberOfItems; i++) {
        for (int j = i + 1; j < numberOfItems; j++) {
            if (b[i] >= numberOfItems || b[j] >= numberOfItems || i == j)
                continue;
            if (b[i] < b[j])
                x = 1;
            else
                x = -1;
            // if zero it means num1 and num2 not apper in the same order in the arrays
            if (ary[b[i]][b[j]] + x == 0)
                count++;
        }
    }
    // free memory
    for (int i = 0; i < numberOfItems; i++)
        delete[] ary[i];
    delete[] ary;

    return count;
}
