// TACSimulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Assembler/Assembler.h"
#include "Simulator/Simulator.h"

#include <iostream>
#include <memory>

using std::string;

Simulator runProgram(const string& inputPath, const string& outputPath) {
    Assembler assembler;
    assembler.assembleFile(inputPath, outputPath);

    // The simulator can hold quite a bit of simulated memory.
    // So, we're using the heap.
    Simulator simulator;
    simulator.loadProgramIntoRAM(outputPath);
    simulator.executeProgram();

    return simulator;
}

int main() {
    string fileName = "malloc";
    string input = "./assemblyFiles/" + fileName + ".asm";
    string output = "./assemblyFiles/output/" + fileName + ".out";

    Simulator simulator = runProgram(input, output);
}