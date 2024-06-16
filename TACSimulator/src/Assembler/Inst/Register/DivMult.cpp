#include "../Assembler/Inst/Register/DivMult.h"

DivMult::DivMult(Token opcode, Token reg1, Token reg2) :
    opcode(opcode),
    reg1(reg1),
    reg2(reg2) {}

AssembledInst DivMult::assembleInst() const {
    AssembledInst inst(0x1, 0x1, 0x1, 0x1);
    return inst;
}