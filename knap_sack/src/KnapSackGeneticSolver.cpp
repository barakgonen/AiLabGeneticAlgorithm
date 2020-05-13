//
// Created by barak on 12/05/2020.
//

#include <ctime>
#include <consts.h>
#include <cmath>
#include <algorithm>
#include <afxres.h>
#include "../include/KnapSackGeneticSolver.h"
#include "vector"
#include "iostream"
#include "../../string_matching/include/consts.h"

KnapSackGeneticSolver::KnapSackGeneticSolver(const int puzzleKey,
                                             const KnapSackStaticDataSetInitializer& staticDataSetInitializer)
: sackSize{staticDataSetInitializer.getCapacity(puzzleKey)}
, optimalSelection{staticDataSetInitializer.getOptimalSelection(puzzleKey)}
, profits{staticDataSetInitializer.getProfits(puzzleKey)}
, weights{staticDataSetInitializer.getWeights(puzzleKey)}
, N{static_cast<int>(weights.size())}
{
//    set_profits(puzzleKey, staticDataSetInitializer);
//    set_weights(puzzleKey, staticDataSetInitializer);
}

void KnapSackGeneticSolver::set_profits(const int puzzleID, const KnapSackStaticDataSetInitializer& staticDataSetInitializer){
//    const auto& profitsVec = staticDataSetInitializer.getProfits(puzzleID);
//    for (int index = 0; index < profitsVec.size(); index++)
//        profits.get()[index] = profitsVec[index];
}
void KnapSackGeneticSolver::set_weights(const int puzzleID, const KnapSackStaticDataSetInitializer& staticDataSetInitializer){
//    const auto& weightsVec = staticDataSetInitializer.getWeights(puzzleID);
//    for (int index = 0; index < weightsVec.size(); index++)
//        weights.get()[index] = weightsVec[index];
}

void KnapSackGeneticSolver::init_population(ga_vector &population, ga_vector &buffer) {
    int tsize = N;

    for (int i = 0; i < GA_POPSIZE; i++) {
        ga_struct citizen;
        citizen.sumweight = 0;
        citizen.fitness = 0;
        for (int j = 0; j < tsize; j++){
            auto end = citizen.sack.end();
            citizen.sack.insert(end, (rand() % 2));
        }
        population.push_back(citizen);
    }

    for (int i = 0; i < GA_POPSIZE; i++) {
        ga_struct citizen;
        citizen.sumweight = 0;
        citizen.fitness = 0;
        for (int j = 0; j < tsize; j++){
            auto end = citizen.sack.end();
            citizen.sack.insert(end, 0);
        }
        buffer.push_back(citizen);
    }
//    buffer.resize(GA_POPSIZE);
}

void KnapSackGeneticSolver::calc_fitness(ga_vector &population) {
    for (int i = 0; i < GA_POPSIZE; i++) {
        double fit = 0;
        double weight = 0;
        for (int j = 0; j < N; j++) {
            if (population[i].sack.at(j) == 1) {
                fit += profits.at(j);
                weight += weights.at(j);
            }
        }
        if (weight > W) {
            fit = 0;
        }
        population.at(i).fitness = fit;
        population.at(i).sumweight = weight;
    }
}

void KnapSackGeneticSolver::Standard_deviation(double avg) {

    std::cout << "Fitness Average: " << avg;
}


double KnapSackGeneticSolver::calcStandardDeviation(ga_vector &population, double avg) {
    double sum = 0, k;
    for (int i = 0; i < population.size(); i++) {
        k = (population[i].fitness - avg);
        k = k * k;
        sum = sum + k;

    }
    sum = sum / GA_POPSIZE;

    return sqrt(sum);
}

double KnapSackGeneticSolver::calcAvgFitness(ga_vector &population) {
    double avg = 0;
    for (int i = 0; i < population.size(); i++) {
        avg += population[i].fitness;
    }
    return avg / GA_POPSIZE;
}

void KnapSackGeneticSolver::sort_by_fitness(ga_vector &population) {
    std::sort(population.begin(),
              population.end(),
              [](const ga_struct &x, const ga_struct &y) {
                  return (x.fitness > y.fitness);
              });
}

void KnapSackGeneticSolver::elitism(ga_vector &population,
             ga_vector &buffer, int esize) {
    for (int i = 0; i < esize; i++) {
        for (int j = 0; j < N; j++){
            auto end = buffer[i].sack.end();
            buffer[i].sack.insert(end, population[i].sack[j]);
        }
        buffer[i].fitness = population[i].fitness;
        buffer[i].sumweight = population[i].sumweight;
    }
}

void KnapSackGeneticSolver::mutate(ga_struct &member) {
    int i = rand() % N;
    int j;
    while ((j = rand() % N) == i) {}
    int temp = member.sack[i];
    member.sack[i] = member.sack[j];
    member.sack[j] = temp;
}

void KnapSackGeneticSolver::mutate2(ga_struct &member) {
    int i = rand() % N;
    int j = rand() % 2;
    member.sack.at(i) = j;
}

int KnapSackGeneticSolver::tournamentSelection(ga_vector &population) {
    int bestGene, randomGene;
    int firstGene, secondGene;
    bestGene = rand() % (GA_POPSIZE);
    for (int i = 0; i < 20; i++) {
        randomGene = rand() % (GA_POPSIZE);
        if (population[randomGene].fitness < population[bestGene].fitness) /*smaller is better*/
            bestGene = randomGene;
    }
    return bestGene;
}

int KnapSackGeneticSolver::RWS(ga_vector &population) {
    unsigned int ptr = 0;
    double AVG = calcAvgFitness(population);
    double slice = sqrt((double) (rand() * AVG / (RAND_MAX + 1)));
    double fitnes_f = 0.0f;
    double maxFitness = population[GA_POPSIZE - 1].fitness;
    for (int p = 0; p < GA_POPSIZE; p++) {
        fitnes_f += sqrt(maxFitness - (double) ((population[p]).fitness));
        if (fitnes_f >= slice)
            return p;
    }
    return -1;
}

void KnapSackGeneticSolver::mate(ga_vector &population, ga_vector &buffer, int TournamentSelection, int rws, int twoPointCross, int Mutate) {
    int esize = GA_POPSIZE * GA_ELITRATE;
    int spos, i1, i2, spos1, spos2;

    elitism(population, buffer, esize);

    // Mate the rest
    for (int i = esize; i < GA_POPSIZE; i++) {

        if (rws) {
            i1 = RWS(population);
            i2 = RWS(population);
        }

        if (TournamentSelection) {
            i1 = tournamentSelection(population);
            i2 = tournamentSelection(population);

        }

        if (!rws && !TournamentSelection) {
            i1 = rand() % (GA_POPSIZE / 2);
            i2 = rand() % (GA_POPSIZE / 2);
        }


        if (!twoPointCross) /*Single point crossover*/
        {
            spos = rand() % N;
            for (int j = 0; j < spos; j++){
                auto end = buffer[i].sack.end();
                buffer[i].sack.insert(end, population[i1].sack[j]);
            }

            for (int j = spos; j < N; j++) {
                auto end = buffer[i].sack.end();
                buffer[i].sack.insert(end, population[i2].sack[j]);
            }

            if (rand() < GA_MUTATION) {
                if (Mutate)
                    mutate(buffer[i]);
                else
                    mutate2(buffer[i]);

            }
        }
        if (twoPointCross) {
            spos1 = rand() % N;
            while ((spos2 = rand() % N) == spos1);

            //if spos1 is after spos2 , swap them
            if (spos1 > spos2) {
                int temp = spos2;
                spos2 = spos1;
                spos1 = spos2;
            }
            for (int j = 0; j < spos1; j++)
                buffer[i].sack[j] = population[i1].sack[j];

            for (int j = spos1; j < spos2; j++)
                buffer[i].sack[j] = population[i2].sack[j];

            for (int j = spos2; j < N; j++)
                buffer[i].sack[j] = population[i1].sack[j];

            if (rand() < GA_MUTATION) {
                if (Mutate == 1)
                    mutate(buffer[i]);
                else
                    mutate2(buffer[i]);
            }
        }
    }
}

void KnapSackGeneticSolver::print_best(ga_vector &gav) {
    std::cout << "Best: ";
    for (int j = 0; j < N; j++){
        std::cout << gav[0].sack.at(j);
//        optimalSelection.push_back(gav[0].sack[j]);
    }
    std:: cout << " (" << gav.at(0).fitness << ")";
}

void KnapSackGeneticSolver::swap(ga_vector *&population,
                 ga_vector *&buffer) {
    ga_vector *temp = population;
    population = buffer;
    buffer = temp;
}

std::vector<int> KnapSackGeneticSolver::solve() {
    clock_t t;
    double avg;
    srand(unsigned(time(NULL)));
    int max = 0, num = 20;
    ga_vector pop_alpha, pop_beta;
    ga_vector *population, *buffer;

    init_population(pop_alpha, pop_beta);
    population = &pop_alpha;
    buffer = &pop_beta;

    for (int i = 0; i < GA_MAXITER; i++) {
        t = clock();
        calc_fitness(*population); // calculate fitness
        sort_by_fitness(*population); // sort them
        print_best(*population); // print the best one
        avg = calcAvgFitness(*population);
        Standard_deviation(avg);
        double st_dev = calcStandardDeviation(*population, avg);
        std::cout << " Standard deviation: " << st_dev;


        if ((*population)[0].fitness == max) {
            num--;
        }

        if ((*population)[0].fitness > max) {
            max = (*population)[0].fitness;
        }
        if (num == 0) {
            t = clock() - t;
            std::cout << " CLOCK TICKS Time :" << t << " Elapsed time:" << ((float) t) / CLOCKS_PER_SEC << std::endl;

            break;
        }

        mate(*population, *buffer, 1, 0, 0, 0); // mate the population together
        swap(population, buffer); // swap buffers
        t = clock() - t;
        std::cout << " CLOCK TICKS Time :" << t << " Elapsed time:" << ((float) t) / CLOCKS_PER_SEC << std::endl;
    }
    return optimalSelection;
}