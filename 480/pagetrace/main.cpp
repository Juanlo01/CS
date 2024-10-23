// Created by Juan Cota on 9/5/2024.
// Red ID: 827272362

#include <iostream>
#include <sstream>
#include <vector>
#include "pageTableLevel.h"
#include "log.h"
#include "tracereader.h"
using namespace std;

int main(int argc, char **argv) {
    if (argc != 3) {
        cerr << "Usage: ./pagetrace <trace_file> <level_bits_string>" << endl;
        return 1;
    }

    // Opens the trace file
    FILE *traceFile = fopen(argv[1], "rb");

    // Prints error if the trace file can not be found
    if (!traceFile) {
        cerr << "Unable to open <<trace.r>>" << argv[1] << endl;
        return 1;
    }

    // Parses the level bits string
    stringstream levelStream(argv[2]);
    vector<unsigned int> levelBits;
    unsigned int bit;
    while (levelStream >> bit) {
        levelBits.push_back(bit);
    }

    unsigned int levelCount = levelBits.size();

    // Throws error if levelCount is 0
    if (levelCount == 0) {
        cerr << "Invalid page table level bits string." << endl;
        fclose(traceFile);
        return 1;
    }

    // Calculates the bitmasks and shifts for each level
    vector<unsigned int> bitMaskAry(levelCount);
    vector<unsigned int> shiftAry(levelCount);
    vector<unsigned int> entryCount(levelCount);

    unsigned int totalBits = 32; // Assuming a 32-bit address space
    unsigned int shift = totalBits;

    for (unsigned int i = 0; i < levelCount; i++) {
        shift -= levelBits[i]; // Shift down by the number of bits for this level
        bitMaskAry[i] = ((1U << levelBits[i]) - 1) << shift; // Use 1U for unsigned
        shiftAry[i] = shift;
        entryCount[i] = 1U << levelBits[i];
    }

    // Creates the page table
    PageTable pageTable(levelCount, bitMaskAry.data(), shiftAry.data(), entryCount.data());

    // Log bitmasks for all levels
    log_bitmasks(levelCount, bitMaskAry.data());

    // Processes the trace file and record page accesses
    p2AddrTr traceAddr;
    while (NextAddress(traceFile, &traceAddr)) {
        unsigned int address = traceAddr.addr;
        vector<unsigned int> pageIndices(levelCount);

        // Extracts page indices and records page access
        for (unsigned int i = 0; i < levelCount; i++) {
            pageIndices[i] = extractPageNumberFromAddress(address, bitMaskAry[i], shiftAry[i]);
        }
        unsigned int numOfAccesses = pageTable.recordPageAccess(address);

        // Log page indices and the number of accesses
        log_pgindices_numofaccesses(address, levelCount, pageIndices.data(), numOfAccesses);
    }

    // Cleans up
    fclose(traceFile);
    return 0;
}