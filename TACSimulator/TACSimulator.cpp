// TACSimulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>
#include "include/Assembler/Assembler.h"
#include "include/Simulator/Simulator.h"

using std::string;

int main() {
    string fileName = "memInst";
    string input = "./assemblyFiles/" + fileName + ".asm";
    string output = "./assemblyFiles/output/" + fileName + ".out";

    Assembler assembler; 
    assembler.assembleFile(input, output);

    // The simulator can hold quite a bit of simulated memory.
    // So, we're using the heap.
    Simulator simulator;
    simulator.loadProgramIntoRAM(output);
    simulator.executeProgram();
}