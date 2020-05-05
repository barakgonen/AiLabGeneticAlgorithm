//
// Created by barak on 30/04/2020.
//

#ifndef AILABGENETICALGORITHM_STRING_MATCHING_CONSTS_H
#define AILABGENETICALGORITHM_STRING_MATCHING_CONSTS_H

static const int GA_MAXITER	= 16384;	// maximum iterations
static const std::string GA_TARGET = std::string("blablabla");
static std::string defaultHeuristic = "DefaultHeuristic";
static std::string bullsAndCows = "BullsAndCows";
static std::string LAB2OutputPath = "Lab2StringMatching/";
static std::string sortedFilesPath = LAB2OutputPath + "sorted/";
static const int YOUNG_GEN_AGE = 5; // consider geune as young as long as it's age is below / equals this value
static const int ADULT_GEN_AGE = 20; // consider gune as an adult while it's below this value

#endif //AILABGENETICALGORITHM_STRING_MATCHING_CONSTS_H
