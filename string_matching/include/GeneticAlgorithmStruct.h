//
// Created by barak on 30/04/2020.
//

#ifndef AILABGENETICALGORITHM_GENETICALGORITHMSTRUCT_H
#define AILABGENETICALGORITHM_GENETICALGORITHMSTRUCT_H

#include <string>

class GeneticAlgorithmStruct {
public:
    // Default empty ctor
    GeneticAlgorithmStruct() = default:;
    GeneticAlgorithmStruct(std::string inputString, unsigned int fitnessValue);
    void appendToString(const char c);
    void setString(const std::string& other);
    std::string& getString();
    void setFitnessValue(unsigned int newValue);
    unsigned int getFitnessValue() const;

private:
    std::string str;
    unsigned int fitnessVal;
};

#endif //AILABGENETICALGORITHM_GENETICALGORITHMSTRUCT_H