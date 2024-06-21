#include "../Assembler/Inst/Label.h"

Label::Label(Token& opcode, Token& label) :
    Inst(opcode),
    label(label) {}

AssembledInst Label::assembleInst() const {
    return AssembledInst(0x0, 0x0, 0x0, 0x0);
}