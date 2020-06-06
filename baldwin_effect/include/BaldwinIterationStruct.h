//
// Created by barak on 06/06/2020.
//

#ifndef AILABGENETICALGORITHM_BALDWINCSVSTRUCT_H
#define AILABGENETICALGORITHM_BALDWINCSVSTRUCT_H

struct BaldwinIterationStruct{
    double questionMarkPerc;
    double onePerc;
    double zeroPerc;
};

struct BaldwinCsvStruct{
    int iterationNumber;
    BaldwinIterationStruct data;
};
#endif //AILABGENETICALGORITHM_BALDWINCSVSTRUCT_H
