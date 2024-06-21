#include "../Assembler/Inst/Immediate/Branch.h"

Branch::Branch(Token& opcode, Token& reg1, Token& reg2, Token& label) :
    Inst(opcode),
    reg1(reg1),
    reg2(reg2),
    label(label) {}

AssembledInst Branch::assembleInst() const {
    AssembledInst inst(0x1, 0x1, 0x1, 0x1);
    return inst;
}