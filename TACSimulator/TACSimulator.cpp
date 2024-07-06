// TACSimulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "include/Assembler/Assembler.h"

using std::string;

int main() {
    string input = "./assemblyFiles/loopLessThan.asm";
    string output = "./assemblyFiles/output/loopLessThan.out";
    Assembler assembler; 
    assembler.assembleFile(input, output);
}