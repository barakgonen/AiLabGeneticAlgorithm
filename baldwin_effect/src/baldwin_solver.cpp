//
// Created by barak on 05/06/2020.
//

#include "../include/baldwin_solver.h"

Baldwin_Solver::Baldwin_Solver(const int numberOfIterations,
                               const int numberOfItems,
                               const int populationSize)
: numberOfIterations{numberOfIterations}
, populationSize{populationSize}
, numberOfItems{numberOfItems} {
    generateTargetGene();
}

void Baldwin_Solver::generateTargetGene() {
    for (int j = 0; j < numberOfItems; j++) {
        if (rand() < RAND_MAX * 0.5)
            // zero
            targetGene.push_back('0');
        else
            // one
            targetGene.push_back('1');
    }
    targetGeneStr = std::string{targetGene.begin(), targetGene.end()};
    std::cout << "Target gene is: " << targetGeneStr << std::endl;
}

void Baldwin_Solver::init_population() {
    for (int i = 0; i < populationSize; i++) {
        Baldwin_Struct citizen;
        citizen.fitnessVal = -1;
        citizen.str.erase();
        int countZero = 0, countOne = 0, countQM = 0;
        while (citizen.str.length() < 20) {
            // decide which char to add by rand nubmer
            int x = rand();
            if (x < RAND_MAX * 0.25 && countZero < 5) {
                // zero
                citizen.str += 48;
                countZero++;
            } else if (x < RAND_MAX * 0.5 && countOne < 5) {
                // one
                citizen.str += 49;
                countOne++;
            } else if (countQM < 10) {
                // question mark
                citizen.str += 63;
                countQM++;
            }
        }
        population.push_back(citizen);
    }
    buffer.resize(populationSize);
}

std::vector<BaldwinCsvStruct> Baldwin_Solver::solve() {
    std::vector<BaldwinCsvStruct> data;
    init_population();
    for (int i = 0; i < numberOfIterations; i++) {
        // calculate avg of question marks
        auto qms = calculateQM();
        // calculate avg of correct and incorrect positions among fixed positions
        auto ons = calculateFixed();
        calc_fitness();        // calculate fitness
        sort_population_by_fitnes();    // sort them
        print_best();        // print the best one
        this->mate();        // mate the population together
        BaldwinCsvStruct currentResult;
        currentResult.iterationNumber = i + 1;
        currentResult.data.onePerc = ons;
        currentResult.data.zeroPerc = 100 - ons - qms;
        currentResult.data.questionMarkPerc = qms;
        data.push_back(std::move(currentResult));
        std::swap(population, buffer);        // swap buffers
    }

    calc_fitness();
    return data;
}

void Baldwin_Solver::sort_population_by_fitnes() {
    std::sort(population.begin(),
              population.end(),
              [](const Baldwin_Struct &x, const Baldwin_Struct &y) {
                  return (x.fitnessVal > y.fitnessVal);
              });
}

void Baldwin_Solver::elitism(const int esize) {
    for (int i = 0; i < esize; i++) {
        buffer[i].str = population[i].str;
        buffer[i].fitnessVal = population[i].fitnessVal;
    }
}

void Baldwin_Solver::calc_fitness() {
    int n = 0;
    std::string s;
    for (int i = 0; i < populationSize; i++) {
        n = 0;
        s = population[i].str;
        while (n < populationSize && targetGeneStr != s) {
            s = population[i].str;
            for (int j = 0; j < targetGeneStr.length(); j++) {
                if (s[j] != '?')
                    continue;
                int r = rand();
                if (r < RAND_MAX * 0.5)
                    s[j] = '0';
                else
                    s[j] = '1';
            }
            n++;
        }
        population[i].fitnessVal = 1 + (19 * (1000 - n) / 1000);
    }
}

void Baldwin_Solver::mutate(Baldwin_Struct &member) {
    int ipos = rand() % 20;
    int num = rand();
    if (num < RAND_MAX * 0.25)
        member.str[ipos] = '0';
    else
        member.str[ipos] = '1';
}

void Baldwin_Solver::calc_rws(int &i1, int &i2) {
    const std::vector<double> weights = get_weights_vector(get_average_fitness());
    i1 = rws(weights);
    i2 = rws(weights);
}

int Baldwin_Solver::rws(const std::vector<double>& weights) {
    // calculate the total weights
    std::vector<double> weightsVec = get_weights_vector(get_average_fitness());
    double weight_sum = weights[populationSize - 1];
    // rand number between 0 and 1
    double value = (rand() / (double) (RAND_MAX + 1)) * weight_sum;
    // locate the random value based on the weights
    for (int i = 0; i < populationSize; i++) {
        value -= weights[i];
        if (value <= 0) {
            return i;
        }
    }
    return 0;
}

std::vector<double> Baldwin_Solver::get_weights_vector(double avg) {
    std::vector<double> weights;
    for (int j = 0; j < populationSize; j++) {
        if (j != 0)
            // we add previous weight for later use in rws function
            weights.push_back(population.at(j).fitnessVal / (avg * populationSize) + weights[j - 1]);
        else
            weights.push_back(population.at(j).fitnessVal / (avg * populationSize));
    }
    return weights;
}

void Baldwin_Solver::mate() {
    int esize = populationSize * GA_ELITRATE;
    int tsize = 20, spos, i1, i2, spos2;

    elitism(esize);

    // Mate the rest
    for (int i = esize; i < populationSize; i++) {
        if (population[i].fitnessVal == 20)
            continue;
        // select parents
        calc_rws(i1, i2);
        // choose two positions
        spos = rand() % tsize;
        spos2 = rand() % tsize;
        // spos will hold the smaller index
        if (spos > spos2) {
            int temp = spos2;
            spos2 = spos;
            spos = temp;
        }
        // two point crossover
        buffer[i].str = population[i1].str.substr(0, spos) +
                        population[i2].str.substr(spos, spos2 - spos) +
                        population[i1].str.substr(spos2, tsize - spos2);
        buffer[i].fitnessVal = -1;

        if (rand() < GA_MUTATION) mutate(buffer[i]);
    }
}

double Baldwin_Solver::calculateQM() {
    int count = 0;
    for (int i = 0; i < populationSize; i++) {
        for (int j = 0; j < targetGeneStr.length(); j++) {
            if (population[i].str[j] == '?')
                count++;
        }
    }
    float avg = (float)count / (populationSize * 20.0);
    std::cout << "question marks: " << avg * 100 << "%" << std::endl;
    return avg * 100;
}

// this function returns 1's percentage. in order to calc 0's -> 100 - 1's - ?'s = 0's
double Baldwin_Solver::calculateFixed() {
    int correct = 0;
    int incorrect = 0;
    for (int i = 0; i < populationSize; i++) {
        for (int j = 0; j < targetGeneStr.length(); j++) {
            if (population[i].str[j] == '?')
                continue;
            if (population[i].str[j] == targetGeneStr[j])
                correct++;
            else
                incorrect++;
        }
    }
    float avg = (float) (correct) / (populationSize * 20.0);
    std::cout << "correct position: " << avg * 100 << "%" << std::endl;
    avg = (float) (incorrect) / (populationSize * 20.0);
    std::cout << "incorrect position: " << avg * 100 << "%" << std::endl;

    return (double)((correct) / (populationSize * 20.0) * 100);
}

void Baldwin_Solver::print_best() {
    std::cout << "Best: " << population[0].str << " (" << population[0].fitnessVal << ")" << std::endl;
}

double Baldwin_Solver::get_average_fitness() {
    double avg = 0;
    for (const auto& citizen : population)
        avg += citizen.fitnessVal;

    return avg / populationSize;
}