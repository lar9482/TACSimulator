#include <iostream>
#include <fstream>
#include <exception>
#include <vector>
#include <memory>

#include "../Simulator/Simulator.h"

using std::string;
using std::vector;

Simulator::Simulator() :
    RAM(std::make_unique<std::array<uint8_t, 0xFFFF>>()) 
{
    RAM->fill(0);
    registers.fill(0);
}

void Simulator::loadProgramIntoRAM(const std::string& filePath) {
    std::ifstream inputFile(filePath);

    if (!inputFile.is_open()) {
        throw std::runtime_error("Unable to read " + filePath);
    }

    string assembledInst;
    size_t addressCounter = 0;
    while (std::getline(inputFile, assembledInst)) {
        std::cout << assembledInst << std::endl;
        uint8_t firstByte = static_cast<uint8_t>(std::stoi(assembledInst.substr(0, 2), nullptr, 16));
        uint8_t secondByte = static_cast<uint8_t>(std::stoi(assembledInst.substr(2, 2), nullptr, 16));
        uint8_t thirdByte = static_cast<uint8_t>(std::stoi(assembledInst.substr(4, 2), nullptr, 16));
        uint8_t fourthByte = static_cast<uint8_t>(std::stoi(assembledInst.substr(6, 2), nullptr, 16));

        RAM->at(addressCounter) = firstByte;
        RAM->at(addressCounter+1) = secondByte;
        RAM->at(addressCounter+2) = thirdByte;
        RAM->at(addressCounter+3) = fourthByte;

        addressCounter += 4;
    }

    inputFile.close();
}

void Simulator::executeProgram() {

}

// ooooooss sssttttt ddddd000 00000000
// ooooooss sssttttt Miiiiiii iiiiiiii
DisassembledInst Simulator::disassembleInst(const std::string& assembledInst) {
    uint8_t firstByte = static_cast<uint8_t>(std::stoi(assembledInst.substr(0, 2), nullptr, 16));
    uint8_t secondByte = static_cast<uint8_t>(std::stoi(assembledInst.substr(2, 2), nullptr, 16));
    uint8_t thirdByte = static_cast<uint8_t>(std::stoi(assembledInst.substr(4, 2), nullptr, 16));
    uint8_t fourthByte = static_cast<uint8_t>(std::stoi(assembledInst.substr(6, 2), nullptr, 16));

    uint8_t opcode = (firstByte & 0b11111100) >> 2;
    uint8_t reg1 = ((firstByte & 0b00000011) << 3) + ((secondByte & 0b11100000) >> 5);
    // uint8_t reg2 = ();
    return DisassembledInst(0, 0, 0, 0, 0);
}

void Simulator::fetchInst() {

}

void Simulator::decodeInst() {

}

void Simulator::executeInst() {

}