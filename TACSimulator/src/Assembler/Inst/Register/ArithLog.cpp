#include "../Assembler/Inst/Register/ArithLog.h"

ArithLog::ArithLog(Token& opcode, Token& reg1, Token& reg2, Token& reg3) :
    Inst(opcode),
    reg1(reg1),
    reg2(reg2),
    reg3(reg3) {}

AssembledInst ArithLog::assembleInst() const {
    AssembledInst inst(0x1, 0x1, 0x1, 0x1);
    return inst;
}