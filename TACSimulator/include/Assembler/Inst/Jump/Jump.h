#pragma once

#include "../Inst.h"
#include "../../Token.h"

class Jump : public Inst {
    Token opcode;
    Token label;

public:
    Jump(Token opcode, Token label);
    AssembledInst assembleInst() const override;
};