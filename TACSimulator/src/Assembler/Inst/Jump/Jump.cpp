#include "../Assembler/Inst/Jump/Jump.h"

Jump::Jump(Token& opcode, Token& label) :
    Inst(opcode),
    label(label) {}

AssembledInst Jump::assembleInst() const {
    AssembledInst inst(0x1, 0x1, 0x1, 0x1);
    return inst;
}