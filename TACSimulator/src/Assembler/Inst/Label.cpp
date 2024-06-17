#include "../Assembler/Inst/Label.h"

Label::Label(Token label) : 
    label(label) {}

AssembledInst Label::assembleInst() const {
    return AssembledInst(0x0, 0x0, 0x0, 0x0);
}