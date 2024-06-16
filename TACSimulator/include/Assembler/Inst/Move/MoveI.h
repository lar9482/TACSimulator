#pragma once

#include "../Inst.h"
#include "../../Token.h"

class MoveI : public Inst {
    Token opcode;
    Token reg;
    Token integer;

public:
    MoveI(Token opcode, Token reg, Token integer);
    AssembledInst assembleInst() const override;
};