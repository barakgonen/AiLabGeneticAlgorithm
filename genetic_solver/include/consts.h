//
// Created by barak on 05/05/2020.
//

#ifndef AILABGENETICALGORITHM_GENETIC_SOLVER_CONSTS_H
#define AILABGENETICALGORITHM_GENETIC_SOLVER_CONSTS_H

#include "stdlib.h"
static const double GA_ELITRATE = 0.10f;		// elitism rate
static const double GA_MUTATIONRATE = 0.25f;		// mutation rate
static const int GA_POPSIZE = 2048;		// ga population size WHY HAVE WE CHANGED IT TO 100? if it necessery, define it as a member of AbstractGeneticSolver
static const double GA_MUTATION	= RAND_MAX * GA_MUTATIONRATE;
static const int K = 4;
static const int GA_MAXITER	= 16384;	// maximum iterations


#endif //AILABGENETICALGORITHM_GENETIC_SOLVER_CONSTS_H
