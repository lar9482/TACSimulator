#include "../Assembler/Inst/Register/ShiftV.h"

ShiftV::ShiftV(Token& opcode, Token& reg1, Token& reg2, Token& reg3) :
    Inst(opcode),
    reg1(reg1),
    reg2(reg2),
    reg3(reg3) {}

AssembledInst ShiftV::assembleInst() const {
    AssembledInst inst(0x1, 0x1, 0x1, 0x1);
    return inst;
}