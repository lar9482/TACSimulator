#include "../Assembler/Inst/Move/MoveI.h"

MoveI::MoveI(Token& opcode, Token& reg, Token& integer) :
    Inst(opcode),
    reg(reg),
    integer(integer) {}

/*
 * Assembling the instruction into the format:
 * ooooooss sssMiiii iiiiiiii iiiiiiii
 * 
 * o: opcode
 * M: 0 means i is positive, 1 means i is negative.
 * s: first register
 * t: second register
 */
AssembledInst MoveI::assembleInst() const {
    uint8_t test = assembleRegister(reg);
    AssembledInst inst(0x1, 0x1, 0x1, 0x1);
    return inst;
}