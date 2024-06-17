#include "../Assembler/Inst/Move/MoveI.h"

MoveI::MoveI(Token opcode, Token reg, Token integer) :
    opcode(opcode),
    reg(reg),
    integer(integer) {}

AssembledInst MoveI::assembleInst() const {
    assembleOpcode(opcode);
    AssembledInst inst(0x1, 0x1, 0x1, 0x1);
    return inst;
}