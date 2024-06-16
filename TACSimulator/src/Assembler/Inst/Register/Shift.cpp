#include "../Assembler/Inst/Register/Shift.h"

Shift::Shift(Token opcode, Token reg1, Token reg2, Token integer) :
    opcode(opcode),
    reg1(reg1),
    reg2(reg2),
    integer(integer) {}

AssembledInst Shift::assembleInst() const {
    AssembledInst inst(0x1, 0x1, 0x1, 0x1);
    return inst;
}