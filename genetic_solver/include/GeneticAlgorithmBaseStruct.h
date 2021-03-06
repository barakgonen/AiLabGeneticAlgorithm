//
// Created by barak on 05/05/2020.
//

#ifndef AILABGENETICALGORITHM_GENETICALGORITHMBASESTRUCT_H
#define AILABGENETICALGORITHM_GENETICALGORITHMBASESTRUCT_H

struct GeneticAlgorithmBaseStruct {
    GeneticAlgorithmBaseStruct()
    : fitnessVal{0}
    , ageVal{0}
    {}

    virtual void resetMembers() {
        fitnessVal = 0;
        ageVal = 0;
    }
    // Default empty ctor
    double fitnessVal;
    int ageVal;
};
#endif //AILABGENETICALGORITHM_GENETICALGORITHMBASESTRUCT_H
