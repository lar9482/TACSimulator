#include "../Assembler/Inst/Immediate/LoadStore.h"

LoadStore::LoadStore(Token& opcode, Token& reg1, Token& offset, Token& reg2) :
    Inst(opcode),
    reg1(reg1),
    offset(offset),
    reg2(reg2) {}

AssembledInst LoadStore::assembleInst() const {
    AssembledInst inst(0x1, 0x1, 0x1, 0x1);
    return inst;
}