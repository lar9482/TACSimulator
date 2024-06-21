#include "../Assembler/Inst/Immediate/BranchZ.h"

BranchZ::BranchZ(Token& opcode, Token& reg, Token& label) :
    Inst(opcode),
    reg(reg),
    label(label) {}

AssembledInst BranchZ::assembleInst() const {
    AssembledInst inst(0x1, 0x1, 0x1, 0x1);
    return inst;
}