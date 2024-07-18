#include <iostream>
#include <fstream>
#include <exception>
#include <vector>
#include <memory>
#include <array>

#include "../Simulator/Simulator.h"
#include "../Simulator/SimulatorEnums.h"

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

        if (isMainLabel(firstByte)) {
            registers[PCRegister] = addressCounter;
        }

        addressCounter += 4;
    }

    inputFile.close();
}

void Simulator::executeProgram() {
    while (!exitProgram) {
        array<uint8_t, 4> fetchedInst = fetchInst();
        DisassembledInst disassembledInst = decodeInst(fetchedInst);
        executeInst(disassembledInst);
        registers[PCRegister] += 4;
    }
}

/*
 * Form: ooooooM0 00000000 00000000 00000000
 * o: Testing that o is the label
 * M: Testing that M is 1, which indicates a main label
 */
bool Simulator::isMainLabel(const uint8_t& firstByte) {
    return (static_cast<Opcode>((firstByte & 0b1111'1100) >> 2) == Opcode::label_Inst)
        &&
    (((firstByte & 0b0000'0010) >> 1) == 1);
}

array<uint8_t, 4> Simulator::fetchInst() const {
    array<uint8_t, 4> fetchedInst;
    fetchedInst[0] = RAM->at(registers[PCRegister]);
    fetchedInst[1] = RAM->at(registers[PCRegister] + 1);
    fetchedInst[2] = RAM->at(registers[PCRegister] + 2);
    fetchedInst[3] = RAM->at(registers[PCRegister] + 3);

    return fetchedInst;
}

// ooooooss sssttttt ddddd000 00000000
// ooooooss sssttttt Miiiiiii iiiiiiii
DisassembledInst Simulator::decodeInst(const std::array<uint8_t, 4>& fetchedInst) const {
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

void Simulator::executeInst(const DisassembledInst& inst) {
    Opcode opcode = static_cast<Opcode>(inst.opcode);

    switch (opcode) {
    case Opcode::mov_Inst: 
        registers[inst.reg1] = registers[inst.reg2];
        break;
    case Opcode::add_Inst: 
        registers[inst.reg1] = registers[inst.reg2] + registers[inst.reg3];
        break;
    case Opcode::sub_Inst: 
        registers[inst.reg1] = registers[inst.reg2] - registers[inst.reg3];
        break;
    case Opcode::mult_Inst: 
        registers[inst.reg1] = registers[inst.reg2] * registers[inst.reg3];
        break;
    case Opcode::div_Inst: 
        registers[inst.reg1] = static_cast<int16_t>(registers[inst.reg2] / registers[inst.reg3]);
        break;
    case Opcode::and_Inst: 
        registers[inst.reg1] = registers[inst.reg2] & registers[inst.reg3];
        break;
    case Opcode::or_Inst: 
        registers[inst.reg1] = registers[inst.reg2] | registers[inst.reg3];
        break;
    case Opcode::xor_Inst: 
        registers[inst.reg1] = registers[inst.reg2] ^ registers[inst.reg3];
        break;
    case Opcode::not_Inst: 
        break;
    case Opcode::nor_Inst: 
        registers[inst.reg1] = ~(registers[inst.reg2] | registers[inst.reg3]);
        break;
    case Opcode::sllv_Inst:
        registers[inst.reg1] = registers[inst.reg2] << registers[inst.reg3];
        break;
    case Opcode::srav_Inst: 
        registers[inst.reg1] = registers[inst.reg2] >> registers[inst.reg3];
        break;
    case Opcode::movI_Inst: 
        registers[inst.reg1] = inst.immediate;
        break;
    case Opcode::addI_Inst: 
        registers[inst.reg1] = registers[inst.reg2] + inst.immediate;
        break;
    case Opcode::subI_Inst: 
        registers[inst.reg1] = registers[inst.reg2] - inst.immediate;
        break;
    case Opcode::multI_Inst: 
        registers[inst.reg1] = registers[inst.reg2] * inst.immediate;
        break;
    case Opcode::divI_Inst: 
        registers[inst.reg1] = static_cast<int16_t>(registers[inst.reg2] / inst.immediate);
        break;
    case Opcode::andI_Inst: 
        registers[inst.reg1] = registers[inst.reg2] & inst.immediate;
        break;
    case Opcode::orI_Inst: 
        registers[inst.reg1] = registers[inst.reg2] | inst.immediate;
        break;
    case Opcode::xorI_Inst: 
        registers[inst.reg1] = registers[inst.reg2] ^ inst.immediate;
        break;
    case Opcode::notI_Inst: 
        break;
    case Opcode::norI_Inst: 
        registers[inst.reg1] = ~(registers[inst.reg2] | inst.immediate);
        break;
    case Opcode::sll_Inst: 
        registers[inst.reg1] = registers[inst.reg2] << inst.immediate;
        break;
    case Opcode::sra_Inst: 
        registers[inst.reg1] = registers[inst.reg2] >> inst.immediate;
        break;
    case Opcode::bEq_Inst: 
        
        break;
    case Opcode::bNe_Inst: break;
    case Opcode::bLt_Inst: break;
    case Opcode::bGt_Inst: break;
    case Opcode::bLTz_Inst: break;
    case Opcode::bGTz_Inst: break;
    case Opcode::jmp_Inst: break;
    case Opcode::jmpL_Inst: break;
    case Opcode::jmpL_Reg_Inst: break;
    case Opcode::jmpReg_Inst: break;
    case Opcode::lb_Inst: break;
    case Opcode::lw_Inst: break;
    case Opcode::sb_Inst: break;
    case Opcode::sw_Inst: break;
    case Opcode::trap_Inst: 
        executeTrap(static_cast<Trapcode>(inst.immediate));
        break;
    case Opcode::label_Inst: break;
    }
}

void Simulator::executeTrap(const Trapcode& trapCode) {
    switch (trapCode) {
    case Trapcode::print_int: 
        std::cout << registers[TrapRegister];
        break;
    case Trapcode::print_string: break;
    case Trapcode::println_string: break;
    case Trapcode::read_int: break;
    case Trapcode::read_string: break;
    case Trapcode::malloc: break;
    case Trapcode::free: break;
    case Trapcode::exit: 
        exitProgram = true;
        break;
    }
}