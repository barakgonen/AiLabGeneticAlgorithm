//
// Created by barak on 30/04/2020.
//

#ifndef AILABGENETICALGORITHM_CONSTS_H
#define AILABGENETICALGORITHM_CONSTS_H

#define GA_POPSIZE		2048		// ga population size
#define GA_MAXITER		16384		// maximum iterations
#define GA_ELITRATE		0.10f		// elitism rate
#define GA_MUTATIONRATE	0.25f		// mutation rate
#define GA_MUTATION		RAND_MAX * GA_MUTATIONRATE
#define GA_TARGET		std::string("blablabla")
static std::string defaultHeuristic = "default";
static std::string bullAndCow = "BullAndCow";
#endif //AILABGENETICALGORITHM_CONSTS_H
