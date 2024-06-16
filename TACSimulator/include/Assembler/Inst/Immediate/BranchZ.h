#pragma once

#include "../Inst.h"
#include "../../Token.h"

class BranchZ : public Inst {
    Token opcode;
    Token reg;
    Token label;

public:
    BranchZ(Token opcode, Token reg, Token label);
    AssembledInst assembleInst() const override;
};