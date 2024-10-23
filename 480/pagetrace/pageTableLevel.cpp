// Created by Juan Cota on 9/5/2024.
// Red ID: 827272362
#include <iostream>
#include "pageTableLevel.h"
using namespace std;

// Defines the PageTable
PageTable::PageTable(unsigned int levelCount, unsigned int* bitMaskAry, unsigned int* shiftAry, unsigned int* entryCount) {
    this->levelCount = levelCount;
    this->bitMaskAry = bitMaskAry;
    this->shiftAry = shiftAry;
    this->entryCount = entryCount;
    rootNodePtr = new Level(0, this);  // Initialize the root level
}


// Defines recordPageAccess for PageTable
unsigned int PageTable::recordPageAccess(unsigned int address) {
    return rootNodePtr->recordPageAccess(address);
}

// Defines the Level
Level::Level(unsigned int depth, PageTable* pageTable) {
    this->depth = depth;
    this->pageTablePtr = pageTable;
    this->numOfAccesses = 0;
    this->nextLevelPtr = new Level*[pageTable->entryCount[depth]];

    for (unsigned int i = 0; i < pageTable->entryCount[depth]; i++) {
        nextLevelPtr[i] = nullptr;
    }
}

// Defines recordPageAccess for Level
unsigned int Level::recordPageAccess(unsigned int address) {
    unsigned int pageIndex = extractPageNumberFromAddress(address, pageTablePtr->bitMaskAry[depth], pageTablePtr->shiftAry[depth]);

    if (depth == pageTablePtr->levelCount) {
        numOfAccesses++;
        return numOfAccesses;
    }

    if (nextLevelPtr[pageIndex] == nullptr) {
        nextLevelPtr[pageIndex] = new Level(depth + 1, pageTablePtr);
    }

    return nextLevelPtr[pageIndex]->recordPageAccess(address);
}

// Defines extractPageNumberFromAddress
unsigned int extractPageNumberFromAddress(unsigned int address, unsigned int mask, unsigned int shift) {
    address = address & mask; // Applies the mask
    return address >> shift; // Shifts and returns the address
}