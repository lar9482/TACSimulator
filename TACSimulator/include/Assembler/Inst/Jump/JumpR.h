#pragma once

#include "../Inst.h"
#include "../../Token.h"

class JumpR : public Inst {
    Token opcode;
    Token reg;

public:
    JumpR(Token opcode, Token reg);
    AssembledInst assembleInst() const override;
};