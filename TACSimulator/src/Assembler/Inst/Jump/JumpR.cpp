#include "../Assembler/Inst/Jump/JumpR.h"

JumpR::JumpR(Token opcode, Token reg) :
    opcode(opcode),
    reg(reg) {}

AssembledInst JumpR::assembleInst() const {
    AssembledInst inst(0x1, 0x1, 0x1, 0x1);
    return inst;
}