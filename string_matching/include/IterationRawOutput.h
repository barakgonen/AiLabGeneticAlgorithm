//
// Created by barak on 30/04/2020.
//

#ifndef AILABGENETICALGORITHM_ITERATIONRAWOUTPUT_H
#define AILABGENETICALGORITHM_ITERATIONRAWOUTPUT_H

struct IterationRawOutput{
    int id;
    float elapsedTimeSeconds;
    double averageFitnessValue;
    double standardDeviation;
    int clockTicks;
};

#endif //AILABGENETICALGORITHM_ITERATIONRAWOUTPUT_H
