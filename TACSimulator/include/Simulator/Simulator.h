#pragma once

#include "Simulator/SimulatorEnums.h"

#include <cstdint>
#include <string>
#include <vector>
#include <array>
#include <memory>

struct DisassembledInst {
    uint8_t opcode;
    uint8_t reg1;
    uint8_t reg2;
    uint8_t reg3;
    int16_t immediate;

    DisassembledInst(
        uint8_t opcode,
        uint8_t reg1,
        uint8_t reg2,
        uint8_t reg3,
        int16_t immediate
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
    std::array<int32_t, 32> dumpRegisters();

    int32_t loadWord(uint32_t addr);
    void storeWord(uint32_t addr, int32_t word);

    uint8_t loadByte(uint32_t addr);
    void storeByte(uint32_t addr, uint8_t byte);

private:

    std::unique_ptr<std::array<uint8_t, 0x1FFFFFFF>> RAM;
    std::array<int32_t, 32> registers;
    const uint8_t IPRegister = 31;
    const uint8_t TrapInputRegister = 26;
    const uint8_t TrapOutputRegister = 27;
    const uint8_t RETRegister = 30;
    bool exitProgram;

    uint8_t freeListHeadAddr;
    const uint8_t freeListHeaderSize = 8;

private:
    bool isMainLabel(const uint8_t& firstByte) const;
    std::array<uint8_t, 4> fetchInst() const;
    DisassembledInst decodeInst(const std::array<uint8_t, 4>& fetchedInst) const;
    void executeInst(const DisassembledInst& inst);
    void executeTrap(const Trapcode& trapCode);
    void malloc(int32_t size);
    void free(uint8_t addr);
};