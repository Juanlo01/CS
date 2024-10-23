// Created by Juan Cota on 9/5/2024.
// Red ID: 827272362
#ifndef PAGETABLELEVEL_H
#define PAGETABLELEVEL_H

// PageTable: Contains information about the tree
class PageTable {
public:
    unsigned int levelCount;       // Number of levels
    unsigned int* bitMaskAry;      // Array of bit masks for each level
    unsigned int* shiftAry;        // Array of shifts for each level
    unsigned int* entryCount;      // Array for the number of entries per level
    class Level* rootNodePtr;      // Pointer to the root level

    PageTable(unsigned int levelCount, unsigned int* bitMaskAry, unsigned int* shiftAry, unsigned int* entryCount);
    unsigned int recordPageAccess(unsigned int address);
};


// Level: The page tree node representation. A structure describing a specific level of the page table.
class Level {
public:
    unsigned int depth;            // Current depth
    PageTable* pageTablePtr;       // Pointer back to the PageTable structure
    unsigned int numOfAccesses;    // Number of accesses to this level
    Level** nextLevelPtr;          // Array of pointers to the next level

    Level(unsigned int depth, PageTable* pageTable);
    unsigned int recordPageAccess(unsigned int address);
};

// Defines function to extract page number from an address.
unsigned int extractPageNumberFromAddress(unsigned int address, unsigned int mask, unsigned int shift);

#endif // PAGETABLELEVEL_H