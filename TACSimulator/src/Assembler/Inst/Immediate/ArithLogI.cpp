#include "../Assembler/Inst/Immediate/ArithLogI.h"

ArithLogI::ArithLogI(Token& opcode, Token& reg1, Token& reg2, Token& integer) :
    Inst(opcode), 
    reg1(reg1), 
    reg2(reg2), 
    integer(integer) {}

AssembledInst ArithLogI::assembleInst() const {
    AssembledInst inst(0x1, 0x1, 0x1, 0x1);
    return inst;
}