//
// Created by barak on 22/05/2020.
//

#ifndef AILABGENETICALGORITHM_BINPACKINGINPUTREADER_H
#define AILABGENETICALGORITHM_BINPACKINGINPUTREADER_H


#include <vector>

class BinPackingInputReader {
public:
    BinPackingInputReader(const std::string basePath, const int numberOfItems);
    virtual ~BinPackingInputReader() = default;

    int getNumberOfItems() const;
    int getBinsCapacity() const;
    std::vector<int> getItemsWeight() const;

protected:
    void initializeDataFromStaticInputFile(const std::string basePath);
    bool isInRightInputFile();
    int readNumberOfItemsFromStaticInputFile();
    int readBinsCapacityFromStaticInputFile();
    std::vector<int> readItemsWeightFromStaticInputFile();
    const int numberOfItems;
    std::string basePath;
    int binsCapacity;
    std::vector<int> itemsWeight;
};


#endif //AILABGENETICALGORITHM_BINPACKINGINPUTREADER_H
