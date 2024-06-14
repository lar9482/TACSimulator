// TACSimulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "include/Assembler/Assembler.h"

using std::string;


int main() {
    string programFilePath = "./assemblyFiles/regInsn.asm";
    assembleFile(programFilePath);
    std::cout << "Hello World!\n";
}