#include <iostream>
#include <fstream>
#include <exception>
#include <vector>
#include <memory>
#include <array>

#include "../Simulator/Simulator.h"

using std::string;
using std::vector;
using std::array;

Simulator::Simulator() :
    RAM(std::make_unique<std::array<uint8_t, 0xFFFF>>()), 
    exitProgram(false)
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
    while (!exitProgram) {
        array<uint8_t, 4> fetchedInst = fetchInst();
        DisassembledInst disassembledInst = decodeInst(fetchedInst);
        registers[PCRegister] += 4;
    }
}

array<uint8_t, 4> Simulator::fetchInst() {
    array<uint8_t, 4> fetchedInst;
    fetchedInst[0] = RAM->at(registers[PCRegister]);
    fetchedInst[1] = RAM->at(registers[PCRegister] + 1);
    fetchedInst[2] = RAM->at(registers[PCRegister] + 2);
    fetchedInst[3] = RAM->at(registers[PCRegister] + 3);

    return fetchedInst;
}

// ooooooss sssttttt ddddd000 00000000
// ooooooss sssttttt Miiiiiii iiiiiiii
DisassembledInst Simulator::decodeInst(const std::array<uint8_t, 4>& fetchedInst) {
    uint8_t opcode = (fetchedInst[0] & 0b1111'1100) >> 2;
    uint8_t reg1 = ((fetchedInst[0] & 0b0000'0011) << 3) + ((fetchedInst[1] & 0b1110'0000) >> 5);
    uint8_t reg2 = fetchedInst[1] & 0b00011111;
    uint8_t reg3 = (fetchedInst[2] & 0b1111'1000) >> 3;

    uint8_t immSign = (fetchedInst[2] & 0b1000'0000) >> 7;
    int16_t decodedImm = ((fetchedInst[2] & 0b0111'1111) << 8) + fetchedInst[3];

    if (immSign == 1) {
        decodedImm = -decodedImm;
    }

    return DisassembledInst(
        opcode, 
        reg1, 
        reg2, 
        reg3, 
        decodedImm
    );
}

void Simulator::executeInst() {

}