//
// Created by barak on 22/05/2020.
//

#include <string>
#include <fstream>
#include <iostream>
#include "../include/BinPackingInputReader.h"
BinPackingInputReader::BinPackingInputReader(const std::string basePath, const int numberOfItems)
: numberOfItems{numberOfItems}
, basePath{basePath}
{
    initializeDataFromStaticInputFile(basePath);
}

void BinPackingInputReader::initializeDataFromStaticInputFile(const std::string basePath) {
    // Reading capacity of the bins & items weight from static input file
    if (!isInRightInputFile())
    {
        std::cout << "<BinPackingInputReader::initializeDataFromStaticInputFile()> ERROR! expected number of items is different than actual. Stopping application" << std::endl;
        exit(-1);
    } else {
        binsCapacity = readBinsCapacityFromStaticInputFile();
        itemsWeight = std::move(readItemsWeightFromStaticInputFile());
    }
}

std::vector<int> BinPackingInputReader::readItemsWeightFromStaticInputFile() {
    std::vector<int> itemWeights;
    std::string itemWeightStr;
    std::ifstream itemWeightsReader{basePath +
                                    "/bin_packing/static_input_files/Falkenauer_u" + std::to_string(numberOfItems) + "_00.txt"};
    // Just reading line number 2, that's file structure
    getline(itemWeightsReader, itemWeightStr);
    getline(itemWeightsReader, itemWeightStr);

    // Starting to read from line 3
    while (getline(itemWeightsReader, itemWeightStr)) {
        // Output the text from the file
        auto it = itemWeights.end();
        itemWeights.insert(it, atoi(itemWeightStr.c_str()));
        itemWeightStr = "";
    }
    itemWeightsReader.close();
    return std::move(itemWeights);
}

bool BinPackingInputReader::isInRightInputFile(){
    return numberOfItems == readNumberOfItemsFromStaticInputFile();
}

int BinPackingInputReader::readNumberOfItemsFromStaticInputFile(){
    std::string actualNumberOfItems;
    std::ifstream numberOfItemsReader{basePath +
    "/bin_packing/static_input_files/Falkenauer_u" + std::to_string(numberOfItems) + "_00.txt"};
    getline(numberOfItemsReader, actualNumberOfItems);
    numberOfItemsReader.close();
    return atoi(actualNumberOfItems.c_str());
}

int BinPackingInputReader::readBinsCapacityFromStaticInputFile() {
    std::string binsSizeStr;
    std::ifstream binsSizeReader{basePath +
                                 "/bin_packing/static_input_files/Falkenauer_u" + std::to_string(numberOfItems) + "_00.txt"};
    // Just reading line number 2, that's file structure
    getline(binsSizeReader, binsSizeStr);
    getline(binsSizeReader, binsSizeStr);
    binsSizeReader.close();
    return atoi(binsSizeStr.c_str());
}

int BinPackingInputReader::getNumberOfItems() const {
    return numberOfItems;
}

int BinPackingInputReader::getBinsCapacity() const {
    return binsCapacity;
}

std::vector<int> BinPackingInputReader::getItemsWeight() const{
    return itemsWeight;
}

