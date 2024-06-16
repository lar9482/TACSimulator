#include "../Assembler/Inst/Move/Move.h"

Move::Move(Token opcode, Token reg1, Token reg2) :
    opcode(opcode),
    reg1(reg1),
    reg2(reg2) {}

AssembledInst Move::assembleInst() const {
    AssembledInst inst(0x1, 0x1, 0x1, 0x1);
    return inst;
}