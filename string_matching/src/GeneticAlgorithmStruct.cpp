//
// Created by barak on 30/04/2020.
//

#include "../include/GeneticAlgorithmStruct.h"

GeneticAlgorithmStruct::GeneticAlgorithmStruct(std::string inputString, unsigned int fitnessValue)
: str{inputString}
, fitnessVal{fitnessValue}
{
}

void GeneticAlgorithmStruct::appendToString(const char c){
    str += c;
}

void GeneticAlgorithmStruct::setString(const std::string& other){
    str = other;
}

std::string& GeneticAlgorithmStruct::getString(){
    return str;
}

void GeneticAlgorithmStruct::setFitnessValue(unsigned int newValue){
    fitnessVal = newValue;
}

unsigned int GeneticAlgorithmStruct::getFitnessValue() const {
    return fitnessVal;
}