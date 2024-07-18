#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <array>
#include "../Simulator/SimulatorEnums.h"

struct DisassembledInst {
    uint8_t opcode;
    uint8_t reg1;
    uint8_t reg2;
    uint8_t reg3;
    int16_t immediate;

    DisassembledInst(
        const uint8_t& opcode,
        const uint8_t& reg1,
        const uint8_t& reg2,
        const uint8_t& reg3,
        const int16_t& immediate
    ) : opcode(opcode),
        reg1(reg1),
        reg2(reg2),
        reg3(reg3),
        immediate(immediate) {}
};

class Simulator {

public:
    Simulator();
    void loadProgramIntoRAM(const std::string& filePath);
    void executeProgram();

private:

    std::unique_ptr<std::array<uint8_t, 0xFFFF>> RAM;
    std::array<int16_t, 32> registers;
    const uint8_t IPRegister = 31;
    const uint8_t TrapRegister = 27;
    const uint8_t RETRegister = 30;
    bool exitProgram;

private:
    bool isMainLabel(const uint8_t& firstByte);
    std::array<uint8_t, 4> fetchInst() const ;
    DisassembledInst decodeInst(const std::array<uint8_t, 4>& fetchedInst) const ;
    void executeInst(const DisassembledInst& inst);
    void executeTrap(const Trapcode& trapCode);
};